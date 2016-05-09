package com.github.codertimo.inflation;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

import java.util.HashMap;

/**
 * Created by codertimo on 2016. 4. 19..
 */
public class ResultActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.result_layout);

        Intent intent = getIntent();
        HashMap<String,String> hashMap = (HashMap)intent.getExtras().get("map");
        TextView textView = (TextView)findViewById(R.id.result);

        textView.setText(hashMap.toString());

    }

}
