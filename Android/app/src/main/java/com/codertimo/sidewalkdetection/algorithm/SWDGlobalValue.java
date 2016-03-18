package com.codertimo.sidewalkdetection.algorithm;

import com.codertimo.sidewalkdetection.algorithm.type.Vec4f;
import com.codertimo.sidewalkdetection.algorithm.type.Vec4i;

import org.opencv.core.Mat;
import org.opencv.core.Point;
import org.opencv.core.Size;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by codertimo on 2015. 12. 17..
 */
public class SWDGlobalValue {

    public static int frameCount = 1; //누적된 frame의 갯수
    public static  double currentSlopeAvg = 0.0; // 현재(30개 내의) 경향성의 평균 각도
    public static  double previousSlopeAvg = 0.0; // 이전(현재 측정중인 30개 이전) 평균 각도
    public static double currentSlope = 0.0;
    public static List<Point> slopeStack = new ArrayList<>();
    public static Size resolution = new Size(640,480);
    public static Mat inputMat;
}
