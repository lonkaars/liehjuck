#include "utility.h"
#include "jdscn_types.h"
#include <array>
#include <math.h>
#include <stdlib.h>

namespace utility
{

jdscn::FloatXY rotate2D(jdscn::FloatXY point, float angle)
{
	float cos = std::cos(angle);
	float sin = std::sin(angle);
	return jdscn::FloatXY({cos * point[0] - sin * point[1], sin * point[0] + cos * point[1]});
}

}; // namespace utility
