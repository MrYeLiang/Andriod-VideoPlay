package com.example.videoplay;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.View;

/**
 * Author: yeliang(yeliang@tv365.net)
 * Date: 2019/2/12
 * Time: 6:50 PM
 * Description:
 */

public class XPlay extends GLSurfaceView implements SurfaceHolder.Callback,View.OnClickListener{

    public XPlay(Context context, AttributeSet attrs) {
        super(context, attrs);
        setOnClickListener(this);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        InitView(holder.getSurface());
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }

    public native void InitView(Object surface);

    public native void playOnPause();

    @Override
    public void onClick(View v) {
        playOnPause();
    }
}
