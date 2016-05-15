package com.github.codertimo.walkingassistance;
import android.app.Activity;
import android.os.Bundle;
import android.speech.tts.TextToSpeech;
import android.util.Log;
import android.view.SurfaceView;
import android.widget.TextView;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.Mat;
import java.util.Locale;

public class MainActivity extends Activity implements CameraBridgeViewBase.CvCameraViewListener2,TextToSpeech.OnInitListener{

    public native int cornerDetection(long matAddr);

    static {
        System.loadLibrary("opencv_java3");
    }

    private Mat mRgba;
    private CameraBridgeViewBase mOpenCvCameraView;
    private TextToSpeech textToSpeech;
    private TextView escape_textview;
    private TextView corner_textview;
    int pre_cornerDetection_code;
    int pre_escapeDetection_code;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        layout_initialize();
    }
    public Mat onCameraFrame(CameraBridgeViewBase.CvCameraViewFrame inputFrame) {

//      1. 입력영상 받아오기
        mRgba = inputFrame.gray();

//      2. 입력영상 RGB로 전환
        if (mRgba != null) {

            // 3. 결과값 받아오기 <NDK>
            int detection_code = cornerDetection(mRgba.getNativeObjAddr());

            int cornerDetection_code = detection_code/10;
            int escapeDetection_code = detection_code%10;


            //4. 결과값 출력 및 TTS
            if(detection_code>CornerCode.NOTHING) {
                pre_cornerDetection_code = cornerDetection_code;
                pre_escapeDetection_code = escapeDetection_code;
                printText();
                speechCode(cornerDetection_code);
            }
        }

        //5. Layout_Camera View 에 Mat 를 넘겨줌
        return mRgba;
    }

    private BaseLoaderCallback mLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS:
                {
                    Log.i("SWD", "OpenCV loaded successfully");
                    System.loadLibrary("native");// Load Native module
                    mOpenCvCameraView.enableView();
                } break;
                default:
                {
                    super.onManagerConnected(status);
                } break;
            }
        }
    };
    private void layout_initialize() {

        corner_textview = (TextView)findViewById(R.id.corner_textview);
        escape_textview = (TextView)findViewById(R.id.escape_textview);

        mOpenCvCameraView = (CameraBridgeViewBase)
                findViewById(R.id.activity_surface_view);
        mOpenCvCameraView.setVisibility(SurfaceView.VISIBLE);
        mOpenCvCameraView.setCvCameraViewListener(this);
        mLoaderCallback.onManagerConnected(LoaderCallbackInterface.SUCCESS);

        textToSpeech = new TextToSpeech(this, this);

        Log.i("SWD", "Layout Initialize Complete");
    }
    public void onPause() {
        super.onPause();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }
    public void onResume() {
        super.onResume();
        if (!OpenCVLoader.initDebug()) {
            Log.d("SWD", "Internal OpenCV library not found.");
            OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_3_1_0, this,
                    mLoaderCallback);
        } else {
            Log.d("SWD", "OpenCV library found inside package. Using it!");
            mLoaderCallback.onManagerConnected(LoaderCallbackInterface.SUCCESS);
        }
    }
    public void onCameraViewStarted(int width, int height) {
        //do nothing
    }
    public void onCameraViewStopped() {
        //do nothing
    }
    public void onInit(int status) {
        textToSpeech.setLanguage(Locale.KOREA);
    }
    private void speechCode(int code) {
        textToSpeech.speak(CornerCode.codeToKoreanString(code) + "가 있습니다", TextToSpeech.QUEUE_FLUSH, null);
    }
    private void printText() {

        Log.i("SWD", "CornerCode :"+CornerCode.codeToString(pre_cornerDetection_code)+" EscapedCode :"+EscapeCode.toString(pre_escapeDetection_code));

        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                escape_textview.setText(EscapeCode.toString(pre_escapeDetection_code));
                corner_textview.setText(CornerCode.codeToString(pre_cornerDetection_code));
            }
        });
    }
}
