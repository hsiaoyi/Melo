#include "MLIapManagerJni.h"

#ifdef ML_NATIVE_IAP_SUPPORT

#include "jni/JniHelper.h"
#include <string.h>

#define kIapAndroidStore "come/hsiaoyi/melo/store/MLIapAndroidManager"

extern "C"
{
    jobject initIapManagerJni(void) {
        JniMethodInfo t;
        jobject instance = NULL;

        if (JniHelper::getMethodInfo(t, kIapAndroidStore, "<init>", "()V")) {
            jobject obj = t.env->NewObject(t.classID, t.methodID);
            instance = t.env->NewGlobalRef(obj);

            t.env->DeleteLocalRef(t.classID);
        }

        return instance;
    }

    void setupIapManagerJni(jobject obj, std::string publicKey) {
        JniMethodInfo t;
        if (JniHelper::getMethodInfo(t, kIapAndroidStore, "setupIapManager", "(Ljava/lang/String;)V")) {
            jstring jPublicKey = t.env->NewStringUTF(publicKey.c_str());
            t.env->CallVoidMethod(obj, t.methodID, jPublicKey);

            t.env->DeleteLocalRef(jPublicKey);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    void requestProductsJni(jobject obj, std::vector<std::string> productIdentifiers) {

        JniMethodInfo t;
        if (JniHelper::getMethodInfo(t, kIapAndroidStore, "getProductsList", "([Ljava/lang/String;)V")) {
            jobjectArray jProductIds = t.env->NewObjectArray(productIdentifiers.size(), t.env->FindClass("java/lang/String"), NULL);
            for (int i = 0; i < productIdentifiers.size(); i++) {
                t.env->SetObjectArrayElement(jProductIds, i, t.env->NewStringUTF(productIdentifiers[i].c_str()));
            }

            t.env->CallVoidMethod(obj, t.methodID, jProductIds);

            t.env->DeleteLocalRef(jProductIds);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    void purchaseProductJni(jobject obj, std::string productIdentifier) {
        JniMethodInfo t;
        if (JniHelper::getMethodInfo(t, kIapAndroidStore, "purchaseProduct", "(Ljava/lang/String;)V")) {
            jstring jProductId = t.env->NewStringUTF(productIdentifier.c_str());
            t.env->CallVoidMethod(obj, t.methodID, jProductId);

            t.env->DeleteLocalRef(jProductId);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    void consumeProductJni(jobject obj, std::string itemType, std::string jsonReceiptInfo, std::string signature) {
        JniMethodInfo t;
        if (JniHelper::getMethodInfo(t, kIapAndroidStore, "consumeProduct", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
            jstring jItemType = t.env->NewStringUTF(itemType.c_str());
            jstring jJsonReceiptInfo = t.env->NewStringUTF(jsonReceiptInfo.c_str());
            jstring jSignature = t.env->NewStringUTF(signature.c_str());
            t.env->CallVoidMethod(obj, t.methodID, jItemType, jJsonReceiptInfo, jSignature);

            t.env->DeleteLocalRef(jItemType);
            t.env->DeleteLocalRef(jJsonReceiptInfo);
            t.env->DeleteLocalRef(jSignature);
            t.env->DeleteLocalRef(t.classID);
        }
    }
}

#endif