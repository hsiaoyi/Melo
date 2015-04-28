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
		mPressed = false;
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
	MLLOG("---input main update---");
	mSigState = MLTouchSignalState::MLTS_None;
	// need change input state here
}

//--------------------------------------------------------------------------------
void MLInputMgr::FetchTouchSignal(/*MLTouchState*/int st, float x, float y)
{
	MLTouchSignalState state = (MLTouchSignalState)st;
	if (x >= 0 && y >= 0)
	{
		switch (state)
		{
		case MLTS_Begin:
			MLInputMgr::GetInstance()->TouchBegin(x, y);
			break;

		case MLTS_Move:
			MLInputMgr::GetInstance()->TouchMove(x, y);
			break;

		case MLTS_End:
			MLInputMgr::GetInstance()->TouchEnd(x, y);
			break;

		case MLTS_Cancel:
			MLInputMgr::GetInstance()->TouchCancel(x, y);
			break;

		default:
			break;
		}
	}// end if
}

// private functions
//--------------------------------------------------------------------------------
void MLInputMgr::TouchBegin(float x, float y)
{
	MLLOG("---touch [Begin]---");
	mSigState = MLTouchSignalState::MLTS_Begin;
}

//--------------------------------------------------------------------------------
void MLInputMgr::TouchMove(float x, float y)
{
	MLLOG("---touch [Move]---");
	mPosX = x;
	mPosY = y;
	mSigState = MLTouchSignalState::MLTS_Move;
}

//--------------------------------------------------------------------------------
void MLInputMgr::TouchEnd(float x, float y)
{
	MLLOG("---touch [End]---");
	mSigState = MLTouchSignalState::MLTS_End;
}

//--------------------------------------------------------------------------------
void MLInputMgr::TouchCancel(float x, float y)
{
	MLLOG("---touch [Cancel]---");
	mSigState = MLTouchSignalState::MLTS_Cancel;
}