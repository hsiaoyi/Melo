//--------------------------------------------------------------------------------
//	File		: MLPlatform.h
//	Description	: 
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#ifndef __ML_PLATFORM_H__
#define __ML_PLATFORM_H__

#if defined(_WIN32) && defined(_WINDOWS)
    #define ML_WIN32
    #pragma message("win32")
#endif	// WIN32

#if defined(CC_TARGET_OS_IPHONE)
    #define ML_IOS
    #pragma message("ios")
#endif

#if defined(ANDROID) || defined(CC_TARGET_OS_ANDROID)
    #define ML_ANDROID
    #pragma message("android")
#endif


#endif	// __ML_PLATFORM_H__