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
	mGlyphW = mFace->size->metrics.max_advance >> 6;
	mGlyphH = mFace->size->metrics.height >> 6;
	*/

	// test code here
	int ww = mFace->size->metrics.max_advance >> 6;
	int hh = mFace->size->metrics.height >> 6;

	mGlyphW = mFontSize;
	mGlyphH = mFontSize;

	mGlyphsPerRow = MLMaxFontTextureSize / mGlyphW;
	mGlyphsPerCol = MLMaxFontTextureSize / mGlyphH;

	mTexData[0] = ML_NEW unsigned char[MLMaxFontTextureSize * MLMaxFontTextureSize * MLFontTextureDepth];
	memset(mTexData[0], 0x77, MLMaxFontTextureSize * MLMaxFontTextureSize *MLFontTextureDepth);
	mTextures[0] = new Texture2D();
	mTextures[0] = Director::getInstance()->getTextureCache()->addImage("red.png");

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLBOOL MLTTFFont::InitFreeType(FT_Library lib)
{
	FT_Error error;

	error = FT_New_Face(lib, mFontName.c_str(), 0, &mFace);
	error = FT_Set_Char_Size(mFace, (mFontSize << 6), (mFontSize << 6), MLFontDpi, MLFontDpi);
	//FT_Set_Pixel_Sizes(mFace, mFontSize, mFontSize);
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
void MLTTFFont::AddString(string str, list<MLWordInfo *> infoList)
{
	u16string u16str;
	StringUtils::UTF8ToUTF16(str, u16str);
	int num = u16str.length();

	for (int i = 0; i < num; ++i)
	{		
		map<char16_t, MLWordInfo *>::iterator it = mWords.find(u16str.c_str()[i]);
		if (it == mWords.end())
		{
			MLINT u;
			MLINT v;
			GetAtlasInfoByIndex(mCurrentIdx, &u, &v);			
			mCurrentIdx++;
			MLWordInfo *info = ML_NEW MLWordInfo(u, v, 0);
			infoList.push_back(info);
			pair<char16_t, MLWordInfo *> p = make_pair(u16str.c_str()[i], info);
			mWords.insert(p);
			GenAtlasTextureByIndex(u16str.c_str()[i], info);
		}
		else
		{
			infoList.push_back(it->second);
		}
	}

	mTextures[0]->updateWithData(mTexData[0], 0, 0, MLMaxFontTextureSize, MLMaxFontTextureSize);

}

//--------------------------------------------------------------------------------
MLBOOL MLTTFFont::GetAtlasInfoByIndex(MLINT idx, MLINT *u, MLINT *v)
{
	if (idx == 0)
	{
		*u = 1;
		*v = 1;
		return MLTRUE;
	}

	*u = (idx % mGlyphsPerRow) * mGlyphW + 1;
	*v = (idx / mGlyphsPerCol) * mGlyphH + 1;

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLBOOL MLTTFFont::GenAtlasTextureByIndex(char16_t c, MLWordInfo *info)
{
	int xOffset = info->u;	// grid point for this glyph image
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
		currData = pStart + j * mTextures[0]->getPixelsWide() * 4;
		for (int i = 0; i < glyphW; ++i)
		{
			currData[0] = mFace->glyph->bitmap.buffer[j * mFace->glyph->bitmap.width + i];
			currData[1] = mFace->glyph->bitmap.buffer[j * mFace->glyph->bitmap.width + i];
			currData[2] = mFace->glyph->bitmap.buffer[j * mFace->glyph->bitmap.width + i];
			currData[3] = 255;//mFace->glyph->bitmap.buffer[j * mFace->glyph->bitmap.width + i];

			currData += 4;
		}
	}
	
	return MLTRUE;
}
