#include "../src/calc.h"
#include "../src/jdscn_types.h"
#include <gtest/gtest.h>

namespace
{

TEST(CalcTest, Rotation2D)
{
	double precision = 0.000001;

	using test_case_type = std::tuple<jdscn::FloatXY, jdscn::FloatXY, float>;

	std::vector<test_case_type> test_cases = {
		{{1, 0}, {-1, 0}, M_PI}, {{1, 0}, {0, 1}, M_PI / 2}, {{1, 0}, {1, 0}, M_PI * 2}};

	for (test_case_type test_case : test_cases) {
		jdscn::FloatXY result = calc::rotate2D(std::get<0>(test_case), std::get<2>(test_case));
		ASSERT_NEAR(result[0], std::get<1>(test_case)[0], precision);
		ASSERT_NEAR(result[1], std::get<1>(test_case)[1], precision);
	}
}

TEST(CalcTest, Rotation3D)
{
	double precision = 0.000001;

	using test_case_type = std::tuple<jdscn::Position, jdscn::Position, jdscn::Orientation>;

	std::vector<test_case_type> test_cases = {
		{{1, 1, 1}, {1, 1, 1}, {0, 0, 0}},		   {{1, 1, 1}, {1, -1, -1}, {M_PI, 0, 0}},
		{{1, 1, 1}, {-1, 1, -1}, {0, M_PI, 0}},	   {{1, 1, 1}, {-1, -1, 1}, {0, 0, M_PI}},
		{{1, 1, 1}, {1, -1, -1}, {0, M_PI, M_PI}}, {{1, 1, 1}, {-1, 1, -1}, {M_PI, 0, M_PI}},
		{{1, 1, 1}, {-1, -1, 1}, {M_PI, M_PI, 0}}, {{1, 1, 1}, {1, 1, 1}, {M_PI, M_PI, M_PI}}};

	for (test_case_type test_case : test_cases) {
		jdscn::Position result = calc::rotate3D(std::get<0>(test_case), std::get<2>(test_case));
		ASSERT_NEAR(result[0], std::get<1>(test_case)[0], precision);
		ASSERT_NEAR(result[1], std::get<1>(test_case)[1], precision);
		ASSERT_NEAR(result[2], std::get<1>(test_case)[2], precision);
	}
}

} // namespace
