/*
 * IntroScene.cpp
 *
 *  Created on: 1 Jun 2015
 *      Author: chu
 */

#include "IntroScene.h"

USING_NS_CC;

Scene* IntroScene::createScene(){
	auto scene = Scene::create();
	auto layer = IntroScene::create();

	scene->addChild(layer);

	return scene;
}


bool IntroScene::init()
{
	if(!Layer::init()){
		return false;
	}


	Size size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite* introBG = Sprite::create("IntroSceneBG.png");

	introBG->setPosition(Vec2(size.width/2 , size.height/2));
	introBG->setScale((float)size.width / introBG->getContentSize().width, (float)size.height / introBG->getContentSize().height);
	addChild(introBG);

	this->scheduleOnce(schedule_selector(IntroScene::changeToMenuScene) , 2.0f);

	return true;
}

void IntroScene::changeToMenuScene(float dt){
	auto menuScene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInR::create(0.25f , menuScene));
}
