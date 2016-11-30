#include "MLIapManager.h"

#ifdef ML_NATIVE_IAP_SUPPORT

#include "jni/JniHelper.h"
#include <jni.h>

#include <stdlib.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_come_hsiaoyi_melo_store_MLIapAndroidManager_nativeSetupStoreSuccess(JNIEnv* env, jobject obj)
    {
        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if (delegate != NULL) {
            delegate->storeSetupSuccess();
        }
    }

    JNIEXPORT void JNICALL Java_come_hsiaoyi_melo_store_MLIapAndroidManager_nativeSetupStoreFailure(JNIEnv* env, jobject obj, jint code, jstring message)
    {
        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if (delegate != NULL) {
            const char* messageStr = env->GetStringUTFChars(message, 0);

            delegate->storeSetupFailure(code, messageStr);

            env->ReleaseStringUTFChars(message, messageStr);
        }
    }

    JNIEXPORT void JNICALL Java_come_hsiaoyi_melo_store_MLIapAndroidManager_nativeStartRequestProducts(JNIEnv* env, jobject obj)
    {
        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if (delegate != NULL) {
            delegate->startRequestProducts();
        }
    }

    JNIEXPORT void JNICALL Java_come_hsiaoyi_melo_store_MLIapAndroidManager_nativeRequestProductsSuccess(JNIEnv* env,
                                                                                                         jobject obj,
                                                                                                         jint count,
                                                                                                         jobjectArray skus,
                                                                                                         jobjectArray titles,
                                                                                                         jobjectArray descriptions,
                                                                                                         jobjectArray prices,
                                                                                                         jobjectArray priceStrs,
                                                                                                         jobjectArray currencySyms)
    {
        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if (delegate != NULL) {
            IapStoreProducts products;
            vector<string> invalidIdentifiers;

            for (int i = 0; i < count; i++) {
                jstring jSku = (jstring)env->GetObjectArrayElement(skus, i);
                const char* skuStr = env->GetStringUTFChars(jSku, 0);
                jstring jTitle = (jstring)env->GetObjectArrayElement(titles, i);
                const char* titleStr = env->GetStringUTFChars(jTitle, 0);
                jstring jDesc = (jstring)env->GetObjectArrayElement(descriptions, i);
                const char* descStr = env->GetStringUTFChars(jDesc, 0);
                jstring jPrice = (jstring)env->GetObjectArrayElement(prices, i);
                const char* priceStr = env->GetStringUTFChars(jPrice, 0);
                jstring jPriceStr = (jstring)env->GetObjectArrayElement(priceStrs, i);
                const char* priceStrStr = env->GetStringUTFChars(jPriceStr, 0);
                jstring jCurrencySym = (jstring)env->GetObjectArrayElement(currencySyms, i);
                const char* currencySymStr = env->GetStringUTFChars(jCurrencySym, 0);

                IapStoreProduct product;
                product.identifier = skuStr;
                product.title = titleStr;
                product.description = descStr;
                product.price = atof(priceStr);
                product.priceStr = priceStrStr;
                product.priceLocale = currencySymStr;

                products.push_back(product);

                env->ReleaseStringUTFChars(jSku, skuStr);
                env->DeleteLocalRef(jSku);
                env->ReleaseStringUTFChars(jTitle, titleStr);
                env->DeleteLocalRef(jTitle);
                env->ReleaseStringUTFChars(jDesc, descStr);
                env->DeleteLocalRef(jDesc);
                env->ReleaseStringUTFChars(jPrice, priceStr);
                env->DeleteLocalRef(jPrice);
                env->ReleaseStringUTFChars(jPriceStr, priceStrStr);
                env->DeleteLocalRef(jPriceStr);
                env->ReleaseStringUTFChars(jCurrencySym, currencySymStr);
                env->DeleteLocalRef(jCurrencySym);
            }

            delegate->requestProductsSuccess(products, invalidIdentifiers);
        }
    }

    JNIEXPORT void JNICALL Java_come_hsiaoyi_melo_store_MLIapAndroidManager_nativeRequestProductsFailure(JNIEnv* env, jobject obj, jint code, jstring message)
    {
        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if (delegate != NULL) {
            const char* messageStr = env->GetStringUTFChars(message, 0);

            delegate->requestProductsFailure(code, messageStr);

            env->ReleaseStringUTFChars(message, messageStr);
        }
    }

    JNIEXPORT void JNICALL Java_come_hsiaoyi_melo_store_MLIapAndroidManager_nativeIsRemainPurchase(JNIEnv* env,
                                                                                                   jobject obj,
                                                                                                   jstring orderId,
                                                                                                   jstring productId,
                                                                                                   jstring purchaseDate,
                                                                                                   jstring originalJson,
                                                                                                   jstring itemType,
                                                                                                   jstring signature,
                                                                                                   jstring price,
                                                                                                   jstring currency)
    {
        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if (delegate != NULL) {
            const char* orderIdStr = env->GetStringUTFChars(orderId, 0);
            const char* productIdStr = env->GetStringUTFChars(productId, 0);
            const char* purchaseDateStr = env->GetStringUTFChars(purchaseDate, 0);
            const char* originalJsonStr = env->GetStringUTFChars(originalJson, 0);
            const char* itemTypeStr = env->GetStringUTFChars(itemType, 0);
            const char* signatureStr = env->GetStringUTFChars(signature, 0);
            const char* priceStr = env->GetStringUTFChars(price, 0);
            const char* currencyStr = env->GetStringUTFChars(currency, 0);

            MLIapTransaction t;
            t.transactionId = orderIdStr;
            t.productId = productIdStr;
            t.purchaseDate = purchaseDateStr;
            t.receipt = originalJsonStr;
            t.itemType = itemTypeStr;
            t.signature = signatureStr;
            t.price = atof(priceStr);
            t.currency = currencyStr;
            t.isConsumed = false;

            delegate->isRemainPurchase(t);

            env->ReleaseStringUTFChars(orderId, orderIdStr);
            env->ReleaseStringUTFChars(productId, productIdStr);
            env->ReleaseStringUTFChars(purchaseDate, purchaseDateStr);
            env->ReleaseStringUTFChars(originalJson, originalJsonStr);
            env->ReleaseStringUTFChars(itemType, itemTypeStr);
            env->ReleaseStringUTFChars(signature, signatureStr);
            env->ReleaseStringUTFChars(price, priceStr);
            env->ReleaseStringUTFChars(currency, currencyStr);
        }
    }

    JNIEXPORT void JNICALL Java_come_hsiaoyi_melo_store_MLIapAndroidManager_nativeStartPurchaseProduct(JNIEnv* env, jobject obj, jstring productId)
    {
        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if (delegate != NULL) {
            const char* productIdStr = env->GetStringUTFChars(productId, 0);

            delegate->startPurchaseProduct(productIdStr);

            env->ReleaseStringUTFChars(productId, productIdStr);
        }
    }

    JNIEXPORT void JNICALL Java_come_hsiaoyi_melo_store_MLIapAndroidManager_nativePurchaseProductSuccess(JNIEnv* env,
                                                                                                         jobject obj,
                                                                                                         jstring orderId,
                                                                                                         jstring productId,
                                                                                                         jstring purchaseDate,
                                                                                                         jstring originalJson,
                                                                                                         jstring itemType,
                                                                                                         jstring signature,
                                                                                                         jstring price,
                                                                                                         jstring currency)
    {
        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if (delegate != NULL) {
            const char* orderIdStr = env->GetStringUTFChars(orderId, 0);
            const char* productIdStr = env->GetStringUTFChars(productId, 0);
            const char* purchaseDateStr = env->GetStringUTFChars(purchaseDate, 0);
            const char* originalJsonStr = env->GetStringUTFChars(originalJson, 0);
            const char* itemTypeStr = env->GetStringUTFChars(itemType, 0);
            const char* signatureStr = env->GetStringUTFChars(signature, 0);
            const char* priceStr = env->GetStringUTFChars(price, 0);
            const char* currencyStr = env->GetStringUTFChars(currency, 0);

            MLIapTransaction t;
            t.transactionId = orderIdStr;
            t.productId = productIdStr;
            t.purchaseDate = purchaseDateStr;
            t.receipt = originalJsonStr;
            t.itemType = itemTypeStr;
            t.signature = signatureStr;
            t.price = atof(priceStr);
            t.currency = currencyStr;
            t.isConsumed = false;

            delegate->purchaseProductSuccess(t);

            env->ReleaseStringUTFChars(orderId, orderIdStr);
            env->ReleaseStringUTFChars(productId, productIdStr);
            env->ReleaseStringUTFChars(purchaseDate, purchaseDateStr);
            env->ReleaseStringUTFChars(originalJson, originalJsonStr);
            env->ReleaseStringUTFChars(itemType, itemTypeStr);
            env->ReleaseStringUTFChars(signature, signatureStr);
            env->ReleaseStringUTFChars(price, priceStr);
            env->ReleaseStringUTFChars(currency, currencyStr);
        }
    }

    JNIEXPORT void JNICALL Java_come_hsiaoyi_melo_store_MLIapAndroidManager_nativePurchaseProductCancel(JNIEnv* env, jobject obj, jint code, jstring message)
    {
        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if (delegate != NULL) {
            const char* messageStr = env->GetStringUTFChars(message, 0);

            delegate->purchaseProductCancel(code, messageStr);

            env->ReleaseStringUTFChars(message, messageStr);
        }
    }

    JNIEXPORT void JNICALL Java_come_hsiaoyi_melo_store_MLIapAndroidManager_nativePurchaseProductFailure(JNIEnv* env, jobject obj, jint code, jstring message)
    {
        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if (delegate != NULL) {
            const char* messageStr = env->GetStringUTFChars(message, 0);

            delegate->purchaseProductFailure(code, messageStr);

            env->ReleaseStringUTFChars(message, messageStr);
        }
    }

    JNIEXPORT void JNICALL Java_come_hsiaoyi_melo_store_MLIapAndroidManager_nativeStartConsumeProduct(JNIEnv* env, jobject obj, jstring orderId)
    {
        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if (delegate != NULL) {
            const char* orderIdStr = env->GetStringUTFChars(orderId, 0);

            delegate->startConsumeProduct(orderIdStr);

            env->ReleaseStringUTFChars(orderId, orderIdStr);
        }
    }

    JNIEXPORT void JNICALL Java_come_hsiaoyi_melo_store_MLIapAndroidManager_nativeConsumeProductSuccess(JNIEnv* env,
                                                                                                        jobject obj,
                                                                                                        jstring orderId,
                                                                                                        jstring productId,
                                                                                                        jstring purchaseDate,
                                                                                                        jstring originalJson,
                                                                                                        jstring itemType,
                                                                                                        jstring signature,
                                                                                                        jstring price,
                                                                                                        jstring currency)
    {
        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if (delegate != NULL) {
            const char* orderIdStr = env->GetStringUTFChars(orderId, 0);
            const char* productIdStr = env->GetStringUTFChars(productId, 0);
            const char* purchaseDateStr = env->GetStringUTFChars(purchaseDate, 0);
            const char* originalJsonStr = env->GetStringUTFChars(originalJson, 0);
            const char* itemTypeStr = env->GetStringUTFChars(itemType, 0);
            const char* signatureStr = env->GetStringUTFChars(signature, 0);
            const char* priceStr = env->GetStringUTFChars(price, 0);
            const char* currencyStr = env->GetStringUTFChars(currency, 0);

            MLIapTransaction t;
            t.transactionId = orderIdStr;
            t.productId = productIdStr;
            t.purchaseDate = purchaseDateStr;
            t.receipt = originalJsonStr;
            t.itemType = itemTypeStr;
            t.signature = signatureStr;
            t.price = atof(priceStr);
            t.currency = currencyStr;
            t.isConsumed = true;

            delegate->consumeProductSuccess(t);

            env->ReleaseStringUTFChars(orderId, orderIdStr);
            env->ReleaseStringUTFChars(productId, productIdStr);
            env->ReleaseStringUTFChars(purchaseDate, purchaseDateStr);
            env->ReleaseStringUTFChars(originalJson, originalJsonStr);
            env->ReleaseStringUTFChars(itemType, itemTypeStr);
            env->ReleaseStringUTFChars(signature, signatureStr);
            env->ReleaseStringUTFChars(price, priceStr);
            env->ReleaseStringUTFChars(currency, currencyStr);
        }
    }

    JNIEXPORT void JNICALL Java_come_hsiaoyi_melo_store_MLIapAndroidManager_nativeConsumeProductFailure(JNIEnv* env, jobject obj, jint code, jstring message)
    {
        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if (delegate != NULL) {
            const char* messageStr = env->GetStringUTFChars(message, 0);

            delegate->consumeProductFailure(code, messageStr);

            env->ReleaseStringUTFChars(message, messageStr);
        }
    }
}

#endif
