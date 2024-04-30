#include "Example/ITest.h"

#include "Defines.h"

////////////////////////////////////////////////////////////////////////////////
void TestStatistics::Reset()
{
	Created = 0;
	Destroyed = 0;
	ComponentsAdded = 0;
	ComponentsChanged = 0;
	ComponentsRemoved = 0;
}

////////////////////////////////////////////////////////////////////////////////
void TestStatistics::Display(int32_t duration) const
{
	Log(std::to_string(duration) + " us" +
		" | Created: " + std::to_string(Created) +
		" | Destroyed: " + std::to_string(Destroyed) +
		" | ComponentsAdded: " + std::to_string(ComponentsAdded) +
		" | ComponentsChanged: " + std::to_string(ComponentsChanged) +
		" | ComponentsRemoved: " + std::to_string(ComponentsRemoved));
}