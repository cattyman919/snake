#include "utils.h"

#include <vector>

#include "raymath.h"
bool ElementInDeque(const Vector2& element, const std::deque<Vector2>& array) {
  for (const auto& item : array) {
    if (element == item) return true;
  }
  return false;
}
