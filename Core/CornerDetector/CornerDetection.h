//
// Created by 김준성 on 2016. 3. 4..
//

#ifndef SIDEWALKDETECTION_CONERDETECTION_H

#include "default.h"

int connerDetection(ResultLines *resultLines, Point vanPoint, Size image ,Size range, double k);
vector<Point> getCrossPoints(vector<Vec4i> roadlines, vector<Vec4i> otherlines, Point vanPoint, Size image, Size range);
Point vanishingPointDetection(ResultLines resultLines, Size image);
int nomalConner(ResultLines *resultLines, Point vanPoint);
int isVerticalConner(ResultLines *resultLines, Point vanPoint);

#endif //SIDEWALKDETECTION_CONERDETECTION_H
