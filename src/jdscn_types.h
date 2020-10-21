#include <array>
#include <vector>

/**
 * @namespace jdscn
 * @brief jdscn types and functions
 *
 * Namespace handling all jdscn file > json import > c++ jdscn::Scene class
 */
namespace jdscn
{

/**
 * @struct FloatXYZ
 * @brief `std::array<float, 3>`, used for 3D position, orientation, scale, and other things
 */
using FloatXYZ = std::array<float, 3>;
/**
 * @struct FloatXY
 * @brief `std::array<float, 2>`, used for 2D position, orientation, scale, and other things
 */
using FloatXY = std::array<float, 2>;

/**
 * @struct Position
 * @brief Alias to `FloatXYZ`
 */
using Position = FloatXYZ;
/**
 * @struct Scale
 * @brief Alias to `FloatXYZ`
 */
using Scale = FloatXYZ;
/**
 * @struct Orientation
 * @brief Alias to `FloatXYZ`
 */
using Orientation = FloatXYZ;

/**
 * @struct Position2D
 * @brief `std::array<int, 2>`
 */
using Position2D = std::array<int, 2>;
/**
 * @struct Color
 * @brief Array of 3 integers, each ranging from 0 to 255
 */
using Color = std::array<int, 3>;

/**
 * @struct Tri
 * @brief Represents a 3D triangle as `std::array<Position, 3>`
 */
using Tri = std::array<Position, 3>;
/**
 * @struct TriXY
 * @brief Represents a 2D triangle as `std::array<FloatXY, 3>`
 */
using TriXY = std::array<FloatXY, 3>;
/**
 * @struct Tri2D
 * @brief Represents a rasterized 2D triangle as `std::array<Position2D, 3>`
 */
using Tri2D = std::array<Position2D, 3>;

/**
 * @struct Vertices
 * @brief `std::vector<Tri>`
 */
using Vertices = std::vector<Tri>;
/**
 * @struct UVFloat
 * @brief `std::vector<TriXY>`
 */
using UVFloat = std::vector<TriXY>;
/**
 * @struct UV
 * @brief `std::vector<Tri2D>`
 */
using UV = std::vector<Tri2D>;

}; // namespace jdscn
