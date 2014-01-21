#include <framework/common.h>
#include <framework/framework.h>

#ifdef PLATFORM_WIN32
int WINAPI WinMain(HINSTANCE , HINSTANCE , LPSTR , int )
#else
int main(int argc, char* argv[])
#endif
{
	Framework fw;
	fw.Run();
}

