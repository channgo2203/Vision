#pragma once
#include"header.h"
#include"CompareableLine.h"

class LineMap
{
private:
	int iStackcount;
	double dCurrentSlopeAvg;
	Mat mRawImg;
	Mat mLineMap;
	vector<Vec4i> vLines;
	vector<Vec4i> vResLine;
	int iAngleProtocol;
public:
	LineMap();
	~LineMap();
	LineMap(Mat);
	void drawLine();
	void calLine();
	void compareCurrent(Vec4f);
	Vec4f getCurrentLine(Mat);
	void sendProtocol();
	void callCornerExist();
	void callPedestrianOutofdirection();
	void compareLine();
	Mat getLineMap();
};