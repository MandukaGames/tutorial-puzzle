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

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

// - Puzzle resources
#define kPuzzleBackground		"puzzle/background.png"

#endif

#endif /* REOURCECONSTANTS_H_ */
