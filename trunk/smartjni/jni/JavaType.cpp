/*
 * JavaType.cpp
 *
 *  Created on: 2012-12-23
 *      Author: boyliang
 */

#include <jni.h>

#include "Class.h"
#include "JavaType.h"
#include "JNIHelper.h"

extern JNIEnv* smart_jnienv;

namespace smart_jni{

	//For Integer Impl
	Integer::Integer() : Class("java/lang/Integer"){}

	Integer::~Integer(){}

	jobject Integer::valueOf(jint value){
		jclass claxx = Integer::type()->mClass;
		jobject result = smart_jnienv->NewObject(claxx, s_Integer_init_ID, value);
		return result;
	}

	jint Integer::intValue(jobject value) {

		jint result = 0xffffffff;
		if (JNIHelper::isAssignableFrom(value, type()->mClass)) {
			result = smart_jnienv->CallIntMethod(value, s_Integer_intValue_ID);
		}

		return result;
	}

	const Integer* Integer::type() {

		if(sInstance == NULL){
			sInstance = new Integer();
		}

		return sInstance;
	}

	Integer* Integer::sInstance = NULL;
	jmethodID Integer::s_Integer_init_ID = JNIHelper::findMethod(false, "java/lang/Integer", "<init>", "(I)V");
	jmethodID Integer::s_Integer_intValue_ID = JNIHelper::findMethod(false, "java/lang/Integer", "intValue", "()I");





	//For Jint Impl
	Jint::Jint() : Class("java/lang/Integer"){
		jclass tmp = mClass;
		mClass = Class::trans2Primitive(mClass);

		smart_jnienv->DeleteGlobalRef(tmp);
		mClass = (jclass)smart_jnienv->NewGlobalRef(mClass);
	}

	Jint::~Jint(){}

	const Jint* Jint::type(){
		if(sInstance == NULL){
			sInstance = new Jint();
		}
		return sInstance;
	}

	Jint* Jint::sInstance = NULL;


	//For Long Impl
	Long::Long() : Class("java/lang/Long"){}

	Long::~Long(){}

	const Long* Long::type(){
		if(sInstance == NULL){
			sInstance = new Long();
		}

		return sInstance;
	}

	jobject Long::valueOf(jlong value){
		jclass claxx = type()->mClass;
		jobject result = smart_jnienv->NewObject(claxx, s_Long_init_ID, value);
		return result;
	}

	jlong Long::longValue(jobject value){
		jlong result = 0xffffffff;

		if(JNIHelper::isAssignableFrom(value, type()->mClass)){
			result = smart_jnienv->CallLongMethod(value, s_Long_longValue_ID);
		}

		return result;
	}

	Long* Long::sInstance = NULL;
	jmethodID Long::s_Long_init_ID = JNIHelper::findMethod(false, "java/lang/Long", "<init>", "(J)V");
	jmethodID Long::s_Long_longValue_ID = JNIHelper::findMethod(false,  "java/lang/Long", "longValue", "()J");





	//For Jlong Impl
	Jlong::Jlong() : Class("java/lang/Long"){
		jclass tmp = mClass;
		mClass = (jclass)smart_jnienv->NewGlobalRef(Class::trans2Primitive(mClass));

		smart_jnienv->DeleteGlobalRef(tmp);
	}

	Jlong::~Jlong(){}

	const Jlong* Jlong::type(){

		if(sInstance == NULL){
			sInstance = new Jlong();
		}

		return sInstance;
	}

	Jlong* Jlong::sInstance = NULL;
}


