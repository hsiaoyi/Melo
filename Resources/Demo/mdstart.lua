ctr = 1

if ctr == 1 then
	SetGameBG("Demo/background.png");
	SetGameBGAlignWin(0,0);--hori 0:left, 1:center, 2:right --vert 0:top, 1:center, 2:buttom 
	
	--SetGameBG("Demo/helloworld.png");
	
	SetTitleFont("fonts/NotoSansCJKtc-Light.otf", 24);
	SetTitleText("第一章 中文\n第二行 標題測試");
	SetTileTextWordByWordEffect(0.05, 1.0, true);--period, delay, repeat
	
	SetTitleTextAlignWin(2,1);--hoti 0:left, 1:center, 2:right --vert 0:top, 1:center, 2:buttom 
	--SetTitlePos()//top, center
	--SetTitleColor();
	
end
PauseLua();