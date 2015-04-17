ctr = 1

if ctr == 1 then
	SetGameBG("Demo/background.png");
	--SetGameBG("Demo/helloworld.png");
	
	SetTitleFont("fonts/NotoSansCJKtc-Light.otf", 24);
	SetTitleText("第一章 中文標題");
	SetTileTextWordByWordEffect(0.05, 1.0, true);--period, delay, repeat
	--SetTitlePos()//top, center
	--SetTitleColor();
	
end
--PauseLua();