//--------------------------------------------------------------------------------
//	File		: MLScriptMgr.h
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#ifndef __MLSCRIPTMGR_H__
#define __MLSCRIPTMGR_H__

#include <map>

#include "Melo.h"

extern "C"
{
    #include "lua.h"
}


//--------------------------------------------------------------------------------
//typedef enum _MLScriptType
//{
//	ML_LUA,
//	ML_NONE
//}MLScriptType;
	// stack index params
	const int MLStackTop = -1;
	const int MLStackT2nd = -2;
	const int MLStackT3rd = -3;
    const int MLStackT4th = -4;

	const int MLStackButtom = 1;
	const int MLStackB2nd = 2;
	const int MLStackB3rd = 3;

	const int MLMaxLuaStringLength = 20;
//--------------------------------------------------------------------------------
class MLScriptMgr
{
public:

	static MLScriptMgr *GetInstance();

	MLBOOL Init();
	void Release();
	MLBOOL ReCreate();
    void Close();

    MLINT Start();
	MLINT Pause();
	MLINT Resume(const int paraNum = 0);
	//void SetType(MLScriptType type);
	//MLScriptType GetType();
    
    MLBOOL AddSearchPath(const char* path);
    void AddLoader(lua_CFunction func);
    MLINT LoadBuffer(const char *chunk, int chunkSize, const char *chunkName);
	
	int LoadFile(const char *luaFileName);	// need resume to use params in lua, or use do file otherwise
	MLBOOL DoFile(const char *luaFileName);
	void RegisterCFunctionForLua(const char *LuaUseName, lua_CFunction cFunc);

	void Call(const int nargs, const int nresults);
	MLINT PCall(const int nargs, const int nresults, int errfunc);
	//void CallLuaFunction(const char *LuaFuncName, const char *ArguString, ...);
	void CallLuaFunctionTEST(const char *LuaFuncName, const char *ArguString, ...);

	void CallLuaFunction(const char *LuaFuncName, const char *ArguString, ...);

	void GetGlobal(const char *valName);
	
	// c-lua access funcitons
	// push
	void PushNumber(const int number);
	void PushString(const char *str);
	void PushBool(const bool bVal);
	void PushNil();

	// get lua global params
	void GetNumber(const char *valName, double &number, const int stackPos = MLStackTop);
	void GetNumber(const char *valName, int &number, const int stackPos = MLStackTop);
	void GetNumber(const char *valName, unsigned int &number, const int stackPos = MLStackTop);
	void GetString(const char *valName, char *str, /*signed int maxLength,*/ const int stackPos = MLStackTop);
	void GetBool(const char *valName, bool &bVal, const int stackPos = MLStackTop);

	// todo:fixed length string
	//void GetStringParam(const char *str, signed int maxLength);

	// gets function params passed by lua.
	const char *GetFuncStringParam(int index = MLStackTop);
	double GetFuncDoubleParam(int index = MLStackTop);
	LUA_INTEGER GetFuncIntParam(int index = MLStackTop);
	bool GetFuncBoolParam(int index = MLStackTop);
    
    void SetXXTEAKeyAndSign(const char *key, int keyLen, const char *sign, int signLen);

private:// private functions
	MLScriptMgr();
	MLScriptMgr(const MLScriptMgr&);
	~MLScriptMgr();
	void operator =(const MLScriptMgr&);

    void CleanupXXTEAKeyAndSign();
    
    int ExecuteFunction(int numArgs);
    int ExecuteScriptFile(const char *luaFileName);

private://	private members
	static MLScriptMgr	*mInstance;
	//MLScriptType mType;

	// lua members
	lua_State *mLuaState;
	lua_State *mThreadState;
    
    int _callFromLua;
    bool  _xxteaEnabled;
    char* _xxteaKey;
    int   _xxteaKeyLen;
    char* _xxteaSign;
    int   _xxteaSignLen;
};

#endif // __MLSCRIPTMGR_H__
