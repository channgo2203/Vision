//
// Created by 김준성 on 2016. 5. 14..
//
#include "default.h"
#include "android_core.h"

extern int a, b;

int main()
{
    //Video Input Initializing
    VideoCapture cap("/Users/codertimo/Desktop/Test3/IMG_1390.m4v");


    //Video Frame Loop
    while (1) {

        Mat origin;
        if (!cap.read(origin)) break;

        int result = cornerDetection(origin);

        cvWaitKey(1);
    }

    cout << "Accuracy : " << (double)a/(a+b) << endl;
    cout << "Video Finish" << endl;
}