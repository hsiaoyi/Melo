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

//--------------------------------------------------------------------------------
MLApp::MLApp()
{
	Director::getInstance()->SetMeloMain(&MLApp::main);
	// initial MLSceneMgr, need put here (after cocos initial finished)
	MLSceneMgr::GetInstance()->Init();

	MLScriptMgr::GetInstance()->Init();
	MLFontMgr::GetInstance()->Init();
};

//--------------------------------------------------------------------------------
// note: this funciton called beford actual drawing every frame
void MLApp::main()
{
	//MLLOG("---MELO MAIN LOOP---");
	MLSceneMgr::GetInstance()->Update();
	
	// todo:
	//input handling

}
