package com.github.codertimo.walkingassistance;
import android.app.Activity;
import android.os.Bundle;
import android.speech.tts.TextToSpeech;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.SurfaceView;
import android.view.View;
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

    public native int cornerDetection(long matAddr,int w1,int w2);

    static {
        System.loadLibrary("opencv_java3");
    }

    TextView result_text;
    TextView result_code;
    TextView log;
    TextView w1_textview;
    TextView w2_textview;

    private Mat mRgba;
    private CameraBridgeViewBase mOpenCvCameraView;
    private TextToSpeech textToSpeech;
    private CornerDetector cornerDetector = new CornerDetector();

    private int previous_code =0;

    public static int w1 = 80;
    public static int w2 = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        layout_initialize();
    }


    public Mat onCameraFrame(CameraBridgeViewBase.CvCameraViewFrame inputFrame) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                w1_textview.setText("" + w1);
                w2_textview.setText("" + w2);

            }
        });

//      1. 입력영상 받아오기
        mRgba = inputFrame.rgba();
        Mat source = new Mat(mRgba.size(),CvType.CV_8UC3);;

//      2. 입력영상 RGB로 전환
        if (inputFrame.rgba() != null) {
            ArrayList<Mat> channels = new ArrayList<>();
            Core.split(mRgba, channels);
            channels.remove(3);
            Core.merge(channels, source);

            // 3. 결과값 받아오기 <NDK>
            int result = cornerDetection(source.getNativeObjAddr(),w1,w2);

            //4. 로그 출력
            writeText(result);
            writeLog(result);

            //5. 결과값 가공 및 TTS
            outputProcessing(result);
        }

        //5. Layout_Camera View 에 Mat 를 넘겨줌
        return source;
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

        w1_textview = (TextView)findViewById(R.id.w1);
        w2_textview = (TextView)findViewById(R.id.w2);
        Log.i("SWD","Layout Initialize Complete");
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
    public void writeText(final String string) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                result_text.setText(string);

            }
        });
    }
    public void writeText(final int code) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                result_code.setText(""+code);
            }
        });
    }
    public void writeLog(final int code) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                log.append(code + "\n");
            }
        });
    }
    public void outputProcessing(int result) {

        boolean isvanPoint = result/100==1;

        int code = result%100;

        if(!cornerDetector.isStart()) {
            cornerDetector.checkCanIStart(isvanPoint);
        }
        else
        {
            code = cornerDetector.getFinalCode(code);

            if(previous_code >= CornerDetector.RIGHT_ROUND_CORNER && previous_code <= CornerDetector.LEFT_VERTICAL_CORNER)
            {
                code=previous_code;
            }

            previous_code=code;

            switch (code)
            {
                case CornerDetector.RIGHT_ROUND_CORNER:
                    textToSpeech.speak("오른쪽으로 휘어진 보도가 있습니다",TextToSpeech.QUEUE_FLUSH,null);
                    writeText("Round Right Corner");
                    break;

                case CornerDetector.LEFT_ROUND_CORNER:
                    textToSpeech.speak("왼쪽으로 휘어진 보도가 있습니다",TextToSpeech.QUEUE_FLUSH,null);
                    writeText("Round Left Corner");
                    break;

                case CornerDetector.RIGHT_VERTICAL_CORNER:
                    textToSpeech.speak("오른쪽으로 코너가 있습니다",TextToSpeech.QUEUE_FLUSH,null);
                    writeText("Right Vertical Corner");
                    break;

                case CornerDetector.LEFT_VERTICAL_CORNER:
                    textToSpeech.speak("왼쪽으로 코너가 있습니다",TextToSpeech.QUEUE_FLUSH,null);
                    writeText("Left Vertical Corner");
                    break;

                case CornerDetector.UNKNOWN_VERTICAL_CORNER:
                    textToSpeech.speak("전방에 코너가 있습니다",TextToSpeech.QUEUE_FLUSH,null);
                    writeText("Unknown Vertical Corner");
                    break;

                case CornerDetector.NOTHING:
                    writeText("Clear Road");
                    break;
            }
        }
        Log.i("SWD", "" + result);
    }

    public void onW1UpClicked(View view){w1+=10;}
    public void onW2UpClicked(View view){w2+=5;}
    public void onW1DownClicked(View view){w1-=10;}
    public void onW2DownClicked(View view){
        if(w2>=5)
            w2-=5;
    }

}
