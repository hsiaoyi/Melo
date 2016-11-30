//--------------------------------------------------------------------------------
//  File        : MLIapManager.mm
//  Description :
//  Author      : Chang, Hsiao-Yi
//
//  Copyright (c) 2014-2016. All rights reserved.
//  https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#include "MLIapManager.h"
#import "MLIapIosManager.h"

MLIapDelegate* MLIapManager::m_pDelegate = NULL;

MLIapManager& MLIapManager::getInstance()
{
    static MLIapManager instance;
    return instance;
}

void MLIapManager::setupKey(std::string publicKey)
{
    MLIapIosManager *iapManager = [MLIapIosManager sharedManager];
    if ( iapManager != nil )
    {
        m_pIapManager = (__bridge void *)iapManager;

        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if ( delegate != NULL )
        {
            delegate->iapSetupSuccess();
        }
    } 
    else
    {
        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if (delegate != NULL)
        {
            delegate->iapSetupFailure(0, "store initialize failed");
        }
    }
}

void MLIapManager::requestProducts(std::vector<std::string> productIdentifiers)
{
    MLIapDelegate* delegate = MLIapManager::getDelegate();
    if ( delegate != NULL )
    {
        delegate->startRequestProducts();
    }

    NSMutableSet* productIds = [NSMutableSet new];
    for (auto p : productIdentifiers)
    {
        NSString* str = [NSString stringWithUTF8String:p.c_str()];
        [productIds addObject:str];
    }
    MLIapIosManager* store = (__bridge MLIapIosManager*)m_pIapManager;
    [store requestProducts:productIds];
}

void MLIapManager::purchaseProduct(std::string productIdentifier)
{
    MLIapDelegate* delegate = MLIapManager::getDelegate();
    if (delegate != NULL) 
    {
        delegate->startPurchaseProduct(productIdentifier.c_str());
    }

    NSString* identifier = [NSString stringWithUTF8String:productIdentifier.c_str()];
    MLIapIosManager* iapManager = (__bridge MLIapIosManager*)m_pIapManager;
    [iapManager addPayment:identifier];
}

void MLIapManager::consumeProduct(MLIapTransaction transaction)
{
    transaction.isConsumed = true;

    // iOS don't have consume API. Always success here
    MLIapDelegate* delegate = MLIapManager::getDelegate();
    if ( delegate != NULL )
    {
        delegate->consumeProductSuccess(transaction);
    }
}
