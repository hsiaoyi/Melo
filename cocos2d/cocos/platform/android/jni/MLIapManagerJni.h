#ifndef __ML_Iap_Manager_Jni__
#define __ML_Iap_Manager_Jni__

#ifdef ML_NATIVE_IAP_SUPPORT

#include <jni.h>
#include <string>
#include <vector>

extern "C"
{
    jobject initIapManagerJni(void);

    void setupIapManagerJni(jobject obj, std::string publicKey);
    void requestProductsJni(jobject obj, std::vector<std::string> productIdentifiers);
    void purchaseProductJni(jobject obj, std::string productIdentifier);
    void consumeProductJni(jobject obj, std::string itemType, std::string jsonReceiptInfo, std::string signature);
}

#endif

#endif // __ML_Iap_Manager_Jni__
