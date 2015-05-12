//--------------------------------------------------------------------------------
//	File		: MLMath.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#include "MLMath.h"

//--------------------------------------------------------------------------------
void MLMath::ScreenToWorld(MLVec2& coords)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	coords.y = visibleSize.height - coords.y;
}