#ifndef __START_SCENE_H__
#define __START_SCENE_H__
#include <string>
#include "cocos2d.h"

USING_NS_CC;

class Start : public cocos2d::Layer
{
private:

	Map<std::string,Sprite*> map;

public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	//overriding default scheduler
	void update(float dt) override;

	//custom scheduler
	void updateCustom(float dt);

	//scheduler once
	void updateOnce(float dt);

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	void button1ClickCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Start);
};

#endif // __START_SCENE_H__