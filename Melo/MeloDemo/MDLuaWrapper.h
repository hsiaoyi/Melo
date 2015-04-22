//--------------------------------------------------------------------------------
//	File		: MDLuaWrapper.h
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#ifndef __MDLUAWRAPPER_H__
#define __MDLUAWRAPPER_H__
#include "MDGameScene.h"
#include "lua\lua\lua.h"

//--------------------------------------------------------------------------------
// c++ called functions
void SetGameScene(MDGameScene *game);
//void SetGameLayerId(int id);

//--------------------------------------------------------------------------------
// lua called funcitons, need register first before use
extern "C" int InitDemoScene(lua_State* L);
extern "C" int SetGameBG(lua_State* L);
extern "C" int SetTitleFont(lua_State* L);
extern "C" int SetTitleText(lua_State* L);
extern "C" int SetTileTextWordByWordEffect(lua_State* L);
extern "C" int SetTitleTextAlignWin(lua_State* L);
// todo
//extern "C" int SetTitleColor();
//extern "C" int SetTitlePos();


#endif // __MDLUAWRAPPER_H__