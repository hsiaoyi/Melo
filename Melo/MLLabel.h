//--------------------------------------------------------------------------------
//	File		: MLLabel.h
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#ifndef __ML_LABEL_H__
#define __ML_LABEL_H__
/*
#include <iostream>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
*/
#include <list>
#include "Melo.h"
#include "MLFontMgr.h"

using namespace std;

//--------------------------------------------------------------------------------


//--------------------------------------------------------------------------------
class MLLabel
{
public:
	MLLabel(MLTTFFont *fnt, string str);
	~MLLabel();

	MLBOOL SetString(string str);
	//MLBOOL SetFont(MLFontConfig cfg);
	// todo:
	//SetSize();
	//SetPosition();

private:
	MLBOOL UpdateWordInfo();

	// private members
	string mStr;
	list<MLWordInfo *> mWords;
	MLTTFFont *mFont;

	//MLFontConfig *cfg;
	//list<MLWordInfo> mWordInfo;
};




#endif //__ML_LABEL_H__