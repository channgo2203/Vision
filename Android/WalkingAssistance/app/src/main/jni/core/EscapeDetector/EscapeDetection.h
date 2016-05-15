//
// Created by 김준성 on 2016. 5. 14..
//

#ifndef GOOGLESCIENCEFAIR_ESCAPEDETECTION_H
#define GOOGLESCIENCEFAIR_ESCAPEDETECTION_H

#include "../default.h"
#include "LineMap.h"

void escapeDetection_initailize();
void escapeDetection_lineAccumulate(ResultLines resultLines);
int escapeDetection();

#endif //GOOGLESCIENCEFAIR_ESCAPEDETECTION_H
