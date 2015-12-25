//--------------------------------------------------------------------------------
//	File		: MLUtility.mm
//	Description	:
//	Author		: Su, Hsin-Chnag
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#include "MLUtility.h"
#include "UICKeyChainStore.h"
#include <sys/sysctl.h>
#import <AdSupport/ASIdentifierManager.h>
#import <UIKit/UIKit.h>

using namespace std;

const std::string MLDeviceUtil::getUDIDForVendor(const std::string path, const std::string secretKey)
{
    return [[[[UIDevice currentDevice] identifierForVendor] UUIDString] UTF8String];
}

const std::string MLDeviceUtil::getPlatform()
{
    return "iOS";
}

const std::string MLDeviceUtil::getDevice()
{
    return [[[UIDevice currentDevice] model] UTF8String];
}

const std::string MLDeviceUtil::getDeviceName()
{
    size_t size;
    sysctlbyname("hw.machine", NULL, &size, NULL, 0);
    char *machine = (char *)malloc(size);
    sysctlbyname("hw.machine", machine, &size, NULL, 0);
    NSString* deviceName = [NSString stringWithCString:machine encoding:NSUTF8StringEncoding];
    free(machine);
    return [deviceName UTF8String];
}

const std::string MLDeviceUtil::getOSVersion()
{
    return [[[UIDevice currentDevice] systemVersion] UTF8String];
}

const std::string MLDeviceUtil::getAppVersionName()
{
    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
    return [[infoDictionary objectForKey:@"CFBundleShortVersionString"] UTF8String];
}

const std::string MLDeviceUtil::getAppVersionCode()
{
    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
    return [[infoDictionary objectForKey:@"CFBundleVersion"] UTF8String];
}

const std::string MLDeviceUtil::getCountryCode()
{
    return [[[NSLocale currentLocale] objectForKey:NSLocaleCountryCode] UTF8String];
}

const std::string MLDeviceUtil::getCurrencyCode()
{
    return [[[NSLocale currentLocale] objectForKey:NSLocaleCurrencyCode] UTF8String];
}

const std::string MLDeviceUtil::getAdvertisementID()
{
    if([[ASIdentifierManager sharedManager] isAdvertisingTrackingEnabled])
    {
        NSUUID *IDFA = [[ASIdentifierManager sharedManager] advertisingIdentifier];
        return [[IDFA UUIDString] UTF8String];
    }

    return "";
}

const std::string MLDeviceUtil::getApplicationRoot()
{
    // /var/mobile/Applications/~UDID~/xxx.app
    return [[[NSBundle mainBundle] bundlePath] UTF8String];
}

const std::string MLDeviceUtil::getResource()
{
    // /var/mobile/Applications/~UDID~/xxx.app/
    NSString *path = [[[NSBundle mainBundle] bundlePath] stringByAppendingString:@"/"];
    return [path UTF8String];
}

const std::string MLDeviceUtil::getDocuments()
{
    // /var/mobile/Applications/~UDID~/xxx.app/Documents
    NSArray* p = NSSearchPathForDirectoriesInDomains( NSDocumentDirectory, NSUserDomainMask, YES );
    NSString* path = [[p objectAtIndex:0] stringByAppendingString:@"/"];
    return [path UTF8String];
}

const std::string MLDeviceUtil::getTemp()
{
    // /var/mobile/Applications/~UDID~/xxx.app/Temp/
    NSString *path = [[[NSBundle mainBundle] bundlePath] stringByAppendingString:@"/Temp/"];
    return [path UTF8String];
}

NSString* getKey(const std::string& path)
{
    return [NSString stringWithFormat:@"%@.identifier", [[NSBundle mainBundle] bundleIdentifier]];
}

string MLDeviceUtil::getIdentifier(const std::string& path, const std::string& secretKey)
{
    NSString *keyStr = [UICKeyChainStore stringForKey:getKey(path)];
    if (keyStr == nil)
    {
        return "";
    }
    return [keyStr UTF8String];
}

bool MLDeviceUtil::setIdentifier(const std::string& path, const std::string& identifier, const std::string& secretKey)
{
    NSString* dataStr = [NSString stringWithCString:identifier.c_str() encoding:NSUTF8StringEncoding];
    return [UICKeyChainStore setString:dataStr forKey:getKey(path)] ? true : false;
}

bool MLDeviceUtil::deleteIdentifier(const std::string& path)
{
    return [UICKeyChainStore removeItemForKey:getKey(path)] ? true : false;
}

bool MLDeviceUtil::hasIdentifier(const std::string& path)
{
    return ([UICKeyChainStore stringForKey:getKey(path)] == nil) ? false : true;
}
