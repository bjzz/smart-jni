#include <string.h>
#include <jni.h>
#include <android_runtime/AndroidRuntime.h>

#include "JavaType.h"
#include "Method.h"
#include "Field.h"
#include "LogUtil.h"

using android::AndroidRuntime;

using namespace smart_jni;

JNIEnv* getJNIEnv(){
	return AndroidRuntime::getJNIEnv();
//	return NULL;
}

extern "C" {

void Java_com_demo_smartjni_MainActivity_nativemethod(JNIEnv *env, jobject thiz) {
	Class* claxx = Class::forName("com.demo.smartjni.MainActivity");

	//非静态方法调用
	Method* method1 = claxx->getMethod("method1", Integer::type(), Long::type(), Jint::type(), Jlong::type(), Class::END);
	method1->invoke(thiz, Integer::valueOf(4), Long::valueOf(32), (jint)33, (jlong)44);
	delete method1;

	//静态方法调用
	Method* method2 = claxx->getMethod("method2", Long::type(), Jint::type(), Class::END);
	method2->invoke(NULL, Long::valueOf(44), (jint)65);
	delete method2;

	//非静态字段调用
	Field* field1 = claxx->getField("mValue1");
	Log_i("TTT", "intret1 is %d", field1->getInt(thiz));
	field1->setInt(thiz, 44);
	Log_i("TTT", "intret1 is %d", field1->getInt(thiz));
	delete field1;

	//静态字段调用
	Field* field2 = claxx->getField("mValue2");
	Log_i("TTT", "intret2 is %d", field2->getInt(NULL));
	field2->setInt(NULL, 333);
	Log_i("TTT", "intret2 is %d", field2->getInt(NULL));
	delete field2;

	//静态非原始字段调用
	Field* field3 = claxx->getField("mValue3");
	Log_i("TTT", "intret3 is %d", Jint::valueOf(field3->get(NULL)));
	field3->set(NULL, Integer::valueOf(56));
	Log_i("TTT", "intret3 is %d", Jint::valueOf(field3->get(NULL)));
	delete field3;

	delete claxx;
}

}


