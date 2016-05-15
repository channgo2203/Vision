//
// Created by 김준성 on 2016. 2. 26..
//

#include "../default.h"


#ifndef SIDEWALKDETECTION_LINE_H
#define SIDEWALKDETECTION_LINE_H

void degreeChecking(double degree, Vec4i vec4i, Point pt1, Point pt2, ResultLines* resultLines, Mat origin);
ResultLines lineDetection(Mat origin,int w1, int w2);

#endif //SIDEWALKDETECTION_LINE_H
