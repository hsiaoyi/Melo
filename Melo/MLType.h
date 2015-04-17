//--------------------------------------------------------------------------------
//	File		: MLType.h
//	Description	: 
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#ifndef __ML_TYPE_H__
#define __ML_TYPE_H__

//--------------------------------------------------------------------------------
// win32
#ifdef WIN32

#define MLWIN32 WIN32

//--------------------------------------------------------------------------------
// basic types
#define MLINT		int
#define MLFLOAT		float
#define MLDOUBLE	double
#define MLBOOL		bool

#define MLTRUE		true
#define MLFALSE		false

//--------------------------------------------------------------------------------
// Scene Related types
typedef void(*MLFunc)(void);
typedef MLINT MLLayerId;
typedef MLINT MLSpriteId;
typedef MLINT MLLabelId;

//--------------------------------------------------------------------------------
// general types
/*
typedef struct MLVec2f
{
	MLVec2f()
	{
		x = 0.0;
		y = 0.0;
	}

	MLVec2f(MLFLOAT xx, MLFLOAT yy)
	{
		x = xx;
		y = yy;
	}

	MLFLOAT x;
	MLFLOAT y;	
};

typedef struct MLVec3f
{
	MLVec3f()
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
	}

	MLVec3f(MLFLOAT xx, MLFLOAT yy, MLFLOAT zz)
	{
		x = xx;
		y = yy;
		z = zz;
	}

	MLFLOAT x;
	MLFLOAT y;
	MLFLOAT z;
};

typedef struct MLVec2i
{
	MLVec2i()
	{
		x = 0;
		y = 0;
	}

	MLVec2i(MLINT xx, MLINT yy)
	{
		x = xx;
		y = yy;
	}

	MLINT x;
	MLINT y;
};

typedef struct MLVec3i
{
	MLVec3i()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	MLVec3i(MLINT xx, MLINT yy, MLINT zz)
	{
		x = xx;
		y = yy;
		z = zz;
	}

	MLINT x;
	MLINT y;
	MLINT z;
};
*/


//--------------------------------------------------------------------------------
// special types
/*
typedef struct _MLCOLOR3F
{
	MLFLOAT r;
	MLFLOAT g;
	MLFLOAT b;
}MLColor3f;

typedef struct _MLCOLOR4F
{
	MLFLOAT r;
	MLFLOAT g;
	MLFLOAT b;
	MLFLOAT a;
}MLColor4f;
*/
#endif	// WIN32



#endif	// __ML_TYPE_H__