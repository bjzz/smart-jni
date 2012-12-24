/*
 * JavaType.h
 *
 *  Created on: 2012-12-23
 *      Author: boyliang
 */

#ifndef JAVATYPE_H_
#define JAVATYPE_H_

#include <stddef.h>
#include <jni.h>

#include "Class.h"


namespace smart_jni{

class Integer : public Class{

private:
	static jmethodID s_Integer_init_ID;
	static Integer* sInstance;

	Integer();

public:

	/**
	 * jint -> Integer ×ª»»
	 */
	static jobject valueOf(jint value);
	static const Integer* type();
	virtual ~Integer();
};


class Jint : public Class{

private:
	static jmethodID s_Integer_intValue_ID;

	static Jint* sInstance;
	Jint();

public:
	static const Jint* type();
	static jint valueOf(jobject value);
	virtual ~Jint();

};

class Long : public Class{

private:
	static jmethodID s_Long_init_ID;
	static Long* sInstance;

	Long();

public:

	/**
	 * jlong -> Long ×ª»»
	 */
	static jobject valueOf(jlong value);
	static const Long* type();
	virtual ~Long();
};

class Jlong: public Class{

private:
	static Jlong* sInstance;
	Jlong();

public:
	static const Jlong* type();
	static jlong valueOf(jobject value);
	virtual ~Jlong();

};

}



#endif /* JAVATYPE_H_ */
