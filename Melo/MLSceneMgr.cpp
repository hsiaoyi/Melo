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
		mActive = true;

		// add default layer
		MLLayer *layer = ML_NEW MLLayer;
		mLayers.push_back(layer);

		Director::getInstance()->runWithScene(mLayers[0]->GetCCScene());

	}
}

//--------------------------------------------------------------------------------
void MLSceneMgr::Release()
{

}

//--------------------------------------------------------------------------------
MLBOOL MLSceneMgr::AddChild()
{

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLBOOL MLSceneMgr::RemoveChild()
{

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLBOOL MLSceneMgr::Update()
{

	return MLTRUE;
}