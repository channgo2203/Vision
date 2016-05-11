//
// Created by 김준성 on 2016. 5. 10..
//

#include "EscapeDetection.h"

static Mat smStack(600,400,CV_8UC1);
static int iStackcount = 1;
static double dCurrentSlopeAvg, dPreviousSlopeAvg;

int escape_detection(vector<Vec4i> vLines) {

    int res = 0;
    Mat mContours, mLines;

    for (int i = 0; i < vLines.size(); i++)
        line(smStack, Point(vLines[i][0], vLines[i][1]), Point(vLines[i][2], vLines[i][3]), Scalar(255, 255, 255), 1);

    pair<int, Mat> Result;
    Result = compareCurrent(smStack);
    smStack = Result.second;

    return Result.first;
}
Vec4f calMapSlope(Mat resMap) {
    std::vector<Point> vPoint;
    Vec4f vCurrentLine;

    for (int y = 0; y < resMap.size().height; y++) {
        uchar* ptr = resMap.ptr<uchar>(y);
        for (int x = 0; x < resMap.size().width; x++)
            if (ptr[x] != 0) vPoint.push_back(Point(x, y));
    }

    fitLine(Mat(vPoint), vCurrentLine, CV_DIST_L2, 0, 0.01, 0.01);

    vPoint.clear();
    return vCurrentLine;
}
pair<int,Mat> compareCurrent(Mat smStack) {
//    imshow("smStack",smStack);
    int result_code = 0;
    Vec4f vCurrentLine = calMapSlope(smStack);
    double dTheta;

    if (vCurrentLine[2] == 0) dTheta = 90;
    else dTheta = -1 * atan(vCurrentLine[3] / vCurrentLine[2]) / CV_PI * 180.0;
    if (dTheta < 0) dTheta += 180;

    if (dCurrentSlopeAvg == 0) {
        dCurrentSlopeAvg = dTheta;
        dPreviousSlopeAvg = dCurrentSlopeAvg;
    }

    iStackcount++;

    if (iStackcount % 50 == 0) {
        smStack.create(Size(600, 400),CV_8UC1);
        smStack = Scalar(0);
        iStackcount = 0;
        dPreviousSlopeAvg = dCurrentSlopeAvg;
        dCurrentSlopeAvg = dTheta;
    }
    else if (abs(dPreviousSlopeAvg - dTheta) > 30) {
        waitKey();
        result_code = 1;
    }
    else if (abs(dPreviousSlopeAvg - dTheta) > 20) {
        result_code = 2;
    }
    else {
        dCurrentSlopeAvg *= iStackcount - 1;
        dCurrentSlopeAvg += dTheta;
        dCurrentSlopeAvg /= iStackcount;
    }

    return{ result_code,smStack };
}