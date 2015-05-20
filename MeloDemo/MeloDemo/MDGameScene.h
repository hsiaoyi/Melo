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
class MLTTFFont;

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


	// initial functions
	MLSpriteId SetBG(const std::string &file);
	MLLayerId GetId()
	{
		return mId;
	}
	MLBOOL SetTitleFontTTF(const std::string &font, const int size);
	MLBOOL SetTitle(const std::string &text);
	MLBOOL SetTitleEffectParams(MLDOUBLE period, MLDOUBLE delay, MLBOOL repeat);
	MLBOOL SetTitleAlignWin(int hori, int vert);
	MLBOOL SetBGAlignWin(int hori, int vert);

	void Test();

	CREATE_FUNC(MDGameScene);
private:
	//
	static bool mLoadScene;
	MLLayerId mId;
	MLSpriteId mBGid;
	MLTTFFont *mTitleFont;
	MLLabelId mTitleId;
	MLFLOAT mTitlePosX;
	MLFLOAT mTitlePosY;
	static MDGameScene* mIns;
};

#endif // __MDGAME_SCENE_H__
