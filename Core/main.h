//
// Created by 김준성 on 2016. 5. 9..
//

#ifndef GOOGLESCIENCEFAIR_MAIN_H
#define GOOGLESCIENCEFAIR_MAIN_H

#include "CornerDetector/default.h"
#include "CornerDetector/CornerCode.h"
#include "EscapeDetector/EscapeDetection.h"





void processing_video(string filename, string onlyname);
void filelist(string filedir);

void setLineSize(int size);
void houghline_stablization();
double getVideoTime(string filename);
void calRenderingTime(string filedir);
void resultLineLoging(string fileurl, string filename);
void resultLine_update(ResultLines resultlines);


#endif //GOOGLESCIENCEFAIR_MAIN_H
