/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class cgm_MetafileReader */

#ifndef _Included_cgm_MetafileReader
#define _Included_cgm_MetafileReader
#ifdef __cplusplus
extern "C" {
#endif
#undef cgm_MetafileReader_INVALID_ADDRESS
#define cgm_MetafileReader_INVALID_ADDRESS 0LL
/*
 * Class:     cgm_MetafileReader
 * Method:    construct
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_cgm_MetafileReader_construct
  (JNIEnv *, jobject);

/*
 * Class:     cgm_MetafileReader
 * Method:    read
 * Signature: (Lnitf/IOInterface;)Lcgm/Metafile;
 */
JNIEXPORT jobject JNICALL Java_cgm_MetafileReader_read
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
