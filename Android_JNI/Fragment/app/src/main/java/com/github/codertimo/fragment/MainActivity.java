package com.github.codertimo.fragment;

import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    Fragment1 fragment1;
    Fragment2 fragment2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initation();
    }


    public void initation()
    {
        FragmentManager fragmentManager = getSupportFragmentManager();

        FragmentTransaction fragmentTransaction1 = fragmentManager.beginTransaction();
        fragment1 = new Fragment1();
        fragmentTransaction1.add(R.id.fragment_1,fragment1);
        fragmentTransaction1.commit();

        FragmentTransaction fragmentTransaction2 = fragmentManager.beginTransaction();
        fragment2 = new Fragment2();
        fragmentTransaction2.add(R.id.fragment_2, fragment2);
        fragmentTransaction2.commit();
    }

    public void sendText()
    {
        fragment1.setText("다시만나요");
    }



}
