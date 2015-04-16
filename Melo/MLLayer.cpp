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
#include "MLLabel.h"

//--------------------------------------------------------------------------------
MLLayer::MLLayer(MLFunc initialfunc, MLFunc updatefunc, MLFunc destroyfunc):
mLastSpriteId(0),
mLastLabelId(0),
mActive(MLTRUE)
{
	//MLLOG("MLLayer constructor()");
	
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

	std::map<MLSpriteId, MLSprite*>::iterator it;
	for (it = mSprites.begin(); it != mSprites.end(); ++it)
	{
		ML_DELETE it->second;
	}
	mSprites.clear();

	std::map<MLLabelId, MLLabel*>::iterator it2;
	for (it2 = mLabels.begin(); it2 != mLabels.end(); ++it2)
	{
		ML_DELETE it2->second;
	}
	mLabels.clear();
}

//--------------------------------------------------------------------------------
void MLLayer::Draw()
{
	std::map<MLSpriteId, MLSprite*>::iterator it;
	for (it = mSprites.begin(); it != mSprites.end(); ++it)
	{
		// todo:
		// is active?
		if(it->second != nullptr)
		{
			it->second->Draw();
		}
	}

	std::map<MLLabelId, MLLabel*>::iterator it2;
	for (it2 = mLabels.begin(); it2 != mLabels.end(); ++it2)
	{
		// todo:
		// is active?
		if (it2->second != nullptr)
		{
			it2->second->Draw();
		}
	}
}

//--------------------------------------------------------------------------------
MLSpriteId MLLayer::AddSprite(const std::string &fileName, const MLFLOAT x, const MLFLOAT y, const MLFLOAT rot)
{
	MLSprite *sprite = ML_NEW MLSprite(fileName);
	MLSpriteId id = GenSpriteId();

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
		return nullptr;
	}	
}

//--------------------------------------------------------------------------------
MLBOOL MLLayer::DeleteSprite(const MLSpriteId spriteid)
{
	if (mSprites[spriteid])
	{
		mSprites.erase(spriteid);
		return MLTRUE;
	}

	return MLFALSE;
}

//--------------------------------------------------------------------------------
MLLabelId MLLayer::AddLabel(MLTTFFont *fnt, string str, MLFLOAT x, MLFLOAT y)
{
	MLLabel *label = ML_NEW MLLabel(fnt, str, x, y);
	MLLabelId id = GenLabelId();

	std::pair<MLLabelId, MLLabel*>pair = std::make_pair(id, label);
	mLabels.insert(pair);
	return id;
}

//--------------------------------------------------------------------------------
MLLabel * MLLayer::GetLabel(const MLLabelId labelid)
{
	if (mLabels[labelid])
	{
		return mLabels[labelid];
	}
	else
	{
		return nullptr;
	}
}

//--------------------------------------------------------------------------------
MLBOOL MLLayer::DeleteLabel(const MLLabelId labelid)
{
	if (mLabels[labelid])
	{
		ML_DELETE mLabels[labelid];

		mLabels.erase(labelid);
		return MLTRUE;
	}

	return MLFALSE;
}

//--------------------------------------------------------------------------------
MLSpriteId MLLayer::GenSpriteId()
{
	return ++mLastSpriteId;
}

//--------------------------------------------------------------------------------
MLLabelId MLLayer::GenLabelId()
{
	return ++mLastLabelId;
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