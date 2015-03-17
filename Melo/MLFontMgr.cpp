//--------------------------------------------------------------------------------
//	File		: MLFontMgr.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#include "MLFontMgr.h"
#include "base\ccUTF8.h"
#include <cstdlib>

USING_NS_CC;

MLFontMgr * MLFontMgr::mInstance = nullptr;

//--------------------------------------------------------------------------------
MLBOOL MLFontMgr::Init()
{
	// init free type 2
	if(FT_Init_FreeType(&mLibrary))
	{
		return MLFALSE;	// failed
	}
	mDpi = 72;
	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLBOOL MLFontMgr::Release()
{
	FT_Done_Face(mFaces);
	FT_Done_FreeType(mLibrary);
	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLFontMgr *MLFontMgr::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = ML_NEW MLFontMgr;
	}
	return mInstance;
}

//--------------------------------------------------------------------------------
//MLBOOL MLFontMgr::CreateWithString(MLFontConfig cfg, std::string str)
MLBOOL MLFontMgr::CreateWithString(MLFontConfig cfg, std::string str, cocos2d::Texture2D *testTex)
{
	if (mLibrary)
	{
		FT_New_Face(mLibrary, cfg.mFontName.c_str(), 0, &mFaces);
		FT_Set_Char_Size(mFaces, 64.f * cfg.mSize, 64.f * cfg.mSize, mDpi, mDpi);
		FT_Select_Charmap(mFaces, FT_ENCODING_UNICODE);

		int xOffset = 0;
		int yOffset = 0;
		const int padding = 5;

		std::u16string utf16;
		StringUtils::UTF8ToUTF16(str, utf16);
		 
		unsigned char* texData = new unsigned char[testTex->getPixelsWide()* testTex->getPixelsHigh() * 4];
		memset(texData, 0x0F, testTex->getPixelsWide()* testTex->getPixelsHigh() * 4);
		int num = utf16.length();
		//int num = 1;

		unsigned idx;
		unsigned preIdx;

		for (int i = 0; i < num; ++i)
		{
			idx = FT_Get_Char_Index(mFaces, utf16.c_str()[i]);

			FT_Load_Glyph(mFaces, idx, FT_LOAD_RENDER | FT_LOAD_NO_AUTOHINT);//laod glyph images into glyph slots			
			FT_Render_Glyph(mFaces->glyph, FT_RENDER_MODE_NORMAL);// convert glyph image into bitmap

			int glyphW = mFaces->glyph->bitmap.width;
			int glyphH = mFaces->glyph->bitmap.rows;

			unsigned char * currData = (unsigned char*)&texData[(yOffset * testTex->getPixelsWide() + xOffset) * 4];

			int startPosX = (mFaces->glyph->metrics.horiBearingX >> 6);
			int startPosY = (mFaces->size->metrics.ascender >> 6) - (mFaces->glyph->metrics.horiBearingY >> 6);

			currData += (startPosY * testTex->getPixelsWide() + startPosX) * 4;
			unsigned char *pStart = currData;

			for (int j = 0; j < mFaces->glyph->bitmap.rows; ++j)
			{
				for (int i = 0; i < mFaces->glyph->bitmap.width; ++i)
				{	
					currData[0] = mFaces->glyph->bitmap.buffer[j * mFaces->glyph->bitmap.width + i];
					currData[1] = mFaces->glyph->bitmap.buffer[j * mFaces->glyph->bitmap.width + i];
					currData[2] = mFaces->glyph->bitmap.buffer[j * mFaces->glyph->bitmap.width + i];					
					currData[3] = 255;
					
					currData += 4;
				}// end for
				currData = pStart + j * testTex->getPixelsWide() * 4;
			}// end for

			// ok code here			
			//xOffset =  xOffset + padding + glyphW;
			/*
			xOffset = xOffset + glyphW + (mFaces->glyph->advance.x>>6);
			
			if (xOffset > testTex->getPixelsWide())
			{
				xOffset = 0;
				//yOffset = yOffset + glyphH + padding;
				yOffset = yOffset + glyphH + (mFaces->glyph->advance.y >> 6);
			}
			*/
			xOffset += (mFaces->glyph->advance.x >> 6);
			preIdx = idx;			
		}// end for (every character in string)

		int w = testTex->getPixelsWide();
		int h = testTex->getPixelsHigh();	
		testTex->updateWithData(texData, 0, 0, w, h);

		return MLTRUE;
	}
	else
	{
		return MLFALSE;
	}

}
