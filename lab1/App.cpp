#include <framework/Common.h>
#include "App.h"

#include <GL/glew.h>

Lab1App::Lab1App()
{
}
Lab1App::~Lab1App()
{
}
GLuint Lab1App::CreateVertexBuffer(uint32_t size, void* vertex_data)
{
	// Vertex buffer objects in opengl are objects that allows us to upload data directly to the GPU.
	//	This means that opengl doesn't need to upload the data everytime we render something. As with 
	//	display lists or glBegin()...glEnd().

	GLuint buffer; // The resulting buffer name will be stored here.

	// Generate a name for our new buffer.
	glGenBuffers(1, &buffer);

	// Bind the buffer, this will also perform the actual creation of the buffer.
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// Upload the data to the buffer.
	glBufferData(GL_ARRAY_BUFFER, 
				size, // The total size of the buffer
				vertex_data, // The data that should be uploaded
				GL_STATIC_DRAW // Specifies that the buffer should be static and it should be used for drawing.
				);

	return buffer;
}
void Lab1App::DrawPrimitive(const Primitive& primitive, const Vec3& position)
{
	glEnableClientState(GL_VERTEX_ARRAY); // Enables the use of the vertex array specified in our vertex buffer.

	glBindBuffer(GL_ARRAY_BUFFER, primitive.vertex_buffer); // Binds the vertex buffer for use.
	
	// Specifies the location and format of the vertex data to use when drawing.
	glVertexPointer(3, // Each vertex contains 3 elements (x, y, z)
					GL_FLOAT, // Our vertex data is represented as floats
					0, // Stride set to 0 as all vertices are consecutive 
					NULL); 
	
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
	
	glDisableClientState(GL_VERTEX_ARRAY); // Disables the use of the vertex array.
}
bool Lab1App::Initialize()
{
	// Initialize SDL and create a 800x600 winodw for rendering.
	if(!InitializeSDL(800, 600))
		return false;

	SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	float vdata[3*4];
	int i = 0;
	vdata[i++] = 0.5f;	vdata[i++] = 0.5f;	vdata[i++] = 0.0f;
	vdata[i++] = 1000.0f;	vdata[i++] = 1000.0f;	vdata[i++] = 1000.0f;
	vdata[i++] = 1000.0f;	vdata[i++] = 1000.0f;	vdata[i++] = 1000.0f;
	vdata[i++] = 1000.0f;	vdata[i++] = 1000.0f;	vdata[i++] = 1000.0f;

	_rectangle_vbo = CreateVertexBuffer(3*4*sizeof(float), vdata);


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

	Primitive prim;
	prim.draw_mode = GL_POINTS;
	prim.vertex_buffer = _rectangle_vbo;
	prim.vertex_count = 4;

	DrawPrimitive(prim, Vec3(0.0f, 0.0f, 0.0f)); 
}
