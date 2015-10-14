#include "CompareableLine.h"

CompareableLine::CompareableLine() {}
CompareableLine::~CompareableLine() {}

CompareableLine::CompareableLine(Vec4i vPoint) {
	try {
		this->vPoint = vPoint;
		iLine_size = (int)pow(vPoint[0] - vPoint[2], 2) + (int)pow(vPoint[1] - vPoint[3], 2);
		if (vPoint[2] == vPoint[0]) throw Exception();
		dSlope = (double)(vPoint[3] - vPoint[1]) / (vPoint[2] - vPoint[0]);
	}
	catch (_exception e) {
		dSlope = 100;
		printf("%s", e.name);
	}
}

Vec4i CompareableLine::getPoint() {
	return vPoint;
}

int CompareableLine::getLine_size() {
	return iLine_size;
}

double CompareableLine::getFunctionS(CompareableLine* ll) {
	if (getFunctionD(dSlope) == 0) return 0x7fffffff-1;
	return cdParameter_beta*(pow(this->iLine_size + ll->getLine_size(),2) - sdAvgCubeLineSize) - getFunctionD(ll->dSlope); // represent loss function of line which involves probablity of loss.
}

double CompareableLine::getFunctionD(double dSlope) {
	if (sdDeniedMaxGap * this->dSlope < dSlope || sdDeniedMinGap * this->dSlope > dSlope) return sqrt(sdAvgCubeLineSize * abs(this->dSlope - dSlope));
	return 0;
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

CompareableLine CompareableLine::operator=(const CompareableLine& p) {
	return p;
}

double CompareableLine::sdAvgLineSize;
double CompareableLine::sdAvgCubeLineSize;