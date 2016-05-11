//
// Created by 김준성 on 2016. 5. 10..
//

#ifndef GOOGLESCIENCEFAIR_ESCAPEDETECTION_H
#define GOOGLESCIENCEFAIR_ESCAPEDETECTION_H

#include "../CornerDetector/default.h"

pair<int,Mat> compareCurrent(Mat smStack);
Vec4f calMapSlope(Mat resMap);
int escape_detection(vector<Vec4i> vLines);

#endif //GOOGLESCIENCEFAIR_ESCAPEDETECTION_H
