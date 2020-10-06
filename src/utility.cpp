#include "utility.h"
#include <array>
#include <math.h>
#include <stdlib.h>

namespace utility
{

std::array<float, 2> rotate2D(std::array<float, 2> point, float angle)
{
	float cos = std::cos(angle);
	float sin = std::sin(angle);
	return std::array<float, 2>{cos * point[0] - sin * point[1], sin * point[0] + cos * point[1]};
}

}; // namespace utility
