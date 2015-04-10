MeloTestPara1 = 1
MeloTestPara2 = 50
MeloTestStr = "Lua test string.!!"

--PauseLua();
if MeloTestPara1 == 1 then
	MeloLuaTest1(MeloTestPara2);
end

--function MeloLua2(str, i1, d1)
function MeloLua2(str)
	MeloLuaTest2(MeloTestStr);
	MeloTestStr = str;
	--MeloLuaTest2(str);
	MeloLuaTest2(MeloTestStr);
	return "I'm MeloLua2 return string!!"
end

function MeloCallTest(i1, d1, b1,str)
	MeloLuaTest2(str);
	res = -3.5;
	-- boolean test
	if b1 == true then
	res = i1 + d1;
	else
	res = i1-d1;
	end
	-- boolean test
	
	return res;
end