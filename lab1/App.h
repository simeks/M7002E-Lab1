#ifndef __LAB1_APP_H__
#define __LAB1_APP_H__

#include <framework/App.h>

#include <GL/glew.h>

struct Primitive
{
	GLuint vertex_buffer; // VBO holding the vertex positions. Expecting the element format: float x, y, z
	GLuint color_buffer; // VBO holding the vertex colors. Expecting the element format: float r, g, b, a

	uint32_t vertex_count; // Number of vertices for this primitive.

	GLenum draw_mode; // Specifies draw mode, e.g. GL_POINTS, GL_TRIANGLES, etc.
};

/// @brief RGBA color
struct Color
{
	Color(float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _a = 1.0f) 
		: r(_r), g(_g), b(_b), a(_a)
	{}

	float r, g, b, a;
};

class Lab1App : public App
{
public:
	Lab1App();
	~Lab1App();

	/// @brief Creates a new vertex buffer.
	/// @param size The total size of the buffer in bytes.
	/// @param vertex_data A pointer to the data that should be copied to the buffer.
	///						NULL means the buffer will be empty.
	GLuint CreateVertexBuffer(uint32_t size, void* vertex_data);

	/// @brief Draws the specified primitive at the specified position.
	void DrawPrimitive(const Primitive& primitive, const Vec3& position);
	
	/// @brief Creates a square based 3d pyramid.
	/// @param size The size of the pyramid.
	/// @param color The color of the pyramid.
	Primitive CreatePyramid(const Vec3& size, const Color& color);

	/// @brief Creates a filled rectangle primitive.
	/// @param size The size of the rectangle.
	/// @param color The color of the rectangle.
	Primitive CreateFilledRectangle(const Vec2& size, const Color& color);
	
	/// @brief Creates a filled star primitive.
	/// @param size The size of the star.
	/// @param color The color of the star.
	Primitive CreateFilledStar(const Vec2& size, const Color& color);

protected:
	bool Initialize();
	void Shutdown();

	/// @brief Callback invoked once every frame to let the application perform rendering.
	void Render();
	
private:
	Primitive _rectangle_primitive;
	Primitive _pyramid_primtive;
	Primitive _star_primtive;

};


#endif // __LAB1_APP_H__
