//--------------------------------------------------------------------------------
//	File		: MLSprite.h
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#ifndef __MLSPRITE_H__
#define __MLSPRITE_H__

#include "Melo.h"

//--------------------------------------------------------------------------------
class MLSprite
{
public:
	MLSprite();
	virtual ~MLSprite();

private:
	MLFLOAT mPosX;
	MLFLOAT mPosY;
	MLFLOAT mRotAng;
	

	// cocos instance
	// ccsprite
};

#endif // __MLSPRITE_H__