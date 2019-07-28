#pragma once
#include "Test.h"
#include "glm/glm.hpp"

namespace Test {
	class TestClearColor : public Test{
	private:
		glm::vec4 m_ClearColor;

	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime) override;
		void OnImguiRender() override;
		void OnRender() override;
	};
}