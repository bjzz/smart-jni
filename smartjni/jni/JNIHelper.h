/*
 * JNIHelper.h
 *
 *  Created on: 2012-12-23
 *      Author: boyliang
 */

#ifndef JNIHELPER_H_
#define JNIHELPER_H_

#include <jni.h>

namespace smart_jni{

class JNIHelper{

private:
	JNIHelper(){}

public:

	/**
	 * find the methodID by the classname, methodname and the methodsigner.
	 */
	static jmethodID findMethod(bool isstatic, const char* classname, const char* methodname, const char* methodsigner);

	/**
	 * find the methodID by the classname, methodname and the methodsigner.
	 */
	static jmethodID findMethod(bool isstatic, const jclass claxx, const char* methodname, const char* methodsigner);

	/**
	 *  check the obj was assigned from class whitch name claxxname
	 */
	static bool isAssignableFrom(const jobject obj, const char* claxxname);

	/**
	 *  check the obj was assigned from claxx
	 */
	static bool isAssignableFrom(const jobject obj, const jclass claxx);

};

}




#endif /* JNIHELPER_H_ */
