/*
 * Class.cpp
 *
 *  Created on: 2012-12-16
 *      Author: boyliang
 *
 */

#include <jni.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>

#include "Class.h"
#include "Method.h"
#include "Field.h"
#include "LogUtil.h"
#include "JNIHelper.h"

extern JNIEnv* getJNIEnv();

JNIEnv* smart_jnienv = getJNIEnv();

namespace smart_jni{

Class* Class::forName(const char* name){
	Class* claxx = new Class(name);
	return claxx;
}

Class* Class::forObject(const jobject object){
	jclass obj_claxx = smart_jnienv->GetObjectClass(object);
	Class* claxx = new Class(obj_claxx);
	smart_jnienv->DeleteLocalRef(obj_claxx);
	return claxx;
}


Class::Class(const char* name){
	char* jniname = trans2JNIName(name);

	mClass = smart_jnienv->FindClass(jniname);
	mClass = (jclass)smart_jnienv->NewGlobalRef(mClass);

	delete jniname;
}

Class::Class(const jclass claxx){
	mClass = (jclass)smart_jnienv->NewGlobalRef(claxx);
}

Class::~Class(){
	if(mClass != NULL){
		smart_jnienv->DeleteGlobalRef(mClass);
	}
}

char* Class::trans2JNIName(const char* name){
	char *jniname = NULL;

	if(name != NULL && strlen(name) > 0){
		jniname = strdup(name);
		int length = strlen(jniname) + 1;

		for(int i=0; i<length; i++){
			if(jniname[i] == '.'){
				jniname[i] = '/';
			}
		}
	}

	return jniname;
}

jclass Class::trans2Primitive(const jclass claxx){
	jclass primitiveclaxx = claxx;
	jfieldID TYPE_filedID = smart_jnienv->GetStaticFieldID(claxx, "TYPE", "Ljava/lang/Class;");
	primitiveclaxx = (jclass) smart_jnienv->GetStaticObjectField(claxx, TYPE_filedID);

	return primitiveclaxx;
}

Method* Class::getMethod(const char* methodname, ...) const{
	va_list vl;
	va_start(vl, methodname);

	int size = 0;
	while(va_arg(vl, Class*) != END){
		size++;
	}

	va_start(vl, methodname);
	Class* claxx = NULL;
	Class** params_claxx = (Class**)malloc(size * sizeof(Class*));
	size = 0;
	while((claxx = va_arg(vl, Class*)) != END){
		params_claxx[size++] = claxx;
	}

	va_end(vl);

	Method* method = new Method(mClass, methodname, size, params_claxx);
	return method;
}

Field* Class::getField(const char* fieldname) const{
	Field* field = new Field(mClass, fieldname);
	return field;
}

const char* Class::getName(){
	jstring jname = (jstring)smart_jnienv->CallObjectMethod(mClass, s_Class_getName_ID);
	return smart_jnienv->GetStringUTFChars(jname, NULL);
}

const jclass Class::getJNIClass(){
	return mClass;
}

jmethodID Class::s_Class_getName_ID = JNIHelper::findMethod(false, "java/lang/Class", "getName", "()Ljava/lang/String;");
const Class* Class::END = NULL;

}




