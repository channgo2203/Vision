
#include "main.h"
#include "Loging/Loging.h"
#include "CornerDetector/CornerDetection.h"
#include "LineDetector/line.h"

static int linesize = 30;
static int w1 =120;
static int frame_count =1;
static LineCounts linecounts;

int main() {
    
    //Python Matplot 초기화
    loging_initalizing();
    
    //랜더링 소요 시간 예상
    calRenderingTime("/Users/codertimo/Desktop/Test3/");
    
    //실제 처리 시작
    filelist("/Users/codertimo/Desktop/Test3/");
}

void processing_video(string fileurl, string name) {

    //Video Input Initializing
    VideoCapture cap(fileurl+name);

    //Video Frame Loop
    while (1) {
        Mat origin,dst;
        if (!cap.read(origin)) break;

        resize(origin, dst, Size(origin.cols*0.3,origin.rows*0.3));

        //Houghline Weight 동적 조정
        houghline_stablization();

        //Houghline 으로 Line 검출 및 분류
        ResultLines resultLines = lineDetection(dst,w1,0);

        //Python Matplot Chart Linking
        matplot_refreash(resultLines);

        //Line 누적 <40Frame>
        linecounts.insert(resultLines);

        //40Frame에 한번 검사
        if(frame_count++%40==0)
        {
            //방향성 검출
            int direction_code = cornerDetection2(linecounts);
            direction_result_print(direction_code);
            linecounts.clear();
        }

        //보도 이탈 검출
        int escape_code = escape_detection(resultLines.roadlines);

        //Line Draw된 Original Mat 출력
        imshow("origin",dst);

        cvWaitKey(1);
    }

    resultLineLoging(fileurl,name);
    plot_clear();
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
