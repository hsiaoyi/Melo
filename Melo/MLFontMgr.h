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

#include "Melo.h"
#include "MLTTFFont.h"

//--------------------------------------------------------------------------------





//--------------------------------------------------------------------------------
class MLFontMgr
{
public:
	MLBOOL Init();
	MLBOOL Release();
	static MLFontMgr *GetInstance();

	MLTTFFont* CreateTTFFont(string fontName, int fontSize);
	MLTTFFont* MLFontMgr::GetTTFFont(string fontName, int fontSize);

private:
	MLFontMgr(){};
	MLFontMgr(const MLFontMgr &);
	~MLFontMgr(){};
	void operator=(const MLFontMgr &);

	string GenFontIndexName(string fontName, MLINT size);

	// private members
	static MLFontMgr *mInstance;
	FT_Library mLibrary;

	MLBOOL mIsInitialized;

	map<string, MLTTFFont*> mFonts;
};




#endif //__ML_FONTMGR_H__