//--------------------------------------------------------------------------------
//	File		: MLFontMgr.h
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#ifndef __ML_FONTMGR_H__
#define __ML_FONTMGR_H__

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include "Melo.h"

//--------------------------------------------------------------------------------
typedef enum _MLFontType
{
	ML_FT_TTF,
	//ML_FT_SYSTEM,
	//ML_FT_FNT
}MLFontType;

typedef struct MLFontConfig
{
	std::string mFontName;
	int	mSize;
	MLFontType mType;

	MLFontConfig() :
		mFontName(),
		mSize(24),
		mType(ML_FT_TTF)
	{
		MLLOG("---------MLFontConfig constructor---------");
	}

	MLFontConfig(std::string fontName, int size, MLFontType type)
	{
		mFontName = fontName;
		mSize = size;
		mType = type;
		MLLOG("---------MLFontConfig constructor2---------");
	}
	//
	// todo: add effect properties
};

#define testsample

//--------------------------------------------------------------------------------
class MLFontMgr
{
public:
	MLBOOL Init();
	MLBOOL Release();
	static MLFontMgr *GetInstance();

	// todo
	//MLBOOL CreateWithString(MLFontConfig cfg, std::string str);
	MLBOOL CreateWithString(MLFontConfig cfg, std::string str, cocos2d::Texture2D *testTex);
private:
	MLFontMgr(){};
	MLFontMgr(const MLFontMgr &);
	~MLFontMgr();
	void operator=(const MLFontMgr &);

// private members
	static MLFontMgr *mInstance;
	FT_Library mLibrary;
	FT_Face mFaces;// will change to map later
	MLINT mDpi;
	MLBOOL mIsInitialized;
};




#endif //__ML_FONTMGR_H__