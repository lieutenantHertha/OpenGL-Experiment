#include "Test.h"
#include "imgui/imgui.h"
#include "Renderer.h"

Test::TestMenu::TestMenu(Test *& currentTest)
	: m_CurrentTestPointer(currentTest)
{
}

void Test::TestMenu::OnImguiRender()
{
	for (std::pair<std::string, std::function<Test*()>>& test : m_Tests)
	{
		if(ImGui::Button(test.first.c_str()))
			m_CurrentTestPointer = test.second();
	}
}

void Test::TestMenu::OnRender()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glClearColor(0.000f, 0.000f, 0.000f, 1.000f));
}
