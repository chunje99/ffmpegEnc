#include "jnifenc.h"


void JNIFenc::Print(){
    std::cout << "Hello World!" << std::endl;
}

#ifdef __cplusplus
extern "C" {
#endif
    /*
     * Class:     JNITest
     * Method:    Print
     * Signature: (J)V
     */
    JNIEXPORT void JNICALL Java_JNITest_Print
        (JNIEnv *, jobject, jlong classNI){
            JNIFenc* fenc= reinterpret_cast<JNIFenc*>(classNI);
            fenc->Print();
        }

    /*
     * Class:     JNITest
     * Method:    CreateNI
     * Signature: ()J
     */
    JNIEXPORT jlong JNICALL Java_JNITest_CreateNI
        (JNIEnv *, jobject){
            return reinterpret_cast<jlong>(new JNIFenc());
        }
/*
 * Class:     JNITest
 * Method:    DeleteNI
 * Signature: (J)V
 */
    JNIEXPORT void JNICALL Java_JNITest_DeleteNI
        (JNIEnv *, jobject, jlong classNI){
            JNIFenc* fenc= reinterpret_cast<JNIFenc*>(classNI);
            delete fenc;
        }
/*
 * Class:     JNITest
 * Method:    setSource
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_JNITest_setSource
  (JNIEnv *env, jobject, jlong classNI, jstring str){
            JNIFenc* fenc= reinterpret_cast<JNIFenc*>(classNI);
            fenc->setSource( env->GetStringUTFChars(str, nullptr) );
  }

/*
 * Class:     JNITest
 * Method:    getSource
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_JNITest_getSource
  (JNIEnv * env, jobject, jlong classNI){
      JNIFenc* fenc= reinterpret_cast<JNIFenc*>(classNI);
      std::string source = fenc->getSource();
	  jstring jstr = env->NewStringUTF(source.c_str());

	  return jstr;
  }

/*
 * Class:     JNITest
 * Method:    setTarget
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_JNITest_setTarget
  (JNIEnv *env, jobject, jlong classNI, jstring str){
            JNIFenc* fenc= reinterpret_cast<JNIFenc*>(classNI);
            fenc->setTarget( env->GetStringUTFChars(str, nullptr) );
  }

/*
 * Class:     JNITest
 * Method:    getTarget
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_JNITest_getTarget
  (JNIEnv * env, jobject, jlong classNI){
      JNIFenc* fenc= reinterpret_cast<JNIFenc*>(classNI);
      std::string target = fenc->getTarget();
	  jstring jstr = env->NewStringUTF(target.c_str());

	  return jstr;
  }

/*
 * Class:     JNITest
 * Method:    setPreset
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_JNITest_setPreset
  (JNIEnv *env, jobject, jlong classNI, jstring str){
            JNIFenc* fenc= reinterpret_cast<JNIFenc*>(classNI);
            fenc->setPreset( env->GetStringUTFChars(str, nullptr) );
  }

/*
 * Class:     JNITest
 * Method:    getPreset
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_JNITest_getPreset
  (JNIEnv * env, jobject, jlong classNI){
      JNIFenc* fenc= reinterpret_cast<JNIFenc*>(classNI);
      std::string preset = fenc->getPreset();
	  jstring jstr = env->NewStringUTF(preset.c_str());

	  return jstr;
  }

/*
 * Class:     JNITest
 * Method:    setThumbnailTime
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_JNITest_setThumbnailTime
  (JNIEnv *env, jobject, jlong classNI, jint ttime){
            JNIFenc* fenc= reinterpret_cast<JNIFenc*>(classNI);
            int t = reinterpret_cast<int>(ttime);
            fenc->setThumbnailTime(t);
  }

/*
 * Class:     JNITest
 * Method:    getThumbnailTime
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_JNITest_getThumbnailTime
  (JNIEnv * env, jobject, jlong classNI){
      JNIFenc* fenc= reinterpret_cast<JNIFenc*>(classNI);
	  return fenc->getThumbnailTime();
  }

/*
 * Class:     JNITest
 * Method:    StartEncode
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_JNITest_StartEncode
  (JNIEnv * env, jobject, jlong classNI){
      JNIFenc* fenc= reinterpret_cast<JNIFenc*>(classNI);
	  fenc->StartEncode();
  }

/*
 * Class:     JNITest
 * Method:    StartThumbnail
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_JNITest_StartThumbnail
  (JNIEnv * env, jobject, jlong classNI){
      JNIFenc* fenc= reinterpret_cast<JNIFenc*>(classNI);
	  fenc->StartThumbnail();
  }
/*
 * Class:     JNITest
 * Method:    Wait
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_JNITest_Wait
  (JNIEnv * env, jobject, jlong classNI){
      JNIFenc* fenc= reinterpret_cast<JNIFenc*>(classNI);
	  fenc->Wait();
  }

#ifdef __cplusplus
}
#endif
