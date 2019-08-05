#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <chrono>

namespace Test {
	class Test {
	public:
		Test() {}
		virtual ~Test() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImguiRender() {}

		struct Timer {

			std::chrono::time_point<std::chrono::steady_clock> start;
			std::chrono::time_point<std::chrono::steady_clock> end;
			std::chrono::duration<float> duration;
			
			Timer() 
			{
				start = std::chrono::high_resolution_clock::now();
			}
			~Timer()
			{
				end = std::chrono::high_resolution_clock::now();
				duration = end - start;
				std::cout << "Timer took " << duration.count() * 1000 << "ms" << std::endl;
			}
		};
	};

	class TestMenu : public Test {
	private:

		Test*& m_CurrentTestPointer;                                                    //Pointer and reference
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
