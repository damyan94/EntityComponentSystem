#pragma once

#include <cstdint>

////////////////////////////////////////////////////////////////////////////////
enum class EComponentType
	: int32_t
{
	Invalid = -1

	, Transform
	, Image
	, Text
	, Action

	, Count
};