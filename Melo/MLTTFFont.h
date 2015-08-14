//--------------------------------------------------------------------------------
//	File		: MLTTFFont.h
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#ifndef __ML_TTFFONT_H__
#define __ML_TTFFONT_H__

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Melo.h"

//--------------------------------------------------------------------------------
// font def constants
const MLINT MLMaxFontTextureSize = 1024;
const MLINT MLFontTextureDepth = 4;
const MLINT MLMaxFontTextureUsage = 2;
const MLINT MLFontDpi = 72;
const MLINT MLFontSizeScaleFactor = 1;


//--------------------------------------------------------------------------------
typedef struct _MLWordInfo
{
	_MLWordInfo(float _u, float _v, int _texIdx)
	{
		u = _u;
		v = _v;
		w = 0;
		h = 0;
		horiBearingX = 0;
		horiBearingY = 0;
		ascender = 0;
		horiAdvance = 0;
		texIdx = _texIdx;
	}

	MLFLOAT u;
	MLFLOAT v;
	MLINT w;
	MLINT h;
    MLINT horiBearingX;
	MLINT horiBearingY;
    MLINT ascender;
    MLINT horiAdvance;
	MLINT texIdx;
}MLWordInfo;

//--------------------------------------------------------------------------------
class MLTTFFont
{
public:
// public functions
	MLTTFFont(string fontName, int fontSize):
		mFontName(fontName),
		mFontSize(fontSize),
		mCellW(0),// max advance
		mCellH(0),// max height
		mGlyphsPerRow(0),
		mGlyphsPerCol(0),
		mCurrentIdx(0)
	{
	}
	~MLTTFFont();
	
	MLBOOL InitFont(FT_Library lib);
	void AddString(u16string u16str, list<MLWordInfo *> infoList);
	void AddChar(char16_t c, list<MLWordInfo *> infoList);

	Texture2D * GetTextrue(int idx)
	{
		return mTextures[idx];
	}

	MLWordInfo *GetAtlasTexture(char16_t c);
	MLINT GetCellHeight()
	{
		return mCellH;
	}

	MLINT GetCellWidth()
	{
		return mCellW;
	}

	MLINT GetFontSize()
	{
		return mFontSize;
	}

private:
// private function
	MLBOOL InitFreeType(FT_Library lib);
	MLBOOL GetCellInfo(MLINT *u, MLINT *v, MLINT *w, MLINT *h);
	MLBOOL GenAtlasTextureByIndex(char16_t c, MLWordInfo *info);	

// private memebers
	string mFontName;
	MLINT mFontSize;

	FT_Face mFace;
	Texture2D *mTextures[MLMaxFontTextureUsage];
	unsigned char *mTexData[MLMaxFontTextureUsage];
	map<char16_t, MLWordInfo *> mWords;

	MLINT mCellW;// max advance
	MLINT mCellH;// max height
	MLINT mGlyphsPerRow;
	MLINT mGlyphsPerCol;

	MLINT mCurrentIdx;
	
};




#endif //__ML_TTFFONT_H__