#include <iostream>
#include "Renderer.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR)
		 ;                 // Clean up all of the error flags to lock OpenGL function errors into one function call.
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "OpenGL Error: 0x" << std::hex << error << std::endl;
		std::cout << function << " from the file " << file << ":" << std::dec << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const
{
	vao.Bind();
	ibo.Bind();
	shader.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ibo.GetElement(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clean()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::SetClearColor(glm::vec4 clearColor)
{
	GLCall(glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]));
}
