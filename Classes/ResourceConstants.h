/*
 * ReourceConstants.h
 *
 *  Created on: 16/06/2014
 *      Author: SlashGame
 */

#ifndef REOURCECONSTANTS_H_
#define REOURCECONSTANTS_H_

#include "cocos2d.h"

USING_NS_CC;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

// - Puzzle resources
#define kPuzzleBackground		"background.png"

// - Common buttons
#define kButtonBack				"bt_back_default.png"
#define kButtonBackPressed		"bt_back_pressed.png"

#define kButtonPause			"bt_pause_default.png"
#define kButtonPausePressed		"bt_pause_pressed.png"

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

// - Puzzle resources
#define kPuzzleBackground		"puzzle/background.png"

// - Common buttons
#define kButtonBack				"commons/bt_back_default.png"
#define kButtonBackPressed		"commons/bt_back_pressed.png"

#define kButtonPause			"commons/bt_pause.png"
#define kButtonPausePressed		"commons/bt_pause_pressed.png"

#endif

#endif /* REOURCECONSTANTS_H_ */
