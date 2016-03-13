//--------------------------------------------------------------------------------
//	File		: MLMath.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#include "MLMath.h"

unsigned int MLMath::mSeed = 0;

//--------------------------------------------------------------------------------
void MLMath::ScreenToWorld(MLVec2& coords)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	coords.y = visibleSize.height - coords.y;
}

//--------------------------------------------------------------------------------
void MLMath::Srand(unsigned int seed)
{
    mSeed = seed;
}

//--------------------------------------------------------------------------------
int MLMath::Random()
{
    return MLMath::Rand();
}

int MLMath::Rand()
{
    int result;
    
    mSeed *= 1103515245;
    mSeed += 12345;
    result = (unsigned int) (mSeed / 65536) % 2048;
    
    mSeed *= 1103515245;
    mSeed += 12345;
    result <<= 10;
    result ^= (unsigned int) (mSeed / 65536) % 1024;
    
    return result;
}

#define	RAND_MAX	0x7fffffff
//--------------------------------------------------------------------------------
float MLMath::Random_Minus_1_1()
{
    return ((2.0f*((float)MLMath::Rand()/RAND_MAX))-1.0f);
}

//--------------------------------------------------------------------------------
float MLMath::Random_0_1()
{
    return ((float)MLMath::Rand()/RAND_MAX);
}
