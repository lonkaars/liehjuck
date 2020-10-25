#include <gtest/gtest.h>
#include "../src/jdscn_types.h"
#include "../src/calc.h"

namespace {

TEST(CalcTest, Rotation2D) {
	EXPECT_EQ(
			jdscn::FloatXY({1, 0}),
			calc::rotate2D(jdscn::FloatXY({0, 1}), M_PI / 2)
			);
}

}

