/*
 * Class.h
 *
 *  Created on: 2012-12-16
 *      Author: boyliang
 */

#ifndef CLASS_H_
#define CLASS_H_

#include <jni.h>

namespace smart_jni{

class Method;
class Field;

class Class {

private:
	static jmethodID s_Class_getName_ID;

protected:
	jclass mClass;

	Class(const char* name);
	Class(const jclass claxx);

	static char* trans2JNIName(const char* name);
	static jclass trans2Primitive(const jclass claxx);

public:
	/**
	 * 根据方法名以及参数表，查找方法
	 */
	Method* getMethod(const char* methodname, ...) const;

	/**
	 * 根据字段名,查找字段
	 */
	Field* getField(const char* filedname) const;

	/**
	 * 获取类名字
	 */
	const char* getName();

	/**
	 * 获取jclass对象
	 */
	const jclass getJNIClass();

	/**
	 * 析构
	 */
	virtual ~Class();

	/**
	 * 获取用户自定义Class
	 */
	static Class* forName(const char* name);

	/**
	 * 获取现存对象获取Class
	 */
	static Class* forObject(const jobject object);

	/**
	 * 参数结尾
	 */
	static const Class* END;
};

}


#endif /* CLASS_H_ */
