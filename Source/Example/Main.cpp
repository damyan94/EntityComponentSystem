#include <stdafx.h>

#include "Defines.h"
#include "Example/BaselineTest.h"
#include "Example/EntityTest.h"
#include "Example/GameObjectTest.h"
#include "Example/SystemTest.h"

#define TARGET_FPS 60

////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argC, char** argV)
{
	srand((uint32_t)time(nullptr));
	
	Logger::SetLogLevel(ELogLevel::LogError);

	bool headless = false;

	if (argC >= 2)
	{
		headless = argV[1][0] == '1' ? true : false;
	}

	int32_t testId = 0;
	std::cin >> testId;

	ITest* test = nullptr;
	switch (testId)
	{
	case 0: test = new BaselineTest(); break;
	case 1: test = new EntityTest(); break;
	case 2: test = new GameObjectTest(); break;
	case 3: test = new SystemTest(); break;
	}
	AssertReturnIf(!test, 1);

	DrawManager::Instance().Init(headless);

	test->Init();

	uint64_t sumfps = 0;
	uint64_t i = 0;

	TimePoint totalUpdate = 0;
	TimePoint totalRender = 0;
	TimePoint totalTotal = 0;

	while (i <= 1000)
	{
		Time start;

		DrawManager::Instance().ClearScreen();

		//test->Run(1);

		test->Update();
		//const auto update = start.GetElapsedTimeUntilNow(EUnitOfTime::Millisecond);
		const auto update = start.GetElapsedTimeUntilNow(EUnitOfTime::Millisecond);
		totalUpdate += update;

		test->Render();
		DrawManager::Instance().FinishFrame();
		const auto render = start.GetElapsedTimeUntilNow(EUnitOfTime::Millisecond);
		totalRender += render;

		const auto total = update + render;
		totalTotal += total;
		const auto sleep = 1000 / TARGET_FPS - total;

		//Logger::Log(Format("Update: {0} ms, Render: {1} ms.", update, render), ETextColor::Cyan);

		//const auto fps = 1000 / (total);
		const auto fps = 1000 / (total + sleep);
		sumfps += fps;
		i++;

		//Logger::Log(Format("{0} FPS.", fps), ETextColor::Cyan);
		//Logger::Log(Format("Average FPS: {0}.", sumfps / i), ETextColor::Cyan);

		std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
	}

	Logger::Log(Format("Update: {0} ms, Render: {1} ms.", totalUpdate / i, totalRender / i), ETextColor::Cyan);
	Logger::Log(Format("Average FPS: {0}.", sumfps / i), ETextColor::Cyan);

	return EXIT_SUCCESS;
}