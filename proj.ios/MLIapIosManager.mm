//--------------------------------------------------------------------------------
//  File        : MLIapIosManager.mm
//  Description :
//  Author      : Chang, Hsiao-Yi
//
//  Copyright (c) 2014-2016. All rights reserved.
//  https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#import "MLIapIosManager.h"
#include "MLIapManager.h"

#define MLIapRemainTransactionCountKey @"MLIapRemainTransactionCountKey"

#define MLIapErrorDomain @"com.hsiaoyi.melo.ios"
typedef enum {
    MLIapErrorUnknown = 0,
    MLIapErrorUnknownProduct,
    MLIapErrorCannotMakePayments
} MLIapErrorCode;

@implementation MLIapIosManager

static NSString * const kReceiptNothing = @"ReceiptNone";

- (id)init
{
    if (self = [super init])
    {
        _products = [NSMutableDictionary dictionary];
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    }
    return self;
}

- (void)dealloc
{
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];
}

+ (id)sharedManager
{
    static MLIapIosManager* sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, 
    ^{
        sharedInstance = [[MLIapIosManager alloc] init];
    });
    return sharedInstance;
}

+ (BOOL)canMakePayments
{
    return [SKPaymentQueue canMakePayments];
}

- (BOOL)isRemainTransactions
{
    BOOL isRemain = NO;
    NSArray* transactions = [SKPaymentQueue defaultQueue].transactions;
    for (SKPaymentTransaction* t in transactions) {
        NSLog(@"Have unfinished transaction: %@ %@ %d", t.transactionIdentifier, t.transactionDate, (int)t.transactionState);
        if (t.transactionState == SKPaymentTransactionStateFailed)
        {
            [[SKPaymentQueue defaultQueue] finishTransaction:t];
        }
        else
        {
            isRemain = YES;
        }
    }
    return isRemain;
}

- (void)requestProducts:(NSSet *)identifiers
{
    SKProductsRequest* request = [[SKProductsRequest alloc] initWithProductIdentifiers:identifiers];
    request.delegate = self;
    [request start];
}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    NSArray* products = [NSArray arrayWithArray:response.products];
    NSArray* invalidProductIdentifiers = [NSArray arrayWithArray:response.invalidProductIdentifiers];

    [_products removeAllObjects];

    for ( SKProduct* product in products )
    {
        _products[product.productIdentifier] = product;
    }

    for ( NSString* identifier in invalidProductIdentifiers )
     {
        NSLog(@"Products Request have invalid identifier: %@", identifier);
    }

    MLIapDelegate* delegate = MLIapManager::getDelegate();
    if ( delegate != NULL )
    {
        std::vector<MLIapProduct> productIdentifiers;
        std::vector<std::string> invalidIdentifiers;
        for ( SKProduct* p in products )
        {
            MLIapProduct product = [self setProductData:p];
            productIdentifiers.push_back(product);
        }
        for ( NSString* s in invalidProductIdentifiers )
        {
            invalidIdentifiers.push_back([s UTF8String]);
        }
        delegate->requestProductsSuccess(productIdentifiers, invalidIdentifiers);
    }
}

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error
{
    NSLog(@"Product request failed. Error %@", error.debugDescription);

    MLIapDelegate* delegate = MLIapManager::getDelegate();
    if (delegate != NULL)
    {
        delegate->requestProductsFailure(error.code, [error.description UTF8String]);
    }
}

- (void)addPayment:(NSString *)productIdentifier
{
    if ( ![SKPaymentQueue canMakePayments] )
    {
        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if ( delegate != NULL )
        {
            delegate->purchaseProductFailure(MLIapErrorCannotMakePayments, "Cannot make payment");
        }
        return;
    }

    SKProduct* product = _products[productIdentifier];

    if ( product == nil )
    {
        MLIapDelegate* delegate = MLIapManager::getDelegate();
        if ( delegate != NULL )
        {
            delegate->purchaseProductFailure(MLIapErrorUnknownProduct, "Purchasing unknown product");
        }
        return;
    }

    SKPayment* payment = [SKPayment paymentWithProduct:product];
    [[SKPaymentQueue defaultQueue] addPayment:payment];
}

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    for ( SKPaymentTransaction* transaction in transactions )
    {
        switch ( transaction.transactionState )
        {
            case SKPaymentTransactionStatePurchasing:
                NSLog(@"SKPaymentTransactionStatePurchasing");
                break;
            case SKPaymentTransactionStatePurchased:
                NSLog(@"SKPaymentTransactionStatePurchased");
                [self completeTransaction:transaction queue:queue];
                break;
            case SKPaymentTransactionStateDeferred:
                NSLog(@"SKPaymentTransactionStateDeferred");
                [self deferredTransaction];
                break;
            case SKPaymentTransactionStateFailed:
                NSLog(@"SKPaymentTransactionStateFailed");
                [self failedTransaction:transaction queue:queue];
                break;
            case SKPaymentTransactionStateRestored:
                NSLog(@"SKPaymentTransactionStateRestored");
                break;
            default:
                break;
        }
    }
}

