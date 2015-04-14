//--------------------------------------------------------------------------------
//	File		: MDLuaWrapper.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#include "MDLuaWrapper.h"
#include "MDAppDelegate.h"
#include "MLSceneMgr.h"

#include "MLScriptMgr.h"

//#include "Melo.h"


//--------------------------------------------------------------------------------
//extern "C" int LuaTestFunction1(lua_State* L)
//{
//	int ii;
//	MLScriptMgr::GetInstance()->GetNumber("MeloTestPara2", ii, MLStackTop);
//	MLLOG("========Lua[1]:%d========", ii);
//	return 0;
//}

//--------------------------------------------------------------------------------
//extern "C" int LuaTestFunction2(lua_State* L)
//{
//	char *str = const_cast<char*>(MLScriptMgr::GetInstance()->GetFuncStringParam());
//
//	MLLOG("========Lua[2]:%s========", str);
//	return 0;
//}

MDGameScene *sGame;
int sGameBG = -1;

//--------------------------------------------------------------------------------
void SetGameScene(MDGameScene *game)
{
	sGame = game;
}

//--------------------------------------------------------------------------------
/*
void SetGameLayerId(int id)
{
	sGameLayer = id;
}
*/

//--------------------------------------------------------------------------------
extern "C" int InitDemoScene(lua_State* L)
{
	return 0;
}

//--------------------------------------------------------------------------------
extern "C" int SetGameBG(lua_State* L)
{
	string file = MLScriptMgr::GetInstance()->GetFuncStringParam();
	if (sGame)
	{
		sGameBG = (int)sGame->SetBG(file);
	}

	return 1;
}

//--------------------------------------------------------------------------------
extern "C" int SetTitleFont(lua_State* L)
{
	string fontName = MLScriptMgr::GetInstance()->GetFuncStringParam(MLStackT2nd);
	int size = MLScriptMgr::GetInstance()->GetFuncIntParam();

	if (sGame)
	{
		sGame->SetTitleFontTTF(fontName, size);
	}

	return 1;

}

//--------------------------------------------------------------------------------
extern "C" int SetTitleText(lua_State* L)
{
	string text = MLScriptMgr::GetInstance()->GetFuncStringParam();

	if (sGame)
	{
		sGame->SetTitle(text);
	}

	return 1;
}