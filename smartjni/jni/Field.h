/*
 * Field.h
 *
 *  Created on: 2012-12-23
 *      Author: boyliang
 */

#ifndef FIELD_H_
#define FIELD_H_

#include <jni.h>

namespace smart_jni{

class Field{

private:
	jobject mFiled;

	static jmethodID s_Class_getDeclaredField_ID;

	static jmethodID s_Field_setAccessible_ID;

	static jmethodID s_Field_getInt_ID;
	static jmethodID s_Field_getLong_ID;
	static jmethodID s_Field_get_ID;

	static jmethodID s_Field_setInt_ID;
	static jmethodID s_Field_setLong_ID;
	static jmethodID s_Field_set_ID;

public:
	Field(jclass claxx, const char* fieldname);
	virtual ~Field();

	jint getInt(jobject obj);
	jlong getLong(jobject obj);
	jobject get(jobject obj);

	void setInt(jobject obj, jint value);
	void setLong(jobject obj, jlong value);
	void set(jobject obj, jobject value);
};

}


#endif /* FIELD_H_ */
