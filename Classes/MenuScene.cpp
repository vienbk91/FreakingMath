/*
 * MenuScene.cpp
 *
 *  Created on: 1 Jun 2015
 *      Author: chu
 */


#include "MenuScene.h"

USING_NS_CC;


Scene* MenuScene::createScene(){
	auto scene = Scene::create();
	auto layer = MenuScene::create();

	scene->addChild(layer);

	return scene;
}


bool MenuScene::init(){
	if( !Layer::init()){
		return false;
	}


	Size size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	/////////////////////////////////////////////////////////////////
	// CREATE BACKGROUND
	/////////////////////////////////////////////////////////////////

	auto menuBG = Sprite::create("MenuSceneBG.png");
	menuBG->setScale((float)size.width / menuBG->getContentSize().width, (float)size.height / menuBG->getContentSize().height);
	menuBG->setPosition(Vec2(size.width/2 , size.height/2));

	this->addChild(menuBG);


	/////////////////////////////////////////////////////////////////
	// CREATE PLAY BUTTON
	/////////////////////////////////////////////////////////////////

	auto playButton = MenuItemImage::create("PlayBtn.png" , "PlayBtnSelected.png" , CC_CALLBACK_1(MenuScene::changePlayScene , this));
	playButton->setPosition(Vec2(size.width / 2, size.height / 2));
	auto menu = Menu::create(playButton , NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);


	return true;
}


void MenuScene::changePlayScene(Ref* pSender){
	auto playScene = PlayScene::createScene();
	Director::getInstance()->replaceScene(playScene);
}
