//--------------------------------------------------------------------------------
//	File		: MDGameScene.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
// MeloDemo includes
#include "MDGameScene.h"

// Melo Engine include
#include "MLSceneMgr.h"
#include "MLScriptMgr.h"
#include "MDLuaWrapper.h"
#include "MLFontMgr.h"
#include "MLLabel.h"
#include "MLInputMgr.h"
#include "MLMath.h"

bool MDGameScene::mLoadScene = false;
MDGameScene* MDGameScene::mIns = nullptr;
//--------------------------------------------------------------------------------
Scene* MDGameScene::createScene()
{
    auto scene = Scene::create();
	auto layer = MDGameScene::create();

    scene->addChild(layer, 0, "MDGameScene");

	return scene;
}
#include "platform/CCFileUtils.h"
//--------------------------------------------------------------------------------
bool MDGameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//------------------------
	// scene tests
	//------------------------
	mId = MLSceneMgr::GetInstance()->AddLayer(NULL, &MDGameScene::MyUpdate, NULL);
	mTitlePosX = origin.x + visibleSize.width / 2 - 30;
	mTitlePosY = origin.y + visibleSize.height - 30;

	mIns = this;
    
    return true;
}

//--------------------------------------------------------------------------------
void MDGameScene::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	MLSceneMgr::GetInstance()->Draw();
}

//--------------------------------------------------------------------------------
void MDGameScene::MyUpdate()
{
	if(!mLoadScene)
	{
        MLScriptMgr::GetInstance()->LoadFile(FileUtils::getInstance()->fullPathForFilename("mdstart.lua").c_str());
		// register c funcitons for lua call, defined in MDLuaWrapper
		MLScriptMgr::GetInstance()->RegisterCFunctionForLua("InitDemoScene", InitDemoScene);
		MLScriptMgr::GetInstance()->RegisterCFunctionForLua("SetGameBG", SetGameBG);
		MLScriptMgr::GetInstance()->RegisterCFunctionForLua("SetTitleFont", SetTitleFont);
		MLScriptMgr::GetInstance()->RegisterCFunctionForLua("SetTitleText", SetTitleText);
		MLScriptMgr::GetInstance()->RegisterCFunctionForLua("SetTileTextWordByWordEffect", SetTileTextWordByWordEffect);
		MLScriptMgr::GetInstance()->RegisterCFunctionForLua("SetTitleTextAlignWin", SetTitleTextAlignWin);
		MLScriptMgr::GetInstance()->RegisterCFunctionForLua("SetGameBGAlignWin", SetGameBGAlignWin);

		MLScriptMgr::GetInstance()->Resume();
		mLoadScene = true;
	}
	else
	{
		mIns->Test();
	}

}

//--------------------------------------------------------------------------------
MLSpriteId MDGameScene::SetBG(const std::string &file)
{
	mBGid = MLSceneMgr::GetInstance()->AddSprite(mId, file);	

	if (MLSceneMgr::GetInstance()->GetSprite(mId, mBGid) == nullptr)
	{
		mBGid = MLSceneMgr::GetInstance()->AddSprite(mId, file);
	}
		
	return mBGid;
}

//--------------------------------------------------------------------------------
MLBOOL MDGameScene::SetTitleFontTTF(const std::string &font, const int size)
{
	mTitleFont = MLFontMgr::GetInstance()->CreateTTFFont(font, size);

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLBOOL MDGameScene::SetTitle(const std::string &text)
{
	mTitleId = MLSceneMgr::GetInstance()->AddLabel(mId, mTitleFont, text, mTitlePosX, mTitlePosY);

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLBOOL MDGameScene::SetTitleEffectParams(MLDOUBLE period, MLDOUBLE delay, MLBOOL repeat)
{
	MLLabel *lb = MLSceneMgr::GetInstance()->GetLabel(mId, mTitleId);
	lb->SetWordByWordEffectParams(period, delay, repeat);

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLBOOL MDGameScene::SetTitleAlignWin(int hori, int vert)
{
	MLLabel *lb = MLSceneMgr::GetInstance()->GetLabel(mId, mTitleId);
	lb->SetLabelAlignWin((MLAlignH)hori, (MLAlignV)vert);

	return MLTRUE;
}

//--------------------------------------------------------------------------------
MLBOOL MDGameScene::SetBGAlignWin(int hori, int vert)
{
	MLSprite *sp = MLSceneMgr::GetInstance()->GetSprite(mId, mBGid);
	sp->SetAlignWin((MLAlignH)hori, (MLAlignV)vert);

	return MLTRUE;
}

void MDGameScene::Test()
{
	MLSprite *sp = MLSceneMgr::GetInstance()->GetSprite(mId, mBGid);
	
	if (sp->IsSelected())
	{
		//MLLOG("BG Selected");
		MLVec2 pos(MLInputMgr::GetInstance()->GetPosX(), MLInputMgr::GetInstance()->GetPosY());
		MLMath::ScreenToWorld(pos);
		sp->SetPosition(pos.x - sp->GetWidth() / 2, pos.y - sp->GetHeight() / 2);
	}
	else
	{
		//MLLOG("---");
	}
}