//--------------------------------------------------------------------------------
//  File        : MLIapManager.h
//  Description :
//  Author      : Chang, Hsiao-Yi
//
//  Copyright (c) 2014-2015. All rights reserved.
//  https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#ifndef _ML_IAP_MANAGER_H_
#define _ML_IAP_MANAGER_H_

#ifdef ML_NATIVE_IAP_SUPPORT

#include <string>
#include <vector>

class MLIapManager;

//--------------------------------------------------------------------------------
class MLIapProduct
{
public:
    MLIapProduct()
    : identifier("")
    , title("")
    , description("")
    , price(0.0f)
    , priceLocale("")
    , priceStr("")
    {};
    
    virtual ~MLIapProduct() {};

    double price;
    std::string identifier;
    std::string title;
    std::string description;
    std::string priceLocale;
    std::string priceStr;
};

//--------------------------------------------------------------------------------
class MLIapTransaction
{
public:
    MLIapTransaction()
    : transactionId("")
    , productId("")
    , purchaseDate("")
    , receipt("")
    , itemType("")
    , signature("")
    , price(0.0f)
    , currency("DEFAULT")
    , quantity(0)
    , isConsumed(false)
    {};
    
    virtual ~MLIapTransaction() {};

    bool isConsumed;
    double price;
    int32_t quantity;
    std::string transactionId;
    std::string productId;
    std::string purchaseDate;
    std::string receipt;
    std::string itemType;
    std::string signature;
    std::string currency;
};

//--------------------------------------------------------------------------------
class MLIapDelegate 
{
public:
    // setup store
    virtual void iapSetupSuccess() {}
    virtual void iapSetupFailure(int64_t code, const char* message) {}

    // products request
    virtual void startRequestProducts() {}
    virtual void requestProductsSuccess(std::vector<MLIapProduct> productIdentifiers, std::vector<std::string> invalidIdentifiers) {}
    virtual void requestProductsFailure(int64_t code, const char* message) {}

    // purchase validation
    virtual void isRemainPurchase(MLIapTransaction transaction) {}

    // purchase product
    virtual void startPurchaseProduct(const char* productIdentifier) {}
    virtual void purchaseProductSuccess(MLIapTransaction transaction) {}
    virtual void purchaseProductFailure(int64_t code, const char* message) {}
    virtual void purchaseProductCancel(int64_t code, const char* message) {}
    virtual void purchaseProductDeferred() {}

    // consume product
    virtual void startConsumeProduct(const char* orderId) {}
    virtual void consumeProductSuccess(MLIapTransaction transaction) {}
    virtual void consumeProductFailure(int64_t code, const char* message) {}
};

//--------------------------------------------------------------------------------
class MLIapManager {
public:
    static MLIapManager& getInstance();

    static void setDelegate(MLIapDelegate* delegate) { m_pDelegate = delegate; }
    static MLIapDelegate* getDelegate() { return m_pDelegate; }

    void setupKey(std::string publicKey);
    void requestProducts(std::vector<std::string> productIdentifiers);
    void purchaseProduct(std::string productIdentifier);
    void consumeProduct(MLIapTransaction transaction);

private:
    MLIapManager() : m_pIapManager(NULL) {}
    virtual ~MLIapManager() {}

    MLIapManager(const MLIapManager& store) = delete;
    void operator=(const MLIapManager &) = delete;

    void* m_pIapManager;
    static MLIapDelegate* m_pDelegate;
};

#endif

#endif // _ML_IAP_MANAGER_H_
