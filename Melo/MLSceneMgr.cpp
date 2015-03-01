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
	}
}

//--------------------------------------------------------------------------------
void MLSceneMgr::Release()
{
	mLayers.clear();
}

//--------------------------------------------------------------------------------
MLBOOL MLSceneMgr::Update()
{
	//MLLOG("---MLSceneMgr::Update---");

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

	// test code first
	//mLayers[mLastLayerId]->Draw();
	std::map<MLLayerId, MLLayer*>::iterator it;
	for (it = mLayers.begin(); it != mLayers.end(); ++it)
	{
		it->second->Draw();
	}

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLLayerId MLSceneMgr::AddLayer(MLFunc initialfunc, MLFunc updatefunc, MLFunc destroyfunc)
{
	MLLayer *layer = ML_NEW MLLayer(initialfunc, updatefunc, destroyfunc);
	MLLayerId id = GenLayerId();
	layer->SetId(id);
	
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
	mLayers.clear();
	return true;
}

//--------------------------------------------------------------------------------
MLSpriteId MLSceneMgr::AddSprite(const MLLayerId layerid, const std::string &file)
{	
	MLSpriteId id;
	if (mLayers[layerid])
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
		return NULL;
	}
}

//--------------------------------------------------------------------------------
MLBOOL MLSceneMgr::DeleteSprite(const MLLayerId layerid, const MLSpriteId spriteid)
{
	// todo
	return true;
}

// pritvate functions
//--------------------------------------------------------------------------------
MLLayerId MLSceneMgr::GenLayerId()
{
	return ++mLastLayerId;
}

//--------------------------------------------------------------------------------
//MLSpriteId MLSceneMgr::GenSpriteId(const MLLayerId layerid)
//{
//	if (mLayers[layerid])// this need test
//	{
//		return mLayers[layerid]->GenSpriteId();
//	}
//	return -1;
//}