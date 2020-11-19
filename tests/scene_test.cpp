#include "../src/jdscn_types.h"
#include "../src/scene.h"
#include "objects.h"
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

namespace
{

jdscn::Object testObject(default_cube);

TEST(SceneTest, TransformScale)
{
	jdscn::Object testObject_transformed(default_cube);
	testObject.transformScale({2, 2, 2});
}

} // namespace
