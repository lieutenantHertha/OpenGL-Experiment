#pragma once
#include <iostream>
#include <string>
#include <memory>

#include "Test.h"
#include "Renderer.h"
#include "Texture.h"

const float WINDOW_WIDTH = 720.000f;
const float WINDOW_HEIGHT = 720.000f;

namespace Test {
	class TestTexture : public Test {
	private:	
		std::unique_ptr<VertexArray>  m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<Shader> m_Shader;
		glm::mat4 projMatrix = glm::perspective(glm::radians(45.000f), WINDOW_WIDTH/WINDOW_HEIGHT, 0.100f, 100.000f);
		glm::mat4 viewMatrix = glm::mat4(1.000f);
		glm::mat4 modelMatrix = glm::mat4(1.000f);
		glm::vec3 m_Transition = glm::vec3(0.000f, 0.000f, 0.000f);
		glm::vec4 m_TexColor = glm::vec4(1.000f, 1.000f, 1.000f, 1.000f);
	public:
		TestTexture();
		~TestTexture();

		void OnUpdate(float deltaTime) override;
		void OnImguiRender() override;
		void OnRender() override;
	};
}
