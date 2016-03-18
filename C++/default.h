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
#include <highgui.h>

using namespace cv;
using namespace std;

#define ClusterK 20
#define MaxColorCount 4

class CompareableLine;
class LineMap;

typedef struct ColorCount
{
    int color;
    int count;
}ColorCount;

typedef struct ResultLines
{
    vector<Point> right_crosspoint;
    vector<Point> left_crosspoint;

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
