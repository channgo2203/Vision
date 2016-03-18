//
// Created by 김준성 on 2016. 3. 10..
//
#include "Processing.h"

void connerTest(char* string)
{
    Mat origin = imread(string);
    Mat vanpoints =Mat(1000,1000,CV_8UC1);
    imshow("original image",origin);
    connerTest(vanpoints,origin,0);
}
void connerTest(Mat vanpoints, Mat mat,int cnt)
{
    Mat origin = mat;
    while(origin.cols>600){
        resize(origin, origin, Size(origin.cols * 0.6, origin.rows * 0.6));
    }
    imshow("origin",origin);
//    ResultLines resultLines = colorDetection(origin, cnt);
    ResultLines resultLines = lineDetection(origin,origin);
    Point vanPoint = vanishingPointDetection(resultLines,origin.size());
    if(vanPoint.x!=0 && vanPoint.y!=0)
        circle( origin, vanPoint, 10, Scalar( 0, 0, 255 ),CV_FILLED);


    if(vanPoint.x!=0 && vanPoint.y!=0) {
//        circle(vanpoints, vanPoint, 4, Scalar(255), CV_FILLED);
        Point rect_p = Point(vanPoint.x - 50, vanPoint.y - 50);
        Rect rect = Rect(rect_p, Size(100, 100));
        rectangle(origin, rect, Scalar(255, 255, 100));

        for (Point point :resultLines.right_crosspoint) {
            circle(origin, point, 4, Scalar(0, 255, 0), CV_FILLED);
        }
        for (Point point:resultLines.left_crosspoint) {
            circle(origin, point, 4, Scalar(0, 0, 255), CV_FILLED);
        }
    }

    char file[100];
    sprintf(file,"/Users/codertimo/Desktop/ResearchTest/test2/%d_h.jpg",cnt);
    imwrite(file,origin);

    int conrerDetecionCode = connerDetection(&resultLines,vanPoint,origin.size(),Size(100,100),0.6);

    /// Font Face
    int myFontFace = 2;
    /// Font Scale
    double myFontScale = 1.2;

    if(conrerDetecionCode >0)
    {
        cout <<","<< 1;
    }
    else
        cout <<","<< 0;

    switch (conrerDetecionCode)
    {
        case 11:
//            cout << "no conner"<< endl;
            putText( origin,"round left corner", Point(20,origin.rows-10), myFontFace, myFontScale, Scalar(255,255,255));
            circle( vanpoints, Point(cnt,100), 3, Scalar(255),CV_FILLED);
            break;
        case 12:
//            cout << "right conner" << endl;
            putText( origin,"round right corner", Point(20,origin.rows-10), myFontFace, myFontScale, Scalar(255,255,255));
            circle( vanpoints, Point(cnt,100), 3,  Scalar(255),CV_FILLED);
            break;
        case 21:
            putText( origin,"vertical right corner", Point(20,origin.rows-10), myFontFace, myFontScale, Scalar(255,255,255));
            circle( vanpoints, Point(cnt,100), 3, Scalar(255),CV_FILLED);
//            cout << "left conner" << endl;
            break;
        case 22:
            putText( origin,"vertical left corner", Point(20,origin.rows-10), myFontFace, myFontScale, Scalar(255,255,255));
            circle( vanpoints, Point(cnt,100), 3,  Scalar(255),CV_FILLED);
            break;
        case 20:
            putText( origin,"vertical corner", Point(20,origin.rows-10), myFontFace, myFontScale, Scalar(255,255,255));
            circle( vanpoints, Point(cnt,100), 3, Scalar(255),CV_FILLED);
            break;
        case 0:
            putText( origin,"nothing", Point(20,origin.rows-10), myFontFace, myFontScale, Scalar(255,255,255));
            break;

    }

    imshow("Final",origin);
    imshow("coner",vanpoints);
    sprintf(file,"/Users/codertimo/Desktop/ResearchTest/test2/final/%d.jpg",cnt);
    imwrite(file,origin);

}

ResultLines colorDetection(Mat origin,int cnt)
{
    fastNlMeansDenoising(origin,origin,15);
    int height = origin.rows/3;
    int width = (int)origin.cols*0.4;
    Rect show = Rect(origin.cols/2-width/2,origin.rows-height,width,height);

    //1. RGB이미지를 CluseterK가지 색으로 집단화 및 hsv모델로 색칠
    Mat hsv = cluster(origin);
    //2. Roi 영역 설정
    Mat roi = setRoi(hsv);
    //3. roi내부에서 발견되는 색을 인덱싱함
    vector<ColorCount> colorCount = getRoiColor(roi);
    //4. 인덱싱된 색중 MaxColorCount갯수만큼을 1로 처리된 이진화 이미지를 가져옴
    Mat noise = convertToBinary(hsv,colorCount);
    //5. 이미지 denoise 작업
    Mat denoise;
    fastNlMeansDenoising(noise,denoise,150);
    imshow("Binary",denoise);
    //6.Canny Detection & 직선검출 및 직선 판별
    ResultLines resultLines = lineDetection(denoise,origin);

    char name[100];
    sprintf(name,"/Users/codertimo/Desktop/ResearchTest/test2/%d.jpg",cnt);
    imwrite(name,denoise);
    return resultLines;
}

//ResultLines houghlines(Mat origin,int cnt)

Mat setRoi(Mat mat)
{
    IplImage *iplImage   = new IplImage(mat);
    int height = mat.rows/3;
    int width = (int)mat.cols*0.4;
    Rect rect = Rect(mat.cols/2-width/2,mat.rows-height,width,height);
    cvSetImageROI(iplImage,rect);
    Mat roi = cvarrToMat(iplImage);
    Mat hsv;
    cvtColor(roi,hsv,CV_RGB2HSV);
    imshow("roi",roi);
    return roi;
}
