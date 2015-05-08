//--------------------------------------------------------------------------------
//	File		: MLLabel.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------

#include "MLLabel.h"
#include "MLSceneMgr.h"
//#include "base\ccUTF8.h"
#include "ccUTF8.h"

//--------------------------------------------------------------------------------
MLLabel::MLLabel(MLTTFFont *fnt, string str, MLFLOAT x, MLFLOAT y):
mFont(fnt),
mPosX(x),
mPosY(y),
mShowCounts(0),
mLineSpacing(3),
mWordSpacing(1),
mWidth(0),
mHeight(0),
//mLineCount(0),
// effect params
mCurrentTime(0.),
mLastTime(0.),
mWordByWordPeriod(0.05),
mDelayedTime(0.5),
mRepeatEffect(true)
{
	SetString(str);
}

//--------------------------------------------------------------------------------
MLLabel::~MLLabel()
{
	mWords.clear();
	mFont = nullptr;
	mU16Str.clear();
}

//--------------------------------------------------------------------------------
MLBOOL MLLabel::SetString(string str)
{
	StringUtils::UTF8ToUTF16(str, mU16Str);
	mFont->AddString(mU16Str, mWords);
	mShowCounts = 0;
	CalContentSize();

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

	mCurrentTime += MLSceneMgr::GetInstance()->GetDeltaTime();

	// calculate how many words to show
	if (mCurrentTime - mLastTime> mWordByWordPeriod)
	{
		if (mShowCounts < mU16Str.length())
		{
			mShowCounts++;
			mLastTime = mCurrentTime;
		}	
		else if ((mCurrentTime - mLastTime) >(mWordByWordPeriod + mDelayedTime))
		{
			if (mRepeatEffect)
			{
				ResetEffect();
			}
		}		
	}

	for (int i = 0; i < mShowCounts; ++i)
	{
		// special character handlings
		char16_t changeLine = '\n';
		if (mU16Str.c_str()[i] == changeLine)
		{
			y -= (mFont->GetCellHeight() + mLineSpacing);	// next line is in revert direction
			x = mPosX;
			continue;
		}

		char16_t whiteSpace = ' ';
		if (mU16Str.c_str()[i] == whiteSpace)
		{
			x += ((int)mFont->GetCellWidth() / 2 + mWordSpacing);
			continue;
		}

		MLWordInfo *w = mFont->GetAtlasTexture(mU16Str.c_str()[i]);

		GLfloat coords[] =
		{
            static_cast<GLfloat>(w->u / 255.),		    static_cast<GLfloat>((w->v + w->h) / 255.), //1
			static_cast<GLfloat>((w->u + w->w) / 255.), static_cast<GLfloat>((w->v + w->h) / 255.), //2
            static_cast<GLfloat>(w->u / 255.),		    static_cast<GLfloat>(w->v / 255.),			//3
			static_cast<GLfloat>((w->u + w->w) / 255.), static_cast<GLfloat>(w->v / 255.),			//4
		};

		GLfloat verts[] =
		{
			static_cast<GLfloat>(x),		static_cast<GLfloat>(y),		//1
			static_cast<GLfloat>(x + w->w), static_cast<GLfloat>(y),		//2
			static_cast<GLfloat>(x),		static_cast<GLfloat>(y + w->h),	//3
			static_cast<GLfloat>(x + w->w), static_cast<GLfloat>(y + w->h),	//4
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

		x += w->w + mWordSpacing;
	}

	return MLTRUE;
}

//--------------------------------------------------------------------------------
void MLLabel::ResetEffect()
{
	mCurrentTime = 0.;
	mLastTime = 0.;
	mShowCounts = 0;
}

//--------------------------------------------------------------------------------
void MLLabel::SetWordByWordEffectParams(MLDOUBLE period, MLDOUBLE delay, MLBOOL repeat)
{
	// todo: negative value check
	mWordByWordPeriod = period;
	mDelayedTime = delay;
	mRepeatEffect = repeat;
	ResetEffect();
}

//--------------------------------------------------------------------------------
void MLLabel::CalContentSize()
{
	int tmpWidth = 0;
	//int tmpHeight = 0;
	mHeight = 0;
	mWidth = 0;

	char16_t newLine = '\n';
	char16_t whiteSpace = ' ';

	if (mU16Str.length() <= 0)
	{
		return;
	}
	else
	{
		//mLineCount = 1;
	}

	for (int i = 0; i < mU16Str.length(); ++i)
	{
		// align with first line
		if (mU16Str.c_str()[i] == newLine)
		{
			mHeight += (mFont->GetCellHeight() + mLineSpacing);
			if (mWidth < tmpWidth)
			{
				mWidth = tmpWidth;
				tmpWidth = 0;
				//mLineCount++;	// maybe check is next char exist
			}
		}
		else if (mU16Str.c_str()[i] == whiteSpace)
		{
			tmpWidth += ((int)mFont->GetCellWidth() / 2 + mWordSpacing);
		}
		else
		{
			MLWordInfo *w = mFont->GetAtlasTexture(mU16Str.c_str()[i]);
			tmpWidth += w->w + mWordSpacing;
		}
	}

	if (mWidth < tmpWidth)
	{
		mWidth = tmpWidth;
	}
	
}

//--------------------------------------------------------------------------------
MLINT MLLabel::GetLabelWidth()
{
	return mWidth;
}

//--------------------------------------------------------------------------------
MLINT MLLabel::GetLabelHeight()
{
	return mHeight;
}

//--------------------------------------------------------------------------------
void MLLabel::SetLabelAlignWin(MLAlignH hori, MLAlignV vert)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vec2 pos(0,0);

	// horizantal
	if(hori == MLAH_Left)
	{
		pos.x = origin.x;
	}
	else if (hori == MLAH_Right)
	{
		pos.x = origin.x + visibleSize.width - GetLabelWidth();
	}
	else//MLAH_Center
	{
		pos.x = origin.x + (visibleSize.width - GetLabelWidth())/2;
	}

	//vertical
	if (vert == MLAV_TOP)
	{
		pos.y = origin.y + visibleSize.height - GetLabelHeight();
	}
	else if (vert == MLAV_Buttom)
	{
		pos.y = origin.y + GetLabelHeight();
	}
	else//MLAV_Center
	{
		pos.y = origin.y + (visibleSize.height - GetLabelHeight()) / 2;
	}	

	SetPosition(pos.x, pos.y);
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