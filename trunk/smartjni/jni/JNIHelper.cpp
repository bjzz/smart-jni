/*
 * JNIHelper.cpp
 *
 *  Created on: 2012-12-23
 *      Author: boyliang
 */

#include <stddef.h>

#include "JNIHelper.h"
#include "LogUtil.h"

extern JNIEnv* smart_jnienv;

namespace smart_jni{

jmethodID JNIHelper::findMethod(bool isstatic, const char* classname, const char* methodname, const char* methodsigner) {
	jclass claxx = smart_jnienv->FindClass(classname);
	jmethodID method = findMethod(isstatic, claxx, methodname, methodsigner);
	smart_jnienv->DeleteLocalRef(claxx);
	return method;
}

inline jmethodID JNIHelper::findMethod(bool isstatic, const jclass claxx, const char* methodname, const char* methodsigner){
	return isstatic ? smart_jnienv->GetStaticMethodID(claxx, methodname, methodsigner) : smart_jnienv->GetMethodID(claxx, methodname, methodsigner);
}

}

