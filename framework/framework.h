#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__


struct SDL_Window;
class Framework
{
public:
	Framework();
	~Framework();

	void Run();

private:
	SDL_Window* _window;
	bool _running; // Specifies whether the framework is currently running, setting this to false will exit the application.
	bool _initialized; // Set to true if the system is fully initialized.

};


#endif // __FRAMEWORK_H__
