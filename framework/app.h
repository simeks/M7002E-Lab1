#ifndef __APP_H__
#define __APP_H__


struct SDL_Window;
class App
{
public:
	App();
	virtual ~App();

	void Run();

protected:

	/// @return True if initialization was successful, false if not.
	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;

	/// @brief Initializes SDL and creates a new primary window for rendering.
	/// @return True if initialization was successful, false if not.
	bool InitializeSDL(uint32_t window_width, uint32_t window_height);

	/// @brief SDL shutdown.
	void ShutdownSDL();

	SDL_Window* _window;
	bool _running; // Specifies whether the framework is currently running, setting this to false will exit the application.

};


#endif // __APP_H__
