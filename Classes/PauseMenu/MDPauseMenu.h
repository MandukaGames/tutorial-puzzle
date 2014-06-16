//
//  MDPauseMenu.h
//  Enigma
//
//  Created by rubenvot on 05/03/14.
//
//

#ifndef __Enigma__MDPauseMenu__
#define __Enigma__MDPauseMenu__

#include <iostream>
#include "cocos2d.h"
#include "MDPauseMenuInterfaz.h"

#define MENU_ITEMS_SPACING 40
#define TOP_DISTANCE 200

USING_NS_CC;

class MDPauseMenu: public CCLayerColor
{
protected:
    MDPauseMenuInterfaz *mTarget;
    
    void resumeGame(Ref* sender);
    void retryGame(Ref* sender);
    void quitGame(Ref* sender);
    
public:
    static MDPauseMenu* create(MDPauseMenuInterfaz* target);
    bool init(MDPauseMenuInterfaz* target);
    
};
#endif /* defined(__Enigma__MDPauseMenu__) */
