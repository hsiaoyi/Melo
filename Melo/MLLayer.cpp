//--------------------------------------------------------------------------------
//	File		: MLLayer.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#include "MLLayer.h"
#include "MLSprite.h"

//--------------------------------------------------------------------------------
MLLayer::MLLayer(MLFunc initialfunc, MLFunc updatefunc, MLFunc destroyfunc):
mId(-1),
mLastSpriteId(0),
mActive(MLTRUE)
{
	MLLOG("MLLayer constructor()");
	
	mInitialFunc = initialfunc;
	mUpdateFunc = updatefunc;
	mDestroyFunc = destroyfunc;

	if (mInitialFunc)
	{
		mInitialFunc();
	}
	
}

//--------------------------------------------------------------------------------
MLLayer::~MLLayer()
{
	if (mDestroyFunc)
	{
		mDestroyFunc();
	}
	mSprites.clear();
}

//--------------------------------------------------------------------------------
void MLLayer::Draw()
{
	std::map<MLSpriteId, MLSprite*>::iterator it;
	for (it = mSprites.begin(); it != mSprites.end(); ++it)
	{
		it->second->Draw();
	}
}

//--------------------------------------------------------------------------------
MLSpriteId MLLayer::AddSprite(const std::string &fileName, const MLFLOAT x, const MLFLOAT y, const MLFLOAT rot)
{
	MLSprite *sprite = ML_NEW MLSprite(fileName);
	MLSpriteId id = GenSpriteId();
	sprite->SetId(id);

	std::pair<MLSpriteId, MLSprite*> pair = std::make_pair(id, sprite);
	mSprites.insert(pair);
	
	return id;
}

//--------------------------------------------------------------------------------
MLSprite * MLLayer::GetSprite(const MLSpriteId spriteid)
{
	if (mSprites[spriteid])
	{
		return mSprites[spriteid];
	}
	else
	{
		return NULL;
	}	
}

//--------------------------------------------------------------------------------
void MLLayer::SetId(MLLayerId id)
{
	mId = id;
}

//--------------------------------------------------------------------------------
MLSpriteId MLLayer::GenSpriteId()
{
	return ++mLastSpriteId;
}

//--------------------------------------------------------------------------------
MLBOOL MLLayer::IsActive()
{
	return mActive;
}

//--------------------------------------------------------------------------------
void MLLayer::SetActive(MLBOOL active)
{
	mActive = active;
}