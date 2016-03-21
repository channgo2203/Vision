//
// Created by 김준성 on 2016. 2. 26..
//

#include "line.h"
#include "ConerDetection.h"

ResultLines lineDetection(Mat src,Mat origin)
{
    vector<Vec2f> lines;
    ResultLines resultlines;

    Mat canny;
    Canny(src,canny,2,300);
    HoughLines(canny, lines, 1, CV_PI / 180, 130, 0, 0);

    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        Vec4i vec4i = Vec4i(pt1.x,pt1.y,pt2.x,pt2.y);
        double degree = theta/CV_PI*180;

        degreeChecking(degree,vec4i,pt1,pt2,&resultlines,origin);
        resultlines.allLines.push_back(vec4i);
    }

    return resultlines;
}

void degreeChecking(double degree, Vec4i vec4i, Point pt1, Point pt2, ResultLines *resultLines, Mat origin)
{

    if(degree>0 && degree<20)
    {
        resultLines->verticalLines.push_back(vec4i);
    }
    else if(degree>20 && degree<60) {
        line(origin, pt1, pt2, Scalar(100,255,100), 3, CV_AA);
        resultLines->roadlines_right.push_back(vec4i);
        resultLines->roadlines.push_back(vec4i);
    }
    else if(degree>115 && degree<155) {
        line(origin, pt1, pt2, Scalar(100,255,100), 3, CV_AA);
        resultLines->roadlines_left.push_back(vec4i);
        resultLines->roadlines.push_back(vec4i);
    }
    else if(degree>60 && degree<115)
    {
        resultLines->otherlines.push_back(vec4i);
        if(degree>60 && degree<85)
        {
            line(origin, pt1, pt2, Scalar(0,255,255), 3, CV_AA);
            resultLines->connerlines.push_back(vec4i);
            resultLines->conerlines_right.push_back(vec4i);
        }
        else if(degree>95 && degree<115)
        {
            line(origin, pt1, pt2, Scalar(255,0,255), 3, CV_AA);
            resultLines->conerline_left.push_back(vec4i);
            resultLines->connerlines.push_back(vec4i);
        }
        else
        {
            line(origin, pt1, pt2, Scalar(255,255,255), 3, CV_AA);
            resultLines->horizenLines.push_back(vec4i);
        }
    }
    else if(degree>155 && degree<180)
    {
        resultLines->verticalLines.push_back(vec4i);
    }
}