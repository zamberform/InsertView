#include "SecondWorldScene.h"

#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#include "HelloWorldScene.h"

USING_NS_CC;

Scene* SecondWorld::createScene() {
	auto scene = Scene::create();

	auto layer = SecondWorld::create();

	scene->addChild(layer, 1);

	return scene;
}

bool SecondWorld::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(SecondWorld::menuCloseCallback, this));

	closeItem->setPosition(
			Point(
					origin.x + visibleSize.width
							- closeItem->getContentSize().width / 2,
					origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	auto label = LabelTTF::create("Second Scene", "Arial", 30);

	label->setPosition(
			Point(origin.x + visibleSize.width / 2,
					origin.y + visibleSize.height
							- label->getContentSize().height));

	this->addChild(label, 2);

	auto dailogLabel = LabelTTF::create("openDailog", "", 30);
	auto dailogItem = MenuItemLabel::create(dailogLabel,
			CC_CALLBACK_1(SecondWorld::openDailogInJni, this));
	dailogItem->setPosition(
			Point(visibleSize.width / 3.5, visibleSize.height / 2));

	auto activityLabel = LabelTTF::create("openActivity", "", 30);
	auto activityItem = MenuItemLabel::create(activityLabel,
			CC_CALLBACK_1(SecondWorld::openOtherActivity, this));
	activityItem->setPosition(
			Point(visibleSize.width / 2, visibleSize.height / 2));

	auto resourceLabel = LabelTTF::create("insertResource", "", 30);
	auto resourceItem = MenuItemLabel::create(resourceLabel,
			CC_CALLBACK_1(SecondWorld::insertOtherLayoutByResourceId, this));
	resourceItem->setPosition(
			Point(visibleSize.width / 1.35, visibleSize.height / 2));

	auto menuController = Menu::create(dailogItem, activityItem, resourceItem,
			NULL);
	menuController->setPosition(Point::ZERO);
	this->addChild(menuController, 2);

	auto backLabel = LabelTTF::create("backToFirst", "", 30);
	backLabel->setColor(Color3B::BLUE);
	auto backItem = MenuItemLabel::create(backLabel,
			CC_CALLBACK_1(SecondWorld::backToFirst, this));
	backItem->setPosition(
			Point(visibleSize.width - backItem->getContentSize().width / 2,
					visibleSize.height - backItem->getContentSize().height));

	auto backMenu = Menu::create(backItem, nullptr);
	backMenu->setPosition(Point::ZERO);
	this->addChild(backMenu, 3);

	return true;
}

void SecondWorld::backToFirst(Object* pSender) {
	auto first = HelloWorld::createScene();
	HelloWorld::resetWebViewInstance();
	Director::getInstance()->replaceScene(first);
}

void SecondWorld::menuCloseCallback(Object* pSender) {
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void SecondWorld::openDailogInJni(Object* pSender) {
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
			"com/sample/insertwebview/MainNativeOne", "getInstance",
			"()Lcom/sample/insertwebview/MainNativeOne;");
	jobject jobj;
	if (isHave) {
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);

		isHave = JniHelper::getMethodInfo(minfo,
				"com/sample/insertwebview/MainNativeOne", "showDialog", "()V");
		if (isHave) {
			minfo.env->CallVoidMethod(jobj, minfo.methodID);
		}
	}
}

void SecondWorld::insertOtherLayoutByResourceId(Object* pSender) {
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
			"com/sample/insertwebview/MainNativeOne", "getInstance",
			"()Lcom/sample/insertwebview/MainNativeOne;");
	jobject jobj;
	if (isHave) {
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);

		isHave = JniHelper::getMethodInfo(minfo,
				"com/sample/insertwebview/MainNativeOne",
				"insertLayoutByResoureId", "()V");
		if (isHave) {
			minfo.env->CallVoidMethod(jobj, minfo.methodID);
		}
	}
}

void SecondWorld::openOtherActivity(Object* pSender) {
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
			"com/sample/insertwebview/MainNativeOne", "getInstance",
			"()Lcom/sample/insertwebview/MainNativeOne;");
	jobject jobj;
	if (isHave) {
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);

		isHave = JniHelper::getMethodInfo(minfo,
				"com/sample/insertwebview/MainNativeOne", "openOtherActivity",
				"()V");
		if (isHave) {
			minfo.env->CallVoidMethod(jobj, minfo.methodID);
		}
	}
}

