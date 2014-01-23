#ifndef __LAB1_APP_H__
#define __LAB1_APP_H__

#include <framework/App.h>

#include "PrimitiveFactory.h"

class Lab1App : public App
{
public:
	Lab1App();
	~Lab1App();

	/// @brief Draws the specified primitive at the specified position.
	void DrawPrimitive(const Primitive& primitive, const Vec3& position);
	

protected:
	bool Initialize();
	void Shutdown();

	/// @brief Callback invoked once every frame to let the application perform rendering.
	void Render();
	
private:
	PrimitiveFactory _primitive_factory;

	Primitive _rectangle_primitive;
	Primitive _pyramid_primtive;
	Primitive _star_primtive;

};


#endif // __LAB1_APP_H__
