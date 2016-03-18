//
// Created by 김준성 on 2016. 2. 26..
//

#ifndef SIDEWALKDETECTION_COLOR_H
#define SIDEWALKDETECTION_COLOR_H

#include "default.h"
#include "cluster.h"

vector<ColorCount> getRoiColor(Mat roi);
bool isWhiteColor(vector<ColorCount> colors, int color);
Mat convertToBinary(Mat src, vector<ColorCount> colors);
bool CompareObj(ColorCount first, ColorCount second);



#endif //SIDEWALKDETECTION_COLOR_H
