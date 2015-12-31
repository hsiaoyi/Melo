//--------------------------------------------------------------------------------
//	File		: MLUtility.mm
//	Description	:
//	Author		: Su, Hsin-Chnag
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#import "UICKeyChainStore.h"
#import <sys/sysctl.h>
#import <UIKit/UIKit.h>
#import <AdSupport/ASIdentifierManager.h>
#import <CommonCrypto/CommonDigest.h>

#include "MLUtility.h"

const std::string MLUtility::getUDIDForVendor(const std::string path, const std::string secretKey)
{
    return [[[[UIDevice currentDevice] identifierForVendor] UUIDString] UTF8String];
}

const std::string MLUtility::getPlatform()
{
    return "iOS";
}

const std::string MLUtility::getDevice()
{
    return [[[UIDevice currentDevice] model] UTF8String];
}

const std::string MLUtility::getDeviceName()
{
    size_t size;
    sysctlbyname("hw.machine", NULL, &size, NULL, 0);
    char *machine = (char *)malloc(size);
    sysctlbyname("hw.machine", machine, &size, NULL, 0);
    NSString* deviceName = [NSString stringWithCString:machine encoding:NSUTF8StringEncoding];
    free(machine);
    return [deviceName UTF8String];
}

const std::string MLUtility::getOSVersion()
{
    return [[[UIDevice currentDevice] systemVersion] UTF8String];
}

const std::string MLUtility::getAppVersionName()
{
    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
    return [[infoDictionary objectForKey:@"CFBundleShortVersionString"] UTF8String];
}

const std::string MLUtility::getAppVersionCode()
{
    NSDictionary *infoDictionary = [[NSBundle mainBundle] infoDictionary];
    return [[infoDictionary objectForKey:@"CFBundleVersion"] UTF8String];
}

const std::string MLUtility::getCountryCode()
{
    return [[[NSLocale currentLocale] objectForKey:NSLocaleCountryCode] UTF8String];
}

const std::string MLUtility::getCurrencyCode()
{
    return [[[NSLocale currentLocale] objectForKey:NSLocaleCurrencyCode] UTF8String];
}

const std::string MLUtility::getAdvertisementID()
{
    if([[ASIdentifierManager sharedManager] isAdvertisingTrackingEnabled])
    {
        NSUUID *IDFA = [[ASIdentifierManager sharedManager] advertisingIdentifier];
        return [[IDFA UUIDString] UTF8String];
    }

    return "";
}

const std::string MLUtility::getCertCode()
{
    unsigned int iSecretKey = 110;
    
    NSDate *currentDate = [[NSDate alloc] init];
    NSDateFormatter *dateYMD = [[NSDateFormatter alloc] init];
    [dateYMD setDateFormat:@"yyyyMMdd"];
    NSString *strYMD = [dateYMD stringFromDate:currentDate];
    unsigned int iYMD = [strYMD intValue];

    NSDateFormatter *dateDay = [[NSDateFormatter alloc] init];
    [dateDay setDateFormat:@"dd"];
    NSString *strDay = [dateDay stringFromDate:currentDate];
    unsigned int iDay = [strDay intValue];
    
    NSDateFormatter *dateHour = [[NSDateFormatter alloc] init];
    [dateHour setDateFormat:@"HH"];
    NSString *strHour = [dateHour stringFromDate:currentDate];
    unsigned int iHour = [strHour intValue];
    
    NSDateFormatter *dateMinute = [[NSDateFormatter alloc] init];
    [dateMinute setDateFormat:@"mm"];
    NSString *strMinute = [dateMinute stringFromDate:currentDate];
    unsigned int iMinute = [strMinute intValue];

    std::string udidStr = MLUtility::getUDIDForVendor("", "");
    unsigned int udid = std::stoi(udidStr);
        
    long shaNumber = 1688 * (udid * iDay + iSecretKey * iYMD + iSecretKey * (int)(iMinute / 10) + iHour);
    std::stringstream ss;
    ss << shaNumber;
    std::string shaStr = getSha1( ss.str() );
    if ( shaStr.length() > 0 )
    {
        return shaStr;
    }
    
    return "9999";
}

const std::string MLUtility::getCertKey(const std::string &rndCode)
{
   
    NSDate *currentDate = [[NSDate alloc] init];
    
    NSDateFormatter *dateDay = [[NSDateFormatter alloc] init];
    [dateDay setDateFormat:@"dd"];
    NSString *strDay = [dateDay stringFromDate:currentDate];
    unsigned int iDay = [strDay intValue];
    
    NSDateFormatter *dateHour = [[NSDateFormatter alloc] init];
    [dateHour setDateFormat:@"HH"];
    NSString *strHour = [dateHour stringFromDate:currentDate];
    unsigned int iHour = [strHour intValue];
    
    NSDateFormatter *dateMinute = [[NSDateFormatter alloc] init];
    [dateMinute setDateFormat:@"mm"];
    NSString *strMinute = [dateMinute stringFromDate:currentDate];
    unsigned int iMinute = [strMinute intValue];
    
    std::string udidStr = MLUtility::getUDIDForVendor("", "");
    unsigned int udid = 1234;//std::stoi(udidStr);
    
    unsigned int iRndCode = std::stoi( rndCode );
    long shaNumber = iRndCode * (iHour + (iHour + (int)(iMinute / 10) + 25) + iDay * (int)(iMinute / 10) + udid );
    std::stringstream ss;
    ss << shaNumber;
    std::string shaStr = getSha1( ss.str() );
    if ( shaStr.length() > 0 )
    {
        return shaStr;
    }
    
    return "8888";
}

