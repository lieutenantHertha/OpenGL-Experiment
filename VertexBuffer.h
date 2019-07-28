#pragma once
#include <GL/glew.h>

class VertexBuffer {
private:

	unsigned int m_Renderer;

public:
	VertexBuffer(unsigned int vertexSize, const void* dataSource);
	~VertexBuffer();
	void Bind() const;
	void UnBind() const;
};