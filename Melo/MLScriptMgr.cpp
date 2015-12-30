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
#include "platform/CCFileUtils.h"
#include "xxtea/xxtea.h"

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

//--------------------------------------------------------------------------------
int InternalLoader(lua_State *lThreadState)
{
    static const std::string BYTECODE_FILE_EXT    = ".luac";
    static const std::string NOT_BYTECODE_FILE_EXT = ".lua";
    
    std::string filename(luaL_checkstring(lThreadState, 1));
    size_t pos = filename.rfind(BYTECODE_FILE_EXT);
    if (pos != std::string::npos)
    {
        filename = filename.substr(0, pos);
    }
    else
    {
        pos = filename.rfind(NOT_BYTECODE_FILE_EXT);
        if (pos == filename.length() - NOT_BYTECODE_FILE_EXT.length())
        {
            filename = filename.substr(0, pos);
        }
    }
    
    pos = filename.find_first_of(".");
    while (pos != std::string::npos)
    {
        filename.replace(pos, 1, "/");
        pos = filename.find_first_of(".");
    }
    
    // search file in package.path
    unsigned char* chunk = nullptr;
    ssize_t chunkSize = 0;
    std::string chunkName;
    FileUtils* utils = FileUtils::getInstance();
    
    lua_getglobal(lThreadState, "package");
    lua_getfield(lThreadState, -1, "path");
    std::string searchpath(lua_tostring(lThreadState, -1));
    lua_pop(lThreadState, 1);
    size_t begin = 0;
    size_t next = searchpath.find_first_of(";", 0);
    
    do
    {
        if (next == std::string::npos)
        {
            next = searchpath.length();
        }
        
        std::string prefix = searchpath.substr(begin, next);
        if (prefix[0] == '.' && prefix[1] == '/')
        {
            prefix = prefix.substr(2);
        }
        
        pos = prefix.find("?.lua");
        chunkName = prefix.substr(0, pos) + filename + BYTECODE_FILE_EXT;
        if (utils->isFileExist(chunkName))
        {
            chunk = utils->getFileData(chunkName.c_str(), "rb", &chunkSize);
            break;
        }
        else
        {
            chunkName = prefix.substr(0, pos) + filename + NOT_BYTECODE_FILE_EXT;
            if (utils->isFileExist(chunkName))
            {
                chunk = utils->getFileData(chunkName.c_str(), "rb", &chunkSize);
                break;
            }
        }
        
        begin = next + 1;
        next = searchpath.find_first_of(";", begin);
    } while (begin < (int)searchpath.length());
    
    if (chunk)
    {
        MLScriptMgr::GetInstance()->LoadBuffer((char*)chunk, (int)chunkSize, chunkName.c_str());
        free(chunk);
    }
    else
    {
        CCLOG("can not get file data of %s", chunkName.c_str());
        return 0;
    }
    
    return 1;
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
MLScriptMgr::MLScriptMgr() : mLuaState(nullptr)
                           , mThreadState(nullptr)
                           , _callFromLua(0)
                           , _xxteaEnabled(false)
                           , _xxteaKey(nullptr)
                           , _xxteaKeyLen(0)
                           , _xxteaSign(nullptr)
                           , _xxteaSignLen(0)
{}

//--------------------------------------------------------------------------------
MLScriptMgr::~MLScriptMgr()
{}

//--------------------------------------------------------------------------------
MLBOOL MLScriptMgr::Init()
{
	if (mLuaState == nullptr)
	{
        mLuaState = lua_open();
        
		luaL_openlibs(mLuaState);
		mThreadState = lua_newthread(mLuaState);
        
        std::string bundlepath = FileUtils::getInstance()->fullPathForFilename("sicfg.lua");
        bundlepath.erase(bundlepath.end()-10, bundlepath.end());
        if (AddSearchPath(bundlepath.c_str()) == MLTRUE)
        {
            AddLoader(InternalLoader);
        }
	}
    return MLFALSE;
}

//--------------------------------------------------------------------------------
void MLScriptMgr::Release()
{
    Close();
	ML_DELETE mInstance;
	mInstance = nullptr;
}

//--------------------------------------------------------------------------------
MLBOOL MLScriptMgr::ReCreate()
{
	if (mLuaState)
	{
        Close();
        return Init();
	}
	return MLFALSE;
}

//--------------------------------------------------------------------------------
void MLScriptMgr::Close()
{
    if (mLuaState)
    {
        lua_close(mLuaState);
        mLuaState = nullptr;
    }
}

MLBOOL MLScriptMgr::AddSearchPath(const char* path)
{
    if (!mLuaState)
        return MLFALSE;
    
    lua_getglobal(mLuaState, "package");                        /* L: package */
    lua_getfield(mLuaState, -1, "path");                        /* get package.path, L: package path */
    const char* cur_path =  lua_tostring(mLuaState, -1);
    
    lua_pushfstring(mLuaState, "%s;%s\\?.lua", cur_path, path); /* L: package path newpath */
    lua_setfield(mLuaState, -3, "path");                        /* package.path = newpath, L: package path */
    lua_pop(mLuaState, 2);
    
    return MLTRUE;
}

void MLScriptMgr::AddLoader(lua_CFunction func)
{
    if (!func)
        return;
    
    // stack content after the invoking of the function
    // get loader table
    lua_getglobal(mLuaState, "package");                               /* L: package */
    lua_getfield(mLuaState, -1, "loaders");                            /* L: package, loaders */
    
    // insert loader into index 2
    lua_pushcfunction(mLuaState, func);                                /* L: package, loaders, func */
    for (int i = (int)(lua_objlen(mLuaState, -2) + 1); i > 2; --i)
    {
        lua_rawgeti(mLuaState, -2, i - 1);                             /* L: package, loaders, func, function */
        // we call lua_rawgeti, so the loader table now is at -3
        lua_rawseti(mLuaState, -3, i);                                 /* L: package, loaders, func */
    }
    lua_rawseti(mLuaState, -2, 2);                                     /* L: package, loaders */
    
    // set loaders into package
    lua_setfield(mLuaState, -2, "loaders");                            /* L: package */
    
    lua_pop(mLuaState, 1);
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

static const std::string BYTECODE_FILE_EXT    = ".luac";
static const std::string NOT_BYTECODE_FILE_EXT = ".lua";
//--------------------------------------------------------------------------------
int MLScriptMgr::LoadFile(const char *luaFileName)
{
    return ExecuteScriptFile(luaFileName);
}

int MLScriptMgr::ExecuteScriptFile(const char *luaFileName)
{
    std::string buf(luaFileName);
    //
    // remove .lua or .luac
    //
    size_t pos = buf.rfind(BYTECODE_FILE_EXT);
    if (pos != std::string::npos)
    {
        buf = buf.substr(0, pos);
    }
    else
    {
        pos = buf.rfind(NOT_BYTECODE_FILE_EXT);
        if (pos == buf.length() - NOT_BYTECODE_FILE_EXT.length())
        {
            buf = buf.substr(0, pos);
        }
    }
    
    FileUtils *utils = FileUtils::getInstance();
    //
    // 1. check .lua suffix
    // 2. check .luac suffix
    //
    std::string tmpfilename = buf + NOT_BYTECODE_FILE_EXT;
    if (utils->isFileExist(tmpfilename))
    {
        buf = tmpfilename;
    }
    else
    {
        tmpfilename = buf + BYTECODE_FILE_EXT;
        if (utils->isFileExist(tmpfilename))
        {
            buf = tmpfilename;
        }
    }
    
    std::string fullPath = utils->fullPathForFilename(buf);
    Data data = utils->getDataFromFile(fullPath);
    int rn = 0;
    if (!data.isNull())
    {
        std::string codes((char *)data.getBytes());
        rn = LoadBuffer((const char*)data.getBytes(), (int)data.getSize(), fullPath.c_str());
    }
    return rn;
}

int MLScriptMgr::ExecuteFunction(int numArgs)
{
    int functionIndex = -(numArgs + 1);
    if (!lua_isfunction(mThreadState, functionIndex))
    {
        CCLOG("value at stack [%d] is not function", functionIndex);
        lua_pop(mThreadState, numArgs + 1); // remove function and arguments
        return 0;
    }
    
    int error = 0;
    ++_callFromLua;
    error = lua_pcall(mThreadState, numArgs, 0, 0);
    --_callFromLua;
    if (error)
    {
        CCLOG("[LUA ERROR] %s", lua_tostring(mThreadState, - 1));        /* L: ... error */
        lua_pop(mThreadState, 1); // remove error message from stack
        return 0;
    }
    
    // get return value
    int ret = 0;
    if (lua_isnumber(mThreadState, -1))
    {
        ret = (int)lua_tointeger(mThreadState, -1);
    }
    else if (lua_isboolean(mThreadState, -1))
    {
        ret = (int)lua_toboolean(mThreadState, -1);
    }
    // remove return value from stack
    lua_pop(mThreadState, 1);                                                /* L: ... [G] */
    
    return ret;
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
MLINT MLScriptMgr::Start()
{
    return ExecuteFunction(0);
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
	if( lua_pcall(mThreadState, nargs, nresults, errfunc) )
    {
        std::string aa = lua_tostring(mThreadState, -1);
        CCLOG("%s", aa.c_str());
    }
    return 0;
}

//--------------------------------------------------------------------------------
void MLScriptMgr::CallLuaFunctionTEST(const char *LuaFuncName, const char *ArguString, ...)
{
	va_list vl;
    
	va_start(vl, ArguString);
	lua_getglobal(mThreadState, LuaFuncName);

	int nArgs = 0;
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
			lua_pushboolean(mThreadState, va_arg(vl, int));
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
	nRes = (int)strlen(ArguString);
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
	size_t l = lua_strlen(mThreadState, stackPos);
	int jj = 0;
	if (tempStr[l] == '\0')
	{
		//return;
		++jj;
	}
	if (strlen(tempStr) <= l)
	{
		//return;
		++jj;
	}

	if (tempStr != nullptr)
	{
		strcpy(string, tempStr);
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
    //return lua_tostring(mThreadState, index);
}

//--------------------------------------------------------------------------------
double MLScriptMgr::GetFuncDoubleParam(int index)
{
	return lua_tonumber(mThreadState, index);
}

//--------------------------------------------------------------------------------
LUA_INTEGER MLScriptMgr::GetFuncIntParam(int index)
{
	return lua_tointeger(mThreadState, index);
}

//--------------------------------------------------------------------------------
bool MLScriptMgr::GetFuncBoolParam(int index)
{
	return lua_toboolean(mThreadState, index) ? true : false;
}

//--------------------------------------------------------------------------------
MLINT MLScriptMgr::LoadBuffer(const char *chunk, int chunkSize, const char *chunkName)
{
    MLINT r = 0;
    
    if (_xxteaEnabled && strncmp(chunk, _xxteaSign, _xxteaSignLen) == 0)
    {
        // decrypt XXTEA
        xxtea_long len = 0;
        unsigned char* result = xxtea_decrypt((unsigned char*)chunk + _xxteaSignLen,
                                              (xxtea_long)chunkSize - _xxteaSignLen,
                                              (unsigned char*)_xxteaKey,
                                              (xxtea_long)_xxteaKeyLen,
                                              &len);
        r = luaL_loadbuffer(mThreadState, (char*)result, len, chunkName);
        free(result);
    }
    else
    {
        r = luaL_loadbuffer(mThreadState, chunk, chunkSize, chunkName);
    }
    
#if defined(COCOS2D_DEBUG) && COCOS2D_DEBUG > 0
    if (r)
    {
        switch (r)
        {
            case LUA_ERRSYNTAX:
                CCLOG("[LUA ERROR] load \"%s\", error: syntax error during pre-compilation.", chunkName);
                break;
                
            case LUA_ERRMEM:
                CCLOG("[LUA ERROR] load \"%s\", error: memory allocation error.", chunkName);
                break;
                
            case LUA_ERRFILE:
                CCLOG("[LUA ERROR] load \"%s\", error: cannot open/read file.", chunkName);
                break;
                
            default:
                CCLOG("[LUA ERROR] load \"%s\", error: unknown.", chunkName);
        }
    }
#endif
    return r;
}

//--------------------------------------------------------------------------------
void MLScriptMgr::SetXXTEAKeyAndSign(const char *key, int keyLen, const char *sign, int signLen)
{
    CleanupXXTEAKeyAndSign();
    
    if (key && keyLen && sign && signLen)
    {
        _xxteaKey = (char*)malloc(keyLen);
        memcpy(_xxteaKey, key, keyLen);
        _xxteaKeyLen = keyLen;
        
        _xxteaSign = (char*)malloc(signLen);
        memcpy(_xxteaSign, sign, signLen);
        _xxteaSignLen = signLen;
        
        _xxteaEnabled = true;
    }
    else
    {
        _xxteaEnabled = false;
    }
}

//--------------------------------------------------------------------------------
void MLScriptMgr::CleanupXXTEAKeyAndSign()
{
    if (_xxteaKey)
    {
        free(_xxteaKey);
        _xxteaKey = nullptr;
        _xxteaKeyLen = 0;
    }
    if (_xxteaSign)
    {
        free(_xxteaSign);
        _xxteaSign = nullptr;
        _xxteaSignLen = 0;
    }
}
