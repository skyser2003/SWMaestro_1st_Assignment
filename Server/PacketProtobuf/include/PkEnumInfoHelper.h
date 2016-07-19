#pragma once

template <class Enum>
constexpr int GetIntVal(Enum enumVal)
{
	return static_cast<int>(enumVal);
}