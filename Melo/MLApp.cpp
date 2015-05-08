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
#include "MLInputMgr.h"

//#if defined(MLIOS)
//#include <sys/time.h>
//#endif


//--------------------------------------------------------------------------------
using namespace std;

MLApp * MLApp::mIns = nullptr;

//--------------------------------------------------------------------------------
MLApp::MLApp():
mDeltaTime(0.),
mLastT(0.),
mNowT(0.)
{
	// initial MLSceneMgr, need put here (after cocos initial finished)
	MLSceneMgr::GetInstance()->Init();

	MLScriptMgr::GetInstance()->Init();
	MLFontMgr::GetInstance()->Init();

	MLInputMgr::GetInstance()->Init();


	Director::getInstance()->SetMeloMain(&MLApp::main);
	Director::getInstance()->SetMeloFetchTouch(&MLInputMgr::FetchTouchSignal);
	//Director::getInstance()->SetMeloTouchCBs(&MLInputMgr::TouchBegin, &MLInputMgr::TouchMove, &MLInputMgr::TouchEnd, &MLInputMgr::TouchCancel);

	// first time
	mIns = this;
	CalculateDeltaTime();
	StepTime();
};

//--------------------------------------------------------------------------------
MLApp::~MLApp()
{
	MLSceneMgr::GetInstance()->Release();
	MLScriptMgr::GetInstance()->Release();
	MLFontMgr::GetInstance()->Release();
}

//--------------------------------------------------------------------------------
// note: this funciton called beford actual drawing every frame
void MLApp::main()
{
	//MLLOG("---MELO MAIN LOOP---");	
	MLApp *app = mIns;
	if (app)
	{
		app->CalculateDeltaTime();
	}

	// sequence:input->physics->render
	MLInputMgr::GetInstance()->Update();// todo: input listener

	MLSceneMgr::GetInstance()->Update(app->GetDeltaTime());
	
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
#if defined(MLWIN32)
	// for win32
	LARGE_INTEGER freq;
	LARGE_INTEGER now;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&now);

	// need to check animation interval if not using cocos
	mNowT = (MLDOUBLE)now.QuadPart / freq.QuadPart;

#elif defined(MLIOS)
    timeval tv;
    gettimeofday(&tv, nullptr);
    
    mNowT = (double)tv.tv_sec + (double)tv.tv_usec/1000000;
#endif
    
    mDeltaTime = mNowT - mLastT;
}

//--------------------------------------------------------------------------------
void MLApp::StepTime()
{
	mLastT = mNowT;
}
