//
// Created by 김준성 on 2016. 5. 9..
//

#ifndef GOOGLESCIENCEFAIR_MAIN_H
#define GOOGLESCIENCEFAIR_MAIN_H

#include "default.h"
#include "CornerDetector/CornerCode.h"
#include "EscapeDetector/EscapeDetection.h"
#include <math.h>





void processing_video(string filename, string onlyname);
void filelist(string filedir);

void setLineSize(int size);
void houghline_stablization();


#endif //GOOGLESCIENCEFAIR_MAIN_H
