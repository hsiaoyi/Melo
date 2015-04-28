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

//--------------------------------------------------------------------------------
void SetGameScene(MDGameScene *game)
{
	sGame = game;
}

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
		sGame->SetBG(file);
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

//--------------------------------------------------------------------------------
extern "C" int SetTileTextWordByWordEffect(lua_State* L)
{
	double period = MLScriptMgr::GetInstance()->GetFuncDoubleParam(MLStackT3rd);
	double delay = MLScriptMgr::GetInstance()->GetFuncDoubleParam(MLStackT2nd);
	bool repeat = MLScriptMgr::GetInstance()->GetFuncBoolParam(MLStackTop);

	sGame->SetTitleEffectParams(period, delay, repeat);

	return 1;
}

//--------------------------------------------------------------------------------
extern "C" int SetTitleTextAlignWin(lua_State* L)
{
	int hori = MLScriptMgr::GetInstance()->GetFuncIntParam(MLStackT2nd);// 0:left, 1:center, 2:right
	int vert = MLScriptMgr::GetInstance()->GetFuncIntParam(MLStackTop); // 0:top, 1:center, 2:buttom

	sGame->SetTitleAlignWin(hori, vert);

	return 1;
}
//--------------------------------------------------------------------------------
extern "C" int SetGameBGAlignWin(lua_State* L)
{
	int hori = MLScriptMgr::GetInstance()->GetFuncIntParam(MLStackT2nd);
	int vert = MLScriptMgr::GetInstance()->GetFuncIntParam(MLStackTop);

	sGame->SetBGAlignWin(hori, vert);

	return 1;
}