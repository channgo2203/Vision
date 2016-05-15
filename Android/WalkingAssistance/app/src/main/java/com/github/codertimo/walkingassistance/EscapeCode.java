package com.github.codertimo.walkingassistance;

import org.opencv.photo.Photo;

/**
 * Created by codertimo on 2016. 5. 14..
 */
public class EscapeCode {
    public final static int ESCAPED = 1;
    public final static int CORENR = 2;
    public final static int NOTHING = 0;


    public static String toString(int code)
    {
        switch (code)
        {
            case ESCAPED:
                return "Escaped";

            case CORENR:
                return "Corner";

            case NOTHING:
                return "Nothing";
        }
        return "Unknown Code";
    }
}
