package com.github.codertimo.inflation;

import android.content.Context;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

import java.util.HashMap;
import java.util.Map;
import java.util.zip.Inflater;

public class MainActivity extends AppCompatActivity {

    String student_name;
    String student_school;
    String student_address;

    String college_name;
    String college_class;

    String essay;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }


    public void onMenuClicked(View view)
    {
        FrameLayout linearLayout = (FrameLayout)findViewById(R.id.frameLayout);
        LayoutInflater layoutInflater = (LayoutInflater)getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        linearLayout.removeAllViews();

        switch (view.getId())
        {
            case R.id.student_menu:
                layoutInflater.inflate(R.layout.student_information,linearLayout,true);
                break;
            case R.id.college_menu:
                layoutInflater.inflate(R.layout.college_information,linearLayout,true);
                break;
            case R.id.essay_menu:
                layoutInflater.inflate(R.layout.essay_information,linearLayout,true);
                break;
        }
    }

    public void onClickSaveStudentInfo(View view)
    {
        EditText name = (EditText)findViewById(R.id.student_name);
        EditText school = (EditText)findViewById(R.id.student_school);
        EditText address = (EditText)findViewById(R.id.student_address);

        student_name = name.getText().toString();
        student_school = school.getText().toString();
        student_address = address.getText().toString();
    }
    public void onClickSaveCollegeInfo(View view)
    {
        EditText name = (EditText)findViewById(R.id.college);
        EditText classes = (EditText)findViewById(R.id.classes);

        college_class = classes.getText().toString();
        college_name = name.getText().toString();

    }
    public void onClickSaveEssayInfo(View view)
    {
        EditText name = (EditText)findViewById(R.id.essay);
        essay = name.getText().toString();

    }

    public void onClickedSubmit(View view)
    {
        Intent intent = new Intent(getApplicationContext(),ResultActivity.class);
        HashMap<String,String> map = new HashMap<>();

        map.put("st_name",student_name);
        map.put("st_school",student_school);
        map.put("st_address",student_address);
        map.put("cl_name",college_name);
        map.put("cl_class",college_class);
        map.put("essay",essay);

        intent.putExtra("map",map);
        startActivity(intent);
        finish();
    }

}
