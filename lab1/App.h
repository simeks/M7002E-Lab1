#ifndef __LAB1_APP_H__
#define __LAB1_APP_H__

#include <framework/App.h>

#include <GL/glew.h>

struct Primitive
{
	GLuint vertex_buffer;
	uint32_t vertex_count;

	GLenum draw_mode; // Specifies draw mode, e.g. GL_POINTS, GL_TRIANGLES, etc.
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

	void DrawPrimitive(const Primitive& primitive, const Vec3& position);

protected:
	bool Initialize();
	void Shutdown();

	/// @brief Callback invoked once every frame to let the application perform rendering.
	void Render();
	
private:
	GLuint _pyramid_vbo; // Shared vertex buffer object for the pyramid shape.
	GLuint _rectangle_vbo; // Shared vertex buffer object for the rectangle shape.
	GLuint _star_vbo; // Shared vertex buffer object for the star shape.


};


#endif // __LAB1_APP_H__
