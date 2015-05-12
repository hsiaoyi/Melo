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
	//MLTS_Pressing,
	MLTS_Move,
	MLTS_End,
	MLTS_Cancel,
	MLTS_None
}MLTouchSignalState;

typedef enum
{
	MLLS_Down,
	MLLS_Pressed,
	MLLS_Up
}MLLogicalState;

class MLInputMgr
{
public:
// public functions
	static MLInputMgr* GetInstance();

	void Init();
	void Release();
	void Update();//main update(internal)

	MLLogicalState GetLogicalState();
	MLFLOAT GetPosX()
	{
		return mPosX;
	}
	MLFLOAT GetPosY()
	{
		return mPosY;
	}

	static void FetchTouchSignal(/*MLTouchState*/int state, float x, float y);
	
private:
// private functions
	MLInputMgr(){};
	MLInputMgr(const MLInputMgr &);
	~MLInputMgr(){};
	void operator=(const MLInputMgr &);

	// callbacks for cc
	void ProcessTouchState(MLTouchSignalState state, MLFLOAT x, MLFLOAT y);

// private members
	static MLInputMgr *mInstance;
	MLFLOAT mPosX;//screen coords
	MLFLOAT mPosY; //screen coords
	MLTouchSignalState mSigState;

	MLLogicalState mLogicState;
	MLBOOL mPressed;

};

#endif // __MLINPUTMGR_H__