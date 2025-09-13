#ifndef SNAKE_H
#define SNAKE_H

#include <array>
#include <deque>
#include <vector>

#include "raylib.h"
enum class SNAKE_DIRECTION : int { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3 };

inline constexpr std::array<Vector2, 4> DIRECTION_VECTORS{{
    {-1, 0},  // LEFT
    {1, 0},   // RIGHT
    {0, -1},  // UP
    {0, 1}    // DOWN
}};

class Snake {
 public:
  Snake() = default;
  Snake(const Snake& other) = delete;
  Snake& operator=(const Snake& other) = delete;

  void DrawSnake() const;
  void Update();
  void CheckInput();
  void Reset();

  // Getters & Setters
  const Vector2 GetHead() const;
  const std::deque<Vector2> GetBody() const;
  void setAddSegment(const bool addSegment);

 private:
  int m_length{1};
  bool m_addSegment{false};
  std::deque<Vector2> body{{6, 9}, {5, 9}, {4, 9}};
  SNAKE_DIRECTION m_direction{SNAKE_DIRECTION::DOWN};
};

#endif
