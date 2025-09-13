#include "utils.h"

#include "raymath.h"
bool ElementInDeque(const Vector2& element, const std::deque<Vector2>& deque) {
  for (const auto& item : deque) {
    if (element == item) return true;
  }
  return false;
}
