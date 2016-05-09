//
// Created by 김준성 on 2016. 3. 20..
//
#include <jni.h>
#include "com_github_codertimo_walkingassistance_MainActivity.h"
#include "core/default.h"
#include "core/Processing.h"

JNIEXPORT jint JNICALL Java_com_github_codertimo_walkingassistance_MainActivity_cornerDetection
        (JNIEnv*, jobject, jlong matAddr, jint w1, jint w2)
{
    Mat& mat = *(Mat*)matAddr;
    int result = cornerDetection(mat,w1,w2);
    return result;
}