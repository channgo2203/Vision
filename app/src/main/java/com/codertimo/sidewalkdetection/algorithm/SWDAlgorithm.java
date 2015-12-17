package com.codertimo.sidewalkdetection.algorithm;

import com.codertimo.sidewalkdetection.algorithm.type.ComparableLine;

/**
 * Created by codertimo on 2015. 12. 17..
 */
public class SWDAlgorithm
{
    /**
     * 판별식 함수
     * @param mainComparableLine
     * @param subComparableLine
     * @return
     */
    public static double getDiscriminantResult(ComparableLine mainComparableLine, ComparableLine subComparableLine)
    {
        if (10 + mainComparableLine.slope < subComparableLine.slope || mainComparableLine.slope - 10 > subComparableLine.slope)
        {
            // |a + b -2c|
            return Math.abs(mainComparableLine.slope + subComparableLine.slope - 2 * SWDGlobalValue.currentSlopeAvg) * (mainComparableLine.slope + subComparableLine.slope);
        }
        return 0;
    }

    /**
     * 손실함수
     * @param beta
     * @param avgLineSize
     * @param mainComparableLine
     * @param subComparableLine
     * @return
     */
    public static double getNonlinearRegressionResult(double beta, double avgLineSize, ComparableLine mainComparableLine, ComparableLine subComparableLine)
    {
        if (getDiscriminantResult(mainComparableLine,subComparableLine) == 0) // 사전 판별
            return -10000000; // 똥값

        return beta * (Math.pow(mainComparableLine.lenth + subComparableLine.lenth,2)
                - avgLineSize
                - getDiscriminantResult(mainComparableLine,subComparableLine))
                + getDiscriminantResult(mainComparableLine,subComparableLine);
    }


}
