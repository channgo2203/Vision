//
// Created by 김준성 on 2016. 3. 10..
//

#ifndef SIDEWALKDETECTION_PROCESSING_H
#define SIDEWALKDETECTION_PROCESSING_H

#include "default.h"
#include "cluster.h"
#include "line.h"
#include "ConerDetection.h"

void connerTest(Mat mat,int cnt);
ResultLines colorDetection(Mat origin,int cnt);
Mat setRoi(Mat mat);
void imageTextWrite(Mat *origin,int cornerCode);


#endif //SIDEWALKDETECTION_PROCESSING_H