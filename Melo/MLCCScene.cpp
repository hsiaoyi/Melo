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
//#include "MLSprite.h"

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

	/*
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
										   CC_CALLBACK_1(MLCCScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
	*/

    // create menu, it's an autorelease object
	/*
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);
	*/

	// initial MLSceneMgr, need put here (after cocos initial finished)
	MLSceneMgr::GetInstance()->Init();

	// construct test scene
	layer =  MLSceneMgr::GetInstance()->AddLayer(NULL, &MLCCScene::MyUpdate, NULL);
	//layer = MLSceneMgr::GetInstance()->AddLayer();

	sp1id = MLSceneMgr::GetInstance()->AddSprite(layer, "background.png");

	btn1id = MLSceneMgr::GetInstance()->AddSprite(layer, "CloseNormal.png");
	btn1 = MLSceneMgr::GetInstance()->GetSprite(layer, btn1id);
	btn1->SetPosition(origin.x + visibleSize.width - btn1->GetWidth(), 0);	//sprite origin is down-left corner
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

