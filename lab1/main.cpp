#include <framework/common.h>
#include "lab_app.h"


#ifdef PLATFORM_WIN32
int WINAPI WinMain(HINSTANCE , HINSTANCE , LPSTR , int )
#else
int main(int argc, char* argv[])
#endif
{
	Lab1App app;
	app.Run();
}

