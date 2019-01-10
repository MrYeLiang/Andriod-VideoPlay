//
// Created by 叶亮 on 2019/1/8.
//

#include <jni.h>
#include <android/native_window_jni.h>
#include <EGL/egl.h>
#include <android/log.h>
#include <GLES2/gl2.h>

#define LOGD(...) __android_log_print(ANDROID_LOG_WARN, "===opengl===", __VA_ARGS__)

//顶点着色器glsl
#define GET_STR(x) #x
static const  char *vertexShader = GET_STR(
        attribute vec4 aPosition; //顶点坐标
        attribute vec2 aTexCoord; //材质顶点坐标
        varying vec2 vTexCoord;  //输出的材质坐标
        void main(){
            vTexCoord = vec2(aTexCoord.x, 1.0-aTexCoord.y);
            gl_Position = aPosition;
        }

);

//片元着色器，软解码和部分x86硬解码
static const char *fragYUV420P = GET_STR(
    precision mediump float;  //精度
    varying vec2 vTexCoord;  //顶点着色器传递的坐标
    uniform sampler2D yTexture; //输入的材质 (不透明度， 单像素)
    uniform sampler2D uTexture;
    uniform sampler2D vTexture;

    void main(){
        vec3 yuv;
        vec3 rgb;
        yuv.r = texture2D(yTexture,vTexCoord).r;
        yuv.g = texture2D(uTexture,vTexCoord).r- 0.5;
        yuv.b = texture2D(vTexture,vTexCoord).r - 0.5;
        rgb = mat3(1.0,     1.0,        1.0,
                   0.0, -0.39465, 2.03211,
                   1.13983, -0.58060, 0.0)*yuv;
        //输出像素颜色
        gl_FragColor = vec4(rgb,1.0);

    }
);

GLint InitShader(const char *const code, GLint type){
    //创建shader
    GLint sh = glCreateShader(type);
    if(sh == 0){
        LOGD("glCreateShader %d failed!", type);
        return 0;
    }

    //加载shader
    glShaderSource(sh,
                   1,       //shader数量
                   &code,   //shader代码
                   0);      //代码长度

    //编译shader
    glCompileShader(sh);

    //获取编译情况
    GLint status;
    glGetShaderiv(sh, GL_COMPILE_STATUS, &status);
    if(status == 0){
        LOGD("glCompileShader failed");
        return 0;
    }

    LOGD("glCompileShader success");
    return sh;


}


extern "C"
JNIEXPORT void JNICALL
Java_com_practice_1opengl_PlayView_open(JNIEnv *env, jobject instance, jstring url_,
                                        jobject surfaceView) {
    const char *url = env->GetStringUTFChars(url_, 0);

    //1 获取原始窗口
    ANativeWindow *nwin = ANativeWindow_fromSurface(env, surfaceView);


    //=======================================EGL
    // 1 EGL dispaly创建和初始化
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if(display == EGL_NO_DISPLAY)
    {
        LOGD("eglGetDisplay failed");
        return;
    }

    //=======================================surface
    //2 surface窗口配置
    //输出配置
    EGLConfig config;
    EGLint configNum;
    EGLint configSpec[] = {
            EGL_RED_SIZE,8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_SURFACE_TYPE,EGL_WINDOW_BIT,EGL_NONE
    };

    if(EGL_TRUE != eglChooseConfig(display, configSpec, &config, 1, &configNum)){
        LOGD("eglChooseConfig failed!");
        return;
    }

    //创建surface
    EGLSurface  winsurface = eglCreateWindowSurface(display, config, nwin, 0);
    if(winsurface == EGL_NO_SURFACE){
        LOGD("eglCreateWindowSurface failed!");
        return;
    }

    //3 context 创建关联的上下文
    const EGLint ctxAttr[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
    };
    EGLContext  context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxAttr);
    if(context == EGL_NO_CONTEXT){
        LOGD("eglCreateContext failed!");
        return;
    }

    if(EGL_TRUE != eglMakeCurrent(display, winsurface, winsurface, context)){
        LOGD("eglMakeCurrent failed！");
        return;
    }

    LOGD("EGL Init Success!");

    //顶点shader初始化
    GLint vsh = InitShader(vertexShader, GL_VERTEX_SHADER);

    //片元yuv420 shader初始化
    GLint fsh = InitShader(fragYUV420P, GL_FRAGMENT_SHADER);
}