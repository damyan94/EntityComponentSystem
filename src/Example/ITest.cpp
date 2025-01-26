#include <stdafx.h>

#include "Example/ITest.h"

////////////////////////////////////////////////////////////////////////////////
void TestStatistics::Reset()
{
	Duration			= 0;
	Created				= 0;
	Destroyed			= 0;
	ComponentsAdded		= 0;
	ComponentsChanged	= 0;
	ComponentsRemoved	= 0;
}

////////////////////////////////////////////////////////////////////////////////
void TestStatistics::Display() const
{
	Logger::LogInfo(Format("{0} us | Created: {1} | Destroyed: {2} | ComponentsAdded: {3} | ComponentsChanged: {4} | ComponentsRemoved: {5}",
		Duration, Created, Destroyed, ComponentsAdded, ComponentsChanged, ComponentsRemoved));
}

////////////////////////////////////////////////////////////////////////////////
void TestStatistics::Display(ETextColor textColor) const
{
	Logger::Log(Format("{0} us | Created: {1} | Destroyed: {2} | ComponentsAdded: {3} | ComponentsChanged: {4} | ComponentsRemoved: {5}",
		Duration, Created, Destroyed, ComponentsAdded, ComponentsChanged, ComponentsRemoved), textColor);
}

////////////////////////////////////////////////////////////////////////////////
void TestStatistics::operator+=(const TestStatistics& other)
{
	Duration			+= other.Duration;
	Created				+= other.Created;
	Destroyed			+= other.Destroyed;
	ComponentsAdded		+= other.ComponentsAdded;
	ComponentsChanged	+= other.ComponentsChanged;
	ComponentsRemoved	+= other.ComponentsRemoved;
}

////////////////////////////////////////////////////////////////////////////////
void TestStatistics::operator/=(int32_t factor)
{
	Duration			/= factor;
	Created				/= factor;
	Destroyed			/= factor;
	ComponentsAdded		/= factor;
	ComponentsChanged	/= factor;
	ComponentsRemoved	/= factor;
}