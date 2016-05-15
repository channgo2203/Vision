//
// Created by 김준성 on 2016. 5. 14..
//
#include "default.h"
#include "android_core.h"

int main()
{
    //Video Input Initializing
    VideoCapture cap("/Users/codertimo/Desktop/Test3/sidewalk10.mp4");


    //Video Frame Loop
    while (1) {

        Mat origin;
        if (!cap.read(origin)) break;

        int result = cornerDetection(origin);

        if(result>0)
        {
            cout << result << endl;
        }
        imshow("gg",origin);
        cvWaitKey(1);

    }
    cout << "Video Finish" << endl;
}