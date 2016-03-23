package com.github.codertimo.walkingassistance;

import android.app.Activity;
import android.os.Bundle;
import android.speech.tts.TextToSpeech;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.SurfaceView;
import android.widget.TextView;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import java.util.ArrayList;
import java.util.Locale;


public class MainActivity extends Activity implements CameraBridgeViewBase.CvCameraViewListener2,TextToSpeech.OnInitListener{

    TextView result_text;
    TextView result_code;
    TextView log;

    static {
        System.loadLibrary("opencv_java3");
    }

    public native int cornerDetection(long matAddr);

    private Mat mRgba;
    private CameraBridgeViewBase mOpenCvCameraView;
    private TextToSpeech textToSpeech;
    private ConnerDetector connerDetector = new ConnerDetector();
    private int previous_code =0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        result_text= (TextView)findViewById(R.id.detection_result);
        result_code = (TextView)findViewById(R.id.result);
        log = (TextView)findViewById(R.id.log);
        log.setMovementMethod(new ScrollingMovementMethod());
        mOpenCvCameraView = (CameraBridgeViewBase)
                findViewById(R.id.activity_surface_view);
        mOpenCvCameraView.setVisibility(SurfaceView.VISIBLE);
        mOpenCvCameraView.setCvCameraViewListener(this);
        mLoaderCallback.onManagerConnected(LoaderCallbackInterface.SUCCESS);

        textToSpeech = new TextToSpeech(this, this);
    }

    @Override
    public void onPause()
    {
        super.onPause();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }

    @Override
    public void onResume()
    {
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

    @Override
    public void onCameraViewStarted(int width, int height)
    {

    }

    @Override
    public void onCameraViewStopped()
    {

    }

    @Override
    public Mat onCameraFrame(CameraBridgeViewBase.CvCameraViewFrame inputFrame) {
        mRgba = inputFrame.rgba();
        Mat source = new Mat(mRgba.size(),CvType.CV_8UC3);;
        if (inputFrame.rgba() != null) {
            ArrayList<Mat> channels = new ArrayList<>();
            Core.split(mRgba, channels);
            channels.remove(3);
            Core.merge(channels, source);
            int result = cornerDetection(source.getNativeObjAddr());
            writeText(result);
            writeLog(result);
            cornerDetection(result);
        }
        return source;
    }

    @Override
    public void onInit(int status) {
        textToSpeech.setLanguage(Locale.KOREA);
    }

    public void writeText(final String string)
    {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                result_text.setText(string);

            }
        });
    }
    public void writeText(final int code)
    {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                result_code.setText(""+code);
            }
        });
    }

    public void writeLog(final int code)
    {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                log.append(code+"\n");
            }
        });
    }




    public void cornerDetection(int result)
    {
        boolean isvanPoint = result/100==1;
        int code = result%100;

        if(!connerDetector.isStart()) {
            connerDetector.checkCanIStart(isvanPoint);
        }
        else
        {
            code = connerDetector.checkFinalResult(code);

            if(previous_code>=20 && previous_code<30 && code==20)
            {
                code=previous_code;
            }
            previous_code=code;
            switch (code)
            {
                case 11:
//            "right corner"
                    textToSpeech.speak("오른쪽으로 휘어진 보도가 있습니다",TextToSpeech.QUEUE_FLUSH,null);
                    writeText("Round Right Corner");
                    break;
                case 12:
                    textToSpeech.speak("왼쪽으로 휘어진 보도가 있습니다",TextToSpeech.QUEUE_FLUSH,null);
                    writeText("Round Left Corner");
//            "left corner"
                    break;
                case 21:
                    textToSpeech.speak("오른쪽으로 코너가 있습니다",TextToSpeech.QUEUE_FLUSH,null);
                    writeText("Right Vertical Corner");
//            "vertical right corner"
                    break;
                case 22:
                    textToSpeech.speak("왼쪽으로 코너가 있습니다",TextToSpeech.QUEUE_FLUSH,null);
                    writeText("Left Vertical Corner");
//            "vertical left corner"
                    break;
                case 20:
                    textToSpeech.speak("전방에 코너가 있습니다",TextToSpeech.QUEUE_FLUSH,null);
                    writeText("Unknown Vertical Corner");
//            "vertical corner"
                    break;
                case 0:
                    writeText("Clear Road");
                    break;
            }
        }
        Log.i("SWD",""+result);
    }

}
