package com.codertimo.sidewalkdetection.algorithm;

import com.codertimo.sidewalkdetection.algorithm.type.Vec4f;
import com.codertimo.sidewalkdetection.algorithm.type.Vec4i;

import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.Point;
import org.opencv.utils.Converters;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by codertimo on 2015. 12. 17..
 */
public class SWDSubAlgorithm
{

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
        Mat mat = Converters.vector_Point_to_Mat(lines);
        return mat;
    }

    /**
     * 라디안으로 변환시킴
     * @param line
     * @return
     */
    public static double convertToRadian(Vec4f line)
    {
        double theta = 0.0;
//
//        // 0으로 나누는 것을 방지
//        if (line.x2 == 0)
//            theta = 90;
//        else
//            theta = -1 * Math.atan(line.y2 / line.x2) / Math.PI * 180.0;
//        if (theta < 0) // 오차 수정
//            theta += 180;
//
        return theta;
    }

}
