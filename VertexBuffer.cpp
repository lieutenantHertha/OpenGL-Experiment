#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(unsigned int vertexSize, const void* dataSource)
{
	glGenBuffers(1, &m_Renderer);
	glBindBuffer(GL_ARRAY_BUFFER, m_Renderer);
	glBufferData(GL_ARRAY_BUFFER, vertexSize, dataSource, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_Renderer);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Renderer);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
