/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class nitf_Reader */

#ifndef _Included_nitf_Reader
#define _Included_nitf_Reader
#ifdef __cplusplus
extern "C" {
#endif
#undef nitf_Reader_INVALID_ADDRESS
#define nitf_Reader_INVALID_ADDRESS 0L
/*
 * Class:     nitf_Reader
 * Method:    construct
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_nitf_Reader_construct
  (JNIEnv *, jobject);

/*
 * Class:     nitf_Reader
 * Method:    destructMemory
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_nitf_Reader_destructMemory
  (JNIEnv *, jobject);

/*
 * Class:     nitf_Reader
 * Method:    read
 * Signature: (Lnitf/IOHandle;)Lnitf/Record;
 */
JNIEXPORT jobject JNICALL Java_nitf_Reader_read
  (JNIEnv *, jobject, jobject);

/*
 * Class:     nitf_Reader
 * Method:    getNewImageReader
 * Signature: (I)Lnitf/ImageReader;
 */
JNIEXPORT jobject JNICALL Java_nitf_Reader_getNewImageReader
  (JNIEnv *, jobject, jint);

/*
 * Class:     nitf_Reader
 * Method:    getNewGraphicReader
 * Signature: (I)Lnitf/SegmentReader;
 */
JNIEXPORT jobject JNICALL Java_nitf_Reader_getNewGraphicReader
  (JNIEnv *, jobject, jint);

/*
 * Class:     nitf_Reader
 * Method:    getNewTextReader
 * Signature: (I)Lnitf/SegmentReader;
 */
JNIEXPORT jobject JNICALL Java_nitf_Reader_getNewTextReader
  (JNIEnv *, jobject, jint);

/*
 * Class:     nitf_Reader
 * Method:    getNewDEReader
 * Signature: (I)Lnitf/SegmentReader;
 */
JNIEXPORT jobject JNICALL Java_nitf_Reader_getNewDEReader
  (JNIEnv *, jobject, jint);

/*
 * Class:     nitf_Reader
 * Method:    getInputHandle
 * Signature: ()Lnitf/IOHandle;
 */
JNIEXPORT jobject JNICALL Java_nitf_Reader_getInputHandle
  (JNIEnv *, jobject);

/*
 * Class:     nitf_Reader
 * Method:    getRecord
 * Signature: ()Lnitf/Record;
 */
JNIEXPORT jobject JNICALL Java_nitf_Reader_getRecord
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
