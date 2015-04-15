//--------------------------------------------------------------------------------
//	File		: MLApp.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#include <iostream>
#include "MLApp.h"
#include "MLSceneMgr.h"
#include "MLScriptMgr.h"
#include "MLFontMgr.h"
//--------------------------------------------------------------------------------
using namespace std;

MLApp * MLApp::mIns = nullptr;

//--------------------------------------------------------------------------------
MLApp::MLApp():
mDeltaTime(0.),
mLastT(0.),
mNowT(0.)
{
	Director::getInstance()->SetMeloMain(&MLApp::main);
	// initial MLSceneMgr, need put here (after cocos initial finished)
	MLSceneMgr::GetInstance()->Init();

	MLScriptMgr::GetInstance()->Init();
	MLFontMgr::GetInstance()->Init();

	// first time
	mIns = this;
	CalculateDeltaTime();
	StepTime();
};

//--------------------------------------------------------------------------------
// note: this funciton called beford actual drawing every frame
void MLApp::main()
{
	//MLLOG("---MELO MAIN LOOP---");	
	//MLApp *app = (MLApp*)(Application::getInstance());
	MLApp *app = mIns;
	if (app)
	{
		app->CalculateDeltaTime();
	}

	MLSceneMgr::GetInstance()->Update(app->GetDeltaT());
	
	// todo:
	//input handling

	if (app)
	{
		app->StepTime();
	}

}

//--------------------------------------------------------------------------------
void MLApp::CalculateDeltaTime()
{
	// for win32
	LARGE_INTEGER freq;
	LARGE_INTEGER now;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&now);

	// need to check animation interval if not using cocos
	mNowT = now.QuadPart / freq.QuadPart;
	mDeltaTime = mNowT - mLastT;

}

void MLApp::StepTime()
{
	mLastT = mNowT;
}
