#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>

namespace Test {
	class Test {
	public:
		Test() {}
		virtual ~Test() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImguiRender() {}
	};

	class TestMenu : public Test {
	private:

		Test*& m_CurrentTestPointer;                     //Simutaneanously as a Test class pointer and a reference itself.
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;

	public:
		TestMenu(Test*& currentTestPointer);
		void OnImguiRender() override;
		void OnRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
			std::cout << "Registering : " << name << std::endl;
		}
	};
}
