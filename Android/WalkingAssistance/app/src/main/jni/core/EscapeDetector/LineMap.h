#pragma once
#include"../default.h"

class LineMap
{
	private:
		double dNowSlope;
		double dPrevSlope;
		vector<Vec4i> vLines;
		vector<Vec4i> vResLine;
		static Mat smStack;

	public:
		LineMap();
		~LineMap();
		void accumulate_lines(ResultLines resLines);
		int escapeDetection();
		void static setSmStack(Size);
};