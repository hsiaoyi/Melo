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

typedef struct _MLRect
{
    _MLRect(MLFLOAT _x, MLFLOAT _y, MLFLOAT _width, MLFLOAT _height)
    {
        x = _x;
        y = _y;
        width = _width;
        height = _height;
    }
    
    _MLRect(const _MLRect &_rect)
    {
        x = _rect.x;
        y = _rect.y;
        width = _rect.width;
        height = _rect.height;
    }
    
    void operator=(const _MLRect &_rect)
    {
        x = _rect.x;
        y = _rect.y;
        width = _rect.width;
        height = _rect.height;
    }
    
    MLFLOAT x;
    MLFLOAT y;
    MLFLOAT width;
    MLFLOAT height;
}MLRect;

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