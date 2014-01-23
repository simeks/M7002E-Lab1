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


	float vdata[3*4];
	int i = 0;
	vdata[i++] = 0.5f;	vdata[i++] = 0.5f;	vdata[i++] = 0.0f;
	vdata[i++] = 1000.0f;	vdata[i++] = 1000.0f;	vdata[i++] = 1000.0f;
	vdata[i++] = 1000.0f;	vdata[i++] = 1000.0f;	vdata[i++] = 1000.0f;
	vdata[i++] = 1000.0f;	vdata[i++] = 1000.0f;	vdata[i++] = 1000.0f;
	
	_pyramid_primtive = _primitive_factory.CreatePyramid(Vec3(0.25f, 0.25f, 0.25f), Color(1.0f, 0.0f, 0.0f));
	_rectangle_primitive = _primitive_factory.CreateFilledRectangle(Vec2(0.5f, 0.5f), Color(0.0f, 0.0f, 1.0f));
	_star_primtive = _primitive_factory.CreateFilledStar(Vec2(0.25f, 0.25f), Color(0.0f, 1.0f, 0.0f));

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

	// Transform coordinates from [-1.0f, 1.0f] to [0, 1.0f]
	glTranslatef(-1.0f, -1.0f, 0.0f);
	glScalef(2.0f, 2.0f, 1.0f);
	
	DrawPrimitive(_pyramid_primtive, Vec3(0.5f, 0.0f, 0.0f)); 
	DrawPrimitive(_rectangle_primitive, Vec3(0.0f, 0.0f, 0.0f)); 
	DrawPrimitive(_star_primtive, Vec3(0.75f, 0.0f, 0.0f)); 

}
