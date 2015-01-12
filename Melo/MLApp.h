//--------------------------------------------------------------------------------
//	File		: MLApp.h
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#ifndef __MLAPP_H__
#define __MLAPP_H__

#include "Melo.h"
#include "MLAppDelegate.h"

//================================================================================
class MLApp
{
public:
	MLApp();
	virtual ~MLApp(){};

	static void main();
	//void main();
	
private:
	// windows setting
	// todo: change to vec2 later
	MLINT mWindowWidth;
	MLINT mWindowHeight;

	// todo:
	// fps
	// display cocos debug setting
	// display melo debug setting
	// scene mgr
	// script mgr
	// sound 
	//
	
	//
	MLAppDelegate mAppDelegate;

};

#endif // __MLAPP_H__