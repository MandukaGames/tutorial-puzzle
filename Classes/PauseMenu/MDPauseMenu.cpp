//
//  MDPauseMenu.cpp
//
//  Created by rubenvot on 05/03/14.
//
//

#include "MDPauseMenu.h"

MDPauseMenu* MDPauseMenu::create(MDPauseMenuInterfaz* target)
{
	MDPauseMenu *pauseMenu = new MDPauseMenu();
    
    if (pauseMenu)
    {
    	pauseMenu->init(target);
    	pauseMenu->autorelease();
        target->shouldPauseGame();
        return pauseMenu;
    }
    CC_SAFE_DELETE(pauseMenu);
    
    return NULL;
}

bool MDPauseMenu::init(MDPauseMenuInterfaz* target)
{
    if (CCLayerColor::initWithColor(ccc4(0, 0, 0, 200)) )
    {
        mTarget = target;
        
        Size visibleSize  = Director::getInstance()->getVisibleSize();
        
        // Menu items
        MenuItemFont *btResume = MenuItemFont::create("Resume",
                                                          this,
                                                          menu_selector(MDPauseMenu::resumeGame));
        btResume->setColor(ccc3(255, 255, 255));
        btResume->setAnchorPoint(Vector2(0.5, 1));
        btResume->setPosition(Vector2(0, 0));
        
        MenuItemFont *btRetry = MenuItemFont::create("Retry",
                                                          this,
                                                          menu_selector(MDPauseMenu::retryGame));
        btRetry->setColor(ccc3(255, 255, 255));
        btRetry->setAnchorPoint(Vector2(0.5,1));
        btRetry->setPosition(Vector2(0, btResume->getPosition().y - btResume->getContentSize().height - MENU_ITEMS_SPACING));

        MenuItemFont *btExit = MenuItemFont::create("Exit",
                                                          this,
                                                          menu_selector(MDPauseMenu::quitGame));
        btExit->setColor(ccc3(255, 255, 255));
        btExit->setAnchorPoint(Vector2(0.5,1));
        btExit->setPosition(Vector2(0, btRetry->getPosition().y - btRetry->getContentSize().height - MENU_ITEMS_SPACING));
        
        // Menu
        Menu *menu = Menu::create(btResume, btRetry, btExit, NULL);
        menu->setPosition(Vector2(visibleSize.width/2,  visibleSize.height/2));
        addChild(menu);
        
        return true;
    }
    return false;
}

void MDPauseMenu::resumeGame(Ref* sender)
{
    removeFromParent();
    mTarget->shouldResumeGame();
}

void MDPauseMenu::quitGame(Ref* sender)
{
    removeFromParent();
    mTarget->shouldQuitGame();
}

void MDPauseMenu::retryGame(Ref* sender)
{
    removeFromParent();
    mTarget->shouldRetryGame();
}
