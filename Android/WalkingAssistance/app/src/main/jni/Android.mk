LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#opencv
OPENCVROOT:= /Users/codertimo/GoogleDrive/Develop/OpenCV_LIB/OpenCV-android-sdk
OPENCV_CAMERA_MODULES:=on
OPENCV_INSTALL_MODULES:=on
OPENCV_LIB_TYPE:=SHARED

include ${OPENCVROOT}/sdk/native/jni/OpenCV.mk

LOCAL_SRC_FILES := main.cpp core/CornerDetection/ResultLines.cpp core/CornerDetection/CornerDetection.cpp core/LineDetector/line.cpp
LOCAL_LDLIBS += -llog
LOCAL_MODULE := swd

include $(BUILD_SHARED_LIBRARY)
include $(CLEAR_VARS)

NDK_TOOLCHAIN_VERSION := 4.8
# APP_STL := stlport_shared  --> does not seem to contain C++11 features
APP_STL := gnustl_shared

# Enable c++11 extentions in source code
APP_CPPFLAGS += -std=c++11