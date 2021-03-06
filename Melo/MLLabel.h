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

#include <list>
#include "Melo.h"
#include "MLFontMgr.h"

using namespace std;
//--------------------------------------------------------------------------------
class MLLabel
{
public:
	friend class MLLayer;

//public functions
	MLBOOL SetString(string str);
	MLBOOL SetPosition(MLFLOAT x, MLFLOAT y);
	MLBOOL Draw();
	MLBOOL IsAllShowed();
	void SetAllShowed(MLBOOL showed);

	void SetWordByWordEffectParams(MLDOUBLE period, MLDOUBLE delay, MLBOOL repeat);
	void SetLabelAlignWin(MLAlignH hori, MLAlignV vert);// alignment window
	void SetLineSpacing(MLINT lineSpacing);
	void SetFont(MLTTFFont *fnt);
	MLTTFFont *GetFont(){ return mFont; }
    
    void SetClipRect( const MLRect *clipCect );
    void SetDefaultColor( MLFLOAT red, MLFLOAT green, MLFLOAT blue, MLFLOAT alpha );
    
    MLBOOL IsActive();
    void SetActive(MLBOOL active);
    
    MLINT GetLabelWidth();
    MLINT GetLabelHeight();
    MLFLOAT GetPositionX();
    MLFLOAT GetPositionY();

private:
// private functions
	MLLabel(MLTTFFont *fnt, string str, MLFLOAT x, MLFLOAT y, MLBOOL useClip = MLFALSE, MLINT clipWidth = 0, MLINT clipHeight = 0);
	~MLLabel();

	void ResetEffect();
	MLINT GetStringLength();
	void PreprocessDrawString();
	void CalContentSizeNoClip();
	
	typedef enum
	{
		LSP_NormalString,
		LSP_ControlSign,
		LSP_ControlStartCode,
		LSP_ControlledString,
		LSP_ControlEndCode,
	}LabelStringProcessState;

	void DrawChar(char16_t &currentChar, MLINT &x, MLINT &y, MLFLOAT &r, MLFLOAT &g, MLFLOAT &b, MLFLOAT &a);

// private members

	u16string mU16Str;
	MLINT mDrawStringLength;

	list<MLWordInfo *> mWords;
	MLTTFFont *mFont;

	MLFLOAT mPosX;
	MLFLOAT mPosY;
	MLINT mShowCounts;
	MLBOOL mAllShowedOnce;
	MLINT mLineSpacing;
	MLINT mWordSpacing;
	MLINT mWidth;// entire area
	MLINT mHeight;// entire area
	MLBOOL mClipArea;
	MLINT mClipWidth;
	MLINT mClipHeight;
    
    MLBOOL mActive;
    
    MLBOOL mUsingClipRect;
    MLRect mClipRect;

	// effect paramas
	MLDOUBLE mCurrentTime;
	MLDOUBLE mLastTime;

	MLDOUBLE mWordByWordPeriod;
	MLDOUBLE mDelayedTime;
	MLBOOL mRepeatEffect;

	MLFLOAT mColorR;
	MLFLOAT mColorG;
	MLFLOAT mColorB;
	MLFLOAT mColorA;

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