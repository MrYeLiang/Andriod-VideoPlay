package com.pracitce.videoplay;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String videoPath = Environment.getExternalStorageDirectory() + "/video.mp4";
        open(videoPath);

    }

    public native void open(String videoPath);
}
