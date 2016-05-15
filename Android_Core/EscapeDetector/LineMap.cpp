#include "LineMap.h"
#include"CompareableLine.h"


vector<Vec4i> CompareLines(vector<Vec4i> Lines, Size sz);
double calMapSlope(Mat resMap);

LineMap::LineMap(){}
LineMap::~LineMap(){
	vLines.clear();
	vResLine.clear();
}


void LineMap::setSmStack(Size sSize) {
	smStack = Mat(sSize, CV_8UC1, Scalar(0));
}

void LineMap::accumulate_lines(ResultLines resLines) {

	if (resLines.allLines.size() < 2) return ;

	vResLine = CompareLines(resLines.allLines,Size(600,400));
	for (int i = 0; i < 2; i++) line(smStack, Point(vResLine[i][0], vResLine[i][1]), Point(vResLine[i][2], vResLine[i][3]), Scalar(111), 3, 8);
	
	dNowSlope += (CompareableLine(vResLine[0]).getSlope() + CompareableLine(vResLine[1]).getSlope()) / 2 * 180.0 / CV_PI;
	
	vResLine.clear();

}

int LineMap::escapeDetection() {

	//코너 검출 코드
	if (abs(dPrevSlope - dNowSlope / 40) > 40) return 2;

	//이탈 가능성
	else if (abs(dPrevSlope - dNowSlope / 40) > 30) return 1;

	setSmStack(Size(600, 400));
	smStack = Scalar(0);
	dPrevSlope = dNowSlope / 40;
	dNowSlope = 0;

	return 0;
}

Mat LineMap::smStack;