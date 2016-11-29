LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL2

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include C:\androiddevdir\SDL2-2.0.3\android-project\jni\SDL_image C:\androiddevdir\SDL2-2.0.3\android-project\jni\SDL_ttf

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	52_hello_mobile.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf SDL2_image

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
