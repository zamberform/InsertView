#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include <jni.h>
#include "platform/android/jni/JniHelper.h"

extern "C" {
JNIEXPORT jint JNICALL Java_com_sample_insertwebview_MainNativeOne_closeWebView
  (JNIEnv *, jobject);
}


class HelloWorld : public cocos2d::Layer
{
public:
	static void resetWebViewInstance();
    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    CREATE_FUNC(HelloWorld);

    void openWebViewInJni();

    virtual void update(float time);

private:
    void changeScene();

};

#endif // __HELLOWORLD_SCENE_H__
