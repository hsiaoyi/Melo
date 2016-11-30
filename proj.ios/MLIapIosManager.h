//--------------------------------------------------------------------------------
//  File        : MLIapIosManager.h
//  Description :
//  Author      : Chang, Hsiao-Yi
//
//  Copyright (c) 2014-2016. All rights reserved.
//  https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------


#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

@interface MLIapIosManager : NSObject<SKPaymentTransactionObserver, SKProductsRequestDelegate>

@property (nonatomic, strong) NSMutableDictionary* products;

+ (id)sharedManager;

- (void)requestProducts:(NSSet*)identifiers;

- (void)addPayment:(NSString*)productIdentifier;

+ (BOOL)canMakePayments;

- (BOOL)isRemainTransactions;

@end
