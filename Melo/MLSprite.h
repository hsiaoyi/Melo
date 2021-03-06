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

#include <map>

#include "Melo.h"
#include "cocos2d.h"

//--------------------------------------------------------------------------------
class MLSprite
{
public:
	friend class MLLayer;

// public funcitons
	MLBOOL IsActive();
	void SetActive(MLBOOL active);
	MLBOOL IsSelectable();
	void SetSelectable(MLBOOL selectable);
	MLBOOL IsSelected();
	MLBOOL IsPenetrable();

	void SetPosition(MLFLOAT x, MLFLOAT y);
	MLFLOAT GetXPosition();
	MLFLOAT GetYPosition();
	void SetRotation(MLFLOAT rot);

	MLFLOAT GetWidth();
	MLFLOAT GetHeight();
	MLBOOL SetTexture(const std::string &fileName);

	void SetAlignWin(MLAlignH hori, MLAlignV vert);

	void Draw();

	MLBOOL IsPointIn(MLFLOAT x, MLFLOAT y);
	void ResetSelection();

private:

//private functions
	MLSprite(const std::string &fileName, const MLFLOAT x = 0, const MLFLOAT y = 0, const MLFLOAT rot = 0);
	virtual ~MLSprite();

	MLBOOL SetVerts();

// private members
	MLFLOAT mPosX;
	MLFLOAT mPosY;
	MLFLOAT mRotAng;

	MLFLOAT mHeight;
	MLFLOAT mWidth;

	MLBOOL mActive;
	MLBOOL mSelectable;
	MLBOOL mSelected;
	MLBOOL mPenetrable;

	MLFLOAT mVertices[8];

	std::string mFileName;

	// cocos2d instance
	Texture2D *mCCTex;
};

#endif // __MLSPRITE_H__