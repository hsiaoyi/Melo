#include "MLUtilityJni.h"

#include "jni/JniHelper.h"
#include <jni.h>

#define kMLUtility "com/hsiaoyi/melo/MLUtility"

using namespace cocos2d;

extern "C"
{
    const std::string getUDIDForVendorJni(const std::string path, const std::string secretKey) {
        JniMethodInfo t;
        std::string ret;

        if (JniHelper::getStaticMethodInfo(t, kMLUtility, "getUDIDForVendor", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;")) {
            jstring jPath = t.env->NewStringUTF(path.c_str());
            jstring jSecretKey = t.env->NewStringUTF(secretKey.c_str());

            jstring jRet = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, jPath, jSecretKey);
            const char* str = NULL;
            if (jRet != NULL) {
                str = t.env->GetStringUTFChars(jRet, 0);
                ret = str;
                t.env->ReleaseStringUTFChars(jRet, str);
            }

            t.env->DeleteLocalRef(jPath);
            t.env->DeleteLocalRef(jSecretKey);
            t.env->DeleteLocalRef(t.classID);
        }

        return ret;
    }
    const std::string getDeviceJni() {
        JniMethodInfo t;
        std::string ret;

        if (JniHelper::getStaticMethodInfo(t, kMLUtility, "getDevice", "()Ljava/lang/String;")) {
            jstring jRet = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            const char* str = NULL;
            if (jRet != NULL) {
                str = t.env->GetStringUTFChars(jRet, 0);
                ret = str;
            }
            t.env->ReleaseStringUTFChars(jRet, str);
            t.env->DeleteLocalRef(t.classID);
        }

        return ret;
    }

    const std::string getDeviceNameJni() {
        JniMethodInfo t;
        std::string ret;

        if (JniHelper::getStaticMethodInfo(t, kMLUtility, "getDeviceName", "()Ljava/lang/String;")) {
            jstring jRet = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            const char* str = NULL;
            if (jRet != NULL) {
                str = t.env->GetStringUTFChars(jRet, 0);
                ret = str;
            }
            t.env->ReleaseStringUTFChars(jRet, str);
            t.env->DeleteLocalRef(t.classID);
        }

        return ret;
    }

    const std::string getOSVersionJni() {
        JniMethodInfo t;
        std::string ret;

        if (JniHelper::getStaticMethodInfo(t, kMLUtility, "getOSVersion", "()Ljava/lang/String;")) {
            jstring jRet = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            const char* str = NULL;
            if (jRet != NULL) {
                str = t.env->GetStringUTFChars(jRet, 0);
                ret = str;
            }
            t.env->ReleaseStringUTFChars(jRet, str);
            t.env->DeleteLocalRef(t.classID);
        }

        return ret;
    }

    const std::string getAppVersionNameJni() {
        JniMethodInfo t;
        std::string ret;

        if (JniHelper::getStaticMethodInfo(t, kMLUtility, "getAppVersionName", "()Ljava/lang/String;")) {
            jstring jRet = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            const char* str = NULL;
            if (jRet != NULL) {
                str = t.env->GetStringUTFChars(jRet, 0);
                ret = str;
            }
            t.env->ReleaseStringUTFChars(jRet, str);
            t.env->DeleteLocalRef(t.classID);
        }

        return ret;
    }

    const std::string getAppVersionCodeJni() {
        JniMethodInfo t;
        std::string ret;

        if (JniHelper::getStaticMethodInfo(t, kMLUtility, "getAppVersionCode", "()Ljava/lang/String;")) {
            jstring jRet = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            const char* str = NULL;
            if (jRet != NULL) {
                str = t.env->GetStringUTFChars(jRet, 0);
                ret = str;
            }
            t.env->ReleaseStringUTFChars(jRet, str);
            t.env->DeleteLocalRef(t.classID);
        }

        return ret;
    }

    const std::string getCountryCodeJni() {
        JniMethodInfo t;
        std::string ret;

        if (JniHelper::getStaticMethodInfo(t, kMLUtility, "getCountryCode", "()Ljava/lang/String;")) {
            jstring jRet = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            const char* str = NULL;
            if (jRet != NULL) {
                str = t.env->GetStringUTFChars(jRet, 0);
                ret = str;
            }
            t.env->ReleaseStringUTFChars(jRet, str);
            t.env->DeleteLocalRef(t.classID);
        }

        return ret;
    }

    const std::string getCurrencyCodeJni() {
        JniMethodInfo t;
        std::string ret;

        if (JniHelper::getStaticMethodInfo(t, kMLUtility, "getCurrencyCode", "()Ljava/lang/String;")) {
            jstring jRet = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            const char* str = NULL;
            if (jRet != NULL) {
                str = t.env->GetStringUTFChars(jRet, 0);
                ret = str;
            }
            t.env->ReleaseStringUTFChars(jRet, str);
            t.env->DeleteLocalRef(t.classID);
        }

        return ret;
    }

    const std::string getAdvertisementIDJni() {
        JniMethodInfo t;
        std::string ret;

        if (JniHelper::getStaticMethodInfo(t, kMLUtility, "getAdvertisementID", "()Ljava/lang/String;")) {
            jstring jRet = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            const char* str = NULL;
            if (jRet != NULL) {
                str = t.env->GetStringUTFChars(jRet, 0);
                ret = str;
            }
            t.env->ReleaseStringUTFChars(jRet, str);
            t.env->DeleteLocalRef(t.classID);
        }

        return ret;
    }

    std::string getIdentifierJni(const std::string& path, const std::string& secretKey) {
        JniMethodInfo t;
        std::string ret;

        if (JniHelper::getStaticMethodInfo(t, kMLUtility, "getIdentifier", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;")) {
            jstring jPath = t.env->NewStringUTF(path.c_str());
            jstring jSecretKey = t.env->NewStringUTF(secretKey.c_str());

            jstring jRet = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, jPath, jSecretKey);
            const char* str = NULL;
            if (jRet != NULL) {
                str = t.env->GetStringUTFChars(jRet, 0);
                ret = str;
            }

            t.env->ReleaseStringUTFChars(jRet, str);

            t.env->DeleteLocalRef(jPath);
            t.env->DeleteLocalRef(jSecretKey);
            t.env->DeleteLocalRef(t.classID);
        }

        return ret;
    }

    bool setIdentifierJni(const std::string& path, const std::string& identifier, const std::string& secretKey) {
        JniMethodInfo t;
        bool ret;

        if (JniHelper::getStaticMethodInfo(t, kMLUtility, "setIdentifier", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z")) {
            jstring jPath = t.env->NewStringUTF(path.c_str());
            jstring jIdentifier = t.env->NewStringUTF(identifier.c_str());
            jstring jSecretKey = t.env->NewStringUTF(secretKey.c_str());

            ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, jPath, jIdentifier, jSecretKey);

            t.env->DeleteLocalRef(jPath);
            t.env->DeleteLocalRef(jIdentifier);
            t.env->DeleteLocalRef(jSecretKey);
            t.env->DeleteLocalRef(t.classID);
        }

        return ret;
    }

    bool deleteIdentifierJni(const std::string& path) {
        JniMethodInfo t;
        bool ret;

        if (JniHelper::getStaticMethodInfo(t, kMLUtility, "deleteIdentifier", "(Ljava/lang/String;)Z")) {
            jstring jPath = t.env->NewStringUTF(path.c_str());

            ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, jPath);

            t.env->DeleteLocalRef(jPath);
            t.env->DeleteLocalRef(t.classID);
        }

        return ret;
    }

    bool hasIdentifierJni(const std::string& path) {
        JniMethodInfo t;
        bool ret;

        if (JniHelper::getStaticMethodInfo(t, kMLUtility, "hasIdentifier", "(Ljava/lang/String;)Z")) {
            jstring jPath = t.env->NewStringUTF(path.c_str());

            ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, jPath);

            t.env->DeleteLocalRef(jPath);
            t.env->DeleteLocalRef(t.classID);
        }

        return ret;
    }

    const std::string getCertCodeJni() {
        JniMethodInfo t;
        std::string ret;

        if (JniHelper::getStaticMethodInfo(t, kMLUtility, "getCertCode", "()Ljava/lang/String;")) {
            jstring jRet = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            const char* str = NULL;
            if (jRet != NULL) {
                str = t.env->GetStringUTFChars(jRet, 0);
                ret = str;
            }

            t.env->ReleaseStringUTFChars(jRet, str);
            t.env->DeleteLocalRef(t.classID);
        }

        return ret;
    }

    const std::string getSha1Jni(const std::string& rndCode, unsigned int digestLength) {
        JniMethodInfo t;
        std::string ret;

        if (JniHelper::getStaticMethodInfo(t, kMLUtility, "getSha1", "(Ljava/lang/String;Ljava/lang/String;I)Ljava/lang/String;")) {
            jstring jRndCode = t.env->NewStringUTF(rndCode.c_str());

            jstring jRet = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, jRndCode, digestLength);
            const char* str = NULL;
            if (jRet != NULL) {
                str = t.env->GetStringUTFChars(jRet, 0);
                ret = str;
            }

            t.env->ReleaseStringUTFChars(jRet, str);

            t.env->DeleteLocalRef(jRndCode);
            t.env->DeleteLocalRef(t.classID);
        }

        return ret;
    }
}

