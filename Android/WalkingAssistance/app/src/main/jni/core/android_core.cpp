//
// Created by 김준성 on 2016. 5. 14..
//

#include "android_core.h"

static int linesize = 30;
static int w1 =120;
static int frame_count =1;
static LineCounts linecounts;
static clock_t begin_t;
static double avg_second = 0.0;
static bool isInitialized = false;

int mainDetection(Mat origin) {

    if(!isInitialized)
    {
        escapeDetection_initailize();
        isInitialized = true;
    }

    Mat dst; begin_t = clock();

    resize(origin, dst, Size(origin.cols*0.3,origin.rows*0.3));

    //Houghline Weight 동적 조정
    houghline_stablization_android();

    //Houghline 으로 Line 검출 및 분류
    ResultLines resultLines = lineDetection(dst,w1,0);

    //Line 누적 <40Frame>
    linecounts.insert(resultLines);
    escapeDetection_lineAccumulate(resultLines);

    //40Frame에 한번 검사
    if(frame_count++%20==0)
    {
        if(avg_second > 1.3)
        {
            avg_second=0.0;

            //방향성 검출
            int direction_code = cornerDetection2(linecounts);

            //보도 이탈 가능성 조사
            int escape_code = escapeDetection();

            //누적된 line들 초기화
            linecounts.clear();

            //검출결과 반환
            return direction_code*10 + escape_code;
        }
    }

    avg_second += ((double)(clock()-begin_t))/CLOCKS_PER_SEC;

    return NOTHING;
}

void houghline_stablization_android() {
    //line크기에 따른 HoughLine Weight값 조정
    if(linesize>20)
        w1 += 10;
    if(linesize > 50)
        w1 += 10;
    if(linesize<10 && w1>20)
        w1 -= 10;
}
void setLineSize(int size) {
    linesize = size;
}

