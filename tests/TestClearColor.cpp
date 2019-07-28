#include "TestClearColor.h"
#include "Renderer.h"
#include "imgui/imgui.h"

Test::TestClearColor::TestClearColor() : m_ClearColor(glm::vec4(1.000f, 1.000f, 1.000f, 1.000f))
{
}

Test::TestClearColor::~TestClearColor()
{
}

void Test::TestClearColor::OnUpdate(float deltaTime)
{
}

void Test::TestClearColor::OnImguiRender()
{
	ImGui::ColorEdit4("Clear Color Test", &m_ClearColor[0], 0);
}

void Test::TestClearColor::OnRender()
{
	GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}