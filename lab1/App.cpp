#include <framework/Common.h>
#include "App.h"


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

Primitive Lab1App::CreatePyramid(const Vec3& size, const Color& color)
{
	Primitive primitive;
	primitive.draw_mode = GL_LINE_STRIP;

	// We can draw the outlines of the 3d pyramid with 10 vertices using GL_LINE_STRIP
	primitive.vertex_count = 10; 

	float vertex_data[10*3]; // 6 vertices, 3 floats each (x, y, z)

	int i = 0;

	// The bottom
	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // bottom 1
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // bottom 2
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.z; // bottom 3
	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.z; // bottom 4

	// Side 4 (bottom 4 -> Top)
	vertex_data[i++] = size.x * 0.5f; vertex_data[i++] = size.y; vertex_data[i++] = size.z * 0.5f; // Top

	// Side 3 (Top -> bottom 3 -> Top)
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.z; // bottom 3
	vertex_data[i++] = size.x * 0.5f; vertex_data[i++] = size.y; vertex_data[i++] = size.z * 0.5f; // Top

	// Side 2 (Top -> bottom 2 -> Top)
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // bottom 2
	vertex_data[i++] = size.x * 0.5f; vertex_data[i++] = size.y; vertex_data[i++] = size.z * 0.5f; // Top
	
	// Side 1 (Top -> bottom 1)
	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // bottom 1

	// Create the vertex buffer, possible optimization would be to create a shared vertex buffer for the rectangles
	//	rather than creating a new one for each rectangle.
	primitive.vertex_buffer = CreateVertexBuffer(3*primitive.vertex_count*sizeof(float), vertex_data);
	
	float color_data[10*4]; // 6 vertices, 4 floats each (r, g, b, a)
	
	// Fill the color data, each vertex will have the same color.
	for(i = 0; i < 10; ++i)
	{
		color_data[4*i+0] = color.r; 
		color_data[4*i+1] = color.g; 
		color_data[4*i+2] = color.b; 
		color_data[4*i+3] = color.a; 
	}
	
	// Create the color buffer, this could (and probably should) be interleaved with the other vertex buffer but we keep it simple.
	primitive.color_buffer = CreateVertexBuffer(4*primitive.vertex_count*sizeof(float), color_data);

	return primitive;
}
Primitive Lab1App::CreateFilledRectangle(const Vec2& size, const Color& color)
{
	Primitive primitive;
	primitive.draw_mode = GL_TRIANGLES;

	// The rectangle consists of two triangles, which means we have 6 vertices.
	primitive.vertex_count = 6; 

	float vertex_data[6*3]; // 6 vertices, 3 floats each (x, y, z)

	int i = 0;

	// Triangle 1
	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // Bottom left
	vertex_data[i++] = size.x;	vertex_data[i++] = size.y;	vertex_data[i++] = 0.0f; // Top right
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // Bottom right

	// Triangle 2
	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // Bottom left
	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.y;	vertex_data[i++] = 0.0f; // Top left
	vertex_data[i++] = size.x;	vertex_data[i++] = size.y;	vertex_data[i++] = 0.0f; // Top right

	// Create the vertex buffer, possible optimization would be to create a shared vertex buffer for the rectangles
	//	rather than creating a new one for each rectangle.
	primitive.vertex_buffer = CreateVertexBuffer(3*primitive.vertex_count*sizeof(float), vertex_data);
	
	float color_data[6*4]; // 6 vertices, 4 floats each (r, g, b, a)
	
	// Fill the color data, each vertex will have the same color.
	for(i = 0; i < 6; ++i)
	{
		color_data[4*i+0] = color.r; 
		color_data[4*i+1] = color.g; 
		color_data[4*i+2] = color.b; 
		color_data[4*i+3] = color.a; 
	}
	
	// Create the color buffer, this could (and probably should) be interleaved with the other vertex buffer but we keep it simple.
	primitive.color_buffer = CreateVertexBuffer(4*primitive.vertex_count*sizeof(float), color_data);

	return primitive;
}
Primitive Lab1App::CreateFilledStar(const Vec2& size, const Color& color)
{
	Primitive primitive;
	primitive.draw_mode = GL_TRIANGLES;

	// The star consists of two triangles, which means we have 6 vertices.
	primitive.vertex_count = 6; 

	float vertex_data[6*3]; // 6 vertices, 3 floats each (x, y, z)

	int i = 0;

	// Triangle 1
	vertex_data[i++] = 0.0f;		vertex_data[i++] = size.y*0.25f;	vertex_data[i++] = 0.0f;
	vertex_data[i++] = size.x*0.5f;	vertex_data[i++] = size.y;			vertex_data[i++] = 0.0f; 
	vertex_data[i++] = size.x;		vertex_data[i++] = size.y*0.25f;	vertex_data[i++] = 0.0f; 

	// Triangle 2
	vertex_data[i++] = 0.0f;		vertex_data[i++] = size.y*0.75f;	vertex_data[i++] = 0.0f;
	vertex_data[i++] = size.x;		vertex_data[i++] = size.y*0.75f;	vertex_data[i++] = 0.0f; 
	vertex_data[i++] = size.x*0.5f;	vertex_data[i++] = 0.0f;			vertex_data[i++] = 0.0f; 

	// Create the vertex buffer, possible optimization would be to create a shared vertex buffer for the stars
	//	rather than creating a new one for each star.
	primitive.vertex_buffer = CreateVertexBuffer(3*primitive.vertex_count*sizeof(float), vertex_data);
	
	float color_data[6*4]; // 6 vertices, 4 floats each (r, g, b, a)
	
	// Fill the color data, each vertex will have the same color.
	for(i = 0; i < 6; ++i)
	{
		color_data[4*i+0] = color.r; 
		color_data[4*i+1] = color.g; 
		color_data[4*i+2] = color.b; 
		color_data[4*i+3] = color.a; 
	}
	
	// Create the color buffer, this could (and probably should) be interleaved with the other vertex buffer but we keep it simple.
	primitive.color_buffer = CreateVertexBuffer(4*primitive.vertex_count*sizeof(float), color_data);

	return primitive;
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
	
	_pyramid_primtive = CreatePyramid(Vec3(0.25f, 0.25f, 0.25f), Color(1.0f, 0.0f, 0.0f));
	_rectangle_primitive = CreateFilledRectangle(Vec2(0.5f, 0.5f), Color(0.0f, 0.0f, 1.0f));
	_star_primtive = CreateFilledStar(Vec2(0.25f, 0.25f), Color(0.0f, 1.0f, 0.0f));

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
