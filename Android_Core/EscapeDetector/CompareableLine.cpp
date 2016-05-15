#include "CompareableLine.h"

CompareableLine::CompareableLine() {}
CompareableLine::~CompareableLine() {}

CompareableLine::CompareableLine(Vec4i vPoint)
{
    this->vPoint = vPoint; // Constructing by inputing for Point;
    iLine_size = (int)pow(vPoint[0] - vPoint[2], 2) + (int)pow(vPoint[1] - vPoint[3], 2); // calculate line's size by taxi geometry
    if (vPoint[2] == vPoint[0]) dSlope = 90; // floating point Exception (Set angle 90)
    dSlope = atan(-1 * (double)(vPoint[3] - vPoint[1]) / (vPoint[2] - vPoint[0])) * 180.0 / CV_PI; // convert Radian to DMS
    if (dSlope < 0) dSlope += 180; // angle calculation only absolute value
    if (dSlope < 20) iLine_size = 100;
}

Vec4i CompareableLine::getPoint() {
    return vPoint; // return Point
}

int CompareableLine::getLine_size() {
    return iLine_size;
}

double CompareableLine::getFunctionS(CompareableLine* ll) {
    return cdParameter_beta*pow(this->iLine_size + ll->getLine_size(),2) + getFunctionD(ll->getSlope()); // represent loss function of line which involves probablity of loss.
}

double CompareableLine::getFunctionD(double dSlope) {
    return -1 * abs((atan((double)(this->dSlope))+ atan((double)dSlope)) * 180.0 / CV_PI / 2 - sdMapDegree); // Calculating function D
}

double CompareableLine::getSlope() {
    return dSlope;
}

CompareableLine CompareableLine::operator=(const CompareableLine& p) {
    return p;
}

void CompareableLine::setNowDegree(double dNowDegree) {
    sdMapDegree = dNowDegree;
}

void CompareableLine::setParam(double val)
{
    CompareableLine::cdParameter_beta = val;
}

double CompareableLine::sdMapDegree;
double CompareableLine::cdParameter_beta;