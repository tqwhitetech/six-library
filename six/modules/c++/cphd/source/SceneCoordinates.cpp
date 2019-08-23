/* =========================================================================
 * This file is part of cphd-c++
 * =========================================================================
 *
 * (C) Copyright 2004 - 2018, MDA Information Systems LLC
 *
 * cphd-c++ is free software; you can redistribute it and/or modify
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
 * License along with this program; If not,
 * see <http://www.gnu.org/licenses/>.
 *
 */

#include <six/Enums.h>
#include <six/Init.h>
#include <six/Utilities.h>
#include <cphd/SceneCoordinates.h>

namespace cphd
{
SceneCoordinates::SceneCoordinates() :
    earthModel(EarthModelType::WGS_84)
{
}

IARP::IARP() :
    ecf(six::Init::undefined<Vector3>()),
    llh(six::Init::undefined<LatLonAlt>())
{
}

ReferenceSurface::ReferenceSurface()
{
}

Planar::Planar() :
    uIax(six::Init::undefined<Vector3>()),
    uIay(six::Init::undefined<Vector3>())
{
}

HAE::HAE() :
    uIax(six::Init::undefined<LatLon>()),
    uIay(six::Init::undefined<LatLon>())
{
}

AreaType::AreaType():
    x1y1(six::Init::undefined<Vector2>()),
    x2y2(six::Init::undefined<Vector2>())
{
}

ImageGrid::ImageGrid()
{
}

LineSample::LineSample() :
    line(0.0),
    sample(0.0)
{
}

ImageAreaExtent::ImageAreaExtent() :
    lineSpacing(0.0),
    firstLine(0),
    numLines(0)
{
}

Segment::Segment() :
    startLine(0),
    startSample(0),
    endLine(0),
    endSample(0)
{
}

std::ostream& operator<< (std::ostream& os, const SceneCoordinates& d)
{
    os << "SceneCoordinates::\n"
       << "  EarthModel       : " << d.earthModel.toString() << "\n"
       << "  IARP             : " << d.iarp << "\n"
       << "  ReferenceSurface : " << d.referenceSurface << "\n"
       << "  AreaType        : " << d.imageArea << "\n"
       << "  ImageAreaCornerPoints: ";
    for (size_t ii = 0; ii < 3; ++ii)
    {
        LatLon corner = d.imageAreaCorners.getCorner(ii);
        os << corner.getLat() << "," << corner.getLon() << ";  ";
    }

    LatLon corner = d.imageAreaCorners.getCorner(3);
    os << corner.getLat() << "," << corner.getLon() << "\n";

    if (d.extendedArea.get())
    {
        os << "  ExtendedArea     : " << *d.extendedArea << "\n";
    }
    if (d.imageGrid.get())
    {
        os << "  ImageGrid        : " << *d.imageGrid << "\n";
    }
    return os;
}

std::ostream& operator<< (std::ostream& os, const IARP& d)
{
    os << "IARP::\n"
       << "  ECF              : " << d.ecf
       << "  LLH              : " << d.llh.getLat() << ", "
                                  << d.llh.getLon() << ", "
                                  << d.llh.getAlt() << "\n";
    return os;
}

std::ostream& operator<< (std::ostream& os, const ReferenceSurface& d)
{
    os << "ReferenceSurface::\n";
    if (d.planar.get())
    {
        os << *d.planar << "\n";
    }
    else if (d.hae.get())
    {
        os << *d.hae << "\n";
    }
    return os;
}

std::ostream& operator<< (std::ostream& os, const Planar& d)
{
    os << "Planar::\n"
       << "  uIAX             : " << d.uIax << "\n"
       << "  uIAY             : " << d.uIay << "\n";
    return os;
}

std::ostream& operator<< (std::ostream& os, const HAE& d)
{
    os << "Planar::\n"
       << "  uIAX             : " << d.uIax.getLat() << ", "
                                  << d.uIax.getLon() << "\n"
       << "  uIAY             : " << d.uIay.getLat() << ", "
                                  << d.uIay.getLon() << "\n";
    return os;
}

std::ostream& operator<< (std::ostream& os, const AreaType& d)
{
    os << "AreaType::\n"
       << "  x1y1             : " << d.x1y1 << "\n"
       << "  x2y2             : " << d.x2y2 << "\n";
    for (size_t ii = 0; ii < d.polygon.size(); ++ii)
    {
        os << "  Polygon[" << ii << "]: " << d.polygon[ii] << "\n";
    }

    return os;
}

std::ostream& operator<< (std::ostream& os, const ImageGrid& d)
{
    os << "ImageGrid::\n";
    if (!d.identifier.empty())
    {
        os << "  Identifier      : " << d.identifier << "\n";
    }
    os << "  IARPLocation    : " << d.iarpLocation<< "\n";

    return os;
}

std::ostream& operator<< (std::ostream& os, const LineSample& d)
{
    os << "LineSample::\n"
       << "  Line            : " << d.line << "\n"
       << "  Sample          : " << d.sample << "\n";

    return os;
}

std::ostream& operator<< (std::ostream& os, const ImageAreaExtent& d)
{
    os << "ImageAreaExtent::\n"
       << "  lineSpacing     : " << d.lineSpacing << "\n"
       << "  firstLine       : " << d.firstLine<< "\n"
       << "  numLines        : " << d.numLines << "\n";

    return os;
}

std::ostream& operator<< (std::ostream& os, const Segment& d)
{
    os << "Segment::\n"
       << "  StartLine       : " << d.startLine << "\n"
       << "  StartSample     : " << d.startSample << "\n"
       << "  EndLine         : " << d.endLine << "\n"
       << "  EndSample       : " << d.endSample << "\n";
    for (size_t ii = 0; ii < d.polygon.size(); ++ii)
    {
        os << "  Polygon[" << ii << "]: " << d.polygon[ii] << "\n";
    }

    return os;
}
}
