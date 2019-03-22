package com.example.videoplay;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

/**
 * Author: yeliang(yeliang@tv365.net)
 * Date: 2019/3/16
 * Time: 12:00 PM
 * Description:
 */

public class PlayListActivity extends AppCompatActivity implements View.OnClickListener {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_play_list);

        findViewById(R.id.btn_play_local).setOnClickListener(this);
        findViewById(R.id.btn_play_rtmp).setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_play_local:
                OpenUrl("/storage/emulated/0/video.mp4");
                finish();
                break;
            case R.id.btn_play_rtmp:
                break;
            default:
                break;
        }
    }

    public native void OpenUrl(String url);
}
