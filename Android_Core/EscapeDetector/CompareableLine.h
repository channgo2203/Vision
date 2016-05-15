#pragma once
#include "../default.h"

class CompareableLine
{
private:
	int iLine_size;
	double dSlope;
	static double sdMapDegree;
	static double cdParameter_beta;
	Vec4i vPoint;
public:
	CompareableLine();
	CompareableLine(Vec4i);
	CompareableLine operator=(const CompareableLine&);
	~CompareableLine();
	
	Vec4i getPoint();
	int getLine_size();
	double getFunctionD(double);
	double getFunctionS(CompareableLine*);
	double getSlope();
	void static setNowDegree(double);
	void static setParam(double);
};