package com.codertimo.sidewalkdetection.algorithm.type;
import com.codertimo.sidewalkdetection.algorithm.SWDGlobalValue;

import org.opencv.core.Mat;
import org.opencv.core.Point;
import java.util.ArrayList;
import java.util.List;


/**
 * Created by codertimo & DMK 2015. 11. 2..
 */
public class Vec4f {
    public float vx; // 1
    public float vy; // 2
    public float x0; // 3
    public float y0; // 4

    public Vec4f() {}
    public Vec4f(Mat mat)
    {
        this.vx = (float)mat.get(0,0)[0];
        this.vy = (float)mat.get(1,0)[0];
        this.x0 = (float)mat.get(2,0)[0];
        this.y0 = (float)mat.get(3,0)[0];
    }
    public Vec4f(double[] array)
    {
        this.vx = (float)array[0];
        this.vy = (float)array[1];
        this.x0 = (float)array[2];
        this.y0 = (float)array[3];
    }
    public Vec4f(float[] array)
    {
        this.vx = array[0];
        this.vy = array[1];
        this.x0 = array[2];
        this.y0 = array[3];
    }

    public float[] toArray()
    {
        float[] array = {vx,vy,x0,y0};
        return array;
    }

    public List<Point> toPoints()
    {
        List<Point> points = new ArrayList<>();
        float slope = this.vy/this.vx;
        float equation_b = this.y0 - slope*this.x0;
        Point zero = new Point(0,equation_b);
        Point last = new Point(SWDGlobalValue.resolution.width,slope*SWDGlobalValue.resolution.width+equation_b);
        points.add(zero); points.add(last);
        return points;
    }

}

