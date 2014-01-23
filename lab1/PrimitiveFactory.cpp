#include <framework/Common.h>

#include "PrimitiveFactory.h"

PrimitiveFactory::PrimitiveFactory()
{
}
PrimitiveFactory::~PrimitiveFactory()
{
}

Primitive PrimitiveFactory::CreatePyramid(const Vec3& size, const Color& color)
{
	Primitive primitive;
	primitive.draw_mode = GL_LINE_STRIP;

	// We can draw the outlines of the 3d pyramid with 11 vertices using GL_LINE_STRIP
	primitive.vertex_count = 11; 

	float vertex_data[11*3]; // 6 vertices, 3 floats each (x, y, z)

	int i = 0;

	// The bottom
	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // bottom 1
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // bottom 2
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.z; // bottom 3
	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.z; // bottom 4
	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // bottom 1

	// Side 4 (bottom 1 -> Top)
	vertex_data[i++] = size.x * 0.5f; vertex_data[i++] = size.y; vertex_data[i++] = size.z * 0.5f; // Top

	// Side 3 (Top -> bottom 2 -> Top)
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // bottom 2
	vertex_data[i++] = size.x * 0.5f; vertex_data[i++] = size.y; vertex_data[i++] = size.z * 0.5f; // Top

	// Side 2 (Top -> bottom 3 -> Top)
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.z; // bottom 3
	vertex_data[i++] = size.x * 0.5f; vertex_data[i++] = size.y; vertex_data[i++] = size.z * 0.5f; // Top
	
	// Side 1 (Top -> bottom 4)
	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.z; // bottom 4

	// Create the vertex buffer, possible optimization would be to create a shared vertex buffer for the rectangles
	//	rather than creating a new one for each rectangle.
	primitive.vertex_buffer = CreateVertexBuffer(3*primitive.vertex_count*sizeof(float), vertex_data);
	
	float color_data[11*4]; // 6 vertices, 4 floats each (r, g, b, a)
	
	// Fill the color data, each vertex will have the same color.
	for(i = 0; i < 11; ++i)
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
Primitive PrimitiveFactory::CreateFilledRectangle(const Vec2& size, const Color& color)
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
Primitive PrimitiveFactory::CreateFilledStar(const Vec2& size, const Color& color)
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

Primitive PrimitiveFactory::CreateCube(const Vec3& size, const Color& color)
{
	Primitive primitive;
	primitive.draw_mode = GL_TRIANGLES;

	// The cube consists of six rectangles (six faces), which means we have 6*6 vertices.
	primitive.vertex_count = 36; 

	float vertex_data[36*3]; // 6 vertices, 3 floats each (x, y, z)

	int i = 0;

	// Face 1 (Front)
	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // Bottom left
	vertex_data[i++] = size.x;	vertex_data[i++] = size.y;	vertex_data[i++] = 0.0f; // Top right
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // Bottom right

	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // Bottom left
	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.y;	vertex_data[i++] = 0.0f; // Top left
	vertex_data[i++] = size.x;	vertex_data[i++] = size.y;	vertex_data[i++] = 0.0f; // Top right

	// Face 2 (Back)
	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.z; // Bottom left
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.z; // Bottom right
	vertex_data[i++] = size.x;	vertex_data[i++] = size.y;	vertex_data[i++] = size.z; // Top right

	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.z; // Bottom left
	vertex_data[i++] = size.x;	vertex_data[i++] = size.y;	vertex_data[i++] = size.z; // Top right
	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.y;	vertex_data[i++] = size.z; // Top left

	// Face 3 (Top)
	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.y;	vertex_data[i++] = 0.0f; // Bottom left
	vertex_data[i++] = size.x;	vertex_data[i++] = size.y;	vertex_data[i++] = size.z; // Top right
	vertex_data[i++] = size.x;	vertex_data[i++] = size.y;	vertex_data[i++] = 0.0f; // Bottom right

	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.y;	vertex_data[i++] = 0.0f; // Bottom left
	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.y;	vertex_data[i++] = size.z; // Top left
	vertex_data[i++] = size.x;	vertex_data[i++] = size.y;	vertex_data[i++] = size.z; // Top right

	// Face 4 (Bottom)
	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // Bottom left
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // Bottom right
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.z; // Top right

	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // Bottom left
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.z; // Top right
	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.z; // Top left

	// Face 5 (Left)
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // Bottom left
	vertex_data[i++] = size.x;	vertex_data[i++] = size.y;	vertex_data[i++] = size.z; // Top right
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.z; // Bottom right

	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // Bottom left
	vertex_data[i++] = size.x;	vertex_data[i++] = size.y;	vertex_data[i++] = 0.0f; // Top left
	vertex_data[i++] = size.x;	vertex_data[i++] = size.y;	vertex_data[i++] = size.z; // Top right

	// Face 6
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // Bottom left
	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = size.z; // Bottom right
	vertex_data[i++] = size.x;	vertex_data[i++] = size.y;	vertex_data[i++] = size.z; // Top right

	vertex_data[i++] = size.x;	vertex_data[i++] = 0.0f;	vertex_data[i++] = 0.0f; // Bottom left
	vertex_data[i++] = size.x;	vertex_data[i++] = size.y;	vertex_data[i++] = size.z; // Top right
	vertex_data[i++] = size.x;	vertex_data[i++] = size.y;	vertex_data[i++] = 0.0f; // Top left


	// Create the vertex buffer, possible optimization would be to create a shared vertex buffer for the rectangles
	//	rather than creating a new one for each rectangle.
	primitive.vertex_buffer = CreateVertexBuffer(3*primitive.vertex_count*sizeof(float), vertex_data);
	
	float color_data[36*4]; // 6 vertices, 4 floats each (r, g, b, a)

	// Fill the color data, each vertex will have the same color.
	for(i = 0; i < 36; ++i)
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
Primitive PrimitiveFactory::CreateSphere(float radius, const Color& color)
{
	static const uint32_t line_count = 64; // Number of lines per circle

	Primitive primitive;
	primitive.draw_mode = GL_LINE_STRIP;
	primitive.vertex_count = (line_count+1); 

	float vertex_data[(line_count+1) * 3];
	int vertex_idx = 0;

	//// X-axis
	//for(int i = 0; i <= line_count; ++i)
	//{
	//	float rad = i * (2 * (float)MATH_PI) / line_count;
	//	vertex_data[vertex_idx++] = radius;
	//	vertex_data[vertex_idx++] = cosf(rad) * radius;
	//	vertex_data[vertex_idx++] = sinf(rad) * radius;

	//}
	//
	//// Y-axis
	//for(int i = 0; i <= line_count; ++i)
	//{
	//	float rad = i * (2 * (float)MATH_PI) / line_count;
	//	vertex_data[vertex_idx++] = cosf(rad) * radius;
	//	vertex_data[vertex_idx++] = radius;
	//	vertex_data[vertex_idx++] = sinf(rad) * radius;
	//}

	// Z-axis
	for(int i = 0; i <= line_count; ++i)
	{
		float rad = i * (2 * (float)MATH_PI) / line_count;
		vertex_data[vertex_idx++] = cosf(rad) * radius;
		vertex_data[vertex_idx++] = sinf(rad) * radius;
		vertex_data[vertex_idx++] = radius;
	}

	// Create the vertex buffer, possible optimization would be to create a shared vertex buffer for the rectangles
	//	rather than creating a new one for each rectangle.
	primitive.vertex_buffer = CreateVertexBuffer(3*primitive.vertex_count*sizeof(float), vertex_data);
	
	float color_data[(line_count+1) * 4]; // 6 vertices, 4 floats each (r, g, b, a)
	
	// Fill the color data, each vertex will have the same color.
	for(int i = 0; i < (line_count+1); ++i)
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

GLuint PrimitiveFactory::CreateVertexBuffer(uint32_t size, void* vertex_data)
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