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

#include <map>

#include "Melo.h"

class MLLayer;
class MLSprite;
class MLLabel;
class MLTTFFont;

//--------------------------------------------------------------------------------
class MLSceneMgr
{
public:
// public functions
	static MLSceneMgr* GetInstance();

	void Init();
	void Release();
	MLBOOL Update(MLDOUBLE deltaTime);
	static void DrawCB();
	MLBOOL Draw();

	// layers
	MLLayerId AddLayer(MLFunc initialfunc = NULL, MLFunc updatefunc = NULL, MLFunc destroyfunc = NULL);
	MLLayer *GetLayer(const MLLayerId id);
	MLBOOL DeleteLayer(const MLLayerId id);

	// sprites
	MLSpriteId AddSprite(const MLLayerId layerid, const std::string &file);
	MLSprite *GetSprite(const MLLayerId layerid, const MLSpriteId spriteid);
	MLBOOL DeleteSprite(const MLLayerId layerid, const MLSpriteId spriteid);

	// labels
	MLLabelId AddLabel(const MLLayerId layerid, MLTTFFont *fnt, string str, MLFLOAT x, MLFLOAT y, MLBOOL useClip = MLFALSE, MLINT clipWidth = 0, MLINT clipHeight = 0);
	MLLabel *GetLabel(const MLLayerId layerid, const MLLabelId labelid);
	MLBOOL DeleteLabel(const MLLayerId layerid, const MLLabelId labelid);

	// translate, rotate functions, entire scene
	//MLBOOL TranslateScene();
	//MLBOOL RotateScene();
	//MLBOOL SetActive();
	//MLBOOL IsActive();

	MLDOUBLE GetDeltaTime()
	{
		return mDeltaTime;
	}

private:
// private functions
	MLSceneMgr(){};
	MLSceneMgr(const MLSceneMgr &);
	~MLSceneMgr(){};
	void operator=(const MLSceneMgr &);

	MLLayerId GenLayerId();
	MLLayerId mLastLayerId;
	void ResetSelection();
	void SelectionUpdate();

// private members
	static MLSceneMgr *mInstance;
	std::map<MLLayerId, MLLayer*> mLayers;

	MLDOUBLE mDeltaTime;

	// selected
	MLLayerId mSelLayer;
	MLSpriteId mSelSprite;
};

#endif // __MLSCENEMGR_H__