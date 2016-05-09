#include <fstream>
#include <dirent.h>
#include "main.h"
#include "CornerDetector/default.h"
#include "CornerDetector/CornerCode.h"
#include "CornerDetector/Processing.h"

static int linesize = 30;
static int w1 =120;

int main() {
    filelist("/Users/codertimo/Desktop/Test2/");
}

void processing_video(string fileurl, string name)
{
    ofstream myfile;
    myfile.open (fileurl+"/result/"+name+".txt");

    CvCapture*  cvCapture = cvCreateFileCapture((fileurl+name).c_str());
    IplImage* iFrame;

    while (1) {
        iFrame = cvQueryFrame(cvCapture);
        if (!iFrame) break;

        Mat origin = cvarrToMat(iFrame);
        Mat dst;

        resize(origin, dst, Size(origin.cols*0.3,origin.rows*0.3));

        if(linesize>20)
            w1 += 10;
        if(linesize > 50)
            w1 += 10;

        if(linesize<10)
            w1 -= 10;

        int code = cornerDetection(dst,w1,0);

        printToMat(code);
        imshow("origin",dst);
        cout << code;
        myfile << code;
        cvWaitKey(1);
    }

    myfile.close();
    cvReleaseCapture(&cvCapture);
}

void printToMat(int code) {
    Mat result_mat = Mat::zeros(200,400,CV_8UC1);

    /// Font Face
    int myFontFace = 2;

    /// Font Scale
    double myFontScale = 1.2;

    string result;

    switch(code)
    {
        case RIGHT_VERTICAL:
            result = "Right_Vertical";
            break;

        case LEFT_VERTIVAL:
            result = "Left_Vertical";
            break;

        case UNKNWON_VERTICAL:
            result = "Unknown_Vertical";
            break;

        case RIGHT_ROUND:
            result = "Right_Round";
            break;

        case LEFT_ROUND:
            result = "Left_Round";
            break;

        case ROUND:
            result = "Round";
            break;

        case NOTHING:
            result = "Nothing";
            break;

    }

    cv::putText( result_mat , result, Point(50,50), myFontFace, myFontScale, Scalar::all(255) );

    imshow("result_Text",result_mat);
}
void setLineSize(int size) {
    linesize = size;
}
void filelist(string filedir) {
    DIR            *dir_info;
    struct dirent  *dir_entry;

    dir_info = opendir(filedir.c_str());              // 현재 디렉토리를 열기
    if ( NULL != dir_info)
    {
        while( dir_entry   = readdir( dir_info))  // 디렉토리 안에 있는 모든 파일과 디렉토리 출력
        {
            cout << dir_entry->d_name<<"\n";
            processing_video(filedir,dir_entry->d_name);
            cout << dir_entry->d_name << " finish"<<"\n";
        }
        closedir(dir_info);
    }
}
