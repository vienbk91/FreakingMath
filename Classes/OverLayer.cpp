/*
 * OverLayer.cpp
 *
 *  Created on: 1 Jun 2015
 *      Author: chu
 */


#include "OverLayer.h"

USING_NS_CC;

OverLayer* OverLayer::createWithColor(Color4B color){
	auto overLayer = new OverLayer();
	if (overLayer && overLayer->initWithColor(color))
	{
		overLayer->autorelease();
		return overLayer;
	}
	CC_SAFE_DELETE(overLayer);
	return nullptr;
}


bool OverLayer::initWithColor(Color4B color){
	if (!LayerColor::initWithColor(color))
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////////////////////////////////////////////////////////////
	// BACKGOUND OVERLAYER
	/////////////////////////////////////////////////////////////////////////////////////

	Sprite* overPanel = Sprite::create("Popup.png");

	float _scaleX = (float)((visibleSize.width * 2/3) / overPanel->getContentSize().width );
	float _scaleY = (float)((visibleSize.height * 2/3) / overPanel->getContentSize().height );

	overPanel->setScale( _scaleX , _scaleY);
	overPanel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 ));

	this->addChild(overPanel);

	/////////////////////////////////////////////////////////////////////////////////////
	// Score
	/////////////////////////////////////////////////////////////////////////////////////
	int _scoreFontSize , _hightScoreFontSize;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	_scoreFontSize = 250;
	_hightScoreFontSize = 70;
#endif 

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	_scoreFontSize = 100;
	_hightScoreFontSize = 30;
#endif


	_scoreLabel = Label::createWithTTF("0", "fonts/Square.ttf", _scoreFontSize);
	_scoreLabel->setPosition(origin.x + overPanel->getPositionX() , overPanel->getPositionY() + overPanel->getContentSize().height * _scaleY / 4);

	this->addChild(_scoreLabel);

	_highScoreLabel = Label::createWithTTF("0", "fonts/Square.ttf", _hightScoreFontSize);
	_highScoreLabel->setPosition(origin.x + overPanel->getPositionX() , _scoreLabel->getPositionY() - _highScoreLabel->getContentSize().height - overPanel->getContentSize().height * _scaleY / 6);

	this->addChild(_highScoreLabel);

	/////////////////////////////////////////////////////////////////////////////////////
	// Button
	/////////////////////////////////////////////////////////////////////////////////////

	auto menuBtn = MenuItemImage::create("MenuBtn.png", "MenuBtnSelected.png", CC_CALLBACK_1(OverLayer::gotoMenuScene, this));
	float _scaleBtn = (float) ((overPanel->getContentSize().width * _scaleX / 2 * 2/3) / menuBtn->getContentSize().width);
	menuBtn->setScale(_scaleBtn);
	auto replayBtn = MenuItemImage::create("AgainBtn.png", "AgainBtnSelected.png", CC_CALLBACK_1(OverLayer::gotoPlayScene, this));
	replayBtn->setScale(_scaleBtn);

	auto menu = Menu::create(menuBtn, replayBtn, nullptr);
	menu->alignItemsHorizontallyWithPadding(overPanel->getContentSize().width * _scaleX * 1/6 );
	menu->setPosition(origin.x + visibleSize.width / 2, overPanel->getPositionY() - overPanel->getContentSize().height * _scaleY / 4 + menuBtn->getContentSize().height /2);

	this->addChild(menu);

	return true;
}

void OverLayer::gotoMenuScene(Ref* pSender)
{
	auto menuscene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInL::create(0.25f, menuscene));
}

void OverLayer::gotoPlayScene(Ref* pSender)
{
	auto playscene = PlayScene::createScene();
	Director::getInstance()->replaceScene(playscene);
}
void OverLayer::setScore(int score)
{
	_score = score;

	auto userdefault = UserDefault::getInstance(); // Su dung UserDefault de luu tru db tam thoi voi dung luong thap
	auto highscore = userdefault->getIntegerForKey("HIGHSCORE", 0); // lay gia tri luu bang key

	if (_score > highscore)
	{
		highscore = _score;
		userdefault->setIntegerForKey("HIGHSCORE", highscore); // set gia tri luu bang key
	}

	userdefault->flush();

	_scoreLabel->setString(String::createWithFormat("%d", _score)->getCString());
	_highScoreLabel->setString(String::createWithFormat("HIGH SCORE: %d", highscore)->getCString());
}
