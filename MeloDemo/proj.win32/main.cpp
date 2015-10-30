#include "main.h"
#include "MDAppDelegate.h"
#include "cocos2d.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    
	MDAppDelegate app;
	return Application::getInstance()->run();
}
