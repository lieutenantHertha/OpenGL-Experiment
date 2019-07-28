#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_Renderer);
	glBindVertexArray(m_Renderer);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_Renderer);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_Renderer);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer & vertexBuffer, const VertexBufferLayout & layout)
{
	Bind();
	vertexBuffer.Bind();
	unsigned int offset = 0;
	const std::vector<VertexBufferElement> elements = layout.GetElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		VertexBufferElement element = elements[i];
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		GLCall(glEnableVertexAttribArray(i));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}
