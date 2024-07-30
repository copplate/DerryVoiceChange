package com.example.derryvoicechangeprac;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import org.fmod.FMOD;

public class JavaMainActivity extends AppCompatActivity implements View.OnClickListener {
    //播放的模式
    private static final int MODE_NORMAL = 0;
    private static final int MODE_LUOLI = 1;
    private static final int MODE_DASHU = 2;
    private static final int MODE_JINGSONG =3;
    private static final int MODE_GAOGAUI = 4;
    private static final int MODE_KONGLING = 5;


    static{
        System.loadLibrary("voicechange");
    }

    //音频的来源
    private final static String PATH = "file:///android_asset/安静.mp3";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_java_main);
        FMOD.init(this);
        Button btnNormal = findViewById(R.id.btn_normal);
        Button btnLoli = findViewById(R.id.btn_loli);
        Button btnUncle = findViewById(R.id.btn_uncle);
        Button btnThrill = findViewById(R.id.btn_thrill);
        btnNormal.setOnClickListener(this);

    }



    @Override
    protected void onDestroy() {
        super.onDestroy();
        FMOD.close();
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.btn_normal:
                voiceChangeNative(MODE_NORMAL, PATH);
                break;
            case R.id.btn_loli:
                voiceChangeNative(MODE_LUOLI, PATH);
                break;
            case R.id.btn_uncle:
                voiceChangeNative(MODE_DASHU, PATH);
                break;
            case R.id.btn_thrill:
                voiceChangeNative(MODE_JINGSONG, PATH);
                break;
        }
    }
    //原理：javah com.example.derryvoicechangeprac.JavaMainActivity
    //这种方式可以生成JavaMainActivity对应的头文件
    //使用javah之后，检测到Java的static常量会生成c语言的宏，检测到native函数会自动生成一个jni函数
    private native void voiceChangeNative(int modeNormal, String path);
}