#pragma once

class RandomNumberGenerator
{
public:
	RandomNumberGenerator();
	RandomNumberGenerator(int32_t seed);

	~RandomNumberGenerator();

	void				SetSeed(int32_t seed);
	void				SetMin(int32_t min);
	void				SetMax(int32_t max);

	uint64_t			GenerateUInt64();
	int64_t				GenerateInt64();
	double				GenerateDouble();

	uint64_t			GenerateUInt64(uint64_t min, uint64_t max);
	int64_t				GenerateInt64(int64_t min, int64_t max);
	double				GenerateDouble(double min, double max);

	template <typename T>
	T Generate()
	{
		return (T)Generate(m_Min, m_Max);
	}

	template <typename T>
	T Generate(T min, T max)
	{
		ReturnIf(max - min == 0, 0);
		return min + Lehmer64() % (max - min);
	}

private:
	uint64_t			Lehmer64();

private:
	uint64_t			m_Number;
	uint64_t			m_Min;
	uint64_t			m_Max;
};

template<>
inline float RandomNumberGenerator::Generate(float min, float max)
{
	ReturnIf((max - min) == 0, 0);
	double fraction = (double)GenerateUInt64(1000000000000000, 9999999999999999)
		/ 10000000000000000;

	return min + fraction * (max - min);
}

////////////////////////////////////////////////////////////////////////////////
namespace Utils
{
// @brief Generate a random number in the interval defined by min and max
// @param min: Lower limit inclusive
// @param max: Upper limit inclusive
template <typename T>
inline T Random(T min, T max)
{
	static RandomNumberGenerator rng;

	return rng.Generate<T>(min, max);
}

// @brief Generate true with a given probability 
// @param probability: A decimal number between 0 and 100%
inline bool Probability(float probability)
{
	return Random(0.0f, 100.0f) <= probability;
}
} // !namespace Utils