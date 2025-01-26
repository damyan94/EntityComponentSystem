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
	T random = (T)(rand() % 10001);
	T range = max - min;
	return min + (random * range) / 10000;
}

// @brief Generate true with a given probability 
// @param probability: A decimal number between 0 and 100%
inline bool Probability(float probability)
{
	return Random(0.0f, 100.0f) <= probability;
}
} // !namespace Utils