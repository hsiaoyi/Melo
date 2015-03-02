//--------------------------------------------------------------------------------
//	File		: MLAppDelegate.h
//	Description	: Cocos appdelegate wrapper class
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#ifndef __MLAPP_DELEGATE_H__
#define __MLAPP_DELEGATE_H__

#include "cocos2d.h"
#include "Melo.h"
#include "MLApp.h"

//================================================================================
class MLAppDelegate : private cocos2d::Application
{
public:
	MLAppDelegate();
	virtual ~MLAppDelegate();

	virtual void initGLContextAttrs();

	virtual bool applicationDidFinishLaunching();
	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();

	MLApp *mApp;

};



#endif // __MLAPP_DELEGATE_H__