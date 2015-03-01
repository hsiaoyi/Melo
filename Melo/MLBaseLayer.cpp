//--------------------------------------------------------------------------------
//	File		: MLBaseLayer.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#include "MLBaseLayer.h"

//--------------------------------------------------------------------------------
MLBaseLayer::MLBaseLayer(MLFunc initialfunc, MLFunc updatefunc, MLFunc destroyfunc) :
mPosX(0.0),
mPosY(0.0),
mRotAng(0.0),
mInitialFunc(initialfunc),
mUpdateFunc(updatefunc),
mDestroyFunc(destroyfunc)
{
	MLLOG("MLBaseLayer constructor()");
}

//--------------------------------------------------------------------------------
MLBaseLayer::~MLBaseLayer()
{
}

// todo
//--------------------------------------------------------------------------------
//void MLBaseLayer::SetPosition(MLFLOAT posX, MLFLOAT posY)
//{
//	mPosX = posX;
//	mPosY = posY;
//}

// todo
//--------------------------------------------------------------------------------
//void MLBaseLayer::SetRotation(MLFLOAT eulerAngle)
//{
//	mRotAng = eulerAngle;
//}
