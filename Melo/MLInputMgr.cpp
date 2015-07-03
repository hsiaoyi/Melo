//--------------------------------------------------------------------------------
//	File		: MLInputMgr.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#include "MLInputMgr.h"

MLInputMgr * MLInputMgr::mInstance = nullptr;

// for debug use
//#define MLInputLog MLLOG
#define MLInputLog  

//--------------------------------------------------------------------------------
MLInputMgr* MLInputMgr::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = ML_NEW MLInputMgr;
	}

	return mInstance;
}

//--------------------------------------------------------------------------------
void MLInputMgr::Init()
{
	if (mInstance)
	{
		mPosX = 0.;
		mPosY = 0.;
		mSigState = MLTS_None;
		mLogicState = MLLS_Up;
		mPressed = MLFALSE;
	}
}

//--------------------------------------------------------------------------------
void MLInputMgr::Release()
{
	ML_DELETE mInstance;
}

//--------------------------------------------------------------------------------
void MLInputMgr::Update()
{
	//internal input state update
	if(mSigState == MLTS_Begin)
	{
		if (mPressed)
		{
			mLogicState = MLLS_Down;
			//MLInputLog("====[Down  ]====");
		}
	}
	else 
	if (mSigState == MLTS_Move)
	{
		if (mPressed)
		{
			mLogicState = MLLS_Pressed;
			//MLInputLog("====[Pressed]====");
		}
		else
		{
			mLogicState = MLLS_Up;
			//MLInputLog("----[Up     ]----");
		}
	}
	else
	{
		mLogicState = MLLS_Up;
		//MLInputLog("----[Up     ]----");
	}
}

//--------------------------------------------------------------------------------
void MLInputMgr::FetchTouchSignal(int st, float x, float y)
{
	MLTouchSignalState state = (MLTouchSignalState)st;
	if (x >= 0 && y >= 0)
	{
		MLInputMgr::GetInstance()->ProcessTouchState(state, x, y);
	}
}

//--------------------------------------------------------------------------------
MLLogicalState MLInputMgr::GetLogicalState()
{
	return mLogicState;
}

// private function
//--------------------------------------------------------------------------------
void MLInputMgr::ProcessTouchState(MLTouchSignalState state, MLFLOAT x, MLFLOAT y)
{
	mPosX = x;
	mPosY = y;
	mSigState = state;

	if (state == MLTS_Begin)
	{
		mPressed = MLTRUE;
	}
	else if (state == MLTS_End || state == MLTS_Cancel)
	{
		mPressed = MLFALSE;
	}
}