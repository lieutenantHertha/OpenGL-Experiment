#include "TestTexture.h"
#include "imgui/imgui.h"
#include <GLFW/glfw3.h>

float vertexMessage[] = {
	  -0.500f, -0.500f, -2.000f, 0.000f, 0.000f,
	   0.500f, -0.500f, -2.000f, 1.000f, 0.000f,
	   0.500f,  0.500f, -2.000f, 1.000f, 1.000f,
	  -0.500f,  0.500f, -2.000f, 0.000f, 1.000f
};

unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
};

Test::TestTexture::TestTexture()
{
	m_VertexBuffer = std::make_unique<VertexBuffer>(4 * 5 * sizeof(float), vertexMessage);
	m_VertexArray = std::make_unique<VertexArray>();

	VertexBufferLayout m_Layout;
	m_Layout.Push<float>(3);
	m_Layout.Push<float>(2);

	m_VertexArray->AddBuffer(*m_VertexBuffer, m_Layout);

	m_IndexBuffer = std::make_unique<IndexBuffer>(2 * 3 * sizeof(unsigned int), indices);

	m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
	m_Shader->Bind();

	m_Texture = std::make_unique<Texture>("res/textures/EALogo.png");
	m_Texture->Bind();

	m_Shader->SetUniformMat4f("u_ProjMatrix", projMatrix);
	m_Shader->SetUniformMat4f("u_ViewMatrix", viewMatrix);
	m_Shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
	m_Shader->SetUniform1i("u_Texture", 0);
	m_Shader->SetUniform4f("u_TexColor", m_TexColor[0], m_TexColor[1], m_TexColor[2], m_TexColor[3]);
	std::cout << "Texture is ready." << std::endl;

	// make a simple test to see whether projection matrice works fine, if positions are in the normalized device coordinate system
	glm::vec4 position(0.50f, 0.50f, -0.50f, 1.0f);
	glm::mat4 projection = glm::perspective(45.000f, 4.0f / 3.0f, 0.100f, 100.000f);
	glm::vec4 result = projection * position;
	std::cout << "vector reuslt = {" << result.x << ", " << result.y << ", " << result.z << ", " << result.w << "}" << std::endl;
}

Test::TestTexture::~TestTexture()
{
	m_VertexArray->UnBind();
	m_VertexBuffer->UnBind();
	m_IndexBuffer->UnBind();
	m_Shader->Unbind();
	m_Texture->Unbind();
}

void Test::TestTexture::OnUpdate(float deltaTime)
{
}

void Test::TestTexture::OnImguiRender()
{
	ImGui::SliderFloat("Horizon",  &m_Transition[0], -1.500f,  1.500f);
	ImGui::SliderFloat("Vertical", &m_Transition[1], -1.500f,  1.500f);
	ImGui::SliderFloat("Depth",    &m_Transition[2], -10.000f, 1.000f);
	ImGui::ColorPicker4("TexColor", &m_TexColor[0], 0, (const float*)0);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

void Test::TestTexture::OnRender()
{
	modelMatrix = glm::translate(glm::mat4(1.000f), m_Transition);
	viewMatrix = glm::rotate(glm::mat4(1.000f), glm::radians(-30.000f), glm::vec3(1.000f, 0.000f, 0.000f));
	m_Shader->SetUniformMat4f("u_ModelMatrix", modelMatrix);
	m_Shader->SetUniformMat4f("u_ViewMatrix", viewMatrix);
	m_Shader->SetUniform4f("u_TexColor", m_TexColor[0], m_TexColor[1], m_TexColor[2], m_TexColor[3]);
	Renderer renderer;
	renderer.Clean();
	renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
}
