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
    public Mat smStack;

    /**
     * compareCurrent 에서
     * 내부 static 으로 선언되어있던것을 멤버변수로 옮겼음
     */
    private double dCurrentSlopeAvg = 0.0;
    private  int iStackcount = 1;


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
        Vec4f vCurrentLine = callMapSlope(smStack);
        double dTheta =0.0;

        if (vCurrentLine.x2 == 0)
            dTheta = 90;
        else
            dTheta = -1 * Math.atan(vCurrentLine.y2 / vCurrentLine.x2) / Math.PI * 180.0;

        if (dTheta < 0)
            dTheta += 180;

        if (dCurrentSlopeAvg == 0)
            dCurrentSlopeAvg = dTheta;

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

        for(int i = 0; i<vLines.size(); i++){}
            //line
        for(int i = 0; i<2;i++){}
            //line
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

        Vec4f vCurrent = callMapSlope(mLineMap);
        if(vCurrent.x2 == 0)
            dNowSlope = 90;
        else
            dNowSlope = Math.atan((vCurrent.y2 / vCurrent.x2)) * 180.0 / Math.PI;

        if(dNowSlope < 0)
            dNowSlope += 180;

        /**
         * 도데체 이게 뭐하는 함수......
         */
//        CompareableLine::setAvgLineSize(dSumLineSize / vLines.size());
//        CompareableLine::setAvgCubeLineSize(dSumCubeLineSize / vLines.size());
//        CompareableLine::setNowDegree(dNowSlope);

        ResLine[0] = cLineList.get(0);
        ResLine[1] = cLineList.get(1);

        for(int i= 0; i<vLines.size();i++){
            cLineList.get(i).calParams();

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
    public void setSmStack(Size size)
    {
        smStack = new Mat(size, CvType.CV_8UC1, new Scalar(0));
    }
    private void callCornerExist(){
        Log.i("SWD","There Exist in corner!\n");
    }
    public void callPedestrainOutofDirection()
    {
        Log.i("SWD","Pedestrian Out of direction!\n");
    }
    public void sendProtocol()
    {
        Log.i("SWD","Receive :"+this.iAngleProtocol);
    }

}
