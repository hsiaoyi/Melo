//--------------------------------------------------------------------------------
//	File		: MLUtility.cpp
//	Description	:
//	Author		: Su, Hsin-Chnag
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#if defined(ML_ANDROID)

#include "MLUtility.h"
#include "MLUtilityJni.h"

const std::string MLDeviceUtil::getUDIDForVendor(const std::string path, const std::string secretKey)
{
    return getUDIDForVendorJni(path, secretKey);
}

const std::string MLDeviceUtil::getPlatform()
{
    return "android";
}

const std::string MLDeviceUtil::getDevice()
{
    return getDeviceJni();
}

const std::string MLDeviceUtil::getDeviceName()
{
    return getDeviceNameJni();
}

const std::string MLDeviceUtil::getOSVersion()
{
    return getOSVersionJni();
}

const std::string MLDeviceUtil::getAppVersionName()
{
    return getAppVersionNameJni();
}

const std::string MLDeviceUtil::getAppVersionCode()
{
    return getAppVersionCodeJni();
}

const std::string MLDeviceUtil::getCountryCode()
{
    return getCountryCodeJni();
}

const std::string MLDeviceUtil::getCurrencyCode()
{
    return getCurrencyCodeJni();
}

const std::string MLDeviceUtil::getAdvertisementID()
{
    return getAdvertisementIDJni();
}

///////////////////////////////////////////////////////////////////////////////
const std::string MLDeviceUtil::getApplicationRoot()
{
    return "";
}

const std::string MLDeviceUtil::getResource()
{
    return "";
}

const std::string MLDeviceUtil::getDocuments()
{
    return "/Documents/";
}

const std::string MLDeviceUtil::getTemp()
{
    return "/Temp/";
}

///////////////////////////////////////////////////////////////////////////////
std::string MLDeviceUtil::getIdentifier(const std::string& path, const std::string& secretKey)
{
    return getIdentifierJni(path, secretKey);
}

bool MLDeviceUtil::setIdentifier(const std::string& path, const std::string& identifier, const std::string& secretKey)
{
    return setIdentifierJni(path, identifier, secretKey);
}

bool MLDeviceUtil::deleteIdentifier(const std::string& path)
{
    return deleteIdentifierJni(path);
}

bool MLDeviceUtil::hasIdentifier(const std::string& path)
{
    return hasIdentifierJni(path);
}

///////////////////////////////////////////////////////////////////////////////
const std::string MLDeviceUtil::getCertKey(const std::string &rndCode)
{
    return getCertKeyJni(path);
}

const std::string MLDeviceUtil::getSha1(const std::string src, unsigned int digestLength)
{
    return getSha1Jni(src);
}

#endif