//
// Created by 김준성 on 2016. 2. 26..
//

#ifndef SIDEWALKDETECTION_DEFAULT_H
#define SIDEWALKDETECTION_DEFAULT_H

#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstring>
#include <math.h>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;
class CompareableLine;
class LineMap;


typedef struct ResultLines
{
    vector<Vec4i> allLines;
    vector<Vec4i> roadlines;
    vector<Vec4i> otherlines;
    vector<Vec4i> horizenLines;
    vector<Vec4i> verticalLines;
    vector<Vec4i> connerlines;

    vector<Vec4i> roadlines_right;
    vector<Vec4i> roadlines_left;

    vector<Vec4i> conerlines_right;
    vector<Vec4i> conerline_left;

}ResultLines;



#endif //SIDEWALKDETECTION_DEFAULT_H
