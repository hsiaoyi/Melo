//--------------------------------------------------------------------------------
//	File		: MLBase.h
//	Description	: 
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#ifndef __ML_BASE_H__
#define __ML_BASE_H__

//--------------------------------------------------------------------------------
// memory
#define ML_NEW new
#define ML_DELETE delete

//--------------------------------------------------------------------------------
#ifdef WIN32

	// log
	#ifdef USE_COCOS2DX // use cocos2dx for now
		#define MLASSERT	CC_ASSERT
	#else
	#define MLASSERT(msg)	assert(msg)
	#endif//USE_COCOS2DX

	#ifdef USE_COCOS2DX // use cocos2dx for now
		#define MLLOG		CCLOG
	#else
		//#define MLLOG(msg)		log(msg)
		#define MLLOG
	#endif//USE_COCOS2DX

#endif // WIN32


#endif	// __ML_BASE_H__