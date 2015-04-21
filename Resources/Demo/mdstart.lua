ctr = 1

if ctr == 1 then
	SetGameBG("Demo/background.png");
	--SetGameBG("Demo/helloworld.png");
	
	SetTitleFont("fonts/NotoSansCJKtc-Light.otf", 24);
	SetTitleText("第一章 中文標題");
	SetTileTextWordByWordEffect(0.05, 1.0, true);--period, delay, repeat
	
	SetTitleTextAlignment(2,1); --hoti 0:left, 1:center, 2:right
								--vert 0:top, 1:center, 2:buttom
	--SetTitlePos()//top, center
	--SetTitleColor();
	
end
--PauseLua();