#include <stdafx.h>

#include "Defines.h"
#include "Example/BaselineTest.h"
#include "Example/EntityTest.h"
#include "Example/GameObjectTest.h"
#include "Example/SystemTest.h"

////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argC, char** argV)
{
	srand((uint32_t)time(nullptr));
	
	Logger::SetLogLevel(ELogLevel::LogText);

	DrawManager::Instance().Init();

	while (true)
	{
		Time start;

		BaselineTest test0;
		test0.Run(1);

		//EntityTest test1;
		//test1.Run(1);

		//GameObjectTest test2;
		//test2.Run(1);

		//SystemTest test3;
		//test3.Run(1);

		auto fps = 1000 / (start.GetElapsedTimeUntilNow(EUnitOfTime::Millisecond));
		Logger::Log(Format("{0} FPS.", fps), ETextColor::Cyan);
	}

	return EXIT_SUCCESS;
}