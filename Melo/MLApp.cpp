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
//--------------------------------------------------------------------------------
using namespace std;
USING_NS_CC;

//--------------------------------------------------------------------------------
MLApp::MLApp()
{
	Director::getInstance()->SetMeloMain(&MLApp::main);	
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
