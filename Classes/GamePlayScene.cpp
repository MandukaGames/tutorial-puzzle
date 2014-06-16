#include "GamePlayScene.h"

USING_NS_CC;

Scene* GamePlay::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GamePlay::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePlay::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)))
    {
        return false;
    }
    
    Vector2 origin = Director::getInstance()->getVisibleOrigin();

    // Add Background shape
    Sprite * background = Sprite::create(kPuzzleBackground);
    background->setPosition(Vector2(this->getContentSize().width/2, this->getContentSize().height/2));
    this->addChild(background);
    
    // Position of pieces
    Vector2 positionPieceTopLeft     = Vector2(background->getPositionX()- background->getContentSize().width/4,
                                               background->getPositionY()+ background->getContentSize().height/4);
    
    Vector2 positionPieceTopRight    = Vector2(background->getPositionX()+ background->getContentSize().width/4,
                                               background->getPositionY()+ background->getContentSize().height/4);
    
    Vector2 positionPieceBottomLeft  = Vector2(background->getPositionX()- background->getContentSize().width/4,
                                               background->getPositionY()- background->getContentSize().height/4);
    
    Vector2 positionPieceBottomRight = Vector2(background->getPositionX()+ background->getContentSize().width/4,
                                               background->getPositionY()- background->getContentSize().height/4);
    
    Vector2 positionsArray[4];
    positionsArray[0] = positionPieceTopLeft;
    positionsArray[1] = positionPieceTopRight;
    positionsArray[2] = positionPieceBottomLeft;
    positionsArray[3] = positionPieceBottomRight;
    
    
    this->puzzlePieces = cocos2d::Vector<Piece *>{4};
    
    for (int i = 0; i < 4; i++)
    {
        // Add piece
    	Piece * piece = NULL;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

    	// - Create string with std::to_string from C++11 compiler
    	std::cout<<"piece_0"+std::to_string(i)+".png";
        piece = Piece::create("piece_0"+std::to_string(i)+".png");

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

        // - In Android, use std::ostringstream to build string with integers
        std::ostringstream os;
        os << "puzzle/piece_0" << i << ".png";
        piece = Piece::create(os.str());

#endif

        piece->setTargetPosition(positionsArray[i]);
        this->puzzlePieces.pushBack(piece);
        this->addChild(piece);
    }

    return true;
}
