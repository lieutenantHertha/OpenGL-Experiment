#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "tests/Test.h"
#include "tests/TestClearColor.h"
#include "tests/TestTexture.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the GLFW library */
	if (!glfwInit())
	{
		std::cout << "GLFW library can't be initialized properly." << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a valid windows context */
	window = glfwCreateWindow(640, 640, "OpenGL2019", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(3);

	/* Initialize the GL extension wrangler library */
	if (glewInit() != GLEW_OK)
		std::cout << "Error! GLEW is not initialized properly!" << std::endl;
	else {
		std::cout << "GLEW   version: " << glewGetString(GLEW_VERSION) << std::endl;
		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	}

	/*Setup ImGui context*/
	const char* glsl_version = "#version 330";
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	/*Set up the testing framework*/ 
	Test::Test* currentTest = nullptr;
	Test::TestMenu* testMenu = new Test::TestMenu(currentTest);
	currentTest = testMenu;
	testMenu->RegisterTest<Test::TestClearColor>("Clear color");
	testMenu->RegisterTest<Test::TestTexture>("Texture");

	while (!glfwWindowShouldClose(window))
	{
		// Poll for and process events 
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Show a simple window including a menu to select which test gonna be run.
		if (currentTest) {
			currentTest->OnUpdate(0.0f);
			currentTest->OnRender();
			ImGui::Begin("Test Menu");
			if (currentTest != testMenu && ImGui::Button("<-")) {
				delete currentTest;
				currentTest = testMenu;
			}
			currentTest->OnImguiRender();
			ImGui::End();
		}

		// Rendering Editing Window
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}