//--------------------------------------------------------------------------------
//	File		: MLUtility_win32.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#include "MLUtility.h"
#include "MLScriptMgr.h"

#if defined(ML_WIN32)
//--------------------------------------------------------------------------------
const std::string MLUtility::getUDIDForVendor(const std::string path, const std::string secretKey)
{
	if (!MLScriptMgr::GetInstance()->LoadFile(FileUtils::getInstance()->fullPathForFilename("sicfg.lua").c_str()))
	{
		MLScriptMgr::GetInstance()->Resume();
		/*
		int w = 0;
		int h = 0;
		MLScriptMgr::GetInstance()->GetNumber("WindowWidth", w);
		MLScriptMgr::GetInstance()->GetNumber("WindowHeight", h);

		char str[15];
		MLScriptMgr::GetInstance()->GetString("WindowName", str);
		*/
		char guidstr[15];
		MLScriptMgr::GetInstance()->GetString("Win32Guid", guidstr);

		std::string guid = string(guidstr);

		return guid;
	}
	else
	{
		return "";
	}
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getPlatform()
{
    return "Win32";
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getDevice()
{
    return "editor";
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getDeviceName()
{
    return "editor";
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getOSVersion()
{
    return "";
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getAppVersionName()
{
    return "";
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getAppVersionCode()
{
    return "";
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getCountryCode()
{
    return "TW";
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getCurrencyCode()
{
    return "";
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getAdvertisementID()
{
    return "";
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getApplicationRoot()
{
    return "";
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getResource()
{
    return "";
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getDocuments()
{
    return "/Documents/";
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getTemp()
{
    return "/Temp/";
}

//--------------------------------------------------------------------------------
std::string MLUtility::getIdentifier(const std::string& path, const std::string& secretKey)
{
    //return getIdentifierJni(path, secretKey);
	return "";
}

//--------------------------------------------------------------------------------
bool MLUtility::setIdentifier(const std::string& path, const std::string& identifier, const std::string& secretKey)
{
    //return setIdentifierJni(path, identifier, secretKey);
	return true;
}

//--------------------------------------------------------------------------------
bool MLUtility::deleteIdentifier(const std::string& path)
{
    //return deleteIdentifierJni(path);
	return true;
}

//--------------------------------------------------------------------------------
bool MLUtility::hasIdentifier(const std::string& path)
{
    //return hasIdentifierJni(path);
	return true;
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getCertKey(const std::string &rndCode)
{
    //return getCertKeyJni(rndCode);
	return "";
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getSha1(const std::string src, unsigned int digestLength)
{
    //return getSha1Jni(src, digestLength);
	return "";
}

#endif//(ML_WIN32)