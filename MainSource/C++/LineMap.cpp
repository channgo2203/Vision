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
			if (vResLine[i][0] == vResLine[i][2]) throw Exception();
			dSlope[i] = (double)(vResLine[0][1] - vResLine[0][3]) / (vResLine[0][0] - vResLine[0][2]);
			dYintercept[i] = (double)(vResLine[i][1] - dSlope[i] * vResLine[i][0]);
			line(mRawImg, Point((int)(-1 * dYintercept[i] / dSlope[i]), 0), Point((int)((mRawImg.size().height - dYintercept[i]) / (dSlope[i])), mRawImg.size().height), Scalar(100, 100, 0),3,8);
		}
		imshow("test", mRawImg);
		}
	catch (Exception e) {
		line(mLineMap, Point(vLines[0][0], 0), Point(vLines[0][2], mRawImg.size().height), Scalar(100, 100, 0));
	}
}

void LineMap::calLine() {
	try {
		Mat mContours, mLines;
		Canny(mRawImg, mContours, 50, 200);
		vLines.clear();
		HoughLinesP(mContours, vLines, 1, CV_PI / 180, 50, 50, 10);
		for (int i = 0; i < vLines.size(); i++) 
//			line(mRawImg, Point(vLines[i][0], vLines[i][1]), Point(vLines[i][2], vLines[i][3]), Scalar(0, 255, 255), 1);
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
	CompareableLine* ResLine[2];
	vector<CompareableLine*> cLineList;

	double dSumLineSize = 0, dSumCubeLineSize = 0;
	for (size_t i = 0; i < vLines.size(); i++) cLineList.push_back(new CompareableLine(vLines[i]));
	
	for (size_t i = 0; i < vLines.size(); i++) {
		dSumLineSize += (double)cLineList[i]->getLine_size();
		dSumCubeLineSize += pow(cLineList[i]->getLine_size(), 2);
	}

	CompareableLine::setAvgLineSize(dSumLineSize / vLines.size());
	CompareableLine::setAvgCubeLineSize(dSumCubeLineSize / vLines.size());

	ResLine[0] = cLineList[0];
	ResLine[1] = cLineList[1];

	Vec4i b = ResLine[0]->getPoint();
	Vec4i c = ResLine[0]->getPoint();

	line(mRawImg, Point(b[0], b[1]), Point(b[2], b[3]), Scalar(0, 255, 255), 3);
	line(mRawImg, Point(c[0], c[1]), Point(c[2], c[3]), Scalar(0, 255, 255), 3);

	for (size_t i = 2; i < vLines.size(); i++) {
		cLineList[i]->calParams();
		printf("Compare with %d\n", i);
		printf("previous : %.1f\n", ResLine[0]->getFunctionS(ResLine[1]));
		printf("i with 0 : %.1f\n", ResLine[0]->getFunctionS(ResLine[i]));
		printf("i with 1 : %.1f\n", ResLine[1]->getFunctionS(ResLine[i]));
		printf("%.1f %.1f %.1f\n", ResLine[0]->getSlope(),ResLine[1]->getSlope(),cLineList[i]->getSlope());

		Vec4i a = cLineList[i]->getPoint();
		line(mRawImg, Point(a[0], a[1]), Point(a[2], a[3]), Scalar(111, 111, 111),3);
		imshow("test", mRawImg);
		char cc = waitKey();
		if (cc == 27) break;
		if (ResLine[0]->getFunctionS(ResLine[1]) > min(cLineList[i]->getFunctionS(ResLine[0]), cLineList[i]->getFunctionS(ResLine[1]))) { // if the line's loss function is larger in case of change occur
			bool flag = (cLineList[i]->getFunctionS(ResLine[0]) > cLineList[i]->getFunctionS(ResLine[1])); // show the larger index (As we want less value of loss func)
			ResLine[flag] = cLineList[i];
		}
	}

	vResLine.push_back(ResLine[0]->getPoint());
	vResLine.push_back(ResLine[1]->getPoint());
	
	if (1) {
		Vec4i p1 = ResLine[0]->getPoint();
		Vec4i p2 = ResLine[1]->getPoint();

		circle(mRawImg, Point(p1[0], p1[1]), 3, Scalar(100, 100, 100), 3);
		circle(mRawImg, Point(p2[0], p2[1]), 3, Scalar(100, 100, 100), 3);
		circle(mRawImg, Point(p1[2], p1[3]), 3, Scalar(100, 100, 100), 3);
		circle(mRawImg, Point(p2[2], p2[3]), 3, Scalar(100, 100, 100), 3);
	
		printf("slope : %.1f %.1f\n", ResLine[0]->getSlope(), ResLine[1]->getSlope());
		printf("point : (%d, %d) : (%d,%d)\t(%d,%d):(%d,%d)\n", p1[0], p1[1], p1[2], p1[3], p2[0], p2[1], p2[2], p2[3]);
		printf("%.1f\n", ResLine[0]->getFunctionS(ResLine[1]));
		printf("%.1f\n", ResLine[0]->getFunctionD(ResLine[1]->getSlope()));
	}
}

Mat LineMap::getLineMap() {
	return mLineMap;
} 