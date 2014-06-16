/*
 * InitialMenuScene.cpp
 *
 *  Created on: 10/06/2014
 *      Author: Manduka Games
 */

#include "InitialMenuScene.h"

USING_NS_CC;

Scene* InitialMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = InitialMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool InitialMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)))
    {
        return false;
    }

    Vector2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();

    // - Build the "PLAY" menu item
    MenuItemFont *btnPlay = MenuItemFont::create("PLAY",
                                                      this,
                                                      menu_selector(InitialMenuScene::btnPlayCallback));

    // - Set menu item text color
    btnPlay->setColor(ccc3(0, 0, 0));

    // - Build the menu holding the menu item
    CCMenu *menu = CCMenu::create(btnPlay, NULL);
    menu->setPosition(ccp(visibleSize.width/2,  visibleSize.height/2));

    // - Add menu to the scene
    addChild(menu);

    return true;
}

void InitialMenuScene::btnPlayCallback(Ref* sender) {
    // - Run GamePlay scene when the user clicks "PLAY"
    auto scene = GamePlay::createScene();
    Director::getInstance()->replaceScene(scene);
}
