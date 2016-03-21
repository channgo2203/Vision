//
// Created by 김준성 on 2016. 3. 10..
//
#include "Processing.h"

void connerDetection(Mat mat)
{
    Mat origin = mat;

    while(origin.cols>600){
        resize(origin, origin, Size(origin.cols * 0.6, origin.rows * 0.6));
    }

    ResultLines resultLines = lineDetection(origin,origin);
    Point vanPoint = vanishingPointDetection(resultLines,origin.size());

    if(vanPoint.x!=0 && vanPoint.y!=0)
        circle( origin, vanPoint, 10, Scalar( 0, 0, 255 ),CV_FILLED);


    if(vanPoint.x!=0 && vanPoint.y!=0) {

        Point rect_p = Point(vanPoint.x - 50, vanPoint.y - 50);
        Rect rect = Rect(rect_p, Size(100, 100));
        rectangle(origin, rect, Scalar(255, 255, 100));

        for (Point point :resultLines.right_crosspoint) {
            circle(origin, point, 4, Scalar(0, 255, 0), CV_FILLED);
        }
        for (Point point:resultLines.left_crosspoint) {
            circle(origin, point, 4, Scalar(0, 0, 255), CV_FILLED);
        }
    }

    int conrerDetecionCode = connerDetection(&resultLines,vanPoint,origin.size(),Size(100,100),0.6);


    switch (conrerDetecionCode)
    {
        case 11:
//            "no conner"
            break;
        case 12:
//            "right conner"
            break;
        case 21:
//            "left conner"
            break;
        case 22:
//            "vertical left corner"
            break;
        case 20:
//            "vertical corner"
            break;
        case 0:
            break;

    }
}