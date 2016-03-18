package com.codertimo.sidewalkdetection.test;

import android.graphics.Bitmap;
import android.media.MediaMetadataRetriever;
import android.util.Log;

import com.codertimo.sidewalkdetection.algorithm.SWDGlobalValue;

import org.opencv.android.Utils;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.Size;

import java.io.FileDescriptor;
import java.net.URI;
import java.net.URL;

/**
 * Created by codertimo on 2016. 2. 2..
 */
public class VideoStreaming {

    private String path;
    private MediaMetadataRetriever retriever = new MediaMetadataRetriever();
    public long duration;


    public VideoStreaming(String path)
    {
        this.path = path;
        this.retriever.setDataSource(path);
        this.duration = new Long(retriever.extractMetadata(MediaMetadataRetriever.METADATA_KEY_DURATION));
        Log.i("SWD","Video Duration"+duration);
    }

    public Mat getVideoFrame(long time) {
        try {
            return bitmapToMat(retriever.getFrameAtTime(time));
        } catch (IllegalArgumentException ex) {
            ex.printStackTrace();
        } catch (RuntimeException ex) {
            ex.printStackTrace();
        }
        return null;
    }

    private Mat bitmapToMat(Bitmap bitmap)
    {
        Mat mat = new Mat(bitmap.getWidth(),bitmap.getHeight(),CvType.CV_8UC4);

        Utils.bitmapToMat(bitmap,mat);
        return mat;
    }

}
