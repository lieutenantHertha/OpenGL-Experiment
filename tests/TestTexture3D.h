#pragma once
#include <memory>

#include "Test.h"
#include "Renderer.h"
#include "Texture.h"

namespace Test{
	class TestTexture3D : public Test {
	private:
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture1;
		std::unique_ptr<Texture> m_Texture2;

		glm::mat4 m_ProjMatrix  = glm::perspective(glm::radians(45.000f), 720.000f / 720.000f, 0.100f, 100.000f);
		glm::mat4 m_ViewMatrix  = glm::mat4(1.000f);
		glm::mat4 m_ModelMatrix = glm::mat4(1.000f);
		glm::vec3 m_Transition  = glm::vec3(0.000f, 0.000f, 0.000f);
		glm::vec3 m_Axis = glm::vec3(1.000f, 1.000f, 1.000f);
	public:
		TestTexture3D();
		~TestTexture3D();

		void OnUpdate(float DeltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;
	};
}
