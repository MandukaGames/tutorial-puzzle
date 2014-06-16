#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "cocos2d.h"
#include "Piece.h"
#include "ResourceConstants.h"
#include "InitialMenuScene.h"
#include "MDPauseMenuInterfaz.h"
#include "MDPauseMenu.h"

class GamePlay : public cocos2d::LayerColor, public MDPauseMenuInterfaz
{
private:
    Vector<Piece *> puzzlePieces;
    Menu* menu;
    
    void appendBackAndPauseMenu();

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(GamePlay);

    // - Menu button callbacks
    void btnBackCallback(Ref* sender);
    void btnPauseCallback(Ref* sender);

    // - Pause menu interface
    virtual void shouldPauseGame();
    virtual void shouldResumeGame();
    virtual void shouldQuitGame();
    virtual void shouldRetryGame();
};

#endif // __HELLOWORLD_SCENE_H__
