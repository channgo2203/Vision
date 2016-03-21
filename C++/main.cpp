#include "main.h"

int main()
{
    walkTest();
}
void walkTest()
{
    CvCapture*  cvCapture = cvCreateFileCapture("/Users/codertimo/Desktop/ResearchTest/gym1.mp4");
    IplImage* iFrame;

    Mat vanpoints =Mat(1000,1000,CV_8UC1);
    int cnt=0;

    while (1) {
        iFrame = cvQueryFrame(cvCapture);
        if (!iFrame) break;
        Mat origin = cvarrToMat(iFrame);
        connerTest(vanpoints,origin,cnt++);
        cvWaitKey(1);
    }
    cvWaitKey(0);
}
