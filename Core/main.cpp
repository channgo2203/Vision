
#include "main.h"
#include "Loging/Loging.h"
#include "CornerDetector/CornerDetection.h"
#include "LineDetector/line.h"

#include <time.h>

static int linesize = 30;
static int w1 =120;
static int frame_count =1;
static LineCounts linecounts;

/**
 * Mac환경에서 사용가능하도록 개발된 Main
 */
int main() {
    
    //Python Matplot 초기화
    loging_initalizing(); //윈도우 경우 주석처리
    
    //실제 처리 시작
    filelist("/Users/codertimo/Desktop/Test3/"); //윈도우 경우 주석처리

//    윈도우인경우 아래와 같은 방법으로 사용할것 - 아래 한줄로 사용가능 위에 나머지 전부 주석처리
//    processing_video("C://~~","test.avi");
}

/**
 * Mac 환경에서 사용가능하도록 개발된 함수
 */
void processing_video(string fileurl, string name) {

    cout << "--------------------------"<<endl;
    cout << name << " : start \n";

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

//        //Python Matplot Chart Linking
//        matplot_refreash(resultLines); //윈도우 경우 주석처리

        //Line 누적 <40Frame>
        linecounts.insert(resultLines);

        //40Frame에 한번 검사
        if(frame_count++%40==0)
        {
            //방향성 검출
            int direction_code = cornerDetection2(linecounts);

            //검출결과 출력
            cout << "Time : "<<to_string((cap.get(CV_CAP_PROP_POS_MSEC)*0.001))<<"  "; //이벤트가 발생된 시간
            direction_result_print(direction_code);

            //누적된 line들 초기화
            linecounts.clear();
        }

        //보도 이탈 검출
//        int escape_code = escape_detection(resultLines.roadlines);
    }

//    resultLineLoging(fileurl,name); //윈도우 경우 주석처리

//    plot_clear(); //윈도우 경우 주석처리
    cap.release();
}

int compact_main(Mat origin)
{
    Mat dst;

    resize(origin, dst, Size(origin.cols*0.3,origin.rows*0.3));

    //Houghline Weight 동적 조정
    houghline_stablization();

    //Houghline 으로 Line 검출 및 분류
    ResultLines resultLines = lineDetection(dst,w1,0);

    //Line 누적 <40Frame>
    linecounts.insert(resultLines);

    //40Frame에 한번 검사
    if(frame_count++%40==0)
    {
        //방향성 검출
        int direction_code = cornerDetection2(linecounts);

        //누적된 line들 초기화
        linecounts.clear();

        //검출결과 반환
        return direction_code;
    }

//    보도 이탈 검출
//        int escape_code = escape_detection(resultLines.roadlines);
    return NOTHING;
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
                processing_video(filedir, dir_entry->d_name);
        }
        closedir(dir_info);
    }
}
