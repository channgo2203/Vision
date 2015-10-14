#include"header.h"
#include"CompareableLine.h"
#include"LineMap.h"

void sendProc(int);
void sendProc(int iAngleProtocol) {
	printf("%d\n", iAngleProtocol);
}

int main() {
	CvCapture*  cvCapture = cvCreateFileCapture("C:\\Users\\dongmin\\OneDrive\\Pictures\\Camera Roll\\20150621_194350.mp4");
	IplImage* iFrame;
	if (cvCapture == nullptr) throw("file error!");
	char c;
	Mat mImg;
	
	while (1) {
		iFrame = cvQueryFrame(cvCapture);
		if (!iFrame) break;
		mImg = cvarrToMat(iFrame);
		LineMap frame(mImg);
		frame.calLine();	
		frame.drawLine();
		frame.compareCurrent(frame.getCurrentLine(frame.getLineMap()));
		c = cvWaitKey();
		if (c == 27) break;
	}

	return 0;
}