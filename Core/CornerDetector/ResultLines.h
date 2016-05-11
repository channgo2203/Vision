//
// Created by 김준성 on 2016. 5. 11..
//

#ifndef GOOGLESCIENCEFAIR_RESULTLINES_H
#define GOOGLESCIENCEFAIR_RESULTLINES_H

#include "default.h"

#define ROAD_RIGHT 1
#define ROAD_LEFT 2
#define CORNER_RIGHT 3
#define CORNER_LEFT 4
#define VERTICAL 5

typedef struct ResultLines{
    std::vector<cv::Point> right_crosspoint;
    std::vector<cv::Point> left_crosspoint;

    std::vector<cv::Vec4i> allLines;
    std::vector<cv::Vec4i> roadlines;
    std::vector<cv::Vec4i> otherlines;
    std::vector<cv::Vec4i> horizenLines;
    std::vector<cv::Vec4i> verticalLines;
    std::vector<cv::Vec4i> connerlines;

    std::vector<cv::Vec4i> roadlines_right;
    std::vector<cv::Vec4i> roadlines_left;

    std::vector<cv::Vec4i> conerlines_right;
    std::vector<cv::Vec4i> conerline_left;
}ResultLines;

class LineCounts{
public:
    int rank[5];

    int road_right;
    int road_left;
    int corner_right;
    int corner_left;
    int vertical;

    void clear();
    void sort();
    void insert(int,int,int,int,int);
    void insert(ResultLines);
};


#endif //GOOGLESCIENCEFAIR_RESULTLINES_H
