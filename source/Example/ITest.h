#pragma once

#include <cstdint>

////////////////////////////////////////////////////////////////////////////////
struct TestStatistics
{
	void Reset();
	void Display(int32_t duration) const;

	int32_t Created = 0;
	int32_t Destroyed = 0;
	int32_t ComponentsAdded = 0;
	int32_t ComponentsChanged = 0;
	int32_t ComponentsRemoved = 0;
};

////////////////////////////////////////////////////////////////////////////////
class ITest
{
public:
	ITest() = default;
	virtual ~ITest() = default;

	virtual void Run(int32_t runs) = 0;

protected:
	TestStatistics m_TestStatistics;
};