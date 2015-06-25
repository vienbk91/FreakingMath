/*
 * PlayScene.cpp
 *
 *  Created on: 1 Jun 2015
 *      Author: chu
 */

#include "PlayScene.h"

USING_NS_CC;

Scene* PlayScene::createScene(){
	auto scene = Scene::create();
	auto layer = PlayScene::create();

	scene->addChild(layer);

	return scene;
}

bool PlayScene::init(){
	if( !LayerColor::initWithColor(Color4B(random(1,255) , random(1,255) , random(1,255) , 255 ))){
		return false;
	}


	Size size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	_timer = 5.0f;
	_score = 0.0f;
	/////////////////////////////////////////////////////////////////
	// CREATE BACKGROUND
	/////////////////////////////////////////////////////////////////


	MenuItemImage* trueBtn = MenuItemImage::create("TrueButton_Normal.png" , "TrueButton_Selected.png" , CC_CALLBACK_1(PlayScene::trueButtonCallback , this));

	float scale = (float)(size.width/2 - 40) / trueBtn->getContentSize().width;

	trueBtn->setScale(scale);
	MenuItemImage* wrongBtn = MenuItemImage::create("WrongButton_Normal.png" , "WrongButton_Selected.png" , CC_CALLBACK_1(PlayScene::wrongButtonCallback , this));
	wrongBtn->setScale(scale);

	_menu = Menu::create(wrongBtn , trueBtn  ,  NULL);
	_menu->alignItemsHorizontallyWithPadding(20.0f);
	_menu->setPosition(Vec2(size.width /2 , 10 + trueBtn->getContentSize().height * scale/2));

	this->addChild(_menu);

	/////////////////////////////////////////////////////////////////
	// CREATE LABEL MATH
	/////////////////////////////////////////////////////////////////

	_mathString = "";

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	_mathLabel = Label::createWithTTF(_mathString , "fonts/Square.ttf" , 300);
	_mathLabel->setAlignment(TextHAlignment::CENTER);
	_mathLabel->setLineHeight(300);
	_mathLabel->setPosition(Vec2(size.width/2 , size.height / 2 + 100));
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	_mathLabel = Label::createWithTTF(_mathString, "fonts/Square.ttf", 100);
	_mathLabel->setAlignment(TextHAlignment::CENTER);
	_mathLabel->setLineHeight(100);
	_mathLabel->setPosition(Vec2(size.width / 2, size.height / 2));

#endif

	this->addChild(_mathLabel);

	/////////////////////////////////////////////////////////////////
	// CREATE LABEL TIMER
	/////////////////////////////////////////////////////////////////

	_timeLabel = Label::createWithTTF("0" , "fonts/Square.ttf" , 100);
	_timeLabel->setAnchorPoint(Vec2(0.0f , 0.5f));
	_timeLabel->setPosition(Vec2(20 , size.height - 100));
	this->addChild(_timeLabel);

	/////////////////////////////////////////////////////////////////
	// CREATE LABEL SCORE
	/////////////////////////////////////////////////////////////////

	_scoreLabel = Label::createWithTTF(_mathString , "fonts/Square.ttf", 100);
	_scoreLabel->setAnchorPoint(Vec2(1.0f, 0.5f));
	_scoreLabel->setPosition(Point(size.width - 100, size.height - 100));
	this->addChild(_scoreLabel);

	/////////////////////////////////////////////////////////////////
	// RANDOM MATH
	/////////////////////////////////////////////////////////////////
	randomMath();



	//this->schedule(schedule_selector(PlayScene::update), 1.0f);
	this->scheduleUpdate();

	return true;
}

void PlayScene::update(float dt){
	_timer -= dt;
	_timeLabel->setString(String::createWithFormat("%.2f", _timer)->getCString());

	if (_timer < 0.0f)
	{
		_timer = 0.0f;
		_timeLabel->setString(String::createWithFormat("%.2f", _timer)->getCString());

		showOverLayer();
	}
}

void PlayScene::randomMath(){
	// Random gia tri 1 va 2 theo so diem cua nguoi choi
	int _firstNumber = random(1 , _score + 10);
	int _secondNumber = random(1 , _score + 10);

	// 0 la tru ,1 la cong
	int _operator = random(0,1);
	// true or false
	_result = random(0,1);

	switch(_operator){
	case 0: // Phep tru
	{
		if (_result){
			_mathString = String::createWithFormat("%d - %d\n = %d", _firstNumber, _secondNumber, _firstNumber - _secondNumber)->getCString();
		}
		else {
			_mathString = String::createWithFormat("%d - %d\n = %d", _firstNumber, _secondNumber, random(_firstNumber - _secondNumber + 1, _firstNumber + _secondNumber))->getCString();
		}

		break;
	}
	case 1: // Phep cong
	{
		if (_result){
			_mathString = String::createWithFormat("%d + %d\n = %d", _firstNumber, _secondNumber, _firstNumber + _secondNumber)->getCString();
		}
		else {
			_mathString = String::createWithFormat("%d + %d\n = %d", _firstNumber, _secondNumber, random(_firstNumber, _firstNumber + _secondNumber - 1))->getCString();
		}

		break;
	}
	default :
		break;
	}

	_mathLabel->setString(_mathString);

}


void PlayScene::trueButtonCallback(Ref* pSender){
	if (_result == true)
	{
		_timer = 5.0f;

		randomMath();

		_score++;
		_scoreLabel->setString(String::createWithFormat("%d", _score)->getCString());
	}
	else
	{
		showOverLayer();
	}
}

void PlayScene::wrongButtonCallback(Ref* pSender){
	if (_result == false)
	{
		_timer = 5.0f;

		randomMath();

		_score++;
		_scoreLabel->setString(String::createWithFormat("%d", _score)->getCString());
	}
	else
	{
		showOverLayer();
	}
}

void PlayScene::showOverLayer(){
	this->pause();
	_menu->setEnabled(false);

	auto overLayer = OverLayer::createWithColor(Color4B(0, 0, 0, 180));
	overLayer->setPosition(Vec2::ZERO);
	overLayer->setScore(_score);

	this->addChild(overLayer);
}
