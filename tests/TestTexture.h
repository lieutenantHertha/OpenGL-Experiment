#pragma once
#include <iostream>
#include <string>
#include <memory>

#include "Test.h"
#include "Renderer.h"
#include "Texture.h"

namespace Test {
	class TestTexture : public Test {
	private:	
		std::unique_ptr<VertexArray>  m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<Shader> m_Shader;
		glm::mat4 orthoMatrix = glm::ortho(0.000f, 720.000f, 0.000f, 720.000f);
		glm::mat4 viewMatrix = glm::mat4(1.000f);
		glm::mat4 modelMatrix = glm::mat4(1.000f);
		glm::mat4 m_MVP = orthoMatrix * viewMatrix * modelMatrix;
		glm::vec3 m_Transition = glm::vec3(0.000f, 0.000f, 0.000f);
	public:
		TestTexture();
		~TestTexture();

		void OnUpdate(float deltaTime) override;
		void OnImguiRender() override;
		void OnRender() override;
	};
}
