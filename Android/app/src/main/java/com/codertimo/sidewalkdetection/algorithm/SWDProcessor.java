package com.codertimo.sidewalkdetection.algorithm;

import android.util.Log;

import com.codertimo.sidewalkdetection.algorithm.type.ComparableLine;
import com.codertimo.sidewalkdetection.algorithm.type.Vec4f;
import com.codertimo.sidewalkdetection.algorithm.type.Vec4i;

import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.Point;
import org.opencv.core.Scalar;
import org.opencv.core.Size;
import org.opencv.imgproc.Imgproc;
import org.opencv.utils.Converters;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by codertimo on 2015. 12. 17..
 */
public class SWDProcessor {

    /**
     * 설명 : HoughLine을 적용하는 알고리즘
     * @param mRawImg
     * @return
     */
    public Mat getHoughLineResult(Mat mRawImg)
    {
        Mat mCannyResult = new Mat();
        Mat houghLineResult = new Mat();

        Imgproc.Canny(mRawImg, mCannyResult, 50, 200);
        Imgproc.HoughLinesP(mCannyResult, houghLineResult, 1, Math.PI / 180, 50, 50, 10);

        return houghLineResult;
    }

    /**
     * 설명 : 경향성을 분석해서 어떤 상황인지 판단
     */
    public void compareCurrent()
    {
        Vec4f vCurrentLine = slopeStackFitline(SWDGlobalValue.slopeStack);
        double dTheta = SWDSubAlgorithm.convertToRadian(vCurrentLine); // 현재 각도를 저장


        if (SWDGlobalValue.currentSlopeAvg == 0) { // 만일 기울기가 0 (바로 전에 초기화)
            SWDGlobalValue.currentSlopeAvg = dTheta; // 현재 값으로 초기화
            SWDGlobalValue.previousSlopeAvg = SWDGlobalValue.currentSlopeAvg; // 전체 평균 초기화
        }

        // 프레임 갯수 증가
        SWDGlobalValue.frameCount++;

        // 30번마다 SWDSubAlgorithm 초기화
        if(SWDGlobalValue.frameCount % 30 == 0) {
            Log.d("SWD","Clear");
            SWDGlobalValue.frameCount = 0;
            SWDGlobalValue.slopeStack.clear();
            SWDGlobalValue.previousSlopeAvg = SWDGlobalValue.currentSlopeAvg;
            SWDGlobalValue.currentSlopeAvg = dTheta;
        }
        else if (Math.abs(SWDGlobalValue.currentSlopeAvg - dTheta) > 30) {
            // 30도 이상 회전시 코너로 판별
            // Corner가 나왔을경우 호출
            Log.d("SWD","CONER");
        }
        else if(Math.abs(SWDGlobalValue.currentSlopeAvg - dTheta) > 10) {
            Log.d("SWD","Prison Break");
            //!!사용자 이탈!!//
            // 10~30도면 사용자가 방향을 이탈할 가능성이 있으므로
            // 이탈 각도 (int)Math.abs(SWDGlobalValue.previousSlopeAvg - dTheta)
        }
        else {
            Log.d("SWD","Nothing");
            SWDGlobalValue.currentSlopeAvg *= SWDGlobalValue.frameCount-1; // 아니면 계속 평균 누적
            SWDGlobalValue.currentSlopeAvg += dTheta; // 전환
            SWDGlobalValue.currentSlopeAvg /= SWDGlobalValue.frameCount; // 초기화
            // -> 정상임
        }
    }

