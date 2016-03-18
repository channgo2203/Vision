//
// Created by 김준성 on 2016. 2. 26..
//

#include "color.h"

/**
 * 기존의 hsv모델을 이진화된 8UC1타입의 Mat로 전환하는 과정
 * Parameter : hsv타입 Mat, 1값으로 변환시킬 hsv색 데이터 MaxColorCount개의 vector
 * return : 이진화된 이미지
 */
Mat convertToBinary(Mat src, vector<ColorCount> colors)
{
    Mat dst = Mat(src.rows,src.cols,CV_8UC1);

    for(int y=0; y<src.cols; y++)
    {
        for(int x=0; x<src.rows; x++)
        {
            if(isWhiteColor(colors,src.at<Vec3b>(Point(y,x))[0]))
            {
                dst.at<uchar>(x,y) = 255;
            }
            else
            {
                dst.at<uchar>(x,y) = 0;
            }
        }
    }
    return dst;
}

/**
 * 주어진 백터내에서 인자로 받은 color값이 존재하는지 판별
 * parameter : 가능한 색 값들, 검사하고자 하는 색 값
 * return : bool
*/
bool isWhiteColor(vector<ColorCount> colors, int color){
    for(int i=0;i<MaxColorCount;i++)
    {
        if(colors.at(i).color == color)
            return true;
    }
    return false;
}

/**
 * 지정된 roi내부의 hsv 색값 ClusterK개 추출
 * Parameter : Mat roi
 * return : 색 데이터와 검출된 빈도수에 대한 ColorCount vector
 */
vector<ColorCount> getRoiColor(Mat roi)
{
    vector<ColorCount> count;

    for(int i=0;i<ClusterK;i++)
    {
        ColorCount c;
        c.color=i*(255/ClusterK);
        c.count=0;
        count.push_back(c);
//        cout<<"color"<<count.at(i).color<<endl;
    }

    for(int y=0;y<roi.cols;y++)
    {
        for(int x=0;x<roi.rows;x++)
        {
            count.at((int)roi.at<Vec3b>(Point(y,x))[0]/(255/ClusterK)).count++;
        }
    }

    sort( count.begin(), count.end(), CompareObj ); // std::sort()

    vector<ColorCount> split_lo(count.begin(),count.begin()+MaxColorCount);
//    cout<<"/////////final color////////"<<endl;

    Mat color = Mat(MaxColorCount*100,100,CV_8UC3);
    Mat hsv;
    cvtColor(color,hsv,CV_RGB2HSV);

    for(int i=0;i<MaxColorCount;i++)
    {
        for(int y=0;y<100;y++)
        {
            for(int x=0+i*100;x<i*100+100;x++)
            {
                hsv.at<Vec3b>(Point(y,x))[0]=split_lo.at(i).color;
            }
        }
    }
    return split_lo;

}

//sort 함수인자인 비교함수
bool CompareObj(ColorCount first, ColorCount second)
{
    return first.count > second.count;
}