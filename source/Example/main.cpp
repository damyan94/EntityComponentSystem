#include <cstdint>
#include <ctime>

#include "Defines.h"
#include "Example/EntityTest.h"
#include "Example/GameObjectTest.h"

int32_t main(int32_t argC, char** argV)
{
	srand((uint32_t)time(nullptr));

	//EntityTest test1;
	//test1.Run(10);

	GameObjectTest test2;
	test2.Run(10);

	system("pause");
	return EXIT_SUCCESS;
}