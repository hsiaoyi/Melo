//--------------------------------------------------------------------------------
//	File		: MLFontMgr.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#include "MLFontMgr.h"
//#include "base\ccUTF8.h"
//#include <cstdlib>

MLFontMgr * MLFontMgr::mInstance = nullptr;

//--------------------------------------------------------------------------------
MLBOOL MLFontMgr::Init()
{
	// init free type 2
	if(FT_Init_FreeType(&mLibrary))
	{
		return MLFALSE;	// failed
	}

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLBOOL MLFontMgr::Release()
{
	//FT_Done_Face(mFaces);
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
MLTTFFont* MLFontMgr::CreateTTFFont(string fontName, int fontSize)
{
	string idxName = GenFontIndexName(fontName, fontSize);
	map<string, MLTTFFont*>::iterator it = mFonts.find(idxName);

	if (it != mFonts.end())
	{
		return it->second;
	}

	MLTTFFont *fnt = ML_NEW MLTTFFont(fontName, fontSize);
	pair<string, MLTTFFont*> p = make_pair(idxName, fnt);
	mFonts.insert(p);

	MLBOOL ret =  fnt->InitFont(mLibrary);

	if (ret)
	{
		return fnt;
	}
	else
	{
		return nullptr;
	}


}

//--------------------------------------------------------------------------------
MLTTFFont* MLFontMgr::GeTTFFont(string fontName, int fontSize)
{
	string idxName = GenFontIndexName(fontName, fontSize);
	map<string, MLTTFFont*>::iterator it = mFonts.find(idxName);

	if (it == mFonts.end())
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

//--------------------------------------------------------------------------------
string MLFontMgr::GenFontIndexName(string fontName, MLINT size)
{
	std::stringstream str;
	str << fontName << "_" << size;

	return str.str();
}

//--------------------------------------------------------------------------------
//MLBOOL MLFontMgr::CreateWithString(MLFontConfig cfg, std::string str)
/*
MLBOOL MLFontMgr::CreateWithString(MLFontConfig cfg, std::string str, cocos2d::Texture2D *testTex)
{
	if (mLibrary)
	{
		FT_Error error;

		error = FT_New_Face(mLibrary, cfg.mFontName.c_str(), 0, &mFaces);
		error = FT_Set_Char_Size(mFaces, 64.f * cfg.mSize, 64.f * cfg.mSize, mDpi, mDpi);
		error = FT_Select_Charmap(mFaces, FT_ENCODING_UNICODE);

		int xOffset = 0;
		int yOffset = 5;

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

			FT_Load_Glyph(mFaces, idx, FT_LOAD_RENDER | FT_LOAD_NO_AUTOHINT);//load glyph images into glyph slots			
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
				currData = pStart + j * testTex->getPixelsWide() * 4;
				for (int i = 0; i < mFaces->glyph->bitmap.width; ++i)
				{	
					currData[0] = mFaces->glyph->bitmap.buffer[j * mFaces->glyph->bitmap.width + i];
					currData[1] = mFaces->glyph->bitmap.buffer[j * mFaces->glyph->bitmap.width + i];
					currData[2] = mFaces->glyph->bitmap.buffer[j * mFaces->glyph->bitmap.width + i];					
					currData[3] = 255;
					
					currData += 4;
				}// end for
			}// end for

			// ok code here			
			//xOffset =  xOffset + padding + glyphW;
			
			//xOffset = xOffset + glyphW + (mFaces->glyph->advance.x>>6);
			//
			//if (xOffset > testTex->getPixelsWide())
			//{
			//	xOffset = 0;
			//	//yOffset = yOffset + glyphH + padding;
			//	yOffset = yOffset + glyphH + (mFaces->glyph->advance.y >> 6);
			//}
			
			xOffset += (mFaces->glyph->advance.x >> 6);		
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
*/
