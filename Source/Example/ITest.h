#pragma once

////////////////////////////////////////////////////////////////////////////////
struct TestStatistics
{
	void Reset();
	void Display() const;
	void Display(ETextColor textColor) const;

	void operator+=(const TestStatistics& other);
	void operator/=(int32_t factor);

	int64_t Duration = 0;
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
	TestStatistics m_AverageTestStatistics;
};