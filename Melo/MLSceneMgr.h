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

//#include <vector>
#include <map>

#include "Melo.h"

class MLLayer;
class MLSprite;

//--------------------------------------------------------------------------------
class MLSceneMgr
{
public:
	// public functions
	static MLSceneMgr* GetInstance();

	void Init();
	void Release();
	MLBOOL Update();
	MLBOOL Draw();

	MLLayerId AddLayer(MLFunc initialfunc = NULL, MLFunc updatefunc = NULL, MLFunc destroyfunc = NULL);
	MLLayer *GetLayer(const MLLayerId id);
	MLBOOL DeleteLayer(const MLLayerId id);

	MLSpriteId AddSprite(const MLLayerId layerid, const std::string &file);
	MLSprite *GetSprite(const MLLayerId layerid, const MLSpriteId spriteid);
	MLBOOL DeleteSprite(const MLLayerId layerid, const MLSpriteId spriteid);

	// translate, rotate functions, entire scene
	//MLBOOL TranslateScene();
	//MLBOOL RotateScene();
	//MLBOOL SetActive();
	//MLBOOL IsActive();

private:
	// private functions
	MLSceneMgr(){};
	MLSceneMgr(const MLSceneMgr &);
	~MLSceneMgr(){};
	void operator=(const MLSceneMgr &);

	MLLayerId GenLayerId();
	MLLayerId mLastLayerId;	

	// ML private members
	static MLSceneMgr *mInstance;
	std::map<MLLayerId, MLLayer*> mLayers;
};

#endif // __MLSCENEMGR_H__