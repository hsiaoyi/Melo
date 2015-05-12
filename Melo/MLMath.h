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
typedef struct MLVec2
{	
	MLVec2(MLFLOAT _x, MLFLOAT _y)
	{
		x = _x;
		y = _y;
	}

	MLFLOAT x;
	MLFLOAT y;
};

class MLMath
{
public:
	static void ScreenToWorld(MLVec2& coords);
};

#endif	// __ML_MATH_H__