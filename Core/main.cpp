#include <fstream>
#include <dirent.h>
#include "main.h"
#include "CornerDetector/CornerCode.h"
#include "CornerDetector/Processing.h"


static int linesize = 30;
static int w1 =120;

int main() {
    calRenderingTime("/Users/codertimo/Desktop/Test2/");
    filelist("/Users/codertimo/Desktop/Test2/");
}

void processing_video(string fileurl, string name) {

    //Log 파일 write Initializing
    ofstream logfile;
    logfile.open (fileurl+"/result/"+name+".txt");

    //Video Input Initializing
    VideoCapture cap(fileurl+name);

    //Video Frame Loop
    while (1) {
        Mat origin,dst;
        if (!cap.read(origin)) break;

        resize(origin, dst, Size(origin.cols*0.2,origin.rows*0.2));

        //Houghline Weight 동적 조정
        houghline_stablization();

        //Houghline 으로 Line 검출 및 분류
        ResultLines resultLines = lineDetection(dst,w1,0);

        //1. 코너 검출
        int code = cornerDetection(dst,resultLines ,w1, 0);
        //2. 보도 이탈 검출

        //3. 점자 블록 검출?

        //Log 출력
        printToMat(code);
        imshow("origin",dst);
        logfile << code;
        cvWaitKey(1);
    }

    //Log, Video File Close
    logfile.close();
    cap.release();
}
double getVideoTime(string filename) {
    //Video Input Initializing
    VideoCapture cap(filename);
    return cap.get(CV_CAP_PROP_FRAME_COUNT) * 0.38;
}
void houghline_stablization() {

    //line크기에 따른 HoughLine Weight값 조정
    if(linesize>20)
        w1 += 10;
    if(linesize > 50)
        w1 += 10;
    if(linesize<10)
        w1 -= 10;
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
                cout << dir_entry->d_name << " : start \n";
                processing_video(filedir, dir_entry->d_name);
        }
        closedir(dir_info);
    }
}
void calRenderingTime(string filedir) {
    DIR            *dir_info;
    struct dirent  *dir_entry;
    dir_info = opendir(filedir.c_str());              // 현재 디렉토리를 열기
    double total_time;
    if ( NULL != dir_info)
    {

        while( dir_entry   = readdir( dir_info))  // 디렉토리 안에 있는 모든 파일과 디렉토리 출력
        {
                total_time += getVideoTime(filedir + dir_entry->d_name);
        }
        closedir(dir_info);
    }
    cout << "예상 랜더링 소요 시간 :"<<(int)total_time/60<<"분 "<< ((int)total_time)%60 <<"초 입니다";
}
