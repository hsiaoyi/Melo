//--------------------------------------------------------------------------------
//	File		: MLTTFFont.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#include "MLTTFFont.h"
//#include "base\ccUTF8.h"
#include "ccUTF8.h"

//--------------------------------------------------------------------------------
MLBOOL MLTTFFont::InitFont(FT_Library lib)
{
	if (!InitFreeType(lib))
	{
		return MLFALSE;
	}

	mCellW = mFontSize * MLFontSizeScaleFactor + 1;
	mCellH = mFontSize * MLFontSizeScaleFactor + 1;

	mGlyphsPerRow = MLMaxFontTextureSize / mCellW;
	mGlyphsPerCol = MLMaxFontTextureSize / mCellH;

	mTexData = ML_NEW unsigned char[MLMaxFontTextureSize * MLMaxFontTextureSize * MLFontTextureDepth];
	memset(mTexData, 0, MLMaxFontTextureSize * MLMaxFontTextureSize *MLFontTextureDepth);

	// test code for coloring texture debugging
	mTextures = new Texture2D();
	mTextures->initWithData(mTexData, MLMaxFontTextureSize * MLMaxFontTextureSize * MLFontTextureDepth, Texture2D::PixelFormat::RGBA8888,
		MLMaxFontTextureSize, MLMaxFontTextureSize, Size(MLMaxFontTextureSize, MLMaxFontTextureSize));

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLTTFFont::~MLTTFFont()
{
	FT_Done_Face(mFace);
	mFontName.clear();
	for(int i = 0; i < MLMaxFontTextureUsage; ++i)
	{
		if (mTextures)
		{
			mTextures->release();
			mTextures = nullptr;
			ML_DELETE mTexData;
			mTexData = nullptr;
		}
	}

	mWords.clear();
}


//--------------------------------------------------------------------------------
MLBOOL MLTTFFont::InitFreeType(FT_Library lib)
{
	mFontData = FileUtils::getInstance()->getDataFromFile(FileUtils::getInstance()->fullPathForFilename(mFontName).c_str());
	if (mFontData.isNull())
		return MLFALSE;

	if (FT_New_Memory_Face(lib, mFontData.getBytes(), mFontData.getSize(), 0, &mFace ))
		return MLFALSE;

	if (FT_Set_Char_Size(mFace, (mFontSize << 6) * MLFontSizeScaleFactor, (mFontSize << 6) * MLFontSizeScaleFactor, MLFontDpi, MLFontDpi))
		return MLFALSE;

	if (FT_Select_Charmap(mFace, FT_ENCODING_UNICODE))
		return MLFALSE;

	return MLTRUE;
}

//--------------------------------------------------------------------------------
void MLTTFFont::AddString(u16string u16str/*, list<MLWordInfo *> infoList*/)
{
	size_t num = u16str.length();

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
			//infoList.push_back(info);
			GenAtlasTextureByIndex(u16str.c_str()[i], info);

			pair<char16_t, MLWordInfo *> p = make_pair(u16str.c_str()[i], info);
			mWords.insert(p);

		}
	}

	mTextures->updateWithData(mTexData, 0, 0, MLMaxFontTextureSize, MLMaxFontTextureSize);

}

//--------------------------------------------------------------------------------
void MLTTFFont::AddChar(char16_t c/*, list<MLWordInfo *> infoList*/)
{
	map<char16_t, MLWordInfo *>::iterator it = mWords.find(c);
	if (it == mWords.end())
	{
		MLINT u;
		MLINT v;
		MLINT w;
		MLINT h;
		GetCellInfo(&u, &v, &w, &h);

		MLWordInfo *info = ML_NEW MLWordInfo(u, v, 0);
		GenAtlasTextureByIndex(c, info);

		pair<char16_t, MLWordInfo *> p = make_pair(c, info);
		mWords.insert(p);

	}

	mTextures->updateWithData(mTexData, 0, 0, MLMaxFontTextureSize, MLMaxFontTextureSize);
}

//--------------------------------------------------------------------------------
MLBOOL MLTTFFont::GetCellInfo(MLINT *u, MLINT *v, MLINT *w, MLINT *h)
{
    ++mCurrentIdx;
    
    if (mCurrentIdx >= (mGlyphsPerRow * mGlyphsPerCol))
    {
        mCurrentIdx -= mGlyphsPerRow * mGlyphsPerCol;
    }

    MLINT idx = mCurrentIdx;
    ClearCell(mCurrentIdx);
    
	if (idx == 0)
	{
		*u = 0;
		*v = 0;
	}
	else
	{
		*u = (idx % mGlyphsPerRow) * mCellW;
		*v = (idx / mGlyphsPerCol) * mCellH;
	}

	*w = mCellW;
	*h = mCellH;
    
	return MLTRUE;
}

//--------------------------------------------------------------------------------
void MLTTFFont::ClearCell(MLINT idx)
{
    MLINT u = (idx % mGlyphsPerRow) * mCellW;
    MLINT v = (idx / mGlyphsPerCol) * mCellH;
    
    unsigned char * currData = (unsigned char*)&mTexData[(v * mTextures->getPixelsWide() + u) * MLFontTextureDepth];
    
    unsigned char *pStart = currData;
    
    for (int j = 0; j < mCellH; ++j)
    {
        currData = pStart + j * mTextures->getPixelsWide() * MLFontTextureDepth;
        for (int i = 0; i < mCellW; ++i)
        {
            memset(currData, 0, MLFontTextureDepth);
            currData += 4;
        }
    }
    
    map<char16_t, MLWordInfo *>::iterator it = mWords.begin();
    while(it != mWords.end())
    {
        if((it->second->u == u) && (it->second->v == v))
        {
            mWords.erase(it);
            break;
        }
        ++it;
    }
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
    
    if(glyphW > mCellW)
    {
        glyphW = mCellW;
    }
    if(glyphH > mCellH)
    {
        glyphH = mCellH;
    }
	
	unsigned char * currData = (unsigned char*)&mTexData[(yOffset * mTextures->getPixelsWide() + xOffset) * MLFontTextureDepth];

	int startX = 0;
	int startY = 0;

	currData += (startY * mTextures->getPixelsWide() + startX) * 4;	// for font alignment
	unsigned char *pStart = currData;
	for (int j = 0; j < glyphH; ++j)
	{
		currData = pStart + j * mTextures->getPixelsWide() * MLFontTextureDepth;
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
	info->h = GetFontSize();
    info->u = xOffset + startX;
	info->v = yOffset;
	info->horiBearingX = (static_cast<MLINT>(mFace->glyph->metrics.horiBearingX >> 6));
	info->horiBearingY = (static_cast<MLINT>(mFace->glyph->metrics.horiBearingY >> 6));
	info->ascender = (static_cast<MLINT>(mFace->size->metrics.ascender >> 6));
	info->horiAdvance = (static_cast<MLINT>(mFace->glyph->metrics.horiAdvance >> 6));

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLWordInfo *MLTTFFont::GetAtlasTexture(char16_t c)
{
	map<char16_t, MLWordInfo *>::iterator it = mWords.find(c);
	if (it == mWords.end())
	{
        AddChar(c);
		return mWords.find(c)->second;
	}
	else
	{
        return it->second;
	}
}