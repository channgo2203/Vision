package com.codertimo.sidewalkdetection.test;

import android.util.Log;

import com.codertimo.sidewalkdetection.algorithm.SWDGlobalValue;
import com.codertimo.sidewalkdetection.algorithm.SWDProcessor;
import com.codertimo.sidewalkdetection.algorithm.type.ComparableLine;

import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.Point;
import org.opencv.core.Scalar;
import org.opencv.highgui.Highgui;

/**
 * Created by codertimo on 2016. 2. 1..
 */
public class ProcessingTest
{

    private SWDProcessor processer = new SWDProcessor();
    private VideoStreaming videoStreaming;

    public ProcessingTest()
    {
//        this.videoStreaming = new VideoStreaming("/storage/emulated/0/DCIM/Camera/VID_20160202_004834.mp4");
//        Mat mat = videoStreaming.getVideoFrame(3000);
//        SWDGlobalValue.inputMat = mat;
////        Log.i("SWD",""+videoStreaming.duration);
    }

    public void SWDProcess(Mat input)
    {
        SWDGlobalValue.inputMat = input;
        //1. HoughLine 결과물을 적용함
        Mat houghLineResult = processer.getHoughLineResult(input);

        //2. 2개의 중요 직선을 검출하는 작업
        ComparableLine[] twoLine = processer.getTwoLine(houghLineResult);

        //3. 프래임마다 중요한 직선들을 저장하고 있음
        SWDGlobalValue.slopeStack.addAll(twoLine[0].point.drawLine());
        SWDGlobalValue.slopeStack.addAll(twoLine[1].point.drawLine());

        Core.line(SWDGlobalValue.inputMat, twoLine[0].point.toPoints().get(0), twoLine[0].point.toPoints().get(1), new Scalar(236, 93,87), 5);
        Core.line(SWDGlobalValue.inputMat, twoLine[1].point.toPoints().get(0), twoLine[1].point.toPoints().get(1), new Scalar(236, 93, 87), 5);

        //4. 현재 보행자가 어떤 상황인지 파악
        processer.compareCurrent();
    }


}
