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

    /**
     * compareCurrent 에서
     * 내부 static 으로 선언되어있던것을 멤버변수로 옮겼음
     */

    public LineMap(){}
    public LineMap(Mat mat){
        this.mRawImg = mat;
        this.iAngleProtocol = 0;
    }

    /**
     * 내부 변수들에 대한 설명 :
     * 설명 :
     */
    public void compareCurrent()
    {
        Vec4f vCurrentLine = callMapSlope(SWDUtil.smStack);
        double dTheta;

        if (vCurrentLine.x2 == 0)
            dTheta = 90;
        else
            dTheta = -1 * Math.atan(vCurrentLine.y2 / vCurrentLine.x2) / Math.PI * 180.0;

        if (dTheta < 0)
            dTheta += 180;

        if (SWDUtil.dCurrentSlopeAvg == 0) {
            SWDUtil.dCurrentSlopeAvg = dTheta;
            SWDUtil.dPreviousSlopeAvg = SWDUtil.dCurrentSlopeAvg;
        }
        
        SWDUtil.iStackcount++;


        if(SWDUtil.iStackcount % 30 == 0) {
            setSmStack(new Size(600,400));
//            SWDUtil.smStack = new Mat()
            SWDUtil.iStackcount = 0;
            SWDUtil.dPreviousSlopeAvg = SWDUtil.dCurrentSlopeAvg;
            SWDUtil.dCurrentSlopeAvg = dTheta;
        }
        else if (Math.abs(SWDUtil.dCurrentSlopeAvg - dTheta) > 30) {
            callCornerExist();
        }
        else if(Math.abs(SWDUtil.dCurrentSlopeAvg - dTheta) > 10) {
            callPedestrainOutofDirection((int)Math.abs(SWDUtil.dPreviousSlopeAvg - dTheta));
        }
        else {
            SWDUtil.dCurrentSlopeAvg *= SWDUtil.iStackcount-1;
            SWDUtil.dCurrentSlopeAvg += dTheta;
            SWDUtil.dCurrentSlopeAvg /= SWDUtil.iStackcount;
            iAngleProtocol = 0;
        }
    }

    /**
     * 내부 변수들에 대한 설명 :
     * 설명 :
     */

    public void setLine()
    {
        Mat mContours = null;
        Mat mLines = null;

        Imgproc.Canny(mRawImg, mContours, 50, 200);
        vLines.clear();
        Imgproc.HoughLinesP(mContours, SWDUtil.Vec4iToMat(vLines), 1, Math.PI / 180, 50, 50, 10);

        mLines.create(mRawImg.size(), CvType.CV_32FC1);

        /**
         * 이미지 출력하는 부분인데...
         * 이건 어떻게 할건지 논의 해야 할듯
         */

        for(int i = 0; i<vLines.size(); i++){
            Core.line(mLineMap,new Point(vLines.get(i).x1,vLines.get(i).y1),new Point(vLines.get(i).x2,vLines.get(i).x2),new Scalar(255,255,255),1);
        }

        compareLine();

        for(int i = 0; i<2;i++){
            Core.line(SWDUtil.smStack,new Point(vResLine.get(i).x1,vResLine.get(i).y1),new Point(vResLine.get(i).x2,vResLine.get(i).y2),new Scalar(111),3);
        }

        //imshow?
    }

    /**
     * 내부 변수들에 대한 설명 :
     * 설명 :
     */
    public void compareLine()
    {
        ComparableLine[] ResLine = new ComparableLine[2];
        List<ComparableLine> cLineList = new ArrayList<>();

        double dSumLineSize = 0;
        double dSumCubeLineSize = 0;

        for(int i=0;i<vLines.size();i++)
            cLineList.add(new ComparableLine(vLines.get(i)));

        for(int i=0;i<vLines.size();i++)
        {
            dSumLineSize += cLineList.get(i).getLine_size();
            dSumCubeLineSize += Math.pow(cLineList.get(i).getLine_size(),2);
        }

        double x = 0, y = 0, X_sum = 0, Y_sum = 0;
        for (int i = 0; i < vLines.size(); i++) {
            for (int j = 0; j < vLines.size(); j++) {
                if (i != j) {
                    x += Math.pow(cLineList.get(i).getLine_size() + cLineList.get(j).getLine_size(), 2) - dSumCubeLineSize;
                    y += cLineList.get(i).getFunctionD(cLineList.get(j).getSlope());
                    X_sum += x;
                    Y_sum += y;
                }
            }
        }

        double beta = (2 * Y_sum - 2 * y) / (Math.pow(x, 2) + x - 2 * X_sum + 2 * Y_sum);
        SWDUtil.setParam(beta);


        Vec4f vCurrent = callMapSlope(mLineMap);

        if(vCurrent.x2 == 0)
            dNowSlope = 90;
        else
            dNowSlope = Math.atan((vCurrent.y2 / vCurrent.x2)) * 180.0 / Math.PI;

        if(dNowSlope < 0)
            dNowSlope += 180;


        SWDUtil.sdAvgLineSize = dSumLineSize / vLines.size();
        SWDUtil.sdAvgCubeLineSize = dSumCubeLineSize / vLines.size();
        SWDUtil.sdMapDegree = dNowSlope;


        ResLine[0] = cLineList.get(0);
        ResLine[1] = cLineList.get(1);

        for(int i= 0; i<vLines.size();i++){

            double first = ResLine[0].getFunctionS(ResLine[1]);

            double second = Math.max(
                    cLineList.get(i).getFunctionS(ResLine[0]),
                    cLineList.get(i).getFunctionS(ResLine[1]));

            if(first<second) {
                if (cLineList.get(i).getFunctionS(ResLine[0]) < cLineList.get(i).getFunctionS(ResLine[1]))
                    ResLine[1] = cLineList.get(i);
                else
                    ResLine[0] = cLineList.get(i);

            }

            vResLine.add(ResLine[0].getPoint());
            vResLine.add(ResLine[1].getPoint());
            cLineList.clear();
        }
    }


    /**
     * 내부 변수들에 대한 설명 :
     * 설명 :
     */
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
    public void setSmStack(Size size) {
        SWDUtil.smStack = new Mat(size, CvType.CV_8UC1, new Scalar(0));
    }
    private void callCornerExist(){
        Log.i("SWD","There Exist in corner!\n");
    }
    public void callPedestrainOutofDirection(int code)
    {
        Log.i("SWD","Pedestrian Out of direction!\n");
        Log.i("SWD",""+code);
    }
    public void sendProtocol()
    {
        Log.i("SWD","Receive :"+this.iAngleProtocol);
    }

}
