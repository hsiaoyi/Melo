//--------------------------------------------------------------------------------
//	File		: MLLayer.h
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#ifndef __MLLAYER_H__
#define __MLLAYER_H__

#include <vector>

#include "Melo.h"
#include "MLBaseLayer.h"

//--------------------------------------------------------------------------------
// forward declaration
class MLSprite;

//--------------------------------------------------------------------------------
// currently only support for 2D layer
class MLLayer : public MLBaseLayer
{
public:
	MLLayer(MLFunc initialfunc = NULL, MLFunc updatefunc = NULL, MLFunc destroyfunc = NULL);
	~MLLayer();
	void Draw() override;

	MLSpriteId AddSprite(const std::string &fileName, const MLFLOAT x = 0, const MLFLOAT y = 0, const MLFLOAT rot = 0);
	MLSprite * GetSprite(const MLSpriteId spriteid);

	void SetId(MLLayerId id);
	MLSpriteId GenSpriteId();

	MLBOOL IsActive();
	void SetActive(MLBOOL active);

	// todo
	// get sprite
	// get active sprite count
	// get sprite count
	// gen sprite id


private:
	//std::vector<MLSprite *>mSprites;
	MLLayerId mId;
	MLSpriteId mLastSpriteId;
	std::map<MLSpriteId, MLSprite*> mSprites;

	MLBOOL mActive;

	// test code
	cocos2d::Texture2D *mCCTex;

	
};//

#endif // __MLAPP_H__