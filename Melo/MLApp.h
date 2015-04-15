//--------------------------------------------------------------------------------
//	File		: MLApp.h
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#ifndef __MLAPP_H__
#define __MLAPP_H__

#include "Melo.h"
//#include "MLAppDelegate.h"

//================================================================================
class MLApp
{
public:
	MLApp();
	virtual ~MLApp(){};

	//static void main(void* _app);
	static void main();
	//void main();

	MLFLOAT GetDeltaT()
	{
		return mDeltaTime;
	}

private:
	void CalculateDeltaTime();
	void StepTime();
	
private:
	// windows setting
	// todo: change to vec2 later
	MLINT mWindowWidth;
	MLINT mWindowHeight;

	MLFLOAT mDeltaTime;

	// win32 param
	MLFLOAT mLastT;
	MLFLOAT mNowT;
	static MLApp *mIns;

	// todo:
	// fps
	// display cocos debug setting
	// display melo debug setting
	// scene mgr
	// script mgr
	// sound 
	//
	
	//
	//MLAppDelegate mAppDelegate;

};

#endif // __MLAPP_H__