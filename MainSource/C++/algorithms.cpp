#include"header.h"
#include"CompareableLine.h"
#include"LineMap.h"

void sendProc(int);
void sendProc(int iAngleProtocol) {
	printf("%d\n", iAngleProtocol);
}

int main() {
	Mat img = imread("C:\\Users\\dongmin\\OneDrive\\Pictures\\yui-ponkan.jpg");
	LineMap frame = LineMap(img);
	
	frame.calLine();
	frame.drawLine();
	frame.compareCurrent(frame.getCurrentLine(frame.getLineMap()));
	cvNamedWindow("test");
	imshow("test", img);
	cvWaitKey();

	return 0;
}