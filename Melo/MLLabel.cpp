//--------------------------------------------------------------------------------
//	File		: MLLabel.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#include <string>
#include "MLLabel.h"
#include "MLSceneMgr.h"
#include "ccUTF8.h"

//--------------------------------------------------------------------------------
MLLabel::MLLabel(MLTTFFont *fnt, string str, MLFLOAT x, MLFLOAT y, MLBOOL useClip, MLINT clipWidth, MLINT clipHeight):
mDrawStringLength(0),
mFont(fnt),
mPosX(x),
mPosY(y),
mShowCounts(0),
mAllShowedOnce(MLFALSE),
mLineSpacing(5),
//mLineSpacing(5),
mWordSpacing(MLFontSizeScaleFactor + 2),
//mWordSpacing(0),
mWidth(0),
mHeight(0),
mClipArea(useClip),
mClipWidth(clipWidth),
mClipHeight(clipHeight),
//mLineCount(0),
// effect params
mCurrentTime(0.),
mLastTime(0.),
mWordByWordPeriod(0.),
mDelayedTime(0.5),
mRepeatEffect(MLTRUE),
mColorR(1.0),
mColorG(1.0),
mColorB(1.0),
mColorA(1.0)
{
	SetString(str);
}

//--------------------------------------------------------------------------------
MLLabel::~MLLabel()
{
    for (list<MLWordInfo *>::iterator i = mWords.begin();
         i != mWords.end(); i++)
    {
        ML_DELETE( *i );
    }
	mWords.clear();
    
	mFont = nullptr;
	mU16Str.clear();
}

