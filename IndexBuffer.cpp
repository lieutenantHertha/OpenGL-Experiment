#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(unsigned int indiceSize, const void * dataSource) : m_indices(indiceSize/sizeof(unsigned int))
{
	glGenBuffers(1, &m_Renderer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceSize, dataSource, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_Renderer);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer);
}

void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::GetElement() const
{
	return m_indices;
}
