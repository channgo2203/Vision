#pragma once
#include"../default.h"

class LineMap
{
	private:
		double dNowSlope;
		double dPrevSlope;
		vector<Vec4i> vLines;
		vector<Vec4i> vResLine;

	public:
		Mat smStack;
		LineMap();
		~LineMap();
		void accumulate_lines(ResultLines resLines);
		int escapeDetection();
		void setSmStack(Size);
};