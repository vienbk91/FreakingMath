/*
 * IntroScene.h
 *
 *  Created on: 1 Jun 2015
 *      Author: chu
 */

#ifndef INTROSCENE_H_
#define INTROSCENE_H_

#include "cocos2d.h"
#include "MenuScene.h"

USING_NS_CC;

class IntroScene : public Layer {
public:
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(IntroScene);

private:
	void changeToMenuScene(float dt);
};


#endif /* INTROSCENE_H_ */
