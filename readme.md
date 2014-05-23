##Available in spanish. 

There is also an spansih version of this tutorial in: [Manduka Games](http://www.mandukagames.com) 

##About Manduka Games
[Manduka Games](http://www.mandukagames.com) it´s a mid size videogames studio based in Barcelona. Since our beginnings we have made an effort to open some of our source code and be an active part of the community. We are proud to say that Open Source is in our DNA. So, in that way, this tutorial is distributted under MIT license. We encourage all who want to contribute to send us new variations or extensions from this tutorial. We are commited to include and share every new material we receive to improve the tutorial. 
 
#Creating a simple puzzle with Cocos2d-x v3

_In this tutorial we are going to create a game from scratch. Our puzzle will have four piezes, but if you like how it works and you want to experiment you will find easy to expand it and add more functionalities (gamification!). Let us know your impressions and how this tutorial has helped you to create your own game._

## Setting up the development environment

The new version 3 of Cocos2d-x it's a big step fordward. If you are still using the version 2 you should think about migrating as soon as possible. 

In this tutorial we will supose that you have already downloaded cocos2d-x v3 to your computer and you have instaled the new  _console tool_. If you are not at this point you should visit the  [official github](https://github.com/cocos2d/cocos2d-x) of cocos2d-x. There, you will find every previous steps.

We will use OSX Maverick for this tutorial and we will compile the game for Mac. But only because it's faster and you don't need a device. But keep in mind that every code we are writting here will run in another platforms. We have tried also in an iPad and if you configure the project for Android it should work too. 

Let's go to work!

##Creating a new project with Cocos2dx v3

The first thing we should do is to create a new project. In this case I will create it in the Desktop of my Mac. Open the Terminal and create a new project with the console tool of Cocos. 

	MacBook-Pro:bin Ruben$ cocos new PuzzleTutorial -p com.mandukagames.puzzle -l cpp -d /Users/Ruben/Desktop 
	Runing command: new
	> Copy template into /Users/Ruben/Desktop/PuzzleTutorial
	> Copying cocos2d-x files...
	> Rename project name from 'HelloCpp' to 'PuzzleTutorial'
	> Replace the project name from 'HelloCpp' to 'PuzzleTutorial'
	> Replace the project package name from 'org.cocos2dx.hellocpp' to 'com.mandukagames.puzzle'

If everything was ok you should have a new project in your Desktop called "PuzzleTutorial". Now just go into the folder _proj.ios_mac_ and open the file  _PuzzleTutorial.xcodeproj_

![](https://cloud.githubusercontent.com/assets/1536171/2887204/93b59e02-d4f7-11e3-88ff-688ccb4e48a3.png)


The best way to confirm that everything was ok is to run the project. Go to Xcode and close to the play/stop buttons select the target _PuzzleTutorial Mac_ and _My Mac_ as a device. A new OSX window should be openned executing the project. 

![](https://cloud.githubusercontent.com/assets/1536171/2887241/3df8152a-d4f8-11e3-88e1-6275c22af5ae.png)

##Customizing the new project and creating new classes

We could start coding right now. But I don't like to have a file named _HelloWorldScene_ in my project. So the first we are going to rename it to  _GamePlayScene_ that it's much more descriptive. If your karma doesn't feel wrong about this stuff you can just skitp this step ;-). 

We alse will rename the class  _HelloWorld_ to _GamePlay_ and will make all the necessary changes in code. The easiest way is to use the  _Find and replace_ tool from Xcode  and change very occurrences from "HelloWorld" to "GamePlay". Once is done just press __cmd+b__ to compile and check that everything is ok.

Our puzzle will be compound from a _Layer_ that we will use as  "canvas" and for pieces which user will be able to move to fit it in the right place. This is a good moment to create the class  _Piece_.

___Piece___  will be the class representing the "pieces" of our puzzle. Since it's main representation will be an image we will make it a subclass of _Sprite_. Just go to Xcode press _Add new file_, choose the file  _C++ Class_  and press Accept. Later we will come back over this file. 

Now we will add to the project the resources for the canvas and the pieces. 

We have created an small puzzle from an illustration of Marina (Our designer) with our mascot Manduki. You will find the resources  [here](https://github.com/MandukaGames/tutorial-puzzle/tree/master/Resources/puzzle). 

The Xcode inspector should look now like this:
![](https://cloud.githubusercontent.com/assets/1536171/2887354/4d0e4a32-d4fa-11e3-9fae-1e1ab63dd6f1.png)

## Codding the core of the puzzle

### Delete unnecessary files
We are going to delete de unnecesary code from the class _GamePlay_. Our _init_ method should look like:

	// on "init" you need to initialize your instance
	bool GamePlay::init()
	{
		if ( !Layer::init() )
		{
			return false;
		}
		
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vector2 origin = Director::getInstance()->getVisibleOrigin();
		return true;
	}

I used to leave there the variables _visibleSize_ and _origin_ because finally for one reason or another you always get that you need them. 

You can fulminate the method _menuCloseCallback_ - and his declaration in the header file since it's not necesary for this tutorial. 

_Note: you can keep the method closeCallback if you want to keep the close button in the game, but remember to dont delete the png of the sprite or you will get a crash._

### Add the background image and change the background color

In order to show the users where are expected they move the pieces we will add an image to the Scene. We will use it as a background and will position it in the center. 

_We have marked with the "+"  characterlas the lines that you must add to your init method_

	// on "init" you need to initialize your instance
	bool GamePlay::init()
	{
	    //////////////////////////////
	    // 1. super init first
	    if ( !Layer::init() )
	    {
	        return false;
	    }
	    
	    Size visibleSize = Director::getInstance()->getVisibleSize();
	    Vector2 origin = Director::getInstance()->getVisibleOrigin();

	    +// Add Background shape
	    +Sprite * background = Sprite::create("background.png");
	    +background->setPosition(Vector2(this->getContentSize().width/2, this->getContentSize().height/2));
	    +this->addChild(background);
	    
	    return true;
	}
	
One thing that it's not necessary but we will also do is to change the background color of the scene. Change the heritage of the class from _Layer_ to _LayerColor_ 
	
	class GamePlay : public cocos2d::LayerColor
	
And now change the init for another call that allow you to change the color

	- if (!Layer::init())
	+ if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))

### Adding coordinates to the pieces

Now we are going to positionate the pieces in the screen. 

If you really like this tutorial and finally want to develope a real game starting from it you should create some method little bit more sofisticated to setup the goal position of the pieces in the screen. 
For example: you could create a format _.plist_ based to create an array of pieces and relationate it to a level. This would allow you to create more puzzles and add _levels_ easyly .

But it's not the target of this tutorial to talk about game engines and dynamics so we will just hardcode the init position and goal position for each piece. 

_(If there is enought interested people just visit us in  [Manduka Games](http://www.mandukagames.com) and let us now. We will be please to make  a second part of this tutorial covering another topics like techniques to build game levels_

#### Init position

Starting from background and with a little bit of basig geometry we will calculate the correct position of the puzzle pieces. Bassically what we do is to create a Vector2 - formerly known as  _CCPoint_ - to represent the center of each piece. 

    // Position of pieces
    Vector2 positionPieceTopLeft     = Vector2(background->getPositionX()- background->getContentSize().width/4,
                                               background->getPositionY()+ background->getContentSize().height/4);
    
    Vector2 positionPieceTopRight    = Vector2(background->getPositionX()+ background->getContentSize().width/4,
                                               background->getPositionY()+ background->getContentSize().height/4);
    
    Vector2 positionPieceBottomLeft  = Vector2(background->getPositionX()- background->getContentSize().width/4,
                                               background->getPositionY()- background->getContentSize().height/4);
    
    Vector2 positionPieceBottomRight = Vector2(background->getPositionX()+ background->getContentSize().width/4,
                                               background->getPositionY()- background->getContentSize().height/4);


### The piece class

_Previously we have created the __Piece__ class and now is the time to pick up again._

We will start with the class definition. Just go to the file Piece.h and paste the next code. Don´t worry if you dont understand something, we will study the meanning soon. 

	#include "cocos2d.h"

	USING_NS_CC;

	class Piece: public Sprite
	{
	    bool _actived;
	    Vector2 _targetPosition;
	    
	    void setActived(bool active);
	    
	public:
	        
	    // Constructor
	    static PLPiece* create(const std::string &filename);
	    virtual bool init(const std::string &filename);
    
	    void setTargetPosition(Vector2 targetPosition);
	    bool currentLocationSuccess();
	};

As you can see our pieces will be sprites. We will customize the functions _create_ and _init_ to init the piece with the desired image (which we will pass as a param). 

We have defined to instance vars __actived_ and __targetPosition_:

*  ___actived__  serves as to identify if a piece is actived in a determinate moment or not. We will now if a user is touching this pieces in a concrete momment. We will use this var to know if we should give feedback to the user. For example: if the user is touching the piece we could make it little bit bigger or change the color.  
*   In ___targetPosition__  we will save the exact point in which we consider this piece would be well placed. We also have defined a public setter for this var. 

Finally we have defined a method to ask if the position of the piece in a concret moment is the good one. That will be very useful when we code the logic of the pieces. 

#### Constructors

Let´s go with the implementation of this two basics *create* and *init*. 

This methods are an standard pattern from Cococs2d-x. If you are veteran from Cocos2d-x probably you know them very well and if not you will learn it very fast because if you are planning to develop games you will be using them very often. 

If you are asking yourself how them work just visit the wiki of [Cocos2d-x](http://www.cocos2d-x.org/wiki). Theres a section about memory management and the retain/release pattern inherited from Objetive-C.

Add this code to Piece.m

	Piece* Piece::create(const std::string &filename)
	{
	    Piece *pRet = new Piece();
		if (pRet && pRet->init(filename))
		{
			pRet->autorelease();
		}
		else
		{
			delete pRet;
			pRet = NULL;
		}
	    return pRet;

	}


	bool Piece::init(const std::string &filename)
	{
	    if (!Sprite::initWithFile(filename)) {
	        return false;
	    }

	    return true;
	}
		
	void Piece::setTargetPosition(cocos2d::math::Vector2 targetPosition)
	{
	    this->_targetPosition = targetPosition;
	}


At this point just comment for a moment the methods that we still haven't implemented and press __cmd+r__ to compile and run. We will check that everything works. 
 

### Adding pieces to the scene 

Come back to the GamePlay class, to the place where we were adding the pieces position. Till now we had four vars to save positions in the screeen. 

We are going to create the pieces and assign each position to a different piece. To avoid coding four times the same we will use a _for_ loop and an array. 

Insert the positions __Vector2__ in an array. 

	Vector2 positionsArray[4];
	positionsArray[0] = positionPieceTopLeft;
	positionsArray[1] = positionPieceTopRight;
	positionsArray[2] = positionPieceBottomLeft;
	positionsArray[3] = positionPieceBottomRight;

Create and add a Piece for each position.

    for (int i = 0; i < 4; i++)
    {
        // Add piece
        Piece * piece = Piece::create("piece_0"+std::to_string(i)+".png");
        piece->setTargetPosition(positionsArray[i]);
        this->addChild(piece);
    }

At this point we can compile and run and pieces will be added at point(0,0) with the anchor point (0.5, 0.5). 

![](https://cloud.githubusercontent.com/assets/1536171/2888181/9ef781ea-d506-11e3-97fe-d3be72fb01fe.png)

We should keep a reference to our Pieces now, and a good way could be using a  _Vector_.

In Cocos2d-x in the version 2 we used _CCArray_ that was based in *NSArray* from *Foundation* (Objective-C) but this class has been deprecated. Now you should start using the new class *Vector* wich is based in the standard library of C++ ++ and has some advantages over *CCArray*. You can find a good explanation about this class in [this article](http://dev.bunnyhero.org/2014/01/cocos2d-x-30-beta-the-new-vector-class/) of Wayne A.Lee. (Or you can just trust in the force and continue the tutorial ;-) ). 

Create a new private variable in GamePlay.h  

	private:
	    Vector<Piece *> puzzlePieces;
        
Add the line with the character "+" to the loop.

	for (int i = 0; i < 4; i++)
	{
		// Add piece
		Piece * piece = Piece::create("piece_0"+std::to_string(i)+".png");
		piece->setTargetPosition(positionsArray[i]);
		+ this->puzzlePieces.pushBack(piece);
		this->addChild(piece);
	}

With this we already have a references to the puzzle so we can come back to the Piece class and add the user interaction. 

## Interacting with our puzle

*Cocos2d-x v3 has introduced several improvements over the event management. We advice you to review the official docs about [event handling](http://www.cocos2d-x.org/docs/manual/framework/native/input/event-dispatcher/en). *

We will declare the callbacks in Piece.h: 

	bool onTouchBegan(Touch*, Event*);
	void onTouchMoved(Touch*, Event*);
	void onTouchEnded(Touch*, Event*);
	void onTouchCancel(Touch*, Event*);
	
I call them in this way to keep it standard, but from cocos v3 you are free to change the names or even to declare them inline. Just remember to keep the params and the return type. 

In the implementation of the init method we will add the next code. That registers a new listener for the _touchs_ and relationates the methods that we just declared in the previous step.

    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(Piece::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Piece::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Piece::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(Piece::onTouchCancel, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
Now we are going to jump into one of the more fun parts. The game logic.  

We want to activate a Piece when the user touchs it. We have to check in the callback if the touch has happened over a piece. 

	bool Piece::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
	{
	    if (this->getBoundingBox().containsPoint(touch->getLocation()))
	    {
	        this->setActived(true);
	    }
	    
	    return true;
	}

When the usere release the touch we will deactive the Piece 

	void Piece::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
	{
	    this->setActived(false);
	}
	
If the user is moving the finger the piece also should move: 

	void Piece::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
	{
	    if (this->_actived)
	    {
	        this->setPosition(Vector2(this->getPositionX()+touch->getDelta().x, this->getPositionY()+touch->getDelta().y));
	    }
	}
	
**Compile and execute you must**
![](https://cloud.githubusercontent.com/assets/1536171/2888312/1612c0b2-d509-11e3-926c-5730c7d97b25.png)

If you press over a piece and drag it you will see that it looks like there is only one piece over the scene. (!?)

Keep calm, the pieces are in the window, but they are all moving at the same time under your finger (or your cursor mouse). The touch is just propagating to the back and aplying over every _listeners_. 

To avoid it we will make the next change over the onTouchBegin method.

	bool Piece::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
	{
	    if (this->getBoundingBox().containsPoint(touch->getLocation()))
	    {
	        this->listener->setSwallowTouches(true);
	        this->setActived(true);
	    }
	    else
	    {
	        this->listener->setSwallowTouches(false);
	    }
	    
	    return true;
	}
	
Now we will only propage the touch if the user is touching outside of a piece. When the user press over a piece the pieces will sallow all the touches and will not affect to other listeners in other Layers.  

**Compile and execute again**. Now everything should work ok and you should be able to move every pieces. . 
![](https://cloud.githubusercontent.com/assets/1536171/2888334/71ec6500-d509-11e3-809f-1cb48e4f4602.png)

### ¡A little bit of magic!

We are very proud that you arrived at this point. You are a tough guy! So don't fall now, you are just a few steps from glory. 

**Let's go to recapitulate: **
We already have our board, we have the pieces of our puzzle and the goal positions of this pieces. We have added events to move them and we can already make our puzzle. 

But it would be nice to give a little bit of feedback to the user to improve the experience. 

We will make when the user press over a piece that piece will react scalling itself a little bit. We will use the _setActive_ method and we will modify it in this way: 

	void Piece::setActived(bool active)
	{
	    _actived = active;
	    Action *scale;
	    if (_actived)
	    {
	        scale = ScaleTo::create(0.2, 1.1);
	    }
	    else
	    {
	        scale = ScaleTo::create(0.2, 1);
	    }
	    this->runAction(scale);
	}

So now each time we touch a piece it will increase it's size in a 10% and each time we release the touch it will come back to the original size.  Feel free to compile and make your own experiments. 

Last... 

Come back to the method

 **bool currentLocationSuccess**

It's time to make that when the user releases a piece, if this is very close of the goal position we will move it to the exact point. The first we must implement the method to check if it is in the correct place: 

	bool Piece::currentLocationSuccess()
	{
	    Vector2 currentPosition = this->getPosition();
	    int deltaX, deltaY;
	    deltaX = _targetPosition.x - currentPosition.x;
	    deltaY = _targetPosition.y - currentPosition.y;
	    
		// Current piece is inside the desired range.
	    if ((abs(deltaX) < LOCATION_ACCURACY)&&(abs(deltaY) < LOCATION_ACCURACY))
	    {
	        Action* moveToTargetPosition = MoveTo::create(0.2, _targetPosition);
	        this->runAction(moveToTargetPosition);
	        std::cout << "pieze is now in the correct place";
	        return true;
	    }
	    return false;
	}
	
launch this method from the end of the touch

	void Piece::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
	{
	    this->setActived(false);
	    this->currentLocationSuccess();
	}
	
You would notice we use the constant "LOCATION_ACCURACY" that previously you should define. 

	#define LOCATION_ACCURACY 100

This constant, as you can imagin is the accuracy we want in the puzzle to accept a position as a good position. For our tutorial "100" has proved to be an acceptable value. But of course you can modify it. The lower is the value the harder is to relase the piece. 

![](https://cloud.githubusercontent.com/assets/1536171/2888391/33fbb59c-d50a-11e3-989a-4f122e777498.png)

And thats all! You have completed the tutorial. 

And what now?

## Improving our puzzle

We propose you a list of improvements to practice. If you decide to make someone let us now and send us your feedback and your improvements via pull request to  [github](https://github.com/MandukaGames/tutorial-puzzle)  or email to  developer@mandukagames.com. We will be very happy to add your improvements to the tutorial. 

* Make a bigger puzzle. 
* Position the pieces randomly in the screen to force user to find them. 
* A popup congratulating the user when he finish the puzzle. 
* A reset button to disorder the pieces over the screen (animations?). 
* A counter to punctuate the user by the time he needs to solve the puzzle.
* An init menu with the Play and Menu option to choose the number of pieces and difficulty ot the puzzle. 

We hope you have enjoyed this tutorial! Don't forget to leave us your feedback in [mandukagames.com](www.mandukagames.com).
