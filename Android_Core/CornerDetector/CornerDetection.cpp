//
// Created by 김준성 on 2016. 3. 4..
//
#include "CornerDetection.h"
#include "CornerCode.h"
#include "../default.h"

int cornerDetection2(LineCounts lineCounts)
{
    //직선들을 크기순으로 나열함
    lineCounts.sort();

    //수직 직선의 크기가 제일 크고 && 왼쪽 방향 직선이 2번째로 크며 && 왼쪽 방향직선 > 오른쪽 방향직선 x2
    if(lineCounts.rank[0]==VERTICAL && lineCounts.rank[1]==ROAD_LEFT && lineCounts.road_left>lineCounts.road_right*2)
        return RIGHT_VERTICAL;

    //수직 직선의 크기가 제일 크고 && 오른쪽 방향 직선이 2번째로 크며 && 오른쪽 방향직선 > 왼쪽 방향직선 x2
    if(lineCounts.rank[0]==VERTICAL && lineCounts.rank[1]==ROAD_RIGHT && lineCounts.road_right>lineCounts.road_left*2)
        return LEFT_VERTIVAL;

    //오른쪽 방향 직선이 제일 크고 && 두번째로 수직 직선이 제일 클때
    if(lineCounts.rank[0]==CORNER_RIGHT && lineCounts.rank[1]==VERTICAL)
        return RIGHT_ROUND;

    //왼쪽 방향 직선이 제일 크고 && 두번째로 수직 직선이 제일 클때
    if(lineCounts.rank[0]==CORNER_LEFT && lineCounts.rank[1]==VERTICAL)
        return LEFT_ROUND;

    //아무것도 해당되지 않을 때
    return NOTHING;
}