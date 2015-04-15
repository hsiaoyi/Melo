//--------------------------------------------------------------------------------
//	File		: MLTTFFont.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#include "MLTTFFont.h"
#include "base\ccUTF8.h"


//--------------------------------------------------------------------------------
MLBOOL MLTTFFont::InitFont(FT_Library lib)
{
	if (!InitFreeType(lib))
	{
		return MLFALSE;
	}

	// class structure construction
	/*
	mCellW = mFace->size->metrics.max_advance >> 6;
	mCellH = mFace->size->metrics.height >> 6;
	*/

	// test code here
	//int ww = mFace->size->metrics.max_advance >> 6;
	//int hh = mFace->size->metrics.height >> 6;

	mCellW = mFontSize;
	mCellH = mFontSize;

	mGlyphsPerRow = MLMaxFontTextureSize / mCellW;
	mGlyphsPerCol = MLMaxFontTextureSize / mCellH;

	mTexData[0] = ML_NEW unsigned char[MLMaxFontTextureSize * MLMaxFontTextureSize * MLFontTextureDepth];
	memset(mTexData[0], 0x00, MLMaxFontTextureSize * MLMaxFontTextureSize *MLFontTextureDepth);

	// test code for coloring texture debugging
	/*
	unsigned char * currData = (unsigned char*)&mTexData[0][(0 * MLMaxFontTextureSize + 0) * MLFontTextureDepth];
	for (int jj = 0; jj < 256; ++jj)
	{
		int col=0;

		if (jj > 192)
		{
			col = 192;
		}
		else if (jj > 128)
		{
			col = 128;
		}
		else if (jj > 64)
		{
			col = 64;
		}
		else
		{
			col = 0;
		}

		//currData = pStart + jj * mTextures[0]->getPixelsWide() * MLFontTextureDepth;
		for (int ii = 0; ii < 256; ++ii)
		{
			int col2 = 0;

			if (ii > 192)
			{
				col2 = 192;
			}
			else if (ii > 128)
			{
				col2 = 128;
			}
			else if (ii > 64)
			{
				col2 = 64;
			}
			else
			{
				col2 = 0;
			}


			currData[0] = col;
			currData[1] = col2;
			currData[2] = 0;
			currData[3] = 1;

			currData += 4;
		}
	}
	*/

	mTextures[0] = new Texture2D();
	//mTextures[0] = Director::getInstance()->getTextureCache()->addImage("red.png");
	mTextures[0]->initWithData(mTexData[0], MLMaxFontTextureSize * MLMaxFontTextureSize * MLFontTextureDepth, Texture2D::PixelFormat::RGBA8888,
		MLMaxFontTextureSize, MLMaxFontTextureSize, Size(MLMaxFontTextureSize, MLMaxFontTextureSize));

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLBOOL MLTTFFont::InitFreeType(FT_Library lib)
{
	FT_Error error;

	error = FT_New_Face(lib, mFontName.c_str(), 0, &mFace);
	error = FT_Set_Char_Size(mFace, (mFontSize << 6), (mFontSize << 6), MLFontDpi, MLFontDpi);
	error = FT_Select_Charmap(mFace, FT_ENCODING_UNICODE);

	if(error)
	{
		return MLFALSE;
	}
	else
	{
		return MLTRUE;
	}
}

//--------------------------------------------------------------------------------
void MLTTFFont::AddString(u16string u16str, list<MLWordInfo *> infoList)
{
	int num = u16str.length();

	for (int i = 0; i < num; ++i)
	{		
		map<char16_t, MLWordInfo *>::iterator it = mWords.find(u16str.c_str()[i]);
		if (it == mWords.end())
		{
			MLINT u;
			MLINT v;
			MLINT w;
			MLINT h;
			GetCellInfo(&u, &v, &w, &h);			
			
			MLWordInfo *info = ML_NEW MLWordInfo(u, v, 0);
			infoList.push_back(info);
			GenAtlasTextureByIndex(u16str.c_str()[i], info);

			pair<char16_t, MLWordInfo *> p = make_pair(u16str.c_str()[i], info);
			mWords.insert(p);

		}
		else
		{
			infoList.push_back(it->second);
		}
	}

	mTextures[0]->updateWithData(mTexData[0], 0, 0, MLMaxFontTextureSize, MLMaxFontTextureSize);

}

//--------------------------------------------------------------------------------
MLBOOL MLTTFFont::GetCellInfo(MLINT *u, MLINT *v, MLINT *w, MLINT *h)
{
	MLINT idx = mCurrentIdx;

	if (idx == 0)
	{
		*u = 1;
		*v = 1;
	}
	else
	{
		*u = (idx % mGlyphsPerRow) * mCellW + 1;
		*v = (idx / mGlyphsPerCol) * mCellH + 1;
	}

	*w = mCellW;
	*h = mCellH;

	idx++;
	if (idx >= mGlyphsPerRow * mGlyphsPerCol)
	{
		idx -= mGlyphsPerRow * mGlyphsPerCol;
	}
	mCurrentIdx = idx;

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLBOOL MLTTFFont::GenAtlasTextureByIndex(char16_t c, MLWordInfo *info)
{
	int xOffset = info->u;	// cell for this atlas image
	int yOffset = info->v;

	int idx = FT_Get_Char_Index(mFace, c);

	FT_Error err;

	err = FT_Load_Glyph(mFace, idx, FT_LOAD_RENDER | FT_LOAD_NO_AUTOHINT);	// load glyph images into glyph slots			
	FT_Render_Glyph(mFace->glyph, FT_RENDER_MODE_NORMAL);	// convert glyph image into bitmap

	int glyphW = mFace->glyph->bitmap.width;
	int glyphH = mFace->glyph->bitmap.rows;
	
	unsigned char * currData = (unsigned char*)&mTexData[0][(yOffset * mTextures[0]->getPixelsWide() + xOffset) * MLFontTextureDepth];

	int startX = (mFace->glyph->metrics.horiBearingX >> 6);
	int startY = (mFace->size->metrics.ascender >> 6) - (mFace->glyph->metrics.horiBearingY >> 6);

	currData += (startY * mTextures[0]->getPixelsWide() + startX) * 4;	// for font alignment
	unsigned char *pStart = currData;	
	
	for (int j = 0; j < glyphH; ++j)
	{
		currData = pStart + j * mTextures[0]->getPixelsWide() * MLFontTextureDepth;
		for (int i = 0; i < glyphW; ++i)
		{
			currData[0] = mFace->glyph->bitmap.buffer[j * mFace->glyph->bitmap.width + i];
			currData[1] = mFace->glyph->bitmap.buffer[j * mFace->glyph->bitmap.width + i];
			currData[2] = mFace->glyph->bitmap.buffer[j * mFace->glyph->bitmap.width + i];
			currData[3] = mFace->glyph->bitmap.buffer[j * mFace->glyph->bitmap.width + i];

			currData += 4;
		}
	}
	

	info->w = glyphW;
	info->h = mCellH;
	info->u = xOffset + startX;
	info->v = yOffset;
	
	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLWordInfo *MLTTFFont::GetAtlasTexture(char16_t c)
{
	map<char16_t, MLWordInfo *>::iterator it = mWords.find(c);
	if (it == mWords.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}