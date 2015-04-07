//--------------------------------------------------------------------------------
//	File		: MLScriptMgr.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#include <algorithm>
#include <string>

#include "MLScriptMgr.h"

extern "C"
{
	#include "lua/lua/lualib.h"
	#include "lua/lua/lauxlib.h"
}

//--------------------------------------------------------------------------------
MLScriptMgr *MLScriptMgr::mInstance = nullptr;

//--------------------------------------------------------------------------------
MLScriptMgr *MLScriptMgr::GetInstance()
{
	if (mInstance == nullptr) // todo:
	{
		mInstance = ML_NEW MLScriptMgr;
	}
	return mInstance;
}

//--------------------------------------------------------------------------------
void MLScriptMgr::Init()
{
	mLuaState = lua_open();
	if (mLuaState)
	{
		luaL_openlibs(mLuaState);
		mThreadState = lua_newthread(mLuaState);
	}
}

//--------------------------------------------------------------------------------
void MLScriptMgr::Release()
{
	if (mLuaState)
	{
		lua_close(mLuaState);
	}
}

//--------------------------------------------------------------------------------
MLBOOL MLScriptMgr::ReCreate()
{
	if (mLuaState)
	{
		lua_close(mLuaState);
		mLuaState = lua_open();
		if (mLuaState)
		{
			luaL_openlibs(mLuaState);
			mThreadState = lua_newthread(mLuaState);
			return MLTRUE;
		}
	}
	return MLFALSE;
}

//--------------------------------------------------------------------------------
//void MLScriptMgr::SetType(MLScriptType type)
//{
//	mType = type;
//}

//--------------------------------------------------------------------------------
//MLScriptType MLScriptMgr::GetType()
//{
//	return mType;
//}

//--------------------------------------------------------------------------------
MLBOOL MLScriptMgr::LoadFile(const char *luaFileName)
{
	if (luaL_loadfile(mThreadState, luaFileName) == 0)
	{
		return MLTRUE;
	}
	else
	{
		return MLFALSE;
	}
}

//--------------------------------------------------------------------------------
MLBOOL MLScriptMgr::DoFile(const char *luaFileName)
{
	if (luaL_dofile(mThreadState, luaFileName))
	{
		return MLTRUE;
	}
	else
	{
		return MLFALSE;
	}
}

//--------------------------------------------------------------------------------
MLINT MLScriptMgr::Pause()
{
	return lua_yield(mThreadState, 0);
}

//--------------------------------------------------------------------------------
MLINT MLScriptMgr::Resume(const int paraNum)
{
	return lua_resume(mThreadState, paraNum);
}

//--------------------------------------------------------------------------------
void MLScriptMgr::RegisterCFunctionForLua(const char *LuaUseName, lua_CFunction cFunc)
{
	lua_register(mThreadState, LuaUseName, cFunc);
}

//--------------------------------------------------------------------------------
void MLScriptMgr::Call(int nargs, int nresults)
{
	lua_call(mThreadState, nargs, nresults);
}

//--------------------------------------------------------------------------------
MLINT MLScriptMgr::PCall(const int nargs, const int nresults, int errfunc)
{
	return lua_pcall(mThreadState, nargs, nresults, errfunc);
}

//--------------------------------------------------------------------------------
void MLScriptMgr::CallLuaFunctionTEST(const char *LuaFuncName, const char *ArguString, ...)
{
	va_list vl;
	int nArgs, nResults;

	va_start(vl, ArguString);
	lua_getglobal(mThreadState, LuaFuncName);

	nArgs = 0;
	while (*ArguString)
	{
		lua_pushstring(mThreadState, va_arg(vl, char*));

		nArgs++;
		luaL_checkstack(mThreadState, 1, "melotest too many arguments");
	}
	
	// test call started here
	/*
	lua_pushstring(mThreadState, tempstr);
	lua_pcall(mThreadState, 1, 1, 0);
	va_end(vl);
	*/
}

