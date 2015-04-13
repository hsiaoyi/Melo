//--------------------------------------------------------------------------------
//	File		: MDAppDelegate.h
//	Description	: Cocos appdelegate wrapper class
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#ifndef __MDAPP_DELEGATE_H__
#define __MDAPP_DELEGATE_H__

#include "cocos2d.h"
#include "Melo.h"
#include "MLApp.h"

#include "MDGameScene.h"

//================================================================================
class MDAppDelegate : private cocos2d::Application
{
public:
	MDAppDelegate();
	virtual ~MDAppDelegate();

	virtual void initGLContextAttrs();

	virtual bool applicationDidFinishLaunching();
	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();

	MLApp *mApp;

	//MDGameScene *mScene;
	cocos2d::Scene* mScene;

};



#endif // __MDAPP_DELEGATE_H__