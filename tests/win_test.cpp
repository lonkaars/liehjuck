#include "../src/jdscn_types.h"
#include "../src/win.h"
#include <gtest/gtest.h>

namespace
{

int test_width = 100;
int test_height = 100;
const char *test_title = "[floating] Unit test window";

TEST(WinTest, CreateWindow) { EXPECT_NO_THROW(win::Canvas(test_width, test_height, test_title)); }

TEST(WinTest, Draw)
{
	win::Canvas test(test_width, test_height, test_title);
	EXPECT_NO_THROW(test.draw(50, 50, jdscn::Color({255, 255, 255})));
}

TEST(WinTest, Clear)
{
	win::Canvas test(test_width, test_height, test_title);
	EXPECT_NO_THROW(test.clear());
}

} // namespace
