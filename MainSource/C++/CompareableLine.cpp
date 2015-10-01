#include "CompareableLine.h"

CompareableLine::CompareableLine() {}
CompareableLine::~CompareableLine() {}

CompareableLine::CompareableLine(Vec4i vPoint) {
	try {
		this->vPoint = vPoint;
		iLine_size = (int)pow(vPoint[0] - vPoint[2], 2) + (int)pow(vPoint[1] - vPoint[3], 2);
		dSlope = (vPoint[3] - vPoint[1]) / (vPoint[2] - vPoint[0]);
	}
	catch (_exception e) {
		printf("%s", e.name);
	}
}

Vec4i CompareableLine::getPoint() {
	return vPoint;
}

int CompareableLine::getLine_size() {
	return iLine_size;
}

double CompareableLine::getFunctionS(double dSlope) {
	return pow((cdParameter_beta*pow(this->iLine_size,2) + getFunctionD(this->dSlope)) - pow(cdParameter_beta*sdAvgCubeLineSize+getFunctionD(dSlope),2),2);
}

double CompareableLine::getFunctionD(double dSlope) {
	if (!dSlope || sdDeniedMaxGap * this->dSlope < dSlope || sdDeniedMinGap * this->dSlope > dSlope) return 0;
	return sqrt(sdAvgCubeLineSize * dSlope * cdParameter_beta);
}

bool CompareableLine::calParams() {
	return true;
}

double CompareableLine::getSlope() {
	return dSlope;
}

void CompareableLine::setAvgLineSize(double AvgLineSize) {
	sdAvgLineSize = AvgLineSize;
}

double CompareableLine::getAvgLineSize() {
	return sdAvgLineSize;
}

void CompareableLine::setAvgCubeLineSize(double AvgCubeLineSize) {
	sdAvgCubeLineSize = AvgCubeLineSize;
}

double CompareableLine::sdAvgLineSize;
double CompareableLine::sdAvgCubeLineSize;