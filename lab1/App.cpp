#include <framework/Common.h>
#include "App.h"


Lab1App::Lab1App() : _scene_angle(0.0f)
{
}
Lab1App::~Lab1App()
{
}

void Lab1App::DrawPrimitive(const Primitive& primitive, const Vec3& position, const Vec3& rotation)
{
	glEnableClientState(GL_VERTEX_ARRAY); // Enables the use of the vertex array specified in our vertex buffer.
	glEnableClientState(GL_COLOR_ARRAY); // Enables the use of the color array specified in our vertex color buffer.

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

	// Rotate the primitive
	glRotatef(rotation.x, 1.0f, 0.0f, 0.0f); // Yaw
	glRotatef(rotation.y, 0.0f, 1.0f, 0.0f); // Pitch
	glRotatef(rotation.z, 0.0f, 0.0f, 1.0f); // Roll


	// Perform the actual draw call.
	glDrawArrays(primitive.draw_mode, 0, primitive.vertex_count);

	// Return the modelview matrix to its previous state
	glPopMatrix();
	
	glDisableClientState(GL_COLOR_ARRAY); // Disables the use of the color array.
	glDisableClientState(GL_VERTEX_ARRAY); // Disables the use of the vertex array.
}

bool Lab1App::Initialize()
{
	uint32_t win_width = 1024, win_height = 768;

	// Initialize SDL and create a 800x600 winodw for rendering.
	if(!InitializeSDL(win_width, win_height))
		return false;

	SetWindowTitle("OpenGL - Lab 1");
	SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_CULL_FACE); // Enable face culling
	glEnable(GL_DEPTH_TEST); // Enable depth testing

	// Setup our viewports
	_left_viewport.x = _left_viewport.y = 0;
	_left_viewport.width = win_width / 2;
	_left_viewport.height = win_height;

	_right_viewport.x = win_width / 2; 
	_right_viewport.y = 0;
	_right_viewport.width = win_width / 2;
	_right_viewport.height = win_height;
	

	_pyramid_primitive = _primitive_factory.CreatePyramid(Vec3(75.0f, 75.0f, 75.0f), Color(1.0f, 0.0f, 0.0f));
	_rectangle_primitive = _primitive_factory.CreateFilledRectangle(Vec2(75.0f, 75.0f), Color(0.0f, 0.0f, 1.0f));
	_star_primitive = _primitive_factory.CreateFilledStar(Vec2(75.0f, 75.0f), Color(0.0f, 1.0f, 0.0f));
	_cube_primitive = _primitive_factory.CreateCube(Vec3(75.0f, 75.0f, 75.0f), Color(1.0f, 0.0f, 1.0f));
	_sphere_primitive = _primitive_factory.CreateFilledCircle(75.0f, Color(0.0f, 1.0f, 1.0f));

	return true;
}
void Lab1App::Shutdown()
{
	// Cleanup

	_primitive_factory.DestroyPrimitive(_sphere_primitive);
	_primitive_factory.DestroyPrimitive(_cube_primitive);
	_primitive_factory.DestroyPrimitive(_star_primitive);
	_primitive_factory.DestroyPrimitive(_rectangle_primitive);
	_primitive_factory.DestroyPrimitive(_pyramid_primitive);

	ShutdownSDL();
}
void Lab1App::Render(float dtime)
{
	// Reset the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Render left viewport
	{
		// Save previous viewport
		glPushAttrib(GL_VIEWPORT_BIT); 
		
		// Set viewport attributes
		glViewport(_left_viewport.x, _left_viewport.y, _left_viewport.width, _left_viewport.height);

		// Setup projection matrix
		glMatrixMode(GL_PROJECTION);

		// Save previous matrix
		glPushMatrix();
		
		glLoadIdentity();
		
		// Set the perspective, 45 degrees FOV, aspect ratio to match viewport, z range: [1.0, 1000.0]
		gluPerspective(45.0, (double)_left_viewport.width/(double)_left_viewport.height, 1.0, 1000.0);
		// Set the camera position to (0, 0, 400) and make it look at the center of the scene (0, 0, 0)
		gluLookAt(0.0, 0.0, 400.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

		// Draw the scene
		RenderScene();
		
		// Restore projection matrix
		glPopMatrix();
		// Restore viewport
		glPopAttrib();
	}

	// Render right viewport
	{
		// Save previous viewport
		glPushAttrib(GL_VIEWPORT_BIT); 
		
		// Set viewport attributes
		glViewport(_right_viewport.x, _right_viewport.y, _right_viewport.width, _right_viewport.height);

		// Setup projection matrix
		glMatrixMode(GL_PROJECTION);
		// Save previous matrix
		glPushMatrix();
		
		glLoadIdentity();
		// Set the perspective, 45 degrees FOV, aspect ratio to match viewport, z range: [1.0, 1000.0]
		gluPerspective(45.0, (double)_left_viewport.width/(double)_left_viewport.height, 1.0, 1000.0);
		
		// Make the camera rotate around the scene
		_scene_angle = _scene_angle + dtime * (float)MATH_HALF_PI; // PI/2 rad/s
		// Set the camera position and make it rotate around the center of the scene (0,0,0)
		gluLookAt(400*cos(_scene_angle), 0.0, 400.0*sin(_scene_angle), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

		// Draw the scene
		RenderScene();
		
		// Restore projection matrix
		glPopMatrix();
		// Restore viewport
		glPopAttrib();
	}


}
void Lab1App::RenderScene()
{
	// Render all the primitives in the scene.

	DrawPrimitive(_pyramid_primitive, Vec3(45.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)); 
	DrawPrimitive(_cube_primitive, Vec3(-45.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)); 
	DrawPrimitive(_rectangle_primitive, Vec3(-25.0f, 0.0f, -50.0f), Vec3(0.0f, 0.0f, 0.0f)); 
	DrawPrimitive(_star_primitive, Vec3(25.0f, 0.0f, -45.0f), Vec3(0.0f, 0.0f, 0.0f)); 
	DrawPrimitive(_sphere_primitive, Vec3(0.0f, -45.0f, 0.0f), Vec3(-90.0f, 0.0f, 0.0f)); 
}
