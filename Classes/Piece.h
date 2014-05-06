//
//  Piece.h
//  PuzzleTutorial
//
//  Created by Rubén Vázquez on 05/05/14.
//
//

#ifndef __PuzzleTutorial__Piece__
#define __PuzzleTutorial__Piece__
#define LOCATION_ACCURACY 100

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class Piece: public Sprite
{
    bool _actived;
    Vector2 _targetPosition;
    EventListenerTouchOneByOne *listener;
    void setActived(bool active);
public:
    
    // Constructor
    static Piece* create(const std::string &filename);
    virtual bool init(const std::string &filename);
    
    void setTargetPosition(Vector2 targetPosition);
    bool currentLocationSuccess();
    
    bool onTouchBegan(Touch*, Event*);
    void onTouchMoved(Touch*, Event*);
    void onTouchEnded(Touch*, Event*);
    
};

#endif /* defined(__PuzzleTutorial__Piece__) */
