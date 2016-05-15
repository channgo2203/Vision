//
// Created by 김준성 on 2016. 5. 11..
//

#ifndef GOOGLESCIENCEFAIR_LOGING_H
#define GOOGLESCIENCEFAIR_LOGING_H

#include "../default.h"
#include "../CornerDetector/CornerCode.h"

#include <python2.7/python.h>

#include <fstream>
#include <dirent.h>

void plot();
void direction_result_print(int code);
void matplot_refreash(ResultLines lines);
void plot_clear();
void loging_initalizing();
string vector2String(vector<int> vec);





#endif //GOOGLESCIENCEFAIR_LOGING_H
