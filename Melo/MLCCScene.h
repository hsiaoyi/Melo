//--------------------------------------------------------------------------------
//	File		: MLCCScene.h
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#ifndef __MLCC_SCENE_H__
#define __MLCC_SCENE_H__

#include "cocos2d.h"
#include "Melo.h"

#include "MLSprite.h"
USING_NS_CC;

//--------------------------------------------------------------------------------
//class MLLyer;
class MLSprite;

//--------------------------------------------------------------------------------
class MLCCScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
	// overrided virtual funcitons
	virtual bool init();
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
	//virtual void onEnter();
	static void MyUpdate();

	// todo: collision and callbacks
    //void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(MLCCScene);
	cocos2d::Texture2D *testTex;

};

#endif // __MLCC_SCENE_H__
