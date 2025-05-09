#include "stdafx.h"

#include "Utils/Random.h"

////////////////////////////////////////////////////////////////////////////////
RandomNumberGenerator::RandomNumberGenerator()
	: m_Number(time(nullptr))
	, m_Min(0)
	, m_Max(0)
{
}

////////////////////////////////////////////////////////////////////////////////
RandomNumberGenerator::RandomNumberGenerator(int32_t seed)
	: m_Number(seed)
	, m_Min(0)
	, m_Max(0)
{
}

////////////////////////////////////////////////////////////////////////////////
RandomNumberGenerator::~RandomNumberGenerator()
{
}

////////////////////////////////////////////////////////////////////////////////
void RandomNumberGenerator::SetSeed(int32_t seed)
{
	m_Number = seed;
}

////////////////////////////////////////////////////////////////////////////////
void RandomNumberGenerator::SetMin(int32_t min)
{
	m_Min = min;
}

////////////////////////////////////////////////////////////////////////////////
void RandomNumberGenerator::SetMax(int32_t max)
{
	m_Max = max;
}

////////////////////////////////////////////////////////////////////////////////
uint64_t RandomNumberGenerator::GenerateUInt64()
{
	return GenerateUInt64(m_Min, m_Max);
}

////////////////////////////////////////////////////////////////////////////////
int64_t RandomNumberGenerator::GenerateInt64()
{
	return GenerateInt64(m_Min, m_Max);
}

////////////////////////////////////////////////////////////////////////////////
double RandomNumberGenerator::GenerateDouble()
{
	return GenerateDouble((double)m_Min, (double)m_Max);
}

////////////////////////////////////////////////////////////////////////////////
uint64_t RandomNumberGenerator::GenerateUInt64(uint64_t min, uint64_t max)
{
	ReturnIf(max - min == 0, 0);
	return min + Lehmer64() % (max + 1 - min);
}

////////////////////////////////////////////////////////////////////////////////
int64_t RandomNumberGenerator::GenerateInt64(int64_t min, int64_t max)
{
	ReturnIf(max - min == 0, 0);
	return min + Lehmer64() % (max + 1 - min);
}

////////////////////////////////////////////////////////////////////////////////
double RandomNumberGenerator::GenerateDouble(double min, double max, size_t precision)
{
	//TODO maybe make precision depend on the number of digits of max (log(max))
	//so if we have 2 digits, add 4, to get 6 digit precision, if we have 4 digits, we would have 8
	ReturnIf((max - min) == 0, 0);
	const uint64_t largeNumber = std::pow(10, precision);
	const uint64_t largeNumber10 = largeNumber * 10;
	double fraction = (double)GenerateUInt64(largeNumber, largeNumber10 - 1)
		/ largeNumber10;

	return min + fraction * (max + 1 - min);
}

////////////////////////////////////////////////////////////////////////////////
uint64_t RandomNumberGenerator::Lehmer64()
{
	m_Number += 0xE120FC15;
	uint64_t tmp;

	tmp = m_Number * 0x4A39B70D;
	uint64_t m1 = (tmp >> 32) ^ tmp;

	tmp = m1 * 0x12FAD5C9;
	uint64_t m2 = (tmp >> 32) ^ tmp;

	return m2;
}