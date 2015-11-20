#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <sstream>

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace cocostudio;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	//auto layer = HelloWorld::create();
    // add layer as a child to scene
  // scene->addChild(layer);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto rootNode = CSLoader::createNode("MainScene.csb");
	auto helloworldScene = HelloWorld::create();
	scene->addChild(helloworldScene);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);
	scheduleOnce(schedule_selector(HelloWorld::updateOnce), 0.1f);

	auto node1 = rootNode->getChildByName("FileNode_1");

	auto listener1 = EventListenerTouchOneByOne::create();
	// 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
	listener1->setSwallowTouches(true);//不向下传递触摸
	listener1->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener1->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener1->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);

    return true;
}

void HelloWorld::update(float dt)
{
	log("update");
}

void HelloWorld::updateCustom(float dt)
{
	log("Custom update");
}

void HelloWorld::updateOnce(float dt)
{
	log("Once");
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	log("touched");
	auto btn1 = Sprite::create("SN11.png");
	btn1->setPosition(Point(touch->getLocation().x, touch->getLocation().y));

	/*Creating an animation*/
	auto cache = AnimationCache::getInstance();
	auto animation = Animation::create();
	for (int i = 1; i<4; i++)
	{
		char szName[100] = { 0 };
		sprintf(szName, "SN11_%02d.png", i);
		animation->addSpriteFrameWithFile(szName);
	}
	animation->setDelayPerUnit(0.3f / 3.0f);
	animation->setRestoreOriginalFrame(true);
	cache->addAnimation(animation, "attack");
	
	/*End of creating an animation*/

	auto animate = Animate::create(cache->getAnimation("attack"));
	btn1->runAction(RepeatForever::create(Sequence::create(animate, animate->reverse(), NULL)));
	btn1

	auto moveTo = JumpBy::create(4, Point(960 - touch->getLocation().x, 0), 20, 8);
	auto flipTo = FlipX::create(true);
	auto action = Sequence::create(moveTo, flipTo, moveTo->reverse(),flipTo->reverse(),NULL);
	auto speed = Speed::create(RepeatForever::create(action), 1.1f);
	btn1->runAction(speed);
	Director::getInstance()->getRunningScene()->addChild(btn1);

	/*Skeleton*/

	/*Partical*/
	auto flame = ParticleSystemQuad::create("Smoke.plist");
	flame->setPosition(Point(touch->getLocation().x, touch->getLocation().y));
	Director::getInstance()->getRunningScene()->addChild(flame,1,"flame");
	return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event)
{
	std::stringstream ss;
	ss << touch->getLocation().x<<" ";
	ss<<touch->getLocation().y;
	std::string s;
	ss >> s;
	auto txt = Text::create(s, "Arial", 20);
	txt->setPosition(Point(touch->getLocation().x, touch->getLocation().y));
	this->addChild(txt,1);
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
	log("x:");
	log(touch->getLocation().x);
	log("y:");
	log(touch->getLocation().y);
}

void HelloWorld::button1ClickCallback(cocos2d::Ref* pSender)
{
	auto btn1 = Sprite::create("SN11_02.png");
	btn1->setPosition(Point(300, 300));
	Director::getInstance()->getRunningScene()->addChild(btn1);
}