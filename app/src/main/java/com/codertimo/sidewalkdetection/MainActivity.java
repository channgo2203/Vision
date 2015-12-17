package com.codertimo.sidewalkdetection;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import com.codertimo.sidewalkdetection.algorithm.ComparableLine;
import com.codertimo.sidewalkdetection.algorithm.LineMap;
import com.codertimo.sidewalkdetection.algorithm.SWDGlobalValue;
import com.codertimo.sidewalkdetection.algorithm.SWDUtil;
import com.codertimo.sidewalkdetection.algorithm.Vec4i;

import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.Point;
import org.opencv.core.Scalar;

import java.util.List;


public class MainActivity extends AppCompatActivity {


    private LineMap frame = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    private void SWDProcess(Mat input)
    {
        //1. HoughLine 결과물을 적용함
        Mat houghLineResult = frame.getHoughLineResult(input);

        //2. 2개의 중요 직선을 검출하는 작업
        ComparableLine[] twoLine = frame.getTwoLine(houghLineResult);

        //3. 기울기 메트에 그리기
        Core.line(SWDGlobalValue.slopeStack, new Point(twoLine[0].point.x1, twoLine[0].point.y1), new Point(twoLine[0].point.x2, twoLine[0].point.y2), new Scalar(111), 3);
        Core.line(SWDGlobalValue.slopeStack, new Point(twoLine[1].point.x1, twoLine[1].point.y1), new Point(twoLine[1].point.x2, twoLine[1].point.y2), new Scalar(111), 3);

        //4.
        frame.compareCurrent();

    }


    void sendProtocal(int iAngleProtocol){
        if(iAngleProtocol == 0)
            Log.i("SWD","walking..");
        else
            Log.i("SWD","receive : "+iAngleProtocol);
    }


}
