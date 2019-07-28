#pragma once
#include <GL/glew.h>

class IndexBuffer {
private:

	unsigned int m_Renderer;
	unsigned int m_indices;

public:
	IndexBuffer(unsigned int indiceSize, const void* dataSource);
	~IndexBuffer();
	void Bind() const;
	void UnBind() const;
	unsigned int GetElement() const;
};
