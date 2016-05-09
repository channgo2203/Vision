package com.github.codertimo.worldcup;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    ArrayList<IUImages> imageList = new ArrayList<>();
    IUImages image1;
    IUImages image2;
    boolean stop = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        imageInit();
    }

    public void onImage1Clicked(View view)
    {
        image2 =null;
        ImageView imageView = (ImageView)findViewById(R.id.imageView2);
        image2 = getRandomImage();
        if(stop==true)
            return;
        imageView.setImageResource(image2.url);
    }

    public void onImage2Clicked(View view)
    {
        image1 =null;
        ImageView imageView = (ImageView)findViewById(R.id.imageView1);
        image1 = getRandomImage();
        if(stop==true)
            return;
        imageView.setImageResource(image1.url);
    }

    private void imageInit()
    {
        imageList.add(new IUImages("아이유1",R.drawable.s1));
        imageList.add(new IUImages("아이유2", R.drawable.s2));
        imageList.add(new IUImages("아이유3",R.drawable.s3));
        imageList.add(new IUImages("아이유4",R.drawable.s4));
        imageList.add(new IUImages("아이유5", R.drawable.s5));

        ImageView imageView1 = (ImageView)findViewById(R.id.imageView1);
        image1 = getRandomImage();
        imageView1.setImageResource(image1.url);

        ImageView imageView2 = (ImageView)findViewById(R.id.imageView2);
        image2 = getRandomImage();
        imageView1.setImageResource(image2.url);
    }

    public IUImages getRandomImage()
    {
        if(stop)
            return null;
        //게임 종료
        if(imageList.size()==0)
        {
            if(image1==null)
            {
                gameWin(image2); //image2가 우승
            }
            if(image2 == null)
            {
                gameWin(image1); //image1이 우승
            }
            return null;
        }

        int random = (int)(Math.random()*imageList.size());
        IUImages random_image= imageList.get(random);
        imageList.remove(random);
        return random_image;
    }

    public void gameWin(IUImages winner)
    {
        TextView textView = (TextView)findViewById(R.id.result);
        textView.setText("최종 우승자는 "+winner.name+"입니다!");
        stop=true;
    }
}
