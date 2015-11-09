package com.codertimo.sidewalkdetection;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;

import com.codertimo.sidewalkdetection.algorithm.LineMap;

import org.opencv.core.Mat;


public class MainActivity extends ActionBarActivity {


    private LineMap frame = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    private void SWDProcess(Mat mat)
    {
        frame = new LineMap(mat);
        frame.setLine();
        frame.compareCurrent();
        frame.sendProtocol();
    }


    void sendProtocal(int iAngleProtocol){
        if(iAngleProtocol == 0)
            Log.i("SWD","walking..");
        else
            Log.i("SWD","receive : "+iAngleProtocol);
    }


}
