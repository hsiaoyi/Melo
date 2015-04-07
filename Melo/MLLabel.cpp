//--------------------------------------------------------------------------------
//	File		: MLLabel.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#include "MLLabel.h"
#include "base\ccUTF8.h"

//--------------------------------------------------------------------------------
MLLabel::MLLabel(MLTTFFont *fnt, string str, MLFLOAT x, MLFLOAT y):
mFont(fnt),
mPosX(x),
mPosY(y)
{
	SetString(str);
}

//--------------------------------------------------------------------------------
MLBOOL MLLabel::SetString(string str)
{
	StringUtils::UTF8ToUTF16(str, mU16Str);
	mFont->AddString(mU16Str, mWords);

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLBOOL MLLabel::SetPosition(MLFLOAT x, MLFLOAT y)
{
	// todo: area check
	mPosX = x;
	mPosY = y;

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLBOOL MLLabel::Draw()
{
	MLINT x = mPosX;
	MLINT y = mPosY;

	for (int i = 0; i < mU16Str.length(); ++i)
	{
		char16_t changeLine = '\n';
		if (mU16Str.c_str()[i] == changeLine)
		{
			y -= mFont->GetCellHeight();	// y-axis is in revert direction 
			x = mPosX;
			continue;
		}

		MLWordInfo *w = mFont->GetAtlasTexture(mU16Str.c_str()[i]);

		GLfloat coords[] =
		{
			 w->u / 255.,		  (w->v + w->h) / 255., //1
			(w->u + w->w) / 255., (w->v + w->h) / 255., //2
			 w->u / 255.,		   w->v / 255.,			//3
			(w->u + w->w) / 255.,  w->v / 255.,			//4
		};

		GLfloat verts[] =
		{
			x,		  y,		//1
			x + w->w, y,		//2			
			x,		  y + w->h,	//3
			x + w->w, y + w->h,	//4
		};

		GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
		
		GLProgram* sg = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE);		
		sg->use();
		sg->setUniformsForBuiltins();		

		GL::bindTexture2D(mFont->GetTextrue(w->texIdx)->getName());

		glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, verts);
		glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, coords);

		Director* director = Director::getInstance();
		director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
		Mat4 myid;
		myid.setIdentity();
		director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, myid);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

		x += w->w+1;
	}

	return MLTRUE;
}

//--------------------------------------------------------------------------------
/*
1----0
| \  |
|  \ |
3----2

5----4
| \  |
|  \ |
7----6

*/
/*
void TextureAtlas::setupIndices()
{
	if (_capacity == 0)
		return;

	for (int i = 0; i < _capacity; i++)
	{
		_indices[i * 6 + 0] = i * 4 + 0;
		_indices[i * 6 + 1] = i * 4 + 1;
		_indices[i * 6 + 2] = i * 4 + 2;

		_indices[i * 6 + 3] = i * 4 + 3;
		_indices[i * 6 + 4] = i * 4 + 2;
		_indices[i * 6 + 5] = i * 4 + 1;
	}
}
*/