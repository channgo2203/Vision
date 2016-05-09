package com.github.codertimo.fragment;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import org.w3c.dom.Text;

/**
 * A simple {@link Fragment} subclass.
 */
public class Fragment1 extends Fragment {

    TextView textView;

    public Fragment1() {
        // Required empty public constructor
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        ViewGroup viewGroup = (ViewGroup)inflater.inflate(R.layout.fragment1,container,false);
        textView = (TextView)viewGroup.findViewById(R.id.fragment1_text);

        return viewGroup;
    }

    public void setText(String string)
    {
        textView.setText(string);
    }

}
