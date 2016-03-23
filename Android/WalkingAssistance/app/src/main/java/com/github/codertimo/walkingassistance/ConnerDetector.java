package com.github.codertimo.walkingassistance;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by codertimo on 2016. 3. 23..
 */
public class ConnerDetector {
    private boolean isStart=false;
    private int startCount;

    private int currentCount=20;

    private List<Integer> detectLogs = new ArrayList<>();
    private List<Integer> detectCodes = new ArrayList<>();

    public ConnerDetector()
    {

    }
    public void checkCanIStart(boolean isvanPoint)
    {
        if(isvanPoint)
            startCount++;
        else
            startCount =0;
        if(startCount>5)
            isStart=true;
    }
    public int checkFinalResult(int code)
    {
        writeLog(code);
        detectCodes.add(code);
        if(currentCount==0)
        {
            int result = checkCornerResult(detectCodes);
            detectCodes.clear();
            currentCount=40;
            return result;
        }
        currentCount--;
        return 999;
    }

    private void writeLog(int code)
    {
        detectLogs.add(code);
    }

    public boolean isStart() {
        return isStart;
    }

    public int checkCornerResult(List<Integer> list) {

        int[] count = new int[6];
        for (int code : list) {
            switch (code) {
                case 11:
//            "right corner"
                    count[1]++;
                    break;
                case 12:
                    count[2]++;
//            "left corner"
                    break;
                case 21:
                    count[3]++;
//            "vertical right corner"
                    break;
                case 22:
                    count[4]++;
//            "vertical left corner"
                    break;
                case 20:
                    count[5]++;
//            "vertical corner"
                    break;
                case 0:
                    //nothing
                    count[0]++;
                    break;
            }
        }

        count[0]=count[0]/2;
        int max_index=0,max_count=0;
        for(int i=0;i<6;i++)
        {
            if(max_count<count[i]) {
                max_count = count[i];
                max_index = i;
            }
        }

        switch (max_index) {
            case 1:
                return 11;
            case 2:
                return 12;
            case 3:
                return 21;
            case 4:
                return 22;
            case 5:
                return 20;
            case 0:
                return 0;
        }
        return 0;
    }
}
