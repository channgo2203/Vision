//
// Created by 김준성 on 2016. 5. 11..
//

#include "ResultLines.h"

void LineCounts::sort() {
    vector<pair<int,int>> size;

    size.push_back(make_pair(corner_right,CORNER_RIGHT));
    size.push_back(make_pair(corner_left,CORNER_LEFT));
    size.push_back(make_pair(road_right,ROAD_RIGHT));
    size.push_back(make_pair(road_left,ROAD_LEFT));
    size.push_back(make_pair(vertical,VERTICAL));

    struct sort_pred {
        bool operator()(const std::pair<int,int> &left, const std::pair<int,int> &right) {
            return left.first > right.first;
        }
    };

    std::sort(size.begin(), size.end(), sort_pred());

    for(int i=0;i<5;i++) {
        cout << size[i].first<<" ";
        rank[i] = size[i].second;
    }
}
void LineCounts::clear() {
    road_right=0;
    road_left=0;
    corner_right=0;
    corner_left=0;
    vertical=0;
}
void LineCounts::insert(ResultLines resultLines) {

    road_right+=resultLines.roadlines_right.size();
    road_left+=resultLines.roadlines_left.size();
    corner_right+=resultLines.conerlines_right.size();
    corner_left+=resultLines.conerline_left.size();
    vertical+=resultLines.verticalLines.size();
}


