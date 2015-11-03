package com.codertimo.sidewalkdetection.algorithm;

import org.opencv.core.Mat;

/**
 * Created by codertimo on 2015. 11. 3..
 */
public class ComparableLine {

    /**
     * 이변수들은 쓰지도 않으면서 왜 만듬...?
     */
//    private final double sdAllowedMinGap = 0.9;
//    private final double sdAllowedMaxGap = 1.1;
//    private final double sdDeniedMinGap = 0.8;
//    private final double sdDeniedMaxGap = 1.2;
//    private final double cdParameter_beta = 0.000001;

    private int iLine_size =0;
    private double dSlope =0.0;
    Vec4i vPoint = null;

    /**
     * operator 은 뭐하는거야....?
     */
    //CompareableLine operator=(const CompareableLine&);

    public ComparableLine(){}

    /**
     * 내부 변수들에 대한 설명 :
     * 설명 :
     */
    public ComparableLine(Vec4i vec){
        this.vPoint = vec;

        iLine_size = (int)Math.pow(vPoint.x1-vPoint.x2,2) +(int) Math.pow(vPoint.y1-vPoint.y2,2);

        if(vPoint.x1 == vPoint.x2) dSlope = 90;
            dSlope = Math.atan(-1 * (vPoint.y2 - vPoint.y1)/(vPoint.x2 - vPoint.x1)) * 180.0 /Math.PI;

        if(dSlope < 0)
            dSlope += 180;
    }

    /**
     * getFunctionD 함수는 사용 안하던데..?
     */
    public double getFunctionD(double dSlope)
    {
        if(10 + this.dSlope < dSlope || this.dSlope - 10 > dSlope)
            return Math.sqrt(SWDUtil.sdAvgCubeLineSize * Math.abs(this.dSlope + dSlope - 2 * SWDUtil.sdMapDegree));

        return 0;
    }

    /**
     * 내부 변수들에 대한 설명 :
     * 설명 :
     */
    public double getFunctionS(ComparableLine comparableLine)
    {
        if (10 + this.dSlope < dSlope || this.dSlope - 10 > dSlope)
            return Math.sqrt(SWDUtil.sdAvgCubeLineSize * Math.abs(this.dSlope + dSlope - 2 * SWDUtil.sdMapDegree));

        return 0;
    }

    public Vec4i getPoint(){return vPoint;}
    public int getLine_size(){return iLine_size;}
    public double getSlope(){ return dSlope;}
    public boolean calParams(){return true;}
    
}
