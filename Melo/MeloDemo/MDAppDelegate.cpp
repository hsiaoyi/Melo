//--------------------------------------------------------------------------------
//	File		: MLAppDelegate.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#include "MDAppDelegate.h"
#include "MDGameScene.h"
#include "MLScriptMgr.h"

//--------------------------------------------------------------------------------
MDAppDelegate::MDAppDelegate()
{
	//MLLOG("MLAppDelegate constructor");
	mApp = ML_NEW MLApp;
}

//--------------------------------------------------------------------------------
MDAppDelegate::~MDAppDelegate()
{

}

//--------------------------------------------------------------------------------
void MDAppDelegate::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};// r, g, b, a, depth, stencil
	GLView::setGLContextAttrs(glContextAttrs);
}

//--------------------------------------------------------------------------------
bool MDAppDelegate::applicationDidFinishLaunching()
{
	Director *director = Director::getInstance();
	GLView *glView = director->getOpenGLView();
	if (!glView)
	{
		if (MLScriptMgr::GetInstance()->LoadFile("mdcfg.lua"))		
		{
			MLScriptMgr::GetInstance()->Resume();
			int w = 0;
			int h = 0;
			MLScriptMgr::GetInstance()->GetNumber("WindowWidth", w);
			MLScriptMgr::GetInstance()->GetNumber("WindowHeight", h);

			char str[15];
			MLScriptMgr::GetInstance()->GetString("WindowName", str);

			std::string name = string(str);
			Rect rect = Rect(0, 0, w, h);
			glView = GLViewImpl::createWithRect(name, rect);
		}
		else
		{
			glView = GLViewImpl::create("Melo App");
		}
		director->setOpenGLView(glView);
	}

	// show display FPS setting
	director->setDisplayStats(false);
	//director->setDisplayStats(true);

	// default animation interval
	//director->setAnimationInterval(1.0 / 60.0);

	// add sample test scene first, will replace later
	mScene = MDGameScene::createScene();
	director->runWithScene(mScene);

	return true;
}

//--------------------------------------------------------------------------------
void MDAppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();
}

//--------------------------------------------------------------------------------
void MDAppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();
}