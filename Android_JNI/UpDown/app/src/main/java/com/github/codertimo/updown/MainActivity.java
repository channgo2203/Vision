package com.github.codertimo.updown;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import org.w3c.dom.Text;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    ArrayList<Card> cards = new ArrayList<>();
    Card card1;
    Card card2;

    boolean isCanStart = false;
    int total_account=100;
    int game_money=0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initCard();
    }

    public void onGameStart(View view)
    {
        ImageView card1_img = (ImageView)findViewById(R.id.imageView);
        ImageView card2_img = (ImageView)findViewById(R.id.imageView2);
        card1_img.setImageResource(R.drawable.s0);
        card2_img.setImageResource(R.drawable.s0);
        card1 = null;
        
        card2 = null;
        isCanStart = true;
    }

    public void onOfficalGame(View view)
    {
        if(!isCanStart)
            return;
        EditText editText = (EditText)findViewById(R.id.game_money);
        int game_money = new Integer(editText.getText().toString());

        getRandomCard();

        if(view.getId()==R.id.up)
        {
            if(card1.number>card2.number)
            {
                total_account+=game_money;
            }
            else
            {
                total_account-=game_money;
            }
        }
        else
        {
            if(card1.number<card2.number)
            {
                total_account+=game_money;
            }
            else
            {
                total_account-=game_money;
            }
        }

        if(total_account<0)
            gameover();
        else
            setTotalMoney();

        isCanStart= false;
        game_money=0;
        editText.setText("");
    }

    private void setTotalMoney()
    {
        TextView textView = (TextView)findViewById(R.id.left_money);
        textView.setText("남은 금액 : "+total_account);
    }
    private void gameover()
    {
        Intent intent = new Intent(getApplicationContext(),ResultActivity.class);
        startActivity(intent);
        finish();
    }

    private void getRandomCard()
    {
        int random1 = (int)(Math.random()*cards.size());
        int random2 = (int)(Math.random()*cards.size());
        card1 = cards.get(random1);
        card2 = cards.get(random2);

        ImageView card1_img = (ImageView)findViewById(R.id.imageView);
        ImageView card2_img = (ImageView)findViewById(R.id.imageView2);
        card1_img.setImageResource(card1.url);
        card2_img.setImageResource(card2.url);
    }

    private void initCard()
    {
        this.cards.add(new Card(R.drawable.s1,1));
        this.cards.add(new Card(R.drawable.s2,2));
        this.cards.add(new Card(R.drawable.s3,3));
        this.cards.add(new Card(R.drawable.s4,4));
        this.cards.add(new Card(R.drawable.s5,5));
        this.cards.add(new Card(R.drawable.s6,6));
        this.cards.add(new Card(R.drawable.s7,7));
        this.cards.add(new Card(R.drawable.s8,8));
        this.cards.add(new Card(R.drawable.s9,9));
        this.cards.add(new Card(R.drawable.s10,10));
        this.cards.add(new Card(R.drawable.s11,11));
        this.cards.add(new Card(R.drawable.s12,12));
        this.cards.add(new Card(R.drawable.s13,13));
        this.cards.add(new Card(R.drawable.s14,14));
    }
}
