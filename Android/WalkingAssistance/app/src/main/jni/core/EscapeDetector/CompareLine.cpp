#include "LineMap.h"
#include "CompareableLine.h"

double calMapSlope(Mat resMap) {
	std::vector<Point> vPoint;
	Vec4f vCurrentLine;

	for (int y = 0; y < resMap.size().height; y++) {
		uchar* ptr = resMap.ptr<uchar>(y);
		for (int x = 0; x < resMap.size().width; x++)
			if (ptr[x] != 0) vPoint.push_back(Point(x, y));
	}

	fitLine(Mat(vPoint), vCurrentLine, CV_DIST_L2, 0, 0.01, 0.01);

	vPoint.clear();
	return (double)vCurrentLine[3]/vCurrentLine[2];
}
vector<Vec4i> CompareLines(vector<Vec4i> Lines, Size sz){
	vector<CompareableLine*> cLineList;
	int n = Lines.size();

	for (size_t i = 0; i < n; i++) cLineList.push_back(new CompareableLine(Lines[i]));
	
	Mat tmp(sz, CV_32FC1);
	for (size_t i = 0; i < n; i++) line(tmp, Point(Lines[i][0], Lines[i][1]), Point(Lines[i][2], Lines[i][3]), Scalar(255));
	
	CompareableLine::setNowDegree(calMapSlope(tmp) * 180.0 / CV_PI);

	double Upper = 0, Lower = 0;
	double D, L, sD = 0, sL = 0;

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			sD += cLineList[i]->getFunctionD(cLineList[j]->getSlope());
			sL += pow(cLineList[i]->getLine_size() + cLineList[j]->getLine_size(), 2);
		}
	}

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			D = cLineList[i]->getFunctionD(cLineList[j]->getSlope());
			L = pow(cLineList[i]->getLine_size() + cLineList[j]->getLine_size(), 2);
			Upper += (sD - D * n * n)*(n*n*L - sL);
			Lower += pow(n*n*L - sL,2);
		}
	}
	
	double beta;

	if (Lower == 0) beta = 0;
	else beta = (double)Upper * 1e10 / (double)Lower;

	CompareableLine::setParam(beta);
	
	int px = 0, py = 1;
	int S_max = -1;
	
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			if (i!= j && cLineList[i]->getFunctionS(cLineList[j]) > S_max) {
				S_max = cLineList[i]->getFunctionS(cLineList[j]);
				px = i;
				py = j;
			}
		}
	}
	
	vector<Vec4i> vResLine;

	vResLine.push_back(cLineList[px]->getPoint());
	vResLine.push_back(cLineList[py]->getPoint());

	cLineList.clear();
	return vResLine;
}