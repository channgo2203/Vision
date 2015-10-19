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
	Mat mImg, mRaw;
			
	while (1) {
		iFrame = cvQueryFrame(cvCapture);
		if (!iFrame) break;
		mRaw = cvarrToMat(iFrame);
		resize(mRaw, mImg, Size(600, 400));
		cvWaitKey();
		LineMap::setSmStack(mImg.size());
		LineMap frame(mImg);
		frame.setLine();
		frame.compareCurrent();
		c = cvWaitKey(33);
		if (c == 27) break;
	}

	return 0;
}