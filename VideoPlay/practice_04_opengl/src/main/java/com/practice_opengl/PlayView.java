package com.practice_opengl;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

/**
 * Author: yeliang(yeliang@tv365.net)
 * Date: 2019/1/8
 * Time: 7:25 PM
 * Description:
 */

public class PlayView extends GLSurfaceView implements Runnable, SurfaceHolder.Callback {

    public PlayView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public void run() {
        open("/storage/emulated/0/out.yuv", getHolder().getSurface());
    }

    public native void open(String url, Surface surfaceView);

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
}
