package com.codertimo.sidewalkdetection.algorithm;

import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.Point;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by codertimo on 2015. 11. 2..
 */
public class SWDUtil {

    public static List<Vec4i> MatToVec4is (Mat lines)
    {
        List<Vec4i> vectors = new ArrayList<>();
        for(int x=0;x<lines.cols();x++)
        {
            double[] vec = lines.get(0,x);
            vectors.add(new Vec4i(vec));
        }
        return vectors;
    }

    public static List<Vec4f> MatToVec4f(Mat lines)
    {
        List<Vec4f> vectors = new ArrayList<>();
        for(int x=0;x<lines.cols();x++)
        {
            double[] vec = lines.get(0,x);
            vectors.add(new Vec4f(vec));
        }
        return vectors;
    }


    /**
     * 아래 3개 함수에서, 각각 객체들을 Mat로 변환해주는데
     * 올바르게 만든건지 확인좀
     */

    public static Mat Vec4fToMat(List<Vec4f> lines)
    {
        Mat mat = new Mat();
        mat.create(1,lines.size(), CvType.CV_8UC4);
        for(int x=0;x<lines.size();x++)
        {
            mat.put(0, x, lines.get(x).toArray());
        }
        return mat;
    }

    public static Mat Vec4iToMat(List<Vec4i> lines)
    {
        Mat mat = new Mat();
        mat.create(1,lines.size(), CvType.CV_8UC4);
        for(int x=0;x<lines.size();x++)
        {
            mat.put(0, x, lines.get(x).toArray());
        }
        return mat;
    }

    public static Mat PointsToMat(List<Point> lines)
    {
        Mat mat = new Mat();
        mat.create(1,lines.size(),CvType.CV_8UC1);
        //-------------------------------------//
        //List<Point> to Mat
        //------------------------------------//
        return mat;
    }

}
