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

    setPosition(origin);

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

    // - Append menu
    appendBackAndPauseMenu();

    return true;
}

void GamePlay::appendBackAndPauseMenu() {
	Size visibleSize = Director::getInstance()->getVisibleSize();

    // - Back button
    MenuItemImage *btnBack = MenuItemImage::create(kButtonBack, kButtonBackPressed, CC_CALLBACK_1(GamePlay::btnBackCallback, this));
    btnBack->setPosition(Vector2(100, visibleSize.height - 100));

    // - Pause button
    MenuItemImage *btnPause = MenuItemImage::create(kButtonPause, kButtonPausePressed, CC_CALLBACK_1(GamePlay::btnPauseCallback, this));
    btnPause->setAnchorPoint(Vector2(1, 0.5));
    btnPause->setPosition(Vector2(visibleSize.width - 100, visibleSize.height - 100));

    menu = Menu::create(btnBack,btnPause, NULL);
    menu->setAnchorPoint(Vector2(0.5, 0.5));
    menu->ignoreAnchorPointForPosition(false);
    menu->setPosition(Vector2(visibleSize.width/2, visibleSize.height/2));
    menu->setContentSize(visibleSize);
    addChild(menu);
}

void GamePlay::btnBackCallback(Ref* sender) {
	// - Go back to initial menu
    auto scene = InitialMenuScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void GamePlay::btnPauseCallback(Ref* sender) {
    pauseSchedulerAndActions();

    MDPauseMenu *pauseMenu = MDPauseMenu::create(this);
    addChild(pauseMenu, 5);
}

/**
 *
 * PAUSE MENU INTERFACE
 *
 */

void GamePlay::shouldPauseGame()
{
    menu->setEnabled(false);
}

void GamePlay::shouldResumeGame()
{
    // - Enable gameplay menu buttons
    menu->setEnabled(true);
}

void GamePlay::shouldQuitGame()
{
	// - Go back to initial menu
    auto scene = InitialMenuScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void GamePlay::shouldRetryGame()
{
    // - Enable gameplay menu buttons
    menu->setEnabled(true);
}
