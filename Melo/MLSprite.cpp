//--------------------------------------------------------------------------------
//	File		: MLSprite.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#include "MLSprite.h"
#include "cocos2d.h"

//--------------------------------------------------------------------------------
MLSprite::MLSprite(const std::string &fileName, MLFLOAT x, MLFLOAT y, MLFLOAT rot):
mPosX(x),
mPosY(y),
mRotAng(rot),
mHeight(0.0),
mWidth(0.0),
mActive(MLTRUE),
mFileName(fileName)
{
	MLLOG("Creating sprite %s", mFileName);

	mCCTex = cocos2d::Director::getInstance()->getTextureCache()->addImage(mFileName);
	if (mCCTex)
	{
		mCCTex->retain();
		mHeight = mCCTex->getContentSize().height;
		mWidth = mCCTex->getContentSize().width;
	}
}

//--------------------------------------------------------------------------------
MLSprite::~MLSprite()
{
	mFileName.clear();
	mCCTex->release();
	mCCTex = nullptr;
}

//--------------------------------------------------------------------------------
void MLSprite::Draw()
{
	Director* director = Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	//Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//Size visibleSize = Director::getInstance()->getVisibleSize();

	Mat4 myid;
	myid.setIdentity();
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, myid);

	mCCTex->drawAtPoint(Vec2(mPosX, mPosY));
	// todo: calculate rotation

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

//--------------------------------------------------------------------------------
MLBOOL MLSprite::IsActive()
{
	return mActive;
}

//--------------------------------------------------------------------------------
void MLSprite::SetActive(MLBOOL active)
{
	mActive = active;
}

//--------------------------------------------------------------------------------
void MLSprite::SetPosition(MLFLOAT x, MLFLOAT y)
{
	if (x >= 0 && y >= 0)
	{
		mPosX = x;
		mPosY = y;
	}
}

//--------------------------------------------------------------------------------
void MLSprite::SetRotation(MLFLOAT rot)
{
	mRotAng = rot;
}

//--------------------------------------------------------------------------------
MLFLOAT MLSprite::GetXPosition()
{
	return mPosX;
}

//--------------------------------------------------------------------------------
MLFLOAT MLSprite::GetYPosition()
{
	return mPosY;
}

//--------------------------------------------------------------------------------
MLFLOAT MLSprite::GetWidth()
{
	return mWidth;
}

//--------------------------------------------------------------------------------
MLFLOAT MLSprite::GetHeight()
{
	return mHeight;
}

//--------------------------------------------------------------------------------
MLBOOL MLSprite::SetTexture(const std::string &fileName)
{
	// to do
	return MLTRUE;
}
