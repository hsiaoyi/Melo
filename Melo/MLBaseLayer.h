//--------------------------------------------------------------------------------
//	File		: MLBaseLayer.h
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#ifndef __MLBASELAYER_H__
#define __MLBASELAYER_H__

#include "Melo.h"

USING_NS_CC;

//--------------------------------------------------------------------------------
class MLBaseLayer
{
public:
	MLBaseLayer();
	virtual ~MLBaseLayer();
	
	void AddSprite();

	void SetPosition(MLFLOAT posX, MLFLOAT posY);
	void SetRotation(MLFLOAT eulerAngle);

	cocos2d::Scene* GetCCScene();

private:
	// add initial, process, destroy CBs
	MLFLOAT mPosX;
	MLFLOAT mPosY;
	MLFLOAT mRotAng;// euler angle in z-axis

	//cocos instance
	cocos2d::Scene *mCCScene;
	cocos2d::Layer *mCCLayer;

};//

#endif // __MLAPP_H__