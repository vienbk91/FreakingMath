/*
 * OverLayer.h
 *
 *  Created on: 1 Jun 2015
 *      Author: chu
 */

#ifndef OVERLAYER_H_
#define OVERLAYER_H_

#include "cocos2d.h"
#include "MenuScene.h"

USING_NS_CC;

class OverLayer : public LayerColor {
public:

	static OverLayer* createWithColor(Color4B color);
	virtual bool initWithColor(Color4B color);

	void setScore(int score);
private:

	void gotoMenuScene(Ref* pSender);
	void gotoPlayScene(Ref* pSender);
	int _score;
	Label* _scoreLabel;
	Label* _highScoreLabel;

};



#endif /* OVERLAYER_H_ */
