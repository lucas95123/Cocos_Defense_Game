#include "StartScene.h"
#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;

Scene* Start::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	//auto layer = Start::create();
	// add layer as a child to scene
	// scene->addChild(layer);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto rootNode = CSLoader::createNode("StartScene.csb");
	auto StartScene = Start::create();
	scene->addChild(StartScene);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Start::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("StartScene.csb");

	addChild(rootNode);
	scheduleOnce(schedule_selector(Start::updateOnce), 0.1f);

	Button *button1 = static_cast<Button*>(rootNode->getChildByName("buttonStart"));
	button1->addClickEventListener(CC_CALLBACK_1(Start::button1ClickCallback, this));

	auto listener1 = EventListenerTouchOneByOne::create();
	// 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
	listener1->setSwallowTouches(true);//不向下传递触摸
	listener1->onTouchBegan = CC_CALLBACK_2(Start::onTouchBegan, this);
	listener1->onTouchEnded = CC_CALLBACK_2(Start::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);

	return true;
}

void Start::update(float dt)
{
	log("update");
}

void Start::updateCustom(float dt)
{
	log("Custom update");
}

void Start::updateOnce(float dt)
{
	log("Once");
}

bool Start::onTouchBegan(Touch *touch, Event *unused_event)
{
	log("StartScene touched");
	/*create Vector<Sprite*>*/
	for (int i = 0; i < 10; i++)
	{
	auto sp = Sprite::create("SN11.png");
	sp->setPosition(Point(touch->getLocation().x, touch->getLocation().y+i*10));
	char szName[100] = { 0 };
	sprintf(szName, "SN11_%02d", i);
	sp->setName(szName);
	this->addChild(sp);
	map.insert(szName, sp);
	}
	return true;
}

void Start::onTouchEnded(Touch *touch, Event *unused_event)
{
	log("StartScene touch ended");
	/*create Vector<Sprite*>*/
	this->removeChild(map.find("SN11_01")->second);
}

void Start::button1ClickCallback(cocos2d::Ref* pSender)
{
	auto scene = HelloWorld::createScene();
	auto transitions = TransitionFade::create(1.0f, scene);
	Director::getInstance()->replaceScene(transitions);
}