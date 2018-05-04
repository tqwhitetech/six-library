/* =========================================================================
 * This file is part of NITRO
 * =========================================================================
 *
 * (C) Copyright 2004 - 2018, MDA Information Systems LLC
 *
 * NITRO is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, If not,
 * see <http://www.gnu.org/licenses/>.
 *
 */

#include <string.h>
#include <sstream>
#include <algorithm>
#include <limits>

#include <except/Exception.h>
#include <math/Round.h>
#include <nitf/Writer.hpp>
#include <nitf/CompressedByteProvider.hpp>
#include <nitf/IOStreamWriter.hpp>
#include <io/ByteStream.h>


namespace nitf
{
CompressedByteProvider::CompressedByteProvider() :
    ByteProvider()
{
}

CompressedByteProvider::CompressedByteProvider(Record& record,
        const std::vector<std::vector<size_t> >& bytesPerBlock,
        const std::vector<PtrAndLength>& desData,
        size_t numRowsPerBlock,
        size_t numColsPerBlock,
        size_t maxRowsPerSegment) :
    ByteProvider()
{
    initialize(record, bytesPerBlock, desData, numRowsPerBlock, numColsPerBlock,
            maxRowsPerSegment);
}

void CompressedByteProvider::initialize(Record& record,
        const std::vector<std::vector<size_t> >& bytesPerBlock,
        const std::vector<PtrAndLength>& desData,
        size_t numRowsPerBlock,
        size_t numColsPerBlock,
        size_t maxRowsPerSegment)
{
    // Get all the file headers and offsets
    const size_t numImages = record.getNumImages();
    if (numImages != bytesPerBlock.size())
    {
        std::ostringstream oss;
        oss << "NITF header metadata contains " << numImages << " images, "
            << "but block sizes provided for " << bytesPerBlock.size()
            << " images.";
        throw except::Exception(Ctxt(oss.str()));
    }
    mImageDataLengths.resize(numImages);

    for (size_t ii = 0; ii < numImages; ++ii)
    {
        mImageDataLengths[ii] = 0;
        for (size_t jj = 0; jj < bytesPerBlock[ii].size(); ++jj)
        {
            mImageDataLengths[ii] += bytesPerBlock[ii][jj];
        }
    }
    mBytesInEachBlock = bytesPerBlock;
    mMaxRowsPerSegment = maxRowsPerSegment;
    initializeImpl(record, desData, numRowsPerBlock, numColsPerBlock);
}

size_t CompressedByteProvider::countBytesForCompressedImageData(
        size_t seg, size_t startRow, size_t numRowsToWrite) const
{
    // If we've already compressed, we don't care about padding.
    // We just need to figure out -which- blocks we're writing, and then grab
    // that from the member vector
    const std::vector<size_t>& bytesPerBlock = mBytesInEachBlock[seg];
    types::Range blockRange = findBlocksToWrite(seg, startRow, numRowsToWrite);

    size_t numBytes = 0;
    for (size_t ii = blockRange.mStartElement;
            ii < blockRange.mStartElement + blockRange.mNumElements; ++ii)
    {
        numBytes += bytesPerBlock[ii];
    }
    return numBytes;
}

types::Range CompressedByteProvider::findBlocksToWrite(
        size_t seg, size_t startRow, size_t numRowsToWrite) const
{
    size_t firstRowOfImage = 0;
    size_t firstBlockOfImage = 0;
    for (size_t ii = 0; ii < seg; ++ii)
    {
        firstRowOfImage += mMaxRowsPerSegment;
        firstBlockOfImage += mBytesInEachBlock[ii].size();
    }
    startRow -= firstRowOfImage;

    const size_t numHorizontalBlocks = math::ceilingDivide(mNumCols,
                                                           mNumColsPerBlock);
    const size_t firstRowOfBlocks = math::ceilingDivide(startRow,
                                                        mNumRowsPerBlock[0]);
    const size_t numRowsOfBlocks = math::ceilingDivide(numRowsToWrite,
                                                       mNumRowsPerBlock[0]);
    const size_t numBlocks = numRowsOfBlocks * numHorizontalBlocks;
    const size_t firstBlock = firstRowOfBlocks * numHorizontalBlocks;

    return types::Range(firstBlock, numBlocks);
}

size_t CompressedByteProvider::addImageData(
        size_t seg,
        size_t startRow,
        size_t numRowsToWrite,
        const sys::byte* imageData,
        nitf::Off& fileOffset,
        NITFBufferList& buffers) const
{
    // If we've already compressed, we don't care about padding.
    // We just need to figure out -which- blocks we're writing, and then grab
    // that from the member vector
    const std::vector<size_t>& bytesPerBlock = mBytesInEachBlock[seg];
    types::Range blockRange = findBlocksToWrite(seg, startRow, numRowsToWrite);

    // If the file offset hasn't been set yet,
    // advance it to our starting position
    if (fileOffset == std::numeric_limits<nitf::Off>::max())
    {
        if (blockRange.mStartElement == 0)
        {
            std::ostringstream error;
            error << "Internal logic error. blockRange.mStartElement should "
                  << "never be 0 when fileOffset hasn't been set.";
            throw except::Exception(Ctxt(error.str()));
        }

        fileOffset = mImageSubheaderFileOffsets[seg] + mImageSubheaders[seg].size();
        for (size_t block = 0; block < blockRange.mStartElement; ++block)
        {
            fileOffset += mBytesInEachBlock[seg][block];
        }
    }

    // Copy the image data into the buffer
    size_t bytesWritten = 0;
    for (size_t ii = blockRange.mStartElement;
            ii < blockRange.mStartElement + blockRange.mNumElements;
            ++ii)
    {
        buffers.pushBack(imageData + bytesWritten, bytesPerBlock[ii]);
        bytesWritten += bytesPerBlock[ii];
    }
    return bytesWritten;
}

nitf::Off CompressedByteProvider::getNumBytes(size_t startRow, size_t numRows) const
{
    nitf::Off numBytes(0);
    const size_t imageDataEndRow = startRow + numRows;

    for (size_t seg = 0; seg < mImageSegmentInfo.size(); ++seg)
    {
        // See if we're in this segment
        const SegmentInfo& imageSegmentInfo(mImageSegmentInfo[seg]);

        size_t startGlobalRowToWrite;
        size_t numRowsToWrite;
        if (imageSegmentInfo.isInRange(startRow, numRows,
                                       startGlobalRowToWrite,
                                       numRowsToWrite))
        {
            checkBlocking(seg, startGlobalRowToWrite, numRowsToWrite);
            numBytes += countBytesForHeaders(seg, startRow);
            numBytes += countBytesForCompressedImageData(
                    seg, startGlobalRowToWrite,
                    numRowsToWrite);
            numBytes += countBytesForDES(seg, imageDataEndRow);
        }
    }

    return numBytes;
}

void CompressedByteProvider::getBytes(
        const void* imageData,
        size_t startRow,
        size_t numRows,
        nitf::Off& fileOffset,
        NITFBufferList& buffers) const
{
    const sys::byte* imageDataPtr = static_cast<const sys::byte*>(imageData);
    fileOffset = std::numeric_limits<nitf::Off>::max();
    buffers.clear();

    for (size_t seg = 0; seg < mImageSegmentInfo.size(); ++seg)
    {
        // See if we're in this segment
        const SegmentInfo& imageSegmentInfo(mImageSegmentInfo[seg]);

        size_t startGlobalRowToWrite;
        size_t numRowsToWrite;
        if (imageSegmentInfo.isInRange(startRow, numRows,
                                       startGlobalRowToWrite,
                                       numRowsToWrite))
        {
            checkBlocking(seg, startGlobalRowToWrite, numRowsToWrite);
            addHeaders(seg, startGlobalRowToWrite, fileOffset, buffers);
            const size_t offset = addImageData(seg,
                                               startGlobalRowToWrite,
                                               numRowsToWrite,
                                               imageDataPtr,
                                               fileOffset,
                                               buffers);
            imageDataPtr += offset;
            addDES(seg, startRow, buffers);
        }
    }
}
}
