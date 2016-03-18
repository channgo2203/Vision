package com.codertimo.sidewalkdetection.test;

import android.util.Log;

import com.codertimo.sidewalkdetection.algorithm.SWDGlobalValue;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.core.CvType;
import org.opencv.core.Mat;

/**
 * Created by codertimo on 2016. 2. 2..
 */
public class CameraStreaming {

    private CameraBridgeViewBase cameraView;
    public CameraBridgeViewBase.CvCameraViewListener2 listener;
//    private ProcessingTest processingTest = new ProcessingTest();
    VideoStreaming videoStreaming = new VideoStreaming("/storage/emulated/0/DCIM/Camera/VID_20160202_004834.mp4");
    long count = 0;

    public CameraStreaming(CameraBridgeViewBase cameraView)
    {
        this.cameraView = cameraView;
        this.listenerInit();
    }

    private void listenerInit()
    {
        listener = new CameraBridgeViewBase.CvCameraViewListener2() {
            @Override
            public void onCameraViewStarted(int width, int height) {

            }

            @Override
            public void onCameraViewStopped() {

            }

            @Override
            public Mat onCameraFrame(CameraBridgeViewBase.CvCameraViewFrame inputFrame) {

//                Mat input = inputFrame.rgba();
//                Log.i("SWD", CvType.typeToString(input.type()));
//                processingTest.SWDProcess(input);
                Log.i("SWD","Frame "+count);
                return videoStreaming.getVideoFrame(count++);
            }
        };
    }
}
