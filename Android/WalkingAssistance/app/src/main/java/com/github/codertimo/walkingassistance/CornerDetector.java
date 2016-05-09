package com.github.codertimo.walkingassistance;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by codertimo on 2016. 3. 23..
 */
public class CornerDetector {

    public final static int START_VANISHINGPOINT_COUNT = 5;

    public final static int RIGHT_ROUND_CORNER = 11;
    public final static int LEFT_ROUND_CORNER = 12;

    public final static int RIGHT_VERTICAL_CORNER = 21;
    public final static int LEFT_VERTICAL_CORNER = 22;
    public final static int UNKNOWN_VERTICAL_CORNER = 20;

    public final static int NOTHING = 0;

    public static int CHECK_ROOP_COUNT  = 20;

    private int roop_count = CHECK_ROOP_COUNT;

    private boolean isStart=false;
    private int startCount;

    private List<Integer> detectLogs = new ArrayList<>();
    private List<Integer> detectCodes = new ArrayList<>();

    public void checkCanIStart(boolean isvanPoint) {
        if(isvanPoint)
            startCount++;

        else
            startCount =0;

        //소실점 검출이 5번 이상 검출되면 시작
        if(startCount > START_VANISHINGPOINT_COUNT)
            isStart=true;
    }
    public int getFinalCode(int code) {

        writeLog(code);
        detectCodes.add(code);

        //CHECK_ROOP_COUNT번 마다
        if(roop_count==0)
        {
            int result_code = getMaxIndexCode(detectCodes);
            detectCodes.clear();

            roop_count=CHECK_ROOP_COUNT;
            return result_code;
        }

        roop_count--;
        return 9999;
    }
    private void writeLog(int code)
    {
        detectLogs.add(code);
    }
    public boolean isStart() {
        return isStart;
    }
    public int getMaxIndexCode(List<Integer> list) {

        int[] count = new int[6];

        for (int code : list) {
            switch (code) {

                case RIGHT_ROUND_CORNER:
                    count[1]++;
                    break;

                case LEFT_ROUND_CORNER:
                    count[2]++;
                    break;

                case RIGHT_VERTICAL_CORNER:
                    count[3]++;
                    break;

                case LEFT_VERTICAL_CORNER:
                    count[4]++;
                    break;

                case UNKNOWN_VERTICAL_CORNER:
                    count[5]++;
                    break;

                case NOTHING:
                    count[0]++;
                    break;
            }
        }

        //NOTHING값은 0.5배로 감소시킴
        count[0]=count[0]/2;

        int max_index=0,max_count=0;

        //가장 많이 검출된 index 찾기
        for(int i=0;i<6;i++)
        {
            if(max_count<count[i]) {
                max_count = count[i];
                max_index = i;
            }
        }

        switch (max_index) {
            case 1:
                return RIGHT_ROUND_CORNER;
            case 2:
                return LEFT_ROUND_CORNER;
            case 3:
                return RIGHT_VERTICAL_CORNER;
            case 4:
                return LEFT_VERTICAL_CORNER;
            case 5:
                return UNKNOWN_VERTICAL_CORNER;
            case 0:
                return NOTHING;
        }
        return NOTHING;
    }
}
