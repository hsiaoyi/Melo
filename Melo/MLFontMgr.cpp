//--------------------------------------------------------------------------------
//	File		: MLFontMgr.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#include "MLFontMgr.h"
//#include "base\ccUTF8.h"
//#include <cstdlib>

MLFontMgr * MLFontMgr::mInstance = nullptr;

//--------------------------------------------------------------------------------
MLBOOL MLFontMgr::Init()
{
	// init free type 2
	if(FT_Init_FreeType(&mLibrary))
	{
		return MLFALSE;	// failed
	}

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLBOOL MLFontMgr::Release()
{
	map<string, MLTTFFont*>::iterator it;
	for (it = mFonts.begin(); it != mFonts.end(); ++it)
	{
		ML_DELETE it->second;
		it->second = nullptr;
	}
	mFonts.clear();

	FT_Done_FreeType(mLibrary);
    
    mSpecialWords.clear();

	ML_DELETE mInstance;
	mInstance = nullptr;

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLFontMgr *MLFontMgr::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = ML_NEW MLFontMgr;
	}

	return mInstance;
}

//--------------------------------------------------------------------------------
MLTTFFont* MLFontMgr::CreateTTFFont(string fontName, int fontSize)
{
	string idxName = GenFontIndexName(fontName, fontSize);
	map<string, MLTTFFont*>::iterator it = mFonts.find(idxName);

	if (it != mFonts.end())
	{
		return it->second;
	}

	MLTTFFont *fnt = ML_NEW MLTTFFont(fontName, fontSize);
	pair<string, MLTTFFont*> p = make_pair(idxName, fnt);
	mFonts.insert(p);

	MLBOOL ret =  fnt->InitFont(mLibrary);

	if (ret)
	{
		return fnt;
	}
	else
	{
		return nullptr;
	}
}

//--------------------------------------------------------------------------------
MLTTFFont* MLFontMgr::GetTTFFont(string fontName, int fontSize)
{
	string idxName = GenFontIndexName(fontName, fontSize);
	map<string, MLTTFFont*>::iterator it = mFonts.find(idxName);

	if (it == mFonts.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

//--------------------------------------------------------------------------------
string MLFontMgr::GenFontIndexName(string fontName, MLINT size)
{
	std::stringstream str;
	str << fontName << "_" << size;

	return str.str();
}

//--------------------------------------------------------------------------------
void MLFontMgr::RegisterSpecialWord(MLINT idx, std::string word)
{
    pair<int, std::string> p = make_pair(idx, word);
    mSpecialWords.insert(p);
}

//--------------------------------------------------------------------------------
std::string MLFontMgr::GetSpecialWord(MLINT idx)
{
    return mSpecialWords[idx];
}

