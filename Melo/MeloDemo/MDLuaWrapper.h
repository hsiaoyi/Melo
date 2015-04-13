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

#include "lua\lua\lua.h"

//extern "C" int LuaTestFunction1(lua_State* L);
//extern "C" int LuaTestFunction2(lua_State* L);
extern "C" int InitDemoScene(lua_State* L);
extern "C" int SetBG(lua_State* L);



#endif // __MDLUAWRAPPER_H__