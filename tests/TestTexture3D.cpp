#include "TestTexture3D.h"
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"

float verticeMessage[] = {
	  -0.500f, -0.500f, -2.500f, 0.000f, 0.000f, //0
	   0.500f, -0.500f, -2.500f, 1.000f, 0.000f, //1
	   0.500f,  0.500f, -2.500f, 1.000f, 1.000f, //2
	  -0.500f,  0.500f, -2.500f, 0.000f, 1.000f, //3

	   0.500f, -0.500f, -2.500f, 0.000f, 0.000f, //4
	   0.500f, -0.500f, -3.500f, 1.000f, 0.000f, //5
	   0.500f,  0.500f, -3.500f, 1.000f, 1.000f, //6
	   0.500f,  0.500f, -2.500f, 0.000f, 1.000f, //7

	   0.500f, -0.500f, -3.500f, 0.000f, 0.000f, //8
	  -0.500f, -0.500f, -3.500f, 1.000f, 0.000f, //9
	  -0.500f,  0.500f, -3.500f, 1.000f, 1.000f, //10
	   0.500f,  0.500f, -3.500f, 0.000f, 1.000f, //11

	  -0.500f, -0.500f, -3.500f, 0.000f, 0.000f, //12
	  -0.500f, -0.500f, -2.500f, 1.000f, 0.000f, //13
	  -0.500f,  0.500f, -2.500f, 1.000f, 1.000f, //14
	  -0.500f,  0.500f, -3.500f, 0.000f, 1.000f, //15

	  -0.500f, -0.500f, -2.500f, 0.000f, 0.000f, //16
	   0.500f, -0.500f, -2.500f, 1.000f, 0.000f, //17
	   0.500f, -0.500f, -3.500f, 1.000f, 1.000f, //18
	  -0.500f, -0.500f, -3.500f, 0.000f, 1.000f, //19

	  -0.500f,  0.500f, -2.500f, 0.000f, 0.000f, //20
	   0.500f,  0.500f, -2.500f, 1.000f, 0.000f, //21
	   0.500f,  0.500f, -3.500f, 1.000f, 1.000f, //22
	  -0.500f,  0.500f, -3.500f, 0.000f, 1.000f	 //23
};

unsigned int indices3D[] = {
	 0,  1,  2,
	 2,  0,  3,
	
	 4,  5,  6,
	 6,  4,  7,

	 8,  9, 10,
	10,  8, 11,

	12, 13, 14,
	14, 12, 15,

	16, 17, 18,
	18, 16, 19,

	20, 21, 22,
	22, 20, 23
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

Test::TestTexture3D::TestTexture3D()
{
	Timer();
	m_VertexBuffer = std::make_unique<VertexBuffer>(6 * 4 * 5 * sizeof(float), verticeMessage);
	m_VertexArray = std::make_unique<VertexArray>();

	VertexBufferLayout m_Layout;
	m_Layout.Push<float>(3);
	m_Layout.Push<float>(2);

	m_VertexArray->AddBuffer(*m_VertexBuffer, m_Layout);

	m_IndexBuffer = std::make_unique<IndexBuffer>(6 * 2 * 3 * sizeof(unsigned int), indices3D);

	m_Shader = std::make_unique<Shader>("res/shaders/3DTexture.shader");
	m_Shader->Bind();

	m_Texture1 = std::make_unique<Texture>("res/textures/SmileFace.png");
	m_Texture2 = std::make_unique<Texture>("res/textures/WoodBox.jpg");
	m_Texture1->Bind(0);
	m_Texture2->Bind(1);
	m_Shader->SetUniform1i("u_Texture1", 0);
	m_Shader->SetUniform1i("u_Texture2", 1);

	m_Shader->SetUniformMat4f("u_ProjMatrix", m_ProjMatrix);
	m_Shader->SetUniformMat4f("u_ViewMatrix", m_ViewMatrix);
	m_Shader->SetUniformMat4f("u_ModelMatrix", m_ModelMatrix);
}

Test::TestTexture3D::~TestTexture3D()
{
	m_VertexArray->UnBind();
	m_VertexBuffer->UnBind();
	m_IndexBuffer->UnBind();
	m_Shader->Unbind();
	m_Texture1->Unbind();
	m_Texture2->Unbind();
}

void Test::TestTexture3D::OnUpdate(float DeltaTime)
{
}

void Test::TestTexture3D::OnRender()
{
	Timer();
	Renderer renderer;
	renderer.Clean();
	float camera_X = (float)sin(glfwGetTime()) * radius;
	float camera_Z = (float)cos(glfwGetTime()) * radius;
	m_ViewMatrix = glm::lookAt(glm::vec3(camera_X, 0.000f, camera_Z), m_CameraDirection, glm::vec3(0.000f, 1.000f, 0.000f));
	m_Shader->SetUniformMat4f("u_ViewMatrix", m_ViewMatrix);
	for (unsigned int i = 0; i < 10; i++)
	{
		m_ModelMatrix = glm::translate(glm::mat4(1.000f), cubePositions[i]);
		m_ModelMatrix = glm::rotate(m_ModelMatrix, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
		m_Shader->SetUniformMat4f("u_ModelMatrix", m_ModelMatrix);
		renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
	}
}

void Test::TestTexture3D::OnImguiRender()
{
	ImGui::SliderFloat("Horizon", &m_CameraDirection[0],  -10.000f, 10.000f);
	ImGui::SliderFloat("Vertical", &m_CameraDirection[1], -10.000f, 10.000f);
	ImGui::SliderFloat("Depth", &m_CameraDirection[2], -10.000f, 10.000f);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
