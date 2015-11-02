package com.codertimo.sidewalkdetection.algorithm;

import android.util.Log;

import org.opencv.core.*;
import org.opencv.imgproc.*;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by codertimo on 2015. 10. 26..
 */

public class LineMap {

    private double dNowSlope;
    private Mat mRawImg;
    private Mat mLineMap;
    private List<Vec4i> vLines;
    private List<Vec4i> vResLine;
    private int iAngleProtocol;
    public static Mat smStack;

    public LineMap(){

    }
    public LineMap(Mat mat){
        this.mRawImg = mat;
        this.iAngleProtocol = 0;
    }

    public void compareCurrent()
    {
        Vec4f vCurrentLine = callMapSlope(smStack);
        double dTheta =0.0;
        int iStackcount = 1;
        double dCurrentSlopeAvg = 0.0;

//        if(vCurrentLine == 0) dTheta = 90;
//        if (vCurrentLine[2] == 0) dTheta = 90;
//        else dTheta = -1 * atan(vCurrentLine[3] / vCurrentLine[2]) / CV_PI * 180.0;
//        if (dTheta < 0) dTheta += 180;
//        if (dCurrentSlopeAvg == 0) dCurrentSlopeAvg = dTheta;

        Log.i("SWD", "now : " + dTheta + " Avg : " + dCurrentSlopeAvg);
        if(dCurrentSlopeAvg == 0) {
            dCurrentSlopeAvg = dTheta;
            iStackcount = 1;
        }
        if(iStackcount % 20 == 0) {
            setSmStack(new Size(600,400));
            iStackcount = 1;
            dCurrentSlopeAvg = dTheta;
        }
        else if (Math.abs(dCurrentSlopeAvg - dTheta) > 20) {
            callCornerExist();
            dCurrentSlopeAvg = dTheta;
            iStackcount = 1;
        }
        else if(Math.abs(dCurrentSlopeAvg - dTheta) > 5) {
            callPedestrainOutofDirection();
            if(dTheta < 0)
                iAngleProtocol = (int)Math.abs(dTheta - dCurrentSlopeAvg)/5+5;
            else
                iAngleProtocol = (int)Math.abs(dTheta - dCurrentSlopeAvg) / 5;
            dCurrentSlopeAvg = dTheta;
            iStackcount = 1;
        }
        else {
            dCurrentSlopeAvg *= iStackcount++;
            dCurrentSlopeAvg += dTheta;
            dCurrentSlopeAvg /= iStackcount;
            iAngleProtocol = 0;
        }



    }
    public void setLine()
    {
        Mat mContours = null;
        Mat mLines = null;

        Imgproc.Canny(mRawImg, mContours, 50, 200);
        vLines.clear();
        Imgproc.HoughLinesP(mContours, SWDUtil.Vec4iToMat(vLines), 1, Math.PI / 180, 50, 50, 10);

        mLines.create(mRawImg.size(), CvType.CV_32FC1);

        for(int i = 0; i<vLines.size(); i++)
            //line
        for(int i = 0; i<2;i++)
            //line
        //imshow?
    }
    public void sendProtocol()
    {

    }

    public void callPedestrainOutofDirection()
    {

    }
    public void compareLine(){
        
    }

    private Vec4f callMapSlope(Mat resMap)
    {
        List<Point> vPoint = new ArrayList<>();
        Vec4f vCurrentLine = null;

        for(int y=0;y<resMap.size().height; y++)
        {
            //uchar* ptr = resMap.ptr<uchar>(y);
            for(int x=0;x<resMap.size().width;x++)
            {
                //if (ptr[x] != 0)
                vPoint.add(new Point(x,y));
            }
        }

        Mat line = new Mat();
        Imgproc.fitLine(SWDUtil.PointsToMat(vPoint),line,Imgproc.CV_DIST_L2,0,0.01,0.01);
        vCurrentLine = new Vec4f(line);
        return vCurrentLine;
    }
    public Mat getLineMap()
    {
        return mLineMap;
    }

    public void callConerExist(){
        Log.i("SWD","There Exist in corner!\n");
    }
    public static void setSmStack(Size size)
    {
        smStack = new Mat(size, CvType.CV_8UC1, new Scalar(0));
    }

}
