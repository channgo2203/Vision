//
// Created by 김준성 on 2016. 3. 4..
//
#include "ConerDetection.h"

int connerDetection(ResultLines *resultLines, Point vanPoint, Size image ,Size range, double k)
{

    resultLines->right_crosspoint = getCrossPoints(resultLines->roadlines,resultLines->conerlines_right,vanPoint,image,range);
    resultLines->left_crosspoint = getCrossPoints(resultLines->roadlines,resultLines->conerline_left,vanPoint,image,range);

    int normalCornerresult = nomalConner(resultLines,vanPoint);
    int verticalCornerresult = isVerticalConner(resultLines,vanPoint);

    //수직 조건 리턴
    if(normalCornerresult>0 && verticalCornerresult>0)
        return verticalCornerresult;

    //수직 조건 리턴
    if(verticalCornerresult>0 && normalCornerresult==0)
        return verticalCornerresult;

    //곡선 조건 리턴
    if(normalCornerresult>0 && verticalCornerresult ==0)
        return normalCornerresult;

    else
        return 0;
}

int nomalConner(ResultLines *resultLines, Point vanPoint)
{
    int isvanPoint =0;
    if(vanPoint.x!=0 && vanPoint.y!=0)
        isvanPoint = 100;

    bool road_right_bigger = resultLines->roadlines_right.size() > resultLines->roadlines_left.size()*1.5;
    bool road_left_bigger = resultLines->roadlines_left.size() > resultLines->roadlines_right.size()*1.5;
    bool conner_line_bigger = resultLines->roadlines.size() < resultLines->connerlines.size();
    bool conner_right_bigger = resultLines->conerlines_right.size() > resultLines->conerline_left.size()*1.5;
    bool conner_left_bigger = resultLines->conerline_left.size() > resultLines->conerlines_right.size()*1.5;

    if(conner_line_bigger)
    {
        if(road_left_bigger && conner_left_bigger)
        {
            //오른쪽을 향하는 방향성이 더 큰경우
//            cout << "보도의 왼쪽 방향성이 더 강합니다"<< endl;
            return isvanPoint+11;
        }

        else if(road_right_bigger && conner_right_bigger)
        {
            //왼쪽을 향하는 방향성이 더 큰경우
//            cout << "보도의 오른쪽 방향성이 더 강합니다"<< endl;
            return isvanPoint+12;
        }

        else
        {
            //아무것도 아닌 경우
            return isvanPoint+0;
        }
    }
    else{
        return isvanPoint+0;
    }
}

int isVerticalConner(ResultLines *resultLines, Point vanPoint) {

    int isvanPoint =0;
    if(vanPoint.x!=0 && vanPoint.y!=0)
        isvanPoint = 100;

    bool right_corner = resultLines->roadlines_left.size() > resultLines->roadlines_right.size() * 2;
    bool left_corner = resultLines->roadlines_right.size() > resultLines->roadlines_left.size() * 2;
    bool vertical_Conner =
            (resultLines->roadlines.size() == 0 || resultLines->roadlines.size() < resultLines->horizenLines.size()) &&
            vanPoint.x == 0 && vanPoint.y == 0;

    if (vertical_Conner) {
        if (right_corner) {
//            cout << "오른쪽의 수직 코너 발생" << endl;
            return isvanPoint+21;
        }
        else if (left_corner) {
//            cout << "왼쪽의 수직 코너 발생" << endl;
            return isvanPoint+22;
        }
        else {
//            cout << "수직 코너 발생" << endl;
            return isvanPoint+20;
        }
    }
    return 0;
}

vector<Point> getCrossPoints(vector<Vec4i> roadlines, vector<Vec4i> otherlines, Point vanPoint, Size image, Size range)
{
    vector<Point> cross_points;

    for(Vec4i roadLine:roadlines)
    {
        for(Vec4i otherLine:otherlines)
        {
            int x1 = roadLine[0]; int y1 = roadLine[1];
            int x2 = roadLine[2]; int y2 = roadLine[3];

            int x3 = otherLine[0]; int y3 = otherLine[1];
            int x4 = otherLine[2]; int y4 = otherLine[3];

            Point point;
            point.x = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
            point.y = ((x1*y2-y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));

            if(image.width>point.x && point.x >0 && image.height>point.y && point.y>0)
                cross_points.push_back(point);
        }
    }

    int x1 = vanPoint.x - range.width/2; int x2= vanPoint.x + range.width/2;
    int y1 = vanPoint.y - range.height/2; int y2 = vanPoint.y + range.height/2;

    vector<Point> rangePoint;

    for(Point point :cross_points)
    {
        if(point.x>=x1 && point.x<=x2 && point.y>=y1 && point.y<=y2)
        {
            rangePoint.push_back(point);
        }
    }

    return rangePoint;
}

Point vanishingPointDetection(ResultLines resultLines, Size image)
{
    vector<Point> cross_points;
    int avg_x=0,avg_y=0;
    for(Vec4i line1:resultLines.roadlines_right)
    {
        for(Vec4i line2:resultLines.roadlines_left)
        {

            int x1 = line1[0]; int y1 = line1[1];
            int x2 = line1[2]; int y2 = line1[3];

            int x3 = line2[0]; int y3 = line2[1];
            int x4 = line2[2]; int y4 = line2[3];

            if(((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)) ==0)
                continue;

            Point point;
            point.x = (((x1*y2-y1*x2)*(x3-x4)) - ((x1-x2)*(x3*y4-y3*x4)))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
            point.y = (((x1*y2-y1*x2)*(y3-y4)) - ((y1-y2)*(x3*y4-y3*x4)))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));

            if(image.width>point.x && point.x >0 && image.height>point.y && point.y>0){
                avg_x+=point.x; avg_y+=point.y;
                cross_points.push_back(point);
            }
        }
    }

    if(cross_points.size()==0)
        return Point(0,0);

    Point point = Point(avg_x/cross_points.size(),avg_y/cross_points.size());

    return point;
}