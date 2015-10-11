#include "LineMap.h"
#include "CompareableLine.h"
LineMap::LineMap(){}
LineMap::~LineMap(){}

LineMap::LineMap(Mat mImg) {
	this->mRawImg = mImg;
	this->dCurrentSlopeAvg = 0;
	this->iAngleProtocol = 0;
}

void LineMap::drawLine() {
	try {
		double dSlope[2], dYintercept[2];
		for (int i = 0; i < 2; i++) {
			dSlope[i] = (double)(vLines[0][1] - vLines[0][3]) / (vLines[0][0] - vLines[0][2]);
			dYintercept[i] = (double)(vLines[i][1] - dSlope[i] * vLines[i][0]);
			line(mLineMap, Point((int)(-1 * dYintercept[i] / dSlope[i]), 0), Point((int)((mRawImg.size().height - dYintercept[i]) / (dSlope[i])), mRawImg.size().height), Scalar(100, 100, 0));
		}
	}
	catch (Exception e) {
		line(mLineMap, Point(vLines[0][0], 0), Point(vLines[0][2], mRawImg.size().height), Scalar(100, 100, 0));
	}
}

void LineMap::calLine() {
	try {
		Mat mContours, mLines;
		Canny(mRawImg, mContours, 200, 350);
		vLines.clear();
		HoughLinesP(mContours, vLines, 1, CV_PI / 180, 50, 50, 10);
		compareLine();
	}
	catch (Exception e) {
		printf("%s", e.msg);
	}
}

void LineMap::compareCurrent(Vec4f vCurrentLine) {
	double dTheta = atan2(vCurrentLine[1], vCurrentLine[0]) / CV_PI * 180;
	if (dCurrentSlopeAvg == 0) {
		dCurrentSlopeAvg = dTheta;
		iStackcount = 1;
	}
	else if (abs(dCurrentSlopeAvg - dTheta) > 20) {
		callCornerExist();
		dCurrentSlopeAvg = dTheta;
		iStackcount = 1;
	}
	else if (abs(dCurrentSlopeAvg - dTheta) > 5) {
		callPedestrianOutofdirection();
		if (dTheta < 0)
			iAngleProtocol = (int)abs(dTheta - dCurrentSlopeAvg) / 5 + 5;
		else
			iAngleProtocol = (int)abs(dTheta - dCurrentSlopeAvg) / 5;
	}
	else {
		dCurrentSlopeAvg *= iStackcount++;
		dCurrentSlopeAvg += dTheta;
		dCurrentSlopeAvg /= iStackcount;
		iAngleProtocol = 0;
	}
}

void LineMap::sendProtocol() {
	sendProc(iAngleProtocol);
}

void LineMap::callCornerExist(){
	printf("There Exist in corner!\n");
}

void LineMap::callPedestrianOutofdirection() {
	printf("Pedestrian Out of direction!\n");
}

Vec4f LineMap::getCurrentLine(Mat resMap) {
	std::vector<Point> vPoint;
	Vec4f vCurrentLine;

	for (int y = 0; y < resMap.size().height; y++) {
		uchar* ptr = resMap.ptr<uchar>(y);
		for (int x = 0; x < resMap.size().width; x++)
			if (ptr[x] != 0) vPoint.push_back(Point(x, y));
	}

	fitLine(Mat(vPoint), vCurrentLine, CV_DIST_L2, 0, 0.01, 0.01);

	vPoint.clear();
	return vCurrentLine;
}

void LineMap::compareLine() {
	vector<CompareableLine> cLineList, ResLine;

	double dSumLineSize = 0, dSumCubeLineSize = 0;

	for (size_t i = 0; i < vLines.size(); i++) cLineList.push_back(CompareableLine(vLines[i]));
	
	for (size_t i = 0; i < vLines.size(); i++) {
		dSumLineSize += (double)cLineList[i].getLine_size();
		dSumCubeLineSize += pow(cLineList[i].getLine_size(), 2);
	}

	CompareableLine::setAvgLineSize(dSumLineSize / vLines.size());
	CompareableLine::setAvgCubeLineSize(dSumCubeLineSize / vLines.size());

	ResLine.push_back(cLineList[0]);
	ResLine.push_back(cLineList[1]);

	for (size_t i = 2; i < vLines.size(); i++) {
		cLineList[i].calParams();
		if (cLineList[i].getFunctionD(0) < max(ResLine[0].getFunctionD(cLineList[i].getSlope()), ResLine[1].getFunctionD(cLineList[i].getSlope())))
			ResLine[ResLine[0].getFunctionD(cLineList[i].getSlope()) < ResLine[1].getFunctionD(cLineList[i].getSlope())]
	}

	imshow("res", mLineMap);

	vResLine[0] = ResLine[0].getPoint();
	vResLine[1] = ResLine[1].getPoint();
}

Mat LineMap::getLineMap() {
	return mLineMap;
} 