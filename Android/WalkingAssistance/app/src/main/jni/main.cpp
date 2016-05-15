//
// Created by 김준성 on 2016. 3. 20..
//
#include <jni.h>
#include "com_github_codertimo_walkingassistance_MainActivity.h"
#include "core/default.h"
#include "core/android_core.h"

JNIEXPORT jint JNICALL Java_com_github_codertimo_walkingassistance_MainActivity_cornerDetection
        (JNIEnv*, jobject, jlong matAddr)
{
    Mat& mat = *(Mat*)matAddr;
    int result = mainDetection(mat);
    return result;
}