    /**
     * 설명 : HoughLine으로 추출한 여러개의 직선에서, 2개의 중요 직선을 추출해내는 함수
     * @param houghLineResult
     * @return
     */
    public ComparableLine[] getTwoLine(Mat houghLineResult)
    {
        /**
         * sumLineSize : 선분의모든 길이의 합
         * sumSquaredLineSize : 선분길이의 제곱의 합
         * houghlineResult : Mat 형식으로 저장된 houghline 결과
         * houghlines : HoughLine으로 출력된, List<Vec4i>
         */
        double sumLineSize = 0.0;
        double sumSquaredLineSize =0.0;
        List<Vec4i> houghLines = SWDSubAlgorithm.MatToVec4is(houghLineResult);

        List<ComparableLine> comparableLines = new ArrayList<>();
        ComparableLine[] twoResultLine = new ComparableLine[2];

        // 선의 선분 길이 등 여러 데이터 저장
        for(Vec4i vec4i : houghLines) {
            ComparableLine comparableLine = new ComparableLine(vec4i);
            comparableLines.add(comparableLine);
            sumLineSize += comparableLine.lenth;
            sumSquaredLineSize += Math.pow(comparableLine.lenth, 2);
            Core.line(SWDGlobalValue.inputMat,vec4i.toPoints().get(0),vec4i.toPoints().get(1),new Scalar(200,200,200),2);
        }



        //베타 산출위한 전처리 작업
            double x=0, y=0, x_sum=0, y_sum=0;
            for (int i = 0; i < houghLines.size(); i++) {
                for (int j = 0; j < houghLines.size(); j++) {
                    if (i != j) {
                        x += Math.pow(comparableLines.get(i).lenth + comparableLines.get(j).lenth, 2) - sumSquaredLineSize;
                        y += SWDAlgorithm.getDiscriminantResult(comparableLines.get(i), comparableLines.get(j));
                        x_sum += x;
                        y_sum += y;
                    }
                }
        }

        // 베타를 산출 및 저장
        double beta = Math.round(((2 * y_sum - 2 * y) / (Math.pow(x, 2) + x - 2 * x_sum + 2 * y_sum))*100)/100;

        // 현재 경향성의 기울기
        Vec4f currentSlope = houghlineSlope(houghLines);
        double currentRadianSlope = SWDSubAlgorithm.convertToRadian(currentSlope);
        SWDGlobalValue.currentSlope = currentRadianSlope;

        //평균선분의 길이, 평균선분의^2 길이
        double avgLineSize = sumLineSize/comparableLines.size();
        double avgSquaredLineSize = sumSquaredLineSize /comparableLines.size();

        //임시변수 선언
        twoResultLine[0] = comparableLines.get(0);
        twoResultLine[1] = comparableLines.get(1);

        //중요한 2개의 선 추출
        for(ComparableLine comparableLine : comparableLines){

            double first = SWDAlgorithm.getNonlinearRegressionResult(beta, avgLineSize,
                    twoResultLine[0], twoResultLine[1]);

            double second = Math.max(
                    SWDAlgorithm.getNonlinearRegressionResult(beta, avgLineSize, comparableLine, twoResultLine[0]),
                    SWDAlgorithm.getNonlinearRegressionResult(beta, avgLineSize, comparableLine, twoResultLine[1])
            );

            if(first < second) {
                if(SWDAlgorithm.getNonlinearRegressionResult(beta,avgLineSize,comparableLine,twoResultLine[0])
                        < SWDAlgorithm.getNonlinearRegressionResult(beta,avgLineSize,comparableLine,twoResultLine[1]))
                    twoResultLine[1] = comparableLine;
                else
                    twoResultLine[0] = comparableLine;
            }
        }
        return twoResultLine;
    }


    /**
     * 설명 : HoughLine으로 출력된 영상의 직선들에 대한 선형회귀 결과 return
     * @return Vec4f 선형회귀결과
     */
    private Vec4f houghlineSlope(List<Vec4i> lines)
    {
        List<Point> points = new ArrayList<>();
        for (Vec4i vec : lines)
        {
            points.addAll(vec.drawLine());
        }

        //선형회귀 분석
        Mat fitLineResultMap = new Mat();
        Imgproc.fitLine(Converters.vector_Point_to_Mat(points),fitLineResultMap,Imgproc.CV_DIST_L2,0,0.01,0.01);

        //선형회귀 결과 Mat, Vec4f로 전환 후 리턴
        Vec4f fitline_result = new Vec4f(fitLineResultMap);
        Log.i("SWD","HoughLine Slope : "+fitline_result.vy/fitline_result.vx);
        return fitline_result;

        }

    /**
     * 설명 : Slop들의 축적으로 쌓여진 영상의 직선들에 대한 선형회귀 결과 return
     * @return Vec4f 선형회귀결과
     */
    private Vec4f slopeStackFitline(List<Point> lines)
    {
        //선형회귀 분석
        Mat fitLineResultMap = new Mat();
        Imgproc.fitLine(Converters.vector_Point_to_Mat(lines),fitLineResultMap,Imgproc.CV_DIST_L2,0,0.01,0.01);

        //vx,vy,x0,y0 값으로 retrun된다고 합니다
        //선형회귀 결과 Mat, Vec4f로 전환 후 리턴
        Vec4f fitline_result = new Vec4f(fitLineResultMap);
        Log.i("SWD","Fitline Slope : "+fitline_result.vy/fitline_result.vx);
        return fitline_result;
    }
}
