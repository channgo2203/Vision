#include"header.h"
#include"CompareableLine.h"
#include"LineMap.h"

void sendProc(int);
void sendProc(int iAngleProtocol) {
	printf("receive : %d\n", iAngleProtocol);
}

int main() {
	CvCapture*  cvCapture = cvCreateFileCapture("C:\\Users\\dongmin\\OneDrive\\Pictures\\Camera Roll\\20150621_194350.mp4");
	IplImage* iFrame;
	if (cvCapture == nullptr) throw("file error!");
	char c;
	Mat mImg, mRaw;
	LineMap::setSmStack(Size(600,400));
	LineMap *frame;
	while (1) {
		iFrame = cvQueryFrame(cvCapture);
		if (!iFrame) break;
		mRaw = cvarrToMat(iFrame);
		resize(mRaw, mImg, Size(600, 400));
		imshow("t", mImg);
		frame = new LineMap(mImg);
		frame->setLine();
		frame->compareCurrent();
		frame->sendProtocol();
		c = cvWaitKey(33);	
			
		if (c == 27) break;
	}

	return 0;
}