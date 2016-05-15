//
// Created by 김준성 on 2016. 5. 14..
//

#ifndef GOOGLESCIENCEFAIR_ANDROID_MAIN_H
#define GOOGLESCIENCEFAIR_ANDROID_MAIN_H


#include "default.h"
#include "CornerDetector/CornerCode.h"
#include "CornerDetector/CornerDetection.h"
#include "LineDetector/line.h"
#include "EscapeDetector/EscapeDetection.h"


void setLineSize(int size);
void houghline_stablization_android();
int cornerDetection(Mat origin);

#endif //GOOGLESCIENCEFAIR_ANDROID_MAIN_H
