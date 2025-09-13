#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "raylib.h"
namespace constants {

inline constexpr int cellSize{30};
inline constexpr int cellCount{25};
inline constexpr int offset{75};

}  // namespace constants

namespace color {
// Constants Color
inline constexpr Color green = {173, 204, 96, 255};
inline constexpr Color darkGreen = {43, 51, 24, 255};
}  // namespace color

#endif
