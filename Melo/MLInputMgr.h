//--------------------------------------------------------------------------------
//	File		: MLInputMgr.h
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#ifndef __MLINPUTMGR_H__
#define __MLINPUTMGR_H__

#include "Melo.h"

class MLLayer;
class MLSprite;
class MLLabel;
class MLTTFFont;

//--------------------------------------------------------------------------------
typedef enum
{
	MLTS_Begin,
	MLTS_Move,
	MLTS_End,
	MLTS_Cancel,
	MLTS_None
}MLTouchSignalState;

class MLInputMgr
{
public:
// public functions
	static MLInputMgr* GetInstance();

	void Init();
	void Release();
	void Update();//main update(internal)

	MLTouchSignalState GetTouchState();

	static void FetchTouchSignal(/*MLTouchState*/int state, float x, float y);
	
private:
// private functions
	MLInputMgr(){};
	MLInputMgr(const MLInputMgr &);
	~MLInputMgr(){};
	void operator=(const MLInputMgr &);

	// callbacks for cc
	void TouchBegin(float x, float y);
	void TouchMove(float x, float y);
	void TouchEnd(float x, float y);
	void TouchCancel(float x, float y);

// private members
	static MLInputMgr *mInstance;
	MLFLOAT mPosX;
	MLFLOAT mPosY;
	MLTouchSignalState mSigState;
	MLBOOL mPressed;

};

#endif // __MLINPUTMGR_H__