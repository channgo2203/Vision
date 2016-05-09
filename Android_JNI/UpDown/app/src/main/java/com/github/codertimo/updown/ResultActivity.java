package com.github.codertimo.updown;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class ResultActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_result);
    }

    public void onRestartClikced(View view)
    {
        Intent intent = new Intent(getApplicationContext(),MainActivity.class);
    }
    public void onStopClicked(View view)
    {
        finish();
    }
}
