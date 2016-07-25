//--------------------------------------------------------------------------------
//	File		: MLUtility.h
//	Description	: 
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#ifndef __ML_UTILITY_H__
#define __ML_UTILITY_H__

#include "Melo.h"

class MLUtility
{
public:
    // Device Info
    static const std::string getUDIDForVendor(const std::string path, const std::string secretKey);
    static const std::string getPlatform();
    static const std::string getDevice();
    static const std::string getDeviceName();
    static const std::string getOSVersion();
    static const std::string getAppVersionName();
    static const std::string getAppVersionCode();
    static const std::string getCountryCode();
    static const std::string getCurrencyCode();
    static const std::string getAdvertisementID();
    static const std::string getCertCode();
    static const std::string getSha1(const std::string src, unsigned int digestLength = 20);
    static unsigned int getRndCode();
    static void setRndCode(unsigned int rndCode);
    
    // Path
    static const std::string getApplicationRoot();
    static const std::string getResource();
    static const std::string getDocuments();
    static const std::string getTemp();
    
    // Identifier
    static std::string getIdentifier(const std::string& path, const std::string& secretKey);
    static bool setIdentifier(const std::string& path, const std::string& identifier, const std::string& secretKey);
    static bool deleteIdentifier(const std::string& path);
    static bool hasIdentifier(const std::string& path);
    
private :
    static unsigned int mRndCode;
};

#endif	// __ML_UTILITY_H__
