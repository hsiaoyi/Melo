//--------------------------------------------------------------------------------
//	File		: MLMath.h
//	Description	: 
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#ifndef __ML_MATH_H__
#define __ML_MATH_H__
#include "Melo.h"

//--------------------------------------------------------------------------------
typedef struct _MLVec2
{	
	_MLVec2(MLFLOAT _x, MLFLOAT _y)
	{
		x = _x;
		y = _y;
	}

	MLFLOAT x;
	MLFLOAT y;
}MLVec2;

class MLMath
{
public:
	static void ScreenToWorld(MLVec2& coords);
    static void Srand(unsigned int seed);
    static int Random();
    static float Random_0_1();
    static float Random_Minus_1_1();
    
private :
    static int Rand();
    static unsigned int mSeed;
};

#endif	// __ML_MATH_H__