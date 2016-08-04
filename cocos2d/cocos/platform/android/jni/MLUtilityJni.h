#ifndef __MLDeviceUtilJni__
#define __MLDeviceUtilJni__

#include <string>

extern "C"
{
    const std::string getUDIDForVendorJni(const std::string path, const std::string secretKey);
    const std::string getDeviceJni();
    const std::string getDeviceNameJni();
    const std::string getOSVersionJni();
    const std::string getAppVersionNameJni();
    const std::string getAppVersionCodeJni();
    const std::string getCountryCodeJni();
    const std::string getCurrencyCodeJni();
    const std::string getAdvertisementIDJni();

    std::string getIdentifierJni(const std::string& path, const std::string& secretKey);
    bool setIdentifierJni(const std::string& path, const std::string& identifier, const std::string& secretKey);
    bool deleteIdentifierJni(const std::string& path);
    bool hasIdentifierJni(const std::string& path);

    const std::string getCertCodeJni();
    const std::string getSha1Jni(const std::string& rndCode, unsigned int digestLength);
}

#endif // __MLDeviceUtilJni__