//--------------------------------------------------------------------------------
// example for passing arguments and results
// int iIn1;
// double dIn1;
// bool bIn1;
// char *strIn;
// double &dOut;
// CallLuaFunction("LuaFuncName", "idbs>d", iIn1, dIn1, bIn1, strIn, &dOut)
void MLScriptMgr::CallLuaFunction(const char *LuaFuncName, const char *ArguString, ...)
{
	va_list vl;
	int nArg, nRes;

	va_start(vl, ArguString);
	lua_getglobal(mThreadState, LuaFuncName);

	// push arguments
	nArg = 0;
	while (*ArguString)
	{
		switch (*ArguString++)
		{
		case'd':// double
			lua_pushnumber(mThreadState, va_arg(vl, double));
			break;

		case'i':// int
			lua_pushnumber(mThreadState, va_arg(vl, int));
			break;

		case's':// string
			lua_pushstring(mThreadState, va_arg(vl, char *));
			break;

		case'b':// bool
			lua_pushboolean(mThreadState, va_arg(vl, bool));
			break;

		case'>':// indicating end of inputs
			goto ENDWHILE;		

		default:
			MLLOG( "invalid option (%c)", *(ArguString - 1));
		}
		nArg++;
		luaL_checkstack(mThreadState, 1, "too many arguments");
	} 
ENDWHILE:

	// do the call
	nRes = strlen(ArguString);
	if(lua_pcall(mThreadState, nArg, nRes, 0) != 0)
	{
		MLLOG("error running function `%s': %s", LuaFuncName, lua_tostring(mThreadState, -1));
	}

	// retrive results
	nRes = -nRes;
	while (*ArguString) 
	{
		switch (*ArguString++) 
		{
		case'd':// double
			if(!lua_isnumber(mThreadState, nRes))
			{
				MLLOG("wrong result type");
			}				
			*va_arg(vl, double *) = lua_tonumber(mThreadState, nRes);
			break;

		case'i':// int
			if(!lua_isnumber(mThreadState, nRes))
			{
				MLLOG("wrong result type");
			}
			*va_arg(vl, int *) = (int)lua_tonumber(mThreadState, nRes);
			break;

		case's':// string
			if(!lua_isstring(mThreadState, nRes))
			{
				MLLOG("wrong result type");
			}
			*va_arg(vl, const char **) = lua_tostring(mThreadState, nRes);
			break;
		
		case'b':// bool
			if (!lua_isboolean(mThreadState, nRes))
			{
				MLLOG("wrong result type");
			}
			*va_arg(vl, bool *) = lua_toboolean(mThreadState, nRes);
			break;

		default:
			MLLOG("invalid option (%c)", *(ArguString - 1));
		}
		nRes++;
	}
	va_end(vl);
}

//--------------------------------------------------------------------------------
void MLScriptMgr::GetGlobal(const char *valName)
{
	// pushes onto the stack the value of the global name
	lua_getglobal(mThreadState, valName);
}

//--------------------------------------------------------------------------------
void MLScriptMgr::PushNumber(const int number)
{
	lua_pushnumber(mThreadState, number);
}

//--------------------------------------------------------------------------------
void MLScriptMgr::PushString(const char *str)
{
	lua_pushstring(mThreadState, str);
}

//--------------------------------------------------------------------------------
void MLScriptMgr::PushBool(const bool bVal)
{
	lua_pushboolean(mThreadState, bVal);
}

//--------------------------------------------------------------------------------
void MLScriptMgr::PushNil()
{
	lua_pushnil(mThreadState);
}

//--------------------------------------------------------------------------------
void MLScriptMgr::GetNumber(const char *valName, double &number, const int stackPos)
{
	lua_getglobal(mThreadState, valName);
	number = lua_tonumber(mThreadState, stackPos);
	lua_pop(mThreadState, MLStackTop);
}

//--------------------------------------------------------------------------------
void MLScriptMgr::GetNumber(const char *valName, int &number, const int stackPos)
{
	lua_getglobal(mThreadState, valName);
	number = static_cast<int>(lua_tonumber(mThreadState, stackPos));
	lua_pop(mThreadState, MLStackTop);
}

//--------------------------------------------------------------------------------
void MLScriptMgr::GetNumber(const char *valName, unsigned int &number, const int stackPos)
{
	lua_getglobal(mThreadState, valName);
	number = static_cast<unsigned int>(lua_tonumber(mThreadState, stackPos));
	lua_pop(mThreadState, MLStackTop);
}

//--------------------------------------------------------------------------------
void MLScriptMgr::GetString(const char *valName, char *string, /*signed int maxLength,*/ const int stackPos)
{
	lua_getglobal(mThreadState, valName);
	const char *tempStr = lua_tostring(mThreadState, stackPos);
	if (tempStr != nullptr)
	{
		std::strcpy(string, tempStr);
	}
	lua_pop(mThreadState, MLStackTop);
}

//--------------------------------------------------------------------------------
void MLScriptMgr::GetBool(const char *valName, bool &bval, const int stackPos)
{
	lua_getglobal(mThreadState, valName);

	//lua_toboolean returns 1 for any Lua value different from false and nil
	bval = lua_toboolean(mThreadState, stackPos) ? true : false;
	lua_pop(mThreadState, MLStackTop);
}

//--------------------------------------------------------------------------------
/*
void MLScriptMgr::GetStringParam(const char *str, signed int maxLength)
{	
	if (str == nullptr)
	{
		return;
	}

	const char *tempStr = luaL_checkstring(mThreadState, maxLength);
	if (tempStr != nullptr)
	{
		int length = std::min(static_cast<int>(std::strlen(tempStr)), maxLength);

		//std::strcpy();
	}
	
	// 0210 to finish
}
*/

//--------------------------------------------------------------------------------
const char *MLScriptMgr::GetFuncStringParam(int index)
{
	return luaL_checkstring(mThreadState, index);
}

//--------------------------------------------------------------------------------
double MLScriptMgr::GetFuncDoubleParam(int index)
{
	return lua_tonumber(mThreadState, index);
}

//--------------------------------------------------------------------------------
int MLScriptMgr::GetFuncIntParam(int index)
{
	return lua_tointeger(mThreadState, index);
}

//--------------------------------------------------------------------------------
bool MLScriptMgr::GetFuncBoolParam(int index)
{
	return lua_toboolean(mThreadState, index) ? true : false;
}