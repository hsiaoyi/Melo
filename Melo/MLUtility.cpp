//--------------------------------------------------------------------------------
//	File		: MLUtility.cpp
//	Description	:
//	Author		: Su, Hsin-Chnag
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#include "MLUtility.h"

#if defined(ML_ANDROID)
#include "MLUtilityJni.h"

unsigned int MLUtility::mRndCode = 0;

//--------------------------------------------------------------------------------
const std::string MLUtility::getUDIDForVendor(const std::string path, const std::string secretKey)
{
    return getUDIDForVendorJni(path, secretKey);
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getPlatform()
{
    return "android";
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getDevice()
{
    return getDeviceJni();
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getDeviceName()
{
    return getDeviceNameJni();
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getOSVersion()
{
    return getOSVersionJni();
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getAppVersionName()
{
    return getAppVersionNameJni();
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getAppVersionCode()
{
    return getAppVersionCodeJni();
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getCountryCode()
{
    return getCountryCodeJni();
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getCurrencyCode()
{
    return getCurrencyCodeJni();
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getAdvertisementID()
{
    return getAdvertisementIDJni();
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
    return getIdentifierJni(path, secretKey);
}

//--------------------------------------------------------------------------------
bool MLUtility::setIdentifier(const std::string& path, const std::string& identifier, const std::string& secretKey)
{
    return setIdentifierJni(path, identifier, secretKey);
}

//--------------------------------------------------------------------------------
bool MLUtility::deleteIdentifier(const std::string& path)
{
    return deleteIdentifierJni(path);
}

//--------------------------------------------------------------------------------
bool MLUtility::hasIdentifier(const std::string& path)
{
    return hasIdentifierJni(path);
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getCertCode(int rndCode, const std::string secretKey)
{
    return getCertCodeJni(rndCode, secretKey);
}

//--------------------------------------------------------------------------------
const std::string MLUtility::getSha1(const std::string src, unsigned int digestLength)
{
    return getSha1Jni(src, digestLength);
}

//--------------------------------------------------------------------------------
void MLUtility::setRndCode(unsigned int rndCode)
{
    mRndCode = rndCode;
}

//--------------------------------------------------------------------------------
unsigned int MLUtility::getRndCode()
{
    return mRndCode;
}

#endif//(ML_ANDROID)