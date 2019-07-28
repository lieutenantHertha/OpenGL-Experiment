#include "TestTexture.h"
#include "imgui/imgui.h"

float vertexMessage[] = {
	  0.000f,   0.000f, 0.000f, 0.000f, 0.000f,
	240.000f,   0.000f, 0.000f, 1.000f, 0.000f,
	240.000f, 240.000f, 0.000f, 1.000f, 1.000f,
	  0.000f, 240.000f, 0.000f, 0.000f, 1.000f
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
	m_Texture = std::make_unique<Texture>("res/textures/ACLogo.png");
	m_Texture->Bind();
	m_Shader->SetUniformMat4f("u_MVP", m_MVP);
	m_Shader->SetUniform1i("u_Texture", 0);
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
	ImGui::SliderFloat("Horizon", &m_Transition[0], 0.000f, 480.000f);
	ImGui::SliderFloat("Vertical", &m_Transition[1], 0.000f, 480.000f);
}

void Test::TestTexture::OnRender()
{
	modelMatrix = glm::translate(glm::mat4(1.000f), m_Transition);
	m_MVP = orthoMatrix * viewMatrix * modelMatrix;
	m_Shader->SetUniformMat4f("u_MVP", m_MVP);
	Renderer renderer;
	renderer.Clean();
	renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
}
