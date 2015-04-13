//--------------------------------------------------------------------------------
//	File		: MDGameScene.h
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#ifndef __MDGAME_SCENE_H__
#define __MDGAME_SCENE_H__

#include "cocos2d.h"
#include "Melo.h"
#include "MLSprite.h"


//--------------------------------------------------------------------------------
//class MLLyer;
class MLSprite;

//--------------------------------------------------------------------------------
class MDGameScene : public cocos2d::Layer
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

	// initial functions
	void SetBG(const char* file);

	CREATE_FUNC(MDGameScene);

private:
	//
	MLLayerId mLayer;
	MLSpriteId mBGid;
	MLSprite* mBG;
};

#endif // __MDGAME_SCENE_H__
