//--------------------------------------------------------------------------------
//	File		: MLAppDelegate.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#include "MLAppDelegate.h"
#include "MLCCScene.h"
#include "MLScriptMgr.h"
#include "MLLuaTestFunc.h"

USING_NS_CC;

//--------------------------------------------------------------------------------
MLAppDelegate::MLAppDelegate()
{
	MLLOG("MLAppDelegate constructor");
	//::Application();
	mApp = ML_NEW MLApp();
}

//--------------------------------------------------------------------------------
MLAppDelegate::~MLAppDelegate()
{

}

//--------------------------------------------------------------------------------
void MLAppDelegate::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};// r, g, b, a, depth, stencil
	GLView::setGLContextAttrs(glContextAttrs);
}

//--------------------------------------------------------------------------------
bool MLAppDelegate::applicationDidFinishLaunching()
{
	Director *director = Director::getInstance();
	GLView *glView = director->getOpenGLView();
	if (!glView)
	{
		glView = GLViewImpl::create("Melo App");
		director->setOpenGLView(glView);
	}

	// show display FPS setting
	director->setDisplayStats(false);
	//director->setDisplayStats(true);

	// default animation interval
	//director->setAnimationInterval(1.0 / 60.0);

	// script initial
	MLScriptMgr::GetInstance()->Init();
	MLScriptMgr::GetInstance()->LoadFile("melotest.lua");
	MLScriptMgr::GetInstance()->RegisterCFunctionForLua("MeloLuaTest1", LuaTestFunction1);
	MLScriptMgr::GetInstance()->RegisterCFunctionForLua("MeloLuaTest2", LuaTestFunction2);
	// add sample test scene first, will replace later
	Scene *scene = MLCCScene::createScene();
	director->runWithScene(scene);

	return true;
}

//--------------------------------------------------------------------------------
void MLAppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();
}

//--------------------------------------------------------------------------------
void MLAppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();
}