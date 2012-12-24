LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := smartjni
LOCAL_LDLIBS 	:= -llog -landroid_runtime -lcutils
### Add all source file names to be included in lib separated by a whitespace
LOCAL_SRC_FILES := \
	JNIHelper.cpp\
	Class.cpp\
	Method.cpp\
	Field.cpp\
	JavaType.cpp\
	smartjni.cpp

include $(BUILD_SHARED_LIBRARY)

