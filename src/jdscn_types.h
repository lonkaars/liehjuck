#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>

/** @file jdscn_types.h */

/**
 * @brief jdscn types and functions
 *
 * Namespace handling all jdscn file > json import > c++ jdscn::Scene class
 */
namespace jdscn
{

/** @brief 3D position, orientation, scale, and other things */
using FloatXYZ = std::array<float, 3>;
/** @brief 2D position, orientation, scale, and other things */
using FloatXY = std::array<float, 2>;

using Position = FloatXYZ;
using Scale = FloatXYZ;
using Orientation = FloatXYZ;

/** @brief Rasterized 2D position */
using Position2D = std::array<int, 2>;
/** @brief Array of 3 integers, each ranging from 0 to 255 */
using Color = std::array<int, 3>;

/** @brief Represents a 3D triangle */
using Tri = std::array<Position, 3>;
/** @brief Represents a 2D triangle */
using TriXY = std::array<FloatXY, 3>;
/** @brief Represents a rasterized 2D triangle as */
using Tri2D = std::array<Position2D, 3>;

using Vertices = std::vector<Tri>;
using UVFloat = std::vector<TriXY>;
using UV = std::vector<Tri2D>;

}; // namespace jdscn
