//--------------------------------------------------------------------------------
//	File		: MLLabel.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#include "MLLabel.h"

//--------------------------------------------------------------------------------
MLLabel::MLLabel(MLTTFFont *fnt, string str)
{
	mFont = fnt;
	SetString(str);
}

//--------------------------------------------------------------------------------
MLBOOL MLLabel::SetString(string str)
{
	mStr = str;
	mFont->AddString(mStr, mWords);

	return MLTRUE;
}


//--------------------------------------------------------------------------------



