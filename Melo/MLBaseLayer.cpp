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
MLBaseLayer::MLBaseLayer():
mPosX(0.0),
mPosY(0.0),
mRotAng(0.0)
{
	// todo: set pos to window center
	mCCScene = Scene::create();
	mCCLayer = Layer::create();
	mCCScene->addChild(mCCLayer);
}

//--------------------------------------------------------------------------------
MLBaseLayer::~MLBaseLayer()
{
}

//--------------------------------------------------------------------------------
cocos2d::Scene* MLBaseLayer::GetCCScene()
{
	return mCCScene;
}

//--------------------------------------------------------------------------------
void MLBaseLayer::SetPosition(MLFLOAT posX, MLFLOAT posY)
{
	mPosX = posX;
	mPosY = posY;
}

//--------------------------------------------------------------------------------
void MLBaseLayer::SetRotation(MLFLOAT eulerAngle)
{
	mRotAng = eulerAngle;
}
