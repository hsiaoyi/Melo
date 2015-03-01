//--------------------------------------------------------------------------------
//	File		: MLBaseLayer.h
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#ifndef __MLBASELAYER_H__
#define __MLBASELAYER_H__

#include "Melo.h"

//--------------------------------------------------------------------------------
class MLBaseLayer
{
public:
	MLBaseLayer(MLFunc initialfunc = NULL, MLFunc updatefunc = NULL, MLFunc destroyfunc = NULL);
	virtual ~MLBaseLayer();	
	virtual void Draw() =0;

	// todo
	//void SetPosition(MLFLOAT posX, MLFLOAT posY);
	//void SetRotation(MLFLOAT eulerAngle);


	// add initial, process, destroy CBs
	MLFunc mInitialFunc;
	MLFunc mUpdateFunc;
	MLFunc mDestroyFunc;	
protected:
	// layer geometirc info
	// currently not in used, position set to origin and rotation set to 0
	MLFLOAT mPosX;
	MLFLOAT mPosY;
	MLFLOAT mRotAng;// euler angle in z-axis

};//

#endif // __MLAPP_H__