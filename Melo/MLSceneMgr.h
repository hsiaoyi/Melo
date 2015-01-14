//--------------------------------------------------------------------------------
//	File		: MLSceneMgr.h
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#ifndef __MLSCENEMGR_H__
#define __MLSCENEMGR_H__

#include <vector>

#include "Melo.h"

USING_NS_CC;

class MLLayer;

//================================================================================
class MLSceneMgr
{
public:
	// public functions
	static MLSceneMgr* GetInstance();

	void Init();
	void Release();

	MLBOOL AddChild();
	MLBOOL RemoveChild();
	MLBOOL Update();

	// translate, rotate functions, entire scene
	MLBOOL TranslateScene();
	MLBOOL RotateScene();
	MLBOOL SetActive();
	MLBOOL IsActive();



private:
	// private functions
	MLSceneMgr(){};
	MLSceneMgr(const MLSceneMgr &);
	~MLSceneMgr(){};
	void operator=(const MLSceneMgr &);

	void CreateDefaultNode();


	// ML private members
	static MLSceneMgr *mInstance;
	MLBOOL mActive;
	std::vector<MLLayer*> mLayers;


	// cocos instance for wrapper
	Scene *mCCScene;
};

#endif // __MLSCENEMGR_H__