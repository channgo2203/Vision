#include "main.h"

int main()
{
    cout << "처리 시작" << endl;
    clock_t before;
    before= clock();
    walkTest();
//    connerTest("/Users/codertimo/Desktop/ResearchTest/t3.jpg");
    double time_check = (double)(clock() - before) / CLOCKS_PER_SEC;
    cvWaitKey(0);
    cout << "걸린시간은 " << time_check << "초 입니다.";
}
void walkTest()
{
    cvNamedWindow("Hello",CV_WINDOW_AUTOSIZE);
    CvCapture*  cvCapture = cvCreateFileCapture("/Users/codertimo/Desktop/ResearchTest/gym1.mp4");
    IplImage* iFrame;
    Mat vanpoints =Mat(1000,1000,CV_8UC1);
    int cnt=0;
    cout <<"[";
    while (1) {
        iFrame = cvQueryFrame(cvCapture);
        if (!iFrame) break;
        Mat origin = cvarrToMat(iFrame);
        connerTest(vanpoints,origin,cnt++);
//        imshow("van",vanpoints);
        cvWaitKey(1);
    }
    cout <<"]";
    cvWaitKey(0);
}
