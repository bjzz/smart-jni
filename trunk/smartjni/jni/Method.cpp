/*
 * Method.cpp
 *
 *  Created on: 2012-12-16
 *      Author: boyliang
 */

#include <stddef.h>
#include <stdarg.h>
#include <unistd.h>

#include "LogUtil.h"
#include "JavaType.h"
#include "Method.h"
#include "Class.h"
#include "JNIHelper.h"

extern JNIEnv* smart_jnienv;

namespace smart_jni{

Method::Method(const jclass claxx, const char* methodname, const int n, Class** params_class)
: mClass(claxx),
  mParamsCount(n),
  mParamsClass(params_class),
  mMethod(NULL){

	jclass class_claxx = smart_jnienv->FindClass("java/lang/Class");
	jobjectArray param_class_array = smart_jnienv->NewObjectArray(mParamsCount, class_claxx, NULL);

	for (int i = 0; i < mParamsCount; i++) {
		smart_jnienv->SetObjectArrayElement(param_class_array, i, mParamsClass[i]->getJNIClass());
	}

	jstring jmethod_name = smart_jnienv->NewStringUTF(methodname);
	mMethod = smart_jnienv->CallObjectMethod(mClass, s_Class_getDeclaredMethod_ID, jmethod_name, param_class_array);
	smart_jnienv->CallVoidMethod(mMethod, s_Method_setAccessible_ID, JNI_TRUE);

	//delete localrel
	smart_jnienv->DeleteLocalRef(jmethod_name);
	smart_jnienv->DeleteLocalRef(param_class_array);
	smart_jnienv->DeleteLocalRef(class_claxx);
}

Method::~Method(){
	delete mParamsClass;
}

jobject Method::invoke(jobject receiver, ...){
	jobject result = NULL;

	jclass element_claxx = smart_jnienv->FindClass("java/lang/Object");
	jobjectArray params = smart_jnienv->NewObjectArray(mParamsCount, element_claxx, NULL);

	va_list va;
	va_start(va, receiver);

	for(int i=0; i<mParamsCount; i++){
		Class* cur = mParamsClass[i];
		jobject value = NULL;

		if(cur == Jint::type()){
			value = Integer::valueOf(va_arg(va, jint));
		}else if(cur == Jlong::type()){
			value = Long::valueOf(va_arg(va, jlong));
		}else if(cur == Integer::type() || cur == Long::type()){
			value = va_arg(va, jobject);
		}else{
			value = va_arg(va, jobject);
		}

		smart_jnienv->SetObjectArrayElement(params, i, value);
	}

	va_end(va);

	result = smart_jnienv->CallObjectMethod(mMethod, s_Method_invoke_ID, receiver, params);

	return result;
}

const char* Method::getName(){
	jstring jname = (jstring)smart_jnienv->CallObjectMethod(mMethod, s_Method_getName_ID);
	return smart_jnienv->GetStringUTFChars(jname, NULL);
}

jmethodID Method::s_Class_getDeclaredMethod_ID = JNIHelper::findMethod(false, "java/lang/Class", "getDeclaredMethod", "(Ljava/lang/String;[Ljava/lang/Class;)Ljava/lang/reflect/Method;");
jmethodID Method::s_Method_setAccessible_ID = JNIHelper::findMethod(false, "java/lang/reflect/Method", "setAccessible", "(Z)V");
jmethodID Method::s_Method_invoke_ID = JNIHelper::findMethod(false, "java/lang/reflect/Method", "invoke", "(Ljava/lang/Object;[Ljava/lang/Object;)Ljava/lang/Object;");
jmethodID Method::s_Method_getName_ID = JNIHelper::findMethod(false, "java/lang/reflect/Method", "getName", "()Ljava/lang/String;");

}

