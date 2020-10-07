#include <array>
#include <vector>
namespace jdscn
{

using FloatXYZ = std::array<float, 3>;
using FloatXY = std::array<float, 2>;

using Position = FloatXYZ;	  // [<-, ->]
using Scale = FloatXYZ;		  // [<-, ->]
using Orientation = FloatXYZ; // [0, pi]

using Position2D = std::array<int, 2>; // [<-, ->]
using Color = std::array<int, 3>;	   // int [0, 255]

using Tri = std::array<Position, 3>;
using TriXY = std::array<FloatXY, 3>;
using Tri2D = std::array<Position2D, 3>;

using Vertices = std::vector<Tri>;
using UVFloat = std::vector<TriXY>;
using UV = std::vector<Tri2D>;

}; // namespace jdscn
