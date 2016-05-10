//
// Created by 김준성 on 2016. 3. 10..
//
#include "Processing.h"

int cornerDetection(Mat origin, ResultLines resultLines , int w1, int w2)
{
    Point vanPoint = vanishingPointDetection(resultLines,origin.size());

    if(vanPoint.x!=0 && vanPoint.y!=0)
        circle( origin, vanPoint, 10, Scalar( 0, 0, 255 ),CV_FILLED);

    if(vanPoint.x!=0 && vanPoint.y!=0) {

        Point rect_p = Point(vanPoint.x - 50, vanPoint.y - 50);
        Rect rect = Rect(rect_p, Size(100, 100));
        rectangle(origin, rect, Scalar(255, 255, 100));
    }

    int cornerDetecionCode = connerDetection(&resultLines,vanPoint,origin.size(),Size(100,100),0.6);

    return cornerDetecionCode;
}