#include "main.h"
#include "MLApp.h"
//#include "cocos2d.h"

// Melo test

//#include "..\Melo\Melo.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance

	MLApp app;
    return Application::getInstance()->run();
}