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

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

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
	/* Initiate blender function */
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	glm::mat4 orthoMatrix = glm::ortho(0.000f, 640.000f, 0.000f, 640.000f);
	glm::vec3 translation1 = glm::vec3(0.000f, 0.000f, 0.000f);
	glm::vec3 translation2 = glm::vec3(0.000f, 0.000f, 0.000f);
	glm::mat4 viewMatrix  = glm::mat4(1.000f);
	glm::mat4 modelMatrix = glm::mat4(1.000f);
	glm::mat4 MVP = orthoMatrix * viewMatrix * modelMatrix;
	glm::vec4 clearColor  = glm::vec4(1.000f, 1.000f, 1.000f, 1.000f);
	glm::vec4 texColor    = glm::vec4(1.000f, 1.000f, 1.000f, 1.000f);

	Shader shaderProgram("res/shaders/Basic.shader");
	shaderProgram.Bind();

	Texture texture("res/textures/ACLogo.png");
	texture.Bind(0);
	shaderProgram.SetUniform1i("u_Texture", 0);

	float vertexMessage[] = {
		0.000f,   0.000f,   0.000f, 0.000f, 0.000f,
	    160.000f, 0.000f,   0.000f, 1.000f, 0.000f,
	    160.000f, 160.000f, 0.000f, 1.000f, 1.000f,
		0.000f,   160.000f, 0.000f, 0.000f, 1.000f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	Renderer renderer;

	VertexArray vertexArray = VertexArray();

	VertexBuffer vertexBuffer(4 * 5 * sizeof(float), vertexMessage);

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	vertexArray.AddBuffer(vertexBuffer, layout);

	IndexBuffer indexBuffer(2 * 3 * sizeof(unsigned int), indices);

	/*Setup ImGui context*/
	const char* glsl_version = "#version 330";
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	while (!glfwWindowShouldClose(window))
	{
		/* Poll for and process events */
		glfwPollEvents();
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		renderer.Clean();
		renderer.SetClearColor(clearColor);
		shaderProgram.SetUniform4f("u_Color", texColor[0], texColor[1], texColor[2], texColor[3]);

		viewMatrix = glm::translate(glm::mat4(1.000f), translation1);
		modelMatrix = glm::rotate(glm::mat4(1.000f), 2*(float)glfwGetTime(), glm::vec3(0.000f, 0.000f, -1.000f));
		MVP = orthoMatrix * viewMatrix * modelMatrix;
		shaderProgram.SetUniformMat4f("u_MVP", MVP);

		renderer.Draw(vertexArray, indexBuffer, shaderProgram);

		viewMatrix = glm::translate(glm::mat4(1.000f), translation2);
		MVP = orthoMatrix * viewMatrix * modelMatrix;
		shaderProgram.SetUniformMat4f("u_MVP", MVP);

		renderer.Draw(vertexArray, indexBuffer, shaderProgram);
		
		// Show a simple window editing some basic variables.
		{
			ImGui::Begin("OpenGL2019"); 
			ImGui::ColorEdit4("ClearColor", &clearColor[0], 0);                           //Background color editing
			ImGui::SliderFloat4("TextureColor", &texColor[0], 0.000f, 1.000f);            //Texture    color editing
			ImGui::SliderFloat("Object1 X", &translation1[0], 0.000f, 480.000f);          //Object1 Position editing
			ImGui::SliderFloat("Object1 Y", &translation1[1], 0.000f, 480.000f);
			ImGui::SliderFloat("Object2 X", &translation2[0], 0.000f, 480.000f);          //Object2 Position editing
			ImGui::SliderFloat("Object2 Y", &translation2[1], 0.000f, 480.000f);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
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