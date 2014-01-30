#include "HelloWorldScene.h"

#include <jni.h>
#include "platform/android/jni/JniHelper.h"
USING_NS_CC;

#include "SecondWorldScene.h"

static bool webview_close_flag = false;

void HelloWorld::resetWebViewInstance() {
	webview_close_flag = false;
}

JNIEXPORT jint JNICALL Java_com_sample_insertwebview_MainNativeOne_closeWebView(
		JNIEnv* env, jobject obj) {
	webview_close_flag = true;
	return 1;
}

Scene* HelloWorld::createScene() {
	auto scene = Scene::create();

	auto layer = HelloWorld::create();

	scene->addChild(layer);

	return scene;
}

bool HelloWorld::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto label = LabelTTF::create("hello world", "Arial", 24);
	label->setPosition(
			Point(origin.x + visibleSize.width / 2,
					origin.y + visibleSize.height
							- label->getContentSize().height));

	this->addChild(label, 1);

	auto sprite = Sprite::create("HelloWorld.png");

	sprite->setPosition(
			Point(visibleSize.width / 2 + origin.x,
					visibleSize.height / 2 + origin.y));

	this->addChild(sprite, 0);

	auto labelFade = LabelTTF::create("<Touch To Start>", "Arial", 50);

	labelFade->setPosition(
			Point(origin.x + visibleSize.width / 2,
					origin.y + visibleSize.height / 4));

	this->addChild(labelFade, 2);
	labelFade->runAction(
			RepeatForever::create(
					Sequence::create(FadeTo::create(0.5f, 0),
							FadeTo::create(0.5, 255), nullptr)));

	auto listenerTouch = EventListenerTouch::create(
			Touch::DispatchMode::ONE_BY_ONE);
	listenerTouch->setSwallowTouches(true);

	listenerTouch->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
	};

	listenerTouch->onTouchEnded =
			[=](Touch* touch, Event* event) {
				labelFade->stopAllActions();
				labelFade->runAction(Spawn::createWithTwoActions(ScaleTo::create(1.0,8.0),FadeTo::create(0.5,0)));
				openWebViewInJni();
			};

	EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(
			listenerTouch, this);

	this->scheduleUpdate();

	return true;
}

void HelloWorld::openWebViewInJni() {
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
			"com/sample/insertwebview/MainNativeOne", "getInstance",
			"()Lcom/sample/insertwebview/MainNativeOne;");
	jobject jobj;
	if (isHave) {
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);

		isHave = JniHelper::getMethodInfo(minfo,
				"com/sample/insertwebview/MainNativeOne", "openWebview", "()V");
		if (isHave) {
			minfo.env->CallVoidMethod(jobj, minfo.methodID);
		}
	}
}

void HelloWorld::update(float time) {

	if (webview_close_flag) {
		this->runAction(
				Sequence::create(
						Spawn::createWithTwoActions(DelayTime::create(0.6),
								FadeTo::create(0.5, 125)),
						CallFunc::create(
								CC_CALLBACK_0(HelloWorld::changeScene, this)),
						nullptr));
	}
}

void HelloWorld::changeScene() {
	auto scene = SecondWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