//--------------------------------------------------------------------------------
MLBOOL MLLabel::SetString(string str)
{
	mShowCounts = 0;
	mAllShowedOnce = MLFALSE;
	StringUtils::UTF8ToUTF16(str, mU16Str);

	PreprocessDrawString();
	
	if (!mClipArea)
	{
		//mFont->AddString(mU16Str, mWords);
		CalContentSizeNoClip();
	}
	else
	{
		mWidth = mClipWidth;
		mHeight = mClipHeight;
	}

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
// control codes:
// color control: ~[CRRGGBBAA]xxx[], ex:~[CFF00FF80]controlled words[]
MLBOOL MLLabel::Draw()
{
	MLINT x = mPosX;
	MLINT y = mPosY;

	mCurrentTime += MLSceneMgr::GetInstance()->GetDeltaTime();

	if (mWordByWordPeriod > 0.)
	{
		// calculate how many words to show
		if (mCurrentTime - mLastTime> mWordByWordPeriod)
		{
			if (mShowCounts < GetStringLength())
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
			else
			{
				mAllShowedOnce = MLTRUE;
			}
		}// end if
	}
	else
	{
		mShowCounts = GetStringLength();
	}

	// string process
	LabelStringProcessState state = LSP_NormalString;
	MLFLOAT r = mColorR;
	MLFLOAT g = mColorG;
	MLFLOAT b = mColorB;
	MLFLOAT a = mColorA;

	//MLBOOL drawsucess = MLTRUE;

	for (int showCnt = 0,  i = 0; showCnt < mShowCounts; ++ i)
	{
		char16_t currentChar = mU16Str[i];

		switch (state)
		{
		case LSP_NormalString:
		{
			if (currentChar == '~')
			{
				state = LSP_ControlSign;
			}
			else
			{
				DrawChar(currentChar, x, y, r, g, b, a);
				++ showCnt;
			}
			break;
		}// end LSP_NormalString

		case LSP_ControlSign:
		{
			if (currentChar == '[')
			{
				state = LSP_ControlStartCode;
			}
            else if (currentChar == '~')
            {
                DrawChar(currentChar, x, y, r, g, b, a);
                ++ showCnt;
                state = LSP_ControlSign;
            }
			else
			{
				state = LSP_NormalString;
				char16_t preChar = mU16Str[i-1];

				DrawChar(preChar, x, y, r, g, b, a);
				++ showCnt;

				DrawChar(currentChar, x, y, r, g, b, a);
				++ showCnt;
			}
			break;
		}// end LSP_ControlSign

		case LSP_ControlStartCode:
		{
			//process control codes
			if (currentChar == 'C')	
			{
				char *r1 = (char*)&mU16Str.c_str()[i + 1];
				char *r2 = (char*)&mU16Str.c_str()[i + 2];
				string colorR(r1);
				colorR.append(r2);

                r = MLStringUtil::StringToInt(colorR, 16)/ 255.;

				char *g1 = (char*)&mU16Str.c_str()[i + 3];
				char *g2 = (char*)&mU16Str.c_str()[i + 4];
				string colorG(g1);
				colorG.append(g2);
                g = MLStringUtil::StringToInt(colorG, 16) / 255.;
                
				char *b1 = (char*)&mU16Str.c_str()[i + 5];
				char *b2 = (char*)&mU16Str.c_str()[i + 6];
				string colorB(b1);
				colorB.append(b2);
                b = MLStringUtil::StringToInt(colorB, 16) / 255.;

				char *a1 = (char*)&mU16Str.c_str()[i + 7];
				char *a2 = (char*)&mU16Str.c_str()[i + 8];
				string colorA(a1);
				colorA.append(a2);
                a = MLStringUtil::StringToInt(colorA, 16) / 255.;
			
				i += 9;
				state = LSP_ControlledString;
			}
			else// no matched control codes
			{
				state = LSP_NormalString;

				char16_t preChar = mU16Str[i - 2];		// '~'
				DrawChar(preChar, x, y, r, g, b, a);
				++showCnt;

				preChar = mU16Str[i - 1];				// '['
				DrawChar(preChar, x, y, r, g, b, a);
				++showCnt;

				DrawChar(currentChar, x, y, r, g, b, a);
				++ showCnt;
			}
			break;
		}// end LSP_ControlStartCode

		case LSP_ControlledString:
		{
			if (mU16Str[i] == '[')
			{
				state = LSP_ControlEndCode;
			}
			else
			{
				DrawChar(currentChar, x, y, r, g, b, a);
				++ showCnt;
			}
			break;
		}// end LSP_ControlledString

		case LSP_ControlEndCode:
		{
			if (mU16Str.c_str()[i] != ']')
			{
				state = LSP_ControlledString;
				char16_t preChar = mU16Str[i - 1];			// '['
				DrawChar(preChar, x, y, r, g, b, a);
				++ showCnt;

				DrawChar(currentChar, x, y, r, g, b, a);
				++ showCnt;
			}
			else
			{
				r = mColorR;
				g = mColorG;
				b = mColorB;
				a = mColorA;
				state = LSP_NormalString;
			}
			break;
		}// end LSP_ControlEndCode

		default:
		{
			break;
		}

		}// end switch

	}// End for

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
void MLLabel::CalContentSizeNoClip()
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

	for (int i = 0, j = 0; j < GetStringLength(); ++i)
	{
		// align with first line
		if (mU16Str[i] == newLine)
		{
			mHeight += (mFont->GetFontSize() + mLineSpacing);
			if (mWidth < tmpWidth)
			{
				mWidth = tmpWidth;
				tmpWidth = 0;
				//mLineCount++;	// maybe check is next char exist
			}
			++j;
		}
		else if (mU16Str[i] == whiteSpace)
		{
			tmpWidth += ((int)mFont->GetFontSize() / 2 + mWordSpacing);
			++j;
		}
		else
		{
			MLWordInfo *w = mFont->GetAtlasTexture(mU16Str[i]);
			if (w)
			{
				tmpWidth += w->w + mWordSpacing;
				++j;
			}
		}
	}// end for

	if (mWidth < tmpWidth)
	{
		mWidth = tmpWidth;
	}
	
}

//--------------------------------------------------------------------------------
MLINT MLLabel::GetLabelWidth()
{
	if (mClipArea)
		return mClipWidth;
	else
		return mWidth;
}

//--------------------------------------------------------------------------------
MLINT MLLabel::GetLabelHeight()
{
	if (mClipArea)
		return mClipHeight;
	else
		return mHeight;
}

//--------------------------------------------------------------------------------
MLINT MLLabel::GetStringLength()
{
	return mDrawStringLength;
}

//--------------------------------------------------------------------------------
void MLLabel::PreprocessDrawString()
{
	MLINT length = 0;

	int i = 0;
	LabelStringProcessState state = LSP_NormalString;
    
    // clear old words info
    for (list<MLWordInfo *>::iterator i = mWords.begin();
         i != mWords.end(); i++)
    {
        ML_DELETE( *i );
    }
    mWords.clear();
    
    bool hasColorcode = false;

	while (i < mU16Str.length())
	{
		switch (state)
		{
		case LSP_NormalString:
		{
			if (mU16Str[i] == '~')
			{
				state = LSP_ControlSign;
			}
			else
			{
				++length;
			}
			break;
		}

		case LSP_ControlSign:
		{
			if (mU16Str[i] == '[')
			{
				state = LSP_ControlStartCode;
			}
            else if (mU16Str[i] == '~')
            {
                state = LSP_ControlSign;
                length += 1;
            }
			else
			{
				state = LSP_NormalString;
				length += 2;				// '~' and current char
			}
			break;
		}

		case LSP_ControlStartCode:
		{
			if (mU16Str[i] == 'C')	//skip color control code
			{
				i += 9;						//'CRRGGBBAA]'
				state = LSP_ControlledString;
                hasColorcode = true;
			}
			else if (mU16Str[i] == 'W')//skip orhter control code
            {
                char *w1 = (char*)&mU16Str.c_str()[i + 1];
                char *w2 = (char*)&mU16Str.c_str()[i + 2];
                
                string idxstr(w1);
                idxstr.append(w2);
                int idx = MLStringUtil::StringToInt(idxstr, 16);
             
                u16string specialWordU16;
                StringUtils::UTF8ToUTF16(MLFontMgr::GetInstance()->GetSpecialWord(idx), specialWordU16);
                
                mU16Str.erase(i-2, 6); // '~[W01]'
                mU16Str.insert(i-2, specialWordU16);
                length += specialWordU16.length();
                
                i = (i-2 )+ specialWordU16.length() - 1; // starting from 0
                
                if(hasColorcode)
                {
                    state = LSP_ControlledString;
                }
                else
                {
                    state = LSP_NormalString;
                }
            }
            else// no matched control codes
			{
				state = LSP_NormalString;
				length += 2; //'~['
				++length;
			}
			break;
		}

		case LSP_ControlledString:
		{
			if (mU16Str[i] == '[')
			{
				state = LSP_ControlEndCode;
			}
            else if (mU16Str[i] == '~')
            {
                state = LSP_ControlSign;
            }
			else
			{
				++length;
			}
			break;
		}

		case LSP_ControlEndCode:
		{
			if (mU16Str[i] != ']')
			{
				state = LSP_ControlledString;
				length += 2;				// '[' and current char
                hasColorcode = false;
			}
			else
			{
				state = LSP_NormalString;
			}
			break;
		}
		default:
			break;
		}// end switch
		++i;
	}// end while

	mDrawStringLength = length;
}

//--------------------------------------------------------------------------------
void MLLabel::DrawChar(char16_t &currentChar, MLINT &x, MLINT &y, MLFLOAT &r, MLFLOAT &g, MLFLOAT &b, MLFLOAT &a)
{
	// special character handlings
	if (currentChar == '\n')
	{
		y -= (mFont->GetFontSize() + mLineSpacing);		// next line is in revert direction
		x = mPosX;
		return;
	}

	if (currentChar == ' ')
	{
		x += (mFont->GetFontSize() / 2 + mWordSpacing);
		return;
	}

    //mFont->AddChar(currentChar);
	MLWordInfo *w = mFont->GetAtlasTexture(currentChar);
	if (w == nullptr)
	{
		return;
	}

	if (mClipArea)
	{
		if (w->w + x - mPosX > mClipWidth)// should draw in next line
		{
			y -= (mFont->GetFontSize() + mLineSpacing);	// next line is in revert direction
			x = mPosX;
		}
		if (y - w->h < mPosY - mClipHeight)// should draw in next line
		{
			//y -= (mFont->GetCellHeight() + mLineSpacing);	// next line is in revert direction
			//x = mPosX;
			return;
		}
	}

	GLfloat coords[] =
	{
		static_cast<GLfloat>(w->u / MLMaxFontTextureSize), static_cast<GLfloat>((w->v + w->h) / MLMaxFontTextureSize),			//1
		static_cast<GLfloat>((w->u + w->w) / MLMaxFontTextureSize), static_cast<GLfloat>((w->v + w->h) / MLMaxFontTextureSize), //2
		static_cast<GLfloat>(w->u / MLMaxFontTextureSize), static_cast<GLfloat>(w->v / MLMaxFontTextureSize),					//3
		static_cast<GLfloat>((w->u + w->w) / MLMaxFontTextureSize), static_cast<GLfloat>(w->v / MLMaxFontTextureSize),			//4
	};

	int x1 = x + w->horiBearingX;
	int y1 = y - w->ascender + w->horiBearingY;
	GLfloat verts[] =
	{
		static_cast<GLfloat>(x1), static_cast<GLfloat>(y1),				//1
		static_cast<GLfloat>(x1 + w->w), static_cast<GLfloat>(y1),		//2
		static_cast<GLfloat>(x1), static_cast<GLfloat>(y1 + w->h),		//3
		static_cast<GLfloat>(x1 + w->w), static_cast<GLfloat>(y1 + w->h),	//4
	};
	

	GLfloat colors[] =
	{
		1., 1., 1., 1.,	//1
		1., 1., 1., 1.,	//2
		1., 1., 1., 1.,	//3
		1., 1., 1., 1.,	//4
	};

	GLProgram* sg = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_LABEL_NORMAL);
	sg->use();
	sg->setUniformsForBuiltins();

	GL::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLuint _uniformTextColor = glGetUniformLocation(sg->getProgram(), "u_textColor");
	sg->setUniformLocationWith4f(_uniformTextColor, r, g, b, a);

	GL::bindTexture2D(mFont->GetTextrue(w->texIdx)->getName());

	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, verts);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, coords);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, colors);

	Director* director = Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	Mat4 myid;
	myid.setIdentity();
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, myid);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	x += w->horiAdvance + mWordSpacing;
}

//--------------------------------------------------------------------------------
MLBOOL MLLabel::IsAllShowed()
{
	return mAllShowedOnce;
}

//--------------------------------------------------------------------------------
void MLLabel::SetAllShowed(MLBOOL showed)
{
	mAllShowedOnce = showed;
	if (mAllShowedOnce)
	{
		mShowCounts = GetStringLength();
	}
	else
	{
		mShowCounts = 0;
	}
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
void MLLabel::SetFont(MLTTFFont *fnt)
{
	if (fnt)
	{
		mFont = fnt;
	}
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