- (void)paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray *)transactions
{
}

- (void)completeTransaction:(SKPaymentTransaction*)transaction queue:(SKPaymentQueue*)queue
{
    MLIapDelegate* delegate = MLIapManager::getDelegate();
    if (delegate != NULL) {
        MLIapTransaction t = [self setTransactionData:transaction];
        if (t.receipt == [kReceiptNothing UTF8String]) {
            return;
        }
        delegate->purchaseProductSuccess(t);
        [queue finishTransaction:transaction];
    }
}

- (void)failedTransaction:(SKPaymentTransaction*)transaction queue:(SKPaymentQueue*)queue
{
    NSLog(@"purchase failed with product: %@", transaction.payment.productIdentifier);
    NSLog(@"Error: %@", transaction.error.debugDescription);

    MLIapDelegate* delegate = MLIapManager::getDelegate();
    switch ( transaction.error.code )
    {
        case SKErrorPaymentCancelled:
        {
            if (delegate != nullptr)
            {
                delegate->purchaseProductCancel(transaction.error.code, [transaction.error.description UTF8String]);
            }
        }
        break;
        case SKErrorClientInvalid:
        case SKErrorPaymentInvalid:
        case SKErrorPaymentNotAllowed:
        case SKErrorStoreProductNotAvailable:
        case SKErrorUnknown:
        default:
        {
            if (delegate != nullptr)
            {
                delegate->purchaseProductFailure(transaction.error.code, [transaction.error.description UTF8String]);
            }
        }
        break;
    }

    [queue finishTransaction:transaction];
}

- (void)deferredTransaction
{
    MLIapDelegate* delegate = MLIapManager::getDelegate();
    if (delegate != NULL)
    {
        delegate->purchaseProductDeferred();
    }
}

- (MLIapProduct)setProductData:(SKProduct*)product
{
    MLIapProduct p;

    p.identifier = [product.productIdentifier UTF8String];
    p.title = [product.localizedTitle UTF8String];
    p.description = [product.localizedDescription UTF8String];
    p.price = [product.price doubleValue];
    p.priceLocale = [[product.priceLocale objectForKey:NSLocaleCurrencyCode] UTF8String];

    NSNumberFormatter* nf = [NSNumberFormatter new];
    [nf setNumberStyle:NSNumberFormatterCurrencyStyle];
    [nf setLocale:product.priceLocale];
    p.priceStr = [[nf stringFromNumber:product.price] UTF8String];

    return p;
}

- (MLIapTransaction)setTransactionData:(SKPaymentTransaction*)transaction
{
    MLIapTransaction t;

    t.transactionId = [transaction.transactionIdentifier UTF8String];
    t.productId = [transaction.payment.productIdentifier UTF8String];
    NSTimeInterval timestamp = [transaction.transactionDate timeIntervalSince1970];
    t.purchaseDate = [[NSString stringWithFormat:@"%d", static_cast<int>(timestamp)] UTF8String];

    if (transaction.transactionState == SKPaymentTransactionStatePurchased)
    {
        NSString* receiptStr = nil;
        if (floor(NSFoundationVersionNumber) <= NSFoundationVersionNumber_iOS_6_1)
        {
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
            NSData* data = transaction.transactionReceipt;
            receiptStr = [data base64Encoding];
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
        }
        else
        {
            NSURL* receiptUrl = [[NSBundle mainBundle] appStoreReceiptURL];
            if ([[NSFileManager defaultManager] fileExistsAtPath:[receiptUrl path]])
            {
                NSData* data = [NSData dataWithContentsOfURL:receiptUrl];
                receiptStr = [data base64EncodedStringWithOptions:kNilOptions];
            }
        }

        t.receipt = receiptStr ? [receiptStr UTF8String] : [kReceiptNothing UTF8String];
    }

    t.isConsumed = false;

    return t;
}

@end
