#include <framework/Common.h>
#include "App.h"


Lab1App::Lab1App()
{
}
Lab1App::~Lab1App()
{
}

void Lab1App::DrawPrimitive(const Primitive& primitive, const Vec3& position)
{
	glEnableClientState(GL_VERTEX_ARRAY); // Enables the use of the vertex array specified in our vertex buffer.
	glEnableClientState(GL_COLOR_ARRAY);

	// Binds the vertex buffer for use.
	glBindBuffer(GL_ARRAY_BUFFER, primitive.vertex_buffer); 
	// Specifies the location and format of the vertex data to use when drawing.
	glVertexPointer(3, // Each vertex contains 3 elements (x, y, z)
					GL_FLOAT, // Our vertex data is represented as floats
					0, // Stride set to 0 as all vertices are consecutive 
					0); 

	// Binds the color buffer for use.
	glBindBuffer(GL_ARRAY_BUFFER, primitive.color_buffer); 
	// Specifies the location and format of the color data to use when drawing.
	glColorPointer(4, // Each vertex contains 4 elements (r, g, b, a)
					GL_FLOAT, // Our vertex data is represented as floats
					0, // Stride set to 0 as all vertices are consecutive 
					0); 

	// Specify the modelview matrix as the current matrix.
	glMatrixMode(GL_MODELVIEW);

	// Push a new matrix to the stack so that we easily can pop back to the previous state.
	glPushMatrix();

	// Translate the primitive to the specified position.
	glTranslatef(position.x, position.y, position.z);

	// Perform the actual draw call.
	glDrawArrays(primitive.draw_mode, 0, primitive.vertex_count);

	// Return the modelview matrix to its previous state
	glPopMatrix();
	
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY); // Disables the use of the vertex array.
}

bool Lab1App::Initialize()
{
	// Initialize SDL and create a 800x600 winodw for rendering.
	if(!InitializeSDL(800, 600))
		return false;

	SetWindowTitle("OpenGL - Lab 1");
	SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Setup projection matrix
	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0, 800.0, 0.0, 600.0, 0.0f, -500.0);

	_pyramid_primitive = _primitive_factory.CreatePyramid(Vec3(200.0f, 200.0f, 200.0f), Color(1.0f, 0.0f, 0.0f));
	_rectangle_primitive = _primitive_factory.CreateFilledRectangle(Vec2(200.0f, 200.0f), Color(0.0f, 0.0f, 1.0f));
	_star_primitive = _primitive_factory.CreateFilledStar(Vec2(200.0f, 200.0f), Color(0.0f, 1.0f, 0.0f));
	_cube_primitive = _primitive_factory.CreateCube(Vec3(100.0f, 100.0f, 100.0f), Color(1.0f, 0.0f, 1.0f));
	_sphere_primitive = _primitive_factory.CreateSphere(100.0f, Color(1.0f, 1.0f, 1.0f));

	return true;
}
void Lab1App::Shutdown()
{
	ShutdownSDL();
}
void Lab1App::Render()
{
	// Reset the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	DrawPrimitive(_pyramid_primitive, Vec3(10.0f, 10.0f, 0.0f)); 
	DrawPrimitive(_rectangle_primitive, Vec3(220.0f, 0.0f, 0.0f)); 
	DrawPrimitive(_star_primitive, Vec3(430.0f, 0.0f, 0.0f)); 
	DrawPrimitive(_cube_primitive, Vec3(10.0f, 250.0f, 0.0f)); 
	DrawPrimitive(_sphere_primitive, Vec3(350.0f, 350.0f, 0.0f)); 

}
