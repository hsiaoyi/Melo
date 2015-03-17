//--------------------------------------------------------------------------------
//	File		: MLCCScene.cpp
//	Description	:
//	Author		: Chang, Hsiao-Yi
//
//	Copyright (c) 2014-2015. All rights reserved.
//	https://github.com/hsiaoyi/Melo
//--------------------------------------------------------------------------------
#include "MLCCScene.h"
#include "MLSceneMgr.h"
#include "MLScriptMgr.h"
#include "MLLuaTestFunc.h"
#include "MLFontMgr.h"

MLLayerId layer;
MLSpriteId sp1id;
MLSpriteId btn1id;
MLSprite* btn1;

//--------------------------------------------------------------------------------
Scene* MLCCScene::createScene()
{
    auto scene = Scene::create();
	auto layer = MLCCScene::create();

    scene->addChild(layer);

	return scene;
}

//--------------------------------------------------------------------------------
bool MLCCScene::init()
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
	layer =  MLSceneMgr::GetInstance()->AddLayer(NULL, &MLCCScene::MyUpdate, NULL);

	//sp1id = MLSceneMgr::GetInstance()->AddSprite(layer, "background.png");
	
	btn1id = MLSceneMgr::GetInstance()->AddSprite(layer, "CloseNormal.png");
	btn1 = MLSceneMgr::GetInstance()->GetSprite(layer, btn1id);
	btn1->SetPosition(origin.x + visibleSize.width - btn1->GetWidth(), 0);	//sprite origin is down-left corner
	
	//------------------------
	// font tests
	//------------------------

	// create label texture first //0309
	/*
	cocos2d::Texture2D *testTex = cocos2d::Director::getInstance()->getTextureCache()->addImage("red.png");
	
	Sprite* ts = Sprite::createWithTexture(testTex);
	ts->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - ts->getContentSize().height/2));
	this->addChild(ts, 1);
	*/

	/*
	unsigned char* buff = new unsigned char[testTex->getPixelsWide() * testTex->getPixelsHigh()*4];
	memset(buff, 128, testTex->getPixelsWide() * testTex->getPixelsHigh()*4);
	testTex->updateWithData(buff, 0, 0, testTex->getPixelsWide(), testTex->getPixelsHigh());
	*/

		// cynthia test ok code
	/*
	unsigned char* buff = new unsigned char[64 * 64 * 4];
	memset(buff, 128, 64 * 64 * 4);
	testTex->updateWithData(buff, 30, 30, 64,64);	
	*/


	// read strings from xml file
	auto strings = FileUtils::getInstance()->getValueMapFromFile("MeloTestStrings.xml");
	std::string chstr = strings["chstr1"].asString();

	//MLLOG("---[%s]----", chstr.c_str());

	MLFontConfig *cfg = ML_NEW MLFontConfig("fonts/TestFont1.ttf", 26, ML_FT_TTF);
	//MLFontConfig *cfg = ML_NEW MLFontConfig("fonts/Marker Felt.ttf", 18, ML_FT_TTF);
	//MLFontMgr::GetInstance()->CreateWithString(*cfg, "my eng test string");
	//MLFontMgr::GetInstance()->CreateWithString(*cfg, chstr, testTex);

	testTex = new cocos2d::Texture2D();
	// ok
	testTex = Director::getInstance()->getTextureCache()->addImage("red.png");
	MLFontMgr::GetInstance()->CreateWithString(*cfg, chstr, testTex);

	/*
	Sprite* ts = Sprite::createWithTexture(testTex);
	//ts->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - ts->getContentSize().height / 2));
	//ts->setColor(Color3B::GREEN);
	addChild(ts); 
	*/

	// ok code for cocos label
	/*
	TTFConfig ttfcfg("fonts/TestFont1.ttf", 24);
	auto label = Label::createWithTTF(ttfcfg, chstr);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);
	*/
	

	//------------------------
	// script tests
	//------------------------
	MLScriptMgr::GetInstance()->LoadFile("melotest.lua");
	MLScriptMgr::GetInstance()->RegisterCFunctionForLua("MeloLuaTest1", LuaTestFunction1);
	MLScriptMgr::GetInstance()->RegisterCFunctionForLua("MeloLuaTest2", LuaTestFunction2);

	MLScriptMgr::GetInstance()->Resume();

	//MLScriptMgr::GetInstance()->CallLuaFunction2("MeloLua1");
	char* test = "yi test string\0";
	//MLScriptMgr::GetInstance()->CallLuaFunction("MeloLua2", "yi test string");//MeloLua2 ok
	
	//MLScriptMgr::GetInstance()->CallLuaFunction("MeloLua2", test);//MeloLua2
	//MLLOG("---[LUA2]---:%s", test);

	// test for call function
	int i1 = 3;
	double d1 = 2.7;
	char *str = "Melo call test string";
	bool b1 = false;
	double res;
	// test for generic call fuction
	MLScriptMgr::GetInstance()->CallLuaFunction("MeloCallTest", "idbs>d", i1, d1, b1, str, &res);
	MLLOG("CallTest:res is [%f]", res);
	// end test for call funciton

	//bool b2;
	//MLScriptMgr::GetInstance()->CallLuaFunction("MeloCallTest2", "ddbs>b", i1, d1, b1, str, &b2);
	//MLLOG("CallTest:res is [%d]", (int)b2);

    return true;
}

//--------------------------------------------------------------------------------
void MLCCScene::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	//MLLOG("---MLCCScene DRAW---");
	MLSceneMgr::GetInstance()->Draw();	
	testTex->drawAtPoint(Vec2(0, 0));
}

//--------------------------------------------------------------------------------
/*
void MLCCScene::onEnter()
{

}
*/

//--------------------------------------------------------------------------------
void MLCCScene::MyUpdate()
{
	//MLLOG("---MECCScene UPDATE---");
	/*
	if (btn1->GetXPosition() >  MLSceneMgr::GetInstance()->GetSprite(layer, sp1id)->GetWidth() / 2)
	{
		MLFLOAT xx = btn1->GetXPosition() - 2.0;
		btn1->SetPosition(xx, 0.0);
	}
	*/
	//MLScriptMgr::GetInstance()->Pause();
}


//--------------------------------------------------------------------------------
//void MLCCScene::menuCloseCallback(Ref* pSender)
//{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//  return;
//#endif
//
//  Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//}

