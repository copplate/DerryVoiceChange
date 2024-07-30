#include <jni.h>
#include <string>
#include <unistd.h>
#include "com_example_derryvoicechangeprac_JavaMainActivity.h"

using namespace FMOD;//命名空间


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_derryvoicechangeprac_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

//extern "C" 表示必须采用c的标准。原因：1、因为c语言不允许函数重载，如果不写extern "C"关键字，会出现c++函数重载，就会造成混乱
//                                  2、JNIEnv的里面所有的函数指针，都是采用的c的标准，所以必须明确是c的定义方式。
//JNIEXPORT表示对外暴露JNI
//JNICALL是表示这是一个jni函数的一个标记
extern "C" JNIEXPORT void JNICALL Java_com_example_derryvoicechangeprac_JavaMainActivity_voiceChangeNative
        (JNIEnv * env, jobject thiz, jint mode, jstring path){
        char * content = "默认，播放完毕";//相当于Java的字符串String
        //Java是万物皆对象，c是万物皆指针
        //把 JNIEnv里的几百个函数指针玩透，jni就过关了
        //jstring转换成char*
    const char* path_ = env->GetStringUTFChars(path, NULL);
    System * system = 0;//fmod音效引擎系统
    Sound * sound = 0;//fmod声音
    Channel * channel = 0;//通道 音轨
    DSP * dsp = 0;//数字信号处理(digital signal process)

    //第一步 创建系统。执行完后，system就有丰富的值了
    System_Create(&system); //因为参数是二级指针，所以要用&再次取出指针所对应的地址
    //第二步 系统的初始化，32是最大的音轨数
    system->init(32,FMOD_INIT_NORMAL,0);
    //第三步 创建声音，最重要的环节是把声音在音轨上播放，需要把声音初始化，如果声音是空指针肯定不行
    system->createSound(path_, FMOD_DEFAULT, 0, &sound);
    //第四步 播放声音
    system->playSound(sound, 0, false, &channel);

    bool isPlay = true;
    while(isPlay){
        channel->isPlaying(&isPlay);//如果通道播放完成，会自动修改isPlay地址所对应的值为false
        usleep(1000*30); // 休眠30毫秒
    }

    // 好习惯：释放资源
    dsp->release();
    sound->release();
    system->close();
    system->release();
    env->ReleaseStringUTFChars(path, path_);




}