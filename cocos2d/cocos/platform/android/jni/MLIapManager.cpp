//--------------------------------------------------------------------------------
//  File        : MLIapManager.cpp
//  Description :
//  Author      : Chang, Hsiao-Yi
//
//  Copyright (c) 2014-2015. All rights reserved.
//  https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#include "MLIapManager.h"
#include "MLIapManagerJni.h"

#ifdef ML_NATIVE_IAP_SUPPORT

MLIapDelegate* MLIapManager::m_pDelegate = NULL;

MLIapManager& MLIapManager::getInstance()
{
    static MLIapManager instance;
    return instance;
}

void MLIapManager::setupKey(std::string publicKey)
{
    jobject obj = initIapManagerJni();
    if (obj != NULL) {
        m_pIapManager = (void *) obj;
        setupIapManagerJni((jobject) m_pIapManager, publicKey);
    } else {
        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if (delegate != NULL) {
            delegate->iapSetupFailure(0, NULL);
        }
    }
}

void MLIapManager::requestProducts(std::vector<std::string> productIdentifiers)
{
    if (m_pIapManager != NULL) {
        requestProductsJni((jobject) m_pIapManager, productIdentifiers);
    }
}

void MLIapManager::purchaseProduct(std::string productIdentifier)
{
    if (m_pIapManager != NULL) {
        purchaseProductJni((jobject) m_pIapManager, productIdentifier);
    }
}

void MLIapManager::consumeProduct(MLIapTransaction transaction)
{
    if (m_pIapManager != NULL) {
        consumeProductJni((jobject) m_pIapManager, transaction.itemType, transaction.receipt, transaction.signature);
    }
}

#endif
