#ifndef __LAB1_APP_H__
#define __LAB1_APP_H__

#include <framework/App.h>

#include "PrimitiveFactory.h"

struct Viewport
{
	int x, y;
	int width, height;
};

class Lab1App : public App
{
public:
	Lab1App();
	~Lab1App();

	/// @brief Draws the specified primitive at the specified position.
	/// @param position Position for the primitive.
	/// @param rotation Rotation in angles: (yaw, pitch, roll)
	void DrawPrimitive(const Primitive& primitive, const Vec3& position, const Vec3& rotation);
	

protected:
	bool Initialize();
	void Shutdown();

	/// @brief Callback invoked once every frame to let the application perform rendering.
	void Render(float dtime);

	/// @brief Renders the scene, this does not include any viewport setup, etc, that may be needed.
	void RenderScene();
	
private:
	PrimitiveFactory _primitive_factory;

	Primitive _rectangle_primitive;
	Primitive _pyramid_primitive;
	Primitive _star_primitive;
	Primitive _cube_primitive;
	Primitive _sphere_primitive;

	Viewport _left_viewport;
	Viewport _right_viewport;

	float _scene_angle;
};


#endif // __LAB1_APP_H__
