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
	friend class MLLayer;

//public functions
	MLBOOL SetString(string str);
	MLBOOL SetPosition(MLFLOAT x, MLFLOAT y);
	MLBOOL Draw();

	void SetWordByWordEffectParams(MLDOUBLE period, MLDOUBLE delay, MLBOOL repeat);

private:
// private functions
	MLLabel(MLTTFFont *fnt, string str, MLFLOAT x, MLFLOAT y);
	~MLLabel();

	MLBOOL UpdateWordInfo();
	void ResetEffect();


// private members
	u16string mU16Str;

	list<MLWordInfo *> mWords;
	MLTTFFont *mFont;

	MLFLOAT mPosX;
	MLFLOAT mPosY;
	MLINT mShowCounts;

	// effect paramas
	MLDOUBLE mCurrentTime;
	MLDOUBLE mLastTime;

	MLDOUBLE mWordByWordPeriod;
	MLDOUBLE mDelayedTime;
	MLBOOL mRepeatEffect;


	// todo params:
	//- pos need to be transformable

	//+ index buffer fixed
		// see commented code in ccatalstexture

	//+ shader for rendering
	//+ color for rendering
	//+ blend ops for rendering
	//+ animation time for rendering

};




#endif //__ML_LABEL_H__