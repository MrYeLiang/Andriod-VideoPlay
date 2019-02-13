package com.example.videoplay;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

/**
 * Author: yeliang(yeliang@tv365.net)
 * Date: 2019/2/12
 * Time: 6:50 PM
 * Description:
 */

public class XPlay extends GLSurfaceView implements SurfaceHolder.Callback{

    public XPlay(Context context, AttributeSet attrs) {
        super(context, attrs);
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

    public native void decode();
    public native void InitView(Object surface);
}
