package com.pracitce.videoplay;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Environment;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

/**
 * Author: yeliang(yeliang@tv365.net)
 * Date: 2019/1/4
 * Time: 5:14 PM
 * Description:
 */

public class PlayView extends GLSurfaceView implements Runnable, SurfaceHolder.Callback {

    public PlayView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public void run() {
        String videoPath = Environment.getExternalStorageDirectory() + "/video.mp4";
        open(videoPath, getHolder().getSurface());
    }


    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        new Thread(this).start();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
    }


    public native void open(String url, Object surface);
}
