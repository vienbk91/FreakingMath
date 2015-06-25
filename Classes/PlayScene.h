/*
 * PlayScene.h
 *
 *  Created on: 1 Jun 2015
 *      Author: chu
 */

#ifndef PLAYSCENE_H_
#define PLAYSCENE_H_


#include "cocos2d.h"
#include "OverLayer.h"

USING_NS_CC;

class PlayScene : public LayerColor {
public:
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(PlayScene);

private:

	std::string _mathString;
	int _score;
	float _timer;
	bool _result;

	Label* _mathLabel;
	Label* _timeLabel;
	Label* _scoreLabel;

	Menu* _menu;

	void trueButtonCallback(Ref* pSender);
	void wrongButtonCallback(Ref* pSender);

	void update(float dt);
	void randomMath();
	void showOverLayer();

};

#endif /* PLAYSCENE_H_ */
