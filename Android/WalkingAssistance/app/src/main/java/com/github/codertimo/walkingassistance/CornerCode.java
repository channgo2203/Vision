package com.github.codertimo.walkingassistance;

/**
 * Created by codertimo on 2016. 5. 14..
 */
public class CornerCode {

    public final static int RIGHT_VERTICAL_CORNER = 1;
    public final static int LEFT_VERTICAL_CORNER = 2;
    public final static int RIGHT_BENDED_CORNER = 4;
    public final static int LEFT_BENDED_CORNER = 5;
    public final static int NOTHING = 0;

    public static String codeToString(int code)
    {
        switch (code)
        {
            case RIGHT_VERTICAL_CORNER:
                return "Right Vertical Corner";

            case LEFT_VERTICAL_CORNER:
                return "Left Vertical Corner";

            case RIGHT_BENDED_CORNER:
                return "Right Bended Corner";

            case LEFT_BENDED_CORNER:
                return "Right Bended Corner";

            case NOTHING:
                return "Nothing";

        }
        return "UnKnown Code";
    }
    public static String codeToKoreanString(int code)
    {
        switch (code)
        {
            case RIGHT_VERTICAL_CORNER:
                return "오른쪽 방향 코너";

            case LEFT_VERTICAL_CORNER:
                return "왼쪽 방향 코너";

            case RIGHT_BENDED_CORNER:
                return "오른쪽으로 휜 코너";

            case LEFT_BENDED_CORNER:
                return "왼쪽으로 휜 코너";

            case NOTHING:
                return "아무것도 없습니다";

        }
        return "UnKnown Code";
    }
}
