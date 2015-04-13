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
/*
#include "MLFontMgr.h"
#include "MLTTFFont.h"
#include "MLLabel.h"
*/

/*
MLSpriteId sp1id;
MLSpriteId btn1id;
MLSprite* btn1;
*/
// font test code
/*
MLLabelId lb1id;
MLLabel *label1;
MLTTFFont *fnt;

MLLabelId lb2id;
MLLabel *label2;
MLTTFFont *fnt2;
*/

//--------------------------------------------------------------------------------
Scene* MDGameScene::createScene()
{
    auto scene = Scene::create();
	auto layer = MDGameScene::create();

    scene->addChild(layer);

	return scene;
}

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
	mLayer = MLSceneMgr::GetInstance()->AddLayer(NULL, &MDGameScene::MyUpdate, NULL);

	MLScriptMgr::GetInstance()->LoadFile("mdstart.lua");
	MLScriptMgr::GetInstance()->RegisterCFunctionForLua("InitDemoScene", InitDemoScene);
	
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

}

//--------------------------------------------------------------------------------
void MDGameScene::SetBG(const char* file)
{
	string filePath(file);
	mBGid = MLSceneMgr::GetInstance()->AddSprite(mLayer, filePath);
}