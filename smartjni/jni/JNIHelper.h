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
	static jmethodID findMethod(bool isstatic, const char* classname, const char* methodname, const char* methodsigner);
	static jmethodID findMethod(bool isstatic, const jclass claxx, const char* methodname, const char* methodsigner);

};

}




#endif /* JNIHELPER_H_ */
