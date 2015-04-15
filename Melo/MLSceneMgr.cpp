//--------------------------------------------------------------------------------
//	File		: MLSceneMgr.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#include "MLSceneMgr.h"
#include "MLLayer.h"
#include "MLSprite.h"
#include "MLTTFFont.h"
#include "MLLabel.h"

MLSceneMgr * MLSceneMgr::mInstance = nullptr;

//--------------------------------------------------------------------------------
MLSceneMgr* MLSceneMgr::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = ML_NEW MLSceneMgr;
	}

	return mInstance;
}

//--------------------------------------------------------------------------------
void MLSceneMgr::Init()
{
	if (mInstance)
	{
		mLastLayerId = 0;
		mDeltaTime = 0.;
	}
}

//--------------------------------------------------------------------------------
void MLSceneMgr::Release()
{
	mLayers.clear();
}

//--------------------------------------------------------------------------------
MLBOOL MLSceneMgr::Update(MLFLOAT deltaTime)
{
	//MLLOG("---MLSceneMgr::Update---");

	// set time
	mDeltaTime = deltaTime;

	std::map<MLLayerId, MLLayer*>::iterator it;
	for (it = mLayers.begin(); it != mLayers.end(); ++it)
	{
		if (it->second->mUpdateFunc)
		{
			it->second->mUpdateFunc();
		}		
	}

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLBOOL MLSceneMgr::Draw()
{
	//MLLOG("---MLSceneMgr::Draw---");

	std::map<MLLayerId, MLLayer*>::iterator it;
	for (it = mLayers.begin(); it != mLayers.end(); ++it)
	{
		if (it->second != nullptr)
		{
			it->second->Draw();
		}
	}

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLLayerId MLSceneMgr::AddLayer(MLFunc initialfunc, MLFunc updatefunc, MLFunc destroyfunc)
{
	MLLayer *layer = ML_NEW MLLayer(initialfunc, updatefunc, destroyfunc);
	MLLayerId id = GenLayerId();
	
	std::pair<MLLayerId, MLLayer*> p = std::make_pair(id, layer);	
	mLayers.insert(p);
	return id;
}

//--------------------------------------------------------------------------------
MLLayer *MLSceneMgr::GetLayer(const MLLayerId id)
{
	return mLayers[id];
}

//--------------------------------------------------------------------------------
MLBOOL MLSceneMgr::DeleteLayer(const MLLayerId id)
{
	mLayers.erase(id);
	//mLayers.clear();
	return true;
}

//--------------------------------------------------------------------------------
MLSpriteId MLSceneMgr::AddSprite(const MLLayerId layerid, const std::string &file)
{	
	MLSpriteId id;
	if(mLayers[layerid])
	{
		id = mLayers[layerid]->AddSprite(file);
	}
	
	return id;
}

//--------------------------------------------------------------------------------
MLSprite *MLSceneMgr::GetSprite(const MLLayerId layerid, const MLSpriteId spriteid)
{
	if (mLayers[layerid])
	{
		return mLayers[layerid]->GetSprite(spriteid);
	}
	else
	{
		return nullptr;
	}
}

//--------------------------------------------------------------------------------
MLBOOL MLSceneMgr::DeleteSprite(const MLLayerId layerid, const MLSpriteId spriteid)
{
	if (mLayers[layerid])
	{
		return mLayers[layerid]->DeleteSprite(spriteid);
	}

	return MLFALSE;
}

//--------------------------------------------------------------------------------
MLLabelId MLSceneMgr::AddLabel(const MLLayerId layerid, MLTTFFont *fnt, string str, MLFLOAT x, MLFLOAT y)
{
	MLLabelId id;

	if(mLayers[layerid])
	{
		id = mLayers[layerid]->AddLabel(fnt, str, x, y);
	}

	return id;
}

//--------------------------------------------------------------------------------
MLLabel * MLSceneMgr::GetLabel(const MLLayerId layerid, const MLLabelId labelid)
{
	if (mLayers[layerid])
	{
		return mLayers[layerid]->GetLabel(labelid);
	}
	else
	{
		return nullptr;
	}
}

//--------------------------------------------------------------------------------
MLBOOL MLSceneMgr::DeleteLabel(const MLLayerId layerid, const MLLabelId labelid)
{
	if (mLayers[layerid])
	{
		return mLayers[layerid]->DeleteLabel(labelid);
	}

	return MLFALSE;
}

// pritvate functions
//--------------------------------------------------------------------------------
MLLayerId MLSceneMgr::GenLayerId()
{
	return ++mLastLayerId;
}