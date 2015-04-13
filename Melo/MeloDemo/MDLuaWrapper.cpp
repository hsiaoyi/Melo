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
#include "MDGameScene.h"


//#include "Melo.h"
//#include "MLScriptMgr.h"

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

//--------------------------------------------------------------------------------
extern "C" int InitDemoScene(lua_State* L)
{
	return 0;
}

//--------------------------------------------------------------------------------
extern "C" int SetBG(lua_State* L)
{
	return 0;
}