const std::string MLUtility::getSha1(const std::string src, unsigned int digestLength)
{
    unsigned int uiShaDidgistLength = CC_SHA1_DIGEST_LENGTH;
    if (digestLength == 256 || digestLength == 32)
    {
        uiShaDidgistLength = CC_SHA256_DIGEST_LENGTH;
    }
    else if (digestLength == 384 || digestLength == 48)
    {
        uiShaDidgistLength = CC_SHA384_DIGEST_LENGTH;
    }
    else if (digestLength == 512 || digestLength == 64)
    {
        uiShaDidgistLength = CC_SHA512_DIGEST_LENGTH;
    }

    unsigned int uiShaBlockSize = CC_SHA1_BLOCK_BYTES;
    if (digestLength == 256 || digestLength == 32)
    {
        uiShaBlockSize = CC_SHA256_BLOCK_BYTES;
    }
    else if (digestLength == 384 || digestLength == 48)
    {
        uiShaBlockSize = CC_SHA384_BLOCK_BYTES;
    }
    else if (digestLength == 512 || digestLength == 64)
    {
        uiShaBlockSize = CC_SHA512_BLOCK_BYTES;
    }
    
    NSString* str = [NSString stringWithCString:src.c_str() encoding:NSUTF8StringEncoding];
    NSData *data = [str dataUsingEncoding:NSUTF8StringEncoding];
    uint8_t digest[uiShaDidgistLength];
    
    CC_SHA256(data.bytes, data.length, digest);
    if (digestLength == 256)
    {
        CC_SHA256(data.bytes, data.length, digest);
    }
    else if (digestLength == 384)
    {
        CC_SHA384(data.bytes, data.length, digest);
    }
    else if (digestLength == 512)
    {
        CC_SHA512(data.bytes, data.length, digest);
    }
    else
    {
        CC_SHA1(data.bytes, data.length, digest);
    }
    
    NSMutableString *output = [NSMutableString stringWithCapacity:uiShaBlockSize];
    for (int i = 0; i < uiShaDidgistLength; i++)
    {
        [output appendFormat:@"%02x", digest[i]];
    }
    
    return [output UTF8String];
}

const std::string MLUtility::getApplicationRoot()
{
    // /var/mobile/Applications/~UDID~/xxx.app
    return [[[NSBundle mainBundle] bundlePath] UTF8String];
}

const std::string MLUtility::getResource()
{
    // /var/mobile/Applications/~UDID~/xxx.app/
    NSString *path = [[[NSBundle mainBundle] bundlePath] stringByAppendingString:@"/"];
    return [path UTF8String];
}

const std::string MLUtility::getDocuments()
{
    // /var/mobile/Applications/~UDID~/xxx.app/Documents
    NSArray* p = NSSearchPathForDirectoriesInDomains( NSDocumentDirectory, NSUserDomainMask, YES );
    NSString* path = [[p objectAtIndex:0] stringByAppendingString:@"/"];
    return [path UTF8String];
}

const std::string MLUtility::getTemp()
{
    // /var/mobile/Applications/~UDID~/xxx.app/Temp/
    NSString *path = [[[NSBundle mainBundle] bundlePath] stringByAppendingString:@"/Temp/"];
    return [path UTF8String];
}

NSString* getKey(const std::string& path)
{
    return [NSString stringWithFormat:@"%@.identifier", [[NSBundle mainBundle] bundleIdentifier]];
}

string MLUtility::getIdentifier(const std::string& path, const std::string& secretKey)
{
    NSString *keyStr = [UICKeyChainStore stringForKey:getKey(path)];
    if (keyStr == nil)
    {
        return "";
    }
    return [keyStr UTF8String];
}

bool MLUtility::setIdentifier(const std::string& path, const std::string& identifier, const std::string& secretKey)
{
    NSString* dataStr = [NSString stringWithCString:identifier.c_str() encoding:NSUTF8StringEncoding];
    return [UICKeyChainStore setString:dataStr forKey:getKey(path)] ? true : false;
}

bool MLUtility::deleteIdentifier(const std::string& path)
{
    return [UICKeyChainStore removeItemForKey:getKey(path)] ? true : false;
}

bool MLUtility::hasIdentifier(const std::string& path)
{
    return ([UICKeyChainStore stringForKey:getKey(path)] == nil) ? false : true;
}
