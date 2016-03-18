//
// Created by 김준성 on 2016. 2. 26..
//

#include "cluster.h"

/**
 * [1단계 작업]
 * 이미지 RGB색상을 K-Mean 알고리즘을 이용해서 k개로 집단화시키는 작업
 * Parameter: 기본 RGB이미지
 * return : hsv타입 Mat
 */
Mat cluster(Mat img)
{
    Mat res, points, labels, centers;
    int width, height, x, y, n, nPoints, cIndex, iTemp;
    const int k = ClusterK;

    // 이미지 정보 파악
    width = img.cols, height = img.rows;
    nPoints = width * height;

    // 초기화
    points.create(nPoints, 1, CV_32FC3);        // 입력 데이터
    centers.create(k, 1, points.type());        // k개의 mean 결과값들
    res.create(height, width, img.type());      // 결과 영상

    // kmeans 함수에 맞게 데이터 변환
    for(y = 0, n = 0; y < height; y++)
    {
        for(x = 0; x < width; x++, n++)
        {
            points.at<Vec3f>(n)[0] = img.at<Vec3b>(y, x)[0];
            points.at<Vec3f>(n)[1] = img.at<Vec3b>(y, x)[1];
            points.at<Vec3f>(n)[2] = img.at<Vec3b>(y, x)[2];
        }
    }

    // k-means clustering
    kmeans(points, k, labels, TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0),
           3, KMEANS_PP_CENTERS, centers);


    //클러스팅 결과를 hsv타입 Mat에 적용시키는 작업

    Mat hsv;
    cvtColor(img,hsv,CV_RGB2HSV);
    for(y = 0, n = 0; y < height; y++)
    {
        for(x = 0; x < width; x++, n++)
        {
            cIndex = labels.at<int>(n);
            hsv.at<Vec3b>(Point(x,y))[0] = cIndex*(255/k);
            hsv.at<Vec3b>(Point(x,y))[1] = 0;
            hsv.at<Vec3b>(Point(x,y))[2] = 0;
        }
    }

    return hsv;
}




