/*
 * Field.cpp
 *
 *  Created on: 2012-12-23
 *      Author: boyliang
 */

#include <stddef.h>
#include <jni.h>
#include "Field.h"
#include "JNIHelper.h"

extern JNIEnv* smart_jnienv;

namespace smart_jni{

Field::Field(jclass claxx, const char* fieldname): mFiled(NULL){
	jstring jfieldname = smart_jnienv->NewStringUTF(fieldname);
	mFiled = smart_jnienv->CallObjectMethod(claxx, s_Class_getDeclaredField_ID, jfieldname);
	smart_jnienv->DeleteLocalRef(jfieldname);
	smart_jnienv->CallVoidMethod(mFiled, s_Field_setAccessible_ID, JNI_TRUE);
}

Field::~Field(){}

jint Field::getInt(jobject obj){
	jint result = smart_jnienv->CallIntMethod(mFiled, s_Field_getInt_ID, obj);
	return result;
}

jlong Field::getLong(jobject obj){
	jlong result = smart_jnienv->CallIntMethod(mFiled, s_Field_getLong_ID, obj);
	return result;
}

jobject Field::get(jobject obj){
	jobject result = smart_jnienv->CallObjectMethod(mFiled, s_Field_get_ID, obj);
	return result;
}

void Field::setInt(jobject obj, jint value){
	smart_jnienv->CallVoidMethod(mFiled, s_Field_setInt_ID, obj, value);
}

void Field::setLong(jobject obj, jlong value){
	smart_jnienv->CallVoidMethod(mFiled, s_Field_setLong_ID, obj, value);
}

void Field::set(jobject obj, jobject value){
	smart_jnienv->CallVoidMethod(mFiled, s_Field_set_ID, obj, value);
}

jmethodID Field::s_Class_getDeclaredField_ID = JNIHelper::findMethod(false, "java/lang/Class", "getDeclaredField", "(Ljava/lang/String;)Ljava/lang/reflect/Field;");

#define FIELD_CLASS "java/lang/reflect/Field"

jmethodID Field::s_Field_setAccessible_ID = JNIHelper::findMethod(false, FIELD_CLASS, "setAccessible", "(Z)V");
jmethodID Field::s_Field_getInt_ID 	= JNIHelper::findMethod(false, FIELD_CLASS, "getInt", "(Ljava/lang/Object;)I");
jmethodID Field::s_Field_getLong_ID = JNIHelper::findMethod(false, FIELD_CLASS, "getLong", "(Ljava/lang/Object;)J");
jmethodID Field::s_Field_get_ID 	= JNIHelper::findMethod(false, FIELD_CLASS, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
jmethodID Field::s_Field_setInt_ID 	= JNIHelper::findMethod(false, FIELD_CLASS, "setInt", "(Ljava/lang/Object;I)V");
jmethodID Field::s_Field_setLong_ID = JNIHelper::findMethod(false, FIELD_CLASS, "setLong", "(Ljava/lang/Object;J)V");
jmethodID Field::s_Field_set_ID 	= JNIHelper::findMethod(false, FIELD_CLASS, "set", "(Ljava/lang/Object;Ljava/lang/Object;)V");

}


