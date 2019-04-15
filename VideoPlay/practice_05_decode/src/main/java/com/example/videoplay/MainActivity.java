package com.example.videoplay;

import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.SeekBar;

import java.util.List;

public class MainActivity extends AppCompatActivity implements SeekBar.OnSeekBarChangeListener, View.OnClickListener ,EasyPermissions.PermissionCallbacks{

    static {
        System.loadLibrary("native-lib");
    }

    private SeekBar mSeekBar;
    private Thread mThread;
    private Runnable mRunnable;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //去掉标题栏
        supportRequestWindowFeature(Window.FEATURE_NO_TITLE);
        //全屏，隐藏状态
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN
        );
        //屏幕为横屏
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        setContentView(R.layout.activity_main);

        initView();
        initData();

       EasyPermissions.permissionsCamera(this ,EasyPermissions.PERMISSION_REQUEST, EasyPermissions.MUST_PERMISSIONS);

    }

    private void initView() {
        findViewById(R.id.btn_play).setOnClickListener(this);

        mSeekBar = findViewById(R.id.seek_progress);
        mSeekBar.setOnSeekBarChangeListener(this);
    }


    private void initData() {
        mRunnable = new Runnable() {
            @Override
            public void run() {
                while (true) {
                    int progress = (int) (getPlayPos() * 100);

                    //Log.i("===TAG===", "progress = " + progress * 100);
                    mSeekBar.setProgress(progress);
                    try {
                        Thread.currentThread().sleep(500);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        };
        mThread = new Thread(mRunnable);
        mThread.start();
    }

    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {

    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {
        double pos = (double) seekBar.getProgress() / (double) seekBar.getMax();
        Log.i("===TAG===", "Seek pos = " + pos);
        seekTo(pos);
    }

    //获取播放位置
    public native double getPlayPos();

    //滑动到
    public native double seekTo(double pos);

    //播放
    public native void play(String url);


    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_play:
                play("/storage/emulated/0/video.mp4");
                break;
        }
    }


    @Override
    public void onPermissionsGranted(int requestCode, List<String> perms) {

    }

    @Override
    public void onPermissionsDenied(int requestCode, List<String> perms) {
        EasyPermissions.requestPermissions(this, EasyPermissions.PERMISSION_REQUEST, perms.toArray(new String[perms.size()]));
    }

    @Override
    public void onPermissionsAllGranted() {

    }
}
