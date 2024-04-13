#pragma once

////////////////////////////////////////////////////////////////////////////////
namespace Utils
{
// @brief Generate a random number in the interval defined by min and max
// @param min: Lower limit inclusive
// @param max: Upper limit inclusive
template <typename T>
inline T Random(T min, T max)
{
	double randPercent = (double)(rand() % 10001) / 10000;
	return (T)(randPercent * (max - min)) - min;
}

// @brief Generate true with a given probability 
// @param probability: A decimal number between 0 and 100%
inline bool Probability(float probability)
{
	return (float)(Random(0, 100)) <= probability;
}
} // !namespace Utils