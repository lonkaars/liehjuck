#include <array>
#include <vector>

namespace jdscn
{

/**
 * @struct FloatXYZ
 * Array with 3 floats, used for 3D position, orientation, scale, and other things
 */
using FloatXYZ = std::array<float, 3>;
/**
 * @struct FloatXY
 * Array with 2 floats, used for 2D position, orientation, scale, and other things
 */
using FloatXY = std::array<float, 2>;

/**
 * @struct Position
 * Alias
 */
using Position = FloatXYZ;
/**
 * @struct Scale
 * Alias
 */
using Scale = FloatXYZ;
/**
 * @struct Orientation
 * Alias
 */
using Orientation = FloatXYZ;

/**
 * @struct Position2D
 */
using Position2D = std::array<int, 2>;
/**
 * @struct Color
 */
using Color = std::array<int, 3>;

/**
 * @struct Tri
 */
using Tri = std::array<Position, 3>;
/**
 * @struct TriXY
 */
using TriXY = std::array<FloatXY, 3>;
/**
 * @struct Tri2D
 */
using Tri2D = std::array<Position2D, 3>;

/**
 * @struct Vertices
 */
using Vertices = std::vector<Tri>;
/**
 * @struct UVFloat
 */
using UVFloat = std::vector<TriXY>;
/**
 * @struct UV
 */
using UV = std::vector<Tri2D>;

}; // namespace jdscn
