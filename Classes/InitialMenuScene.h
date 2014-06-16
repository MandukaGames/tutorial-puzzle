/*
 * InitialMenuScene.h
 *
 *  Created on: 10/06/2014
 *      Author: Manduka Games
 */

#ifndef INITIALMENUSCENE_H_
#define INITIALMENUSCENE_H_

#include "cocos2d.h"
#include "GamePlayScene.h"

/**
 * Scene showing a menu with the next options:
 *
 * - PLAY: User clicks this option in order to play the game. Callback: 'btnPlayCallback()'
 *
 */
class InitialMenuScene : public cocos2d::LayerColor {
private:

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(InitialMenuScene);

    // - Button callbacks
    void btnPlayCallback(Ref* sender);
};

#endif /* INITIALMENUSCENE_H_ */
