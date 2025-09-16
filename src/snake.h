#ifndef SNAKE_H
#define SNAKE_H

#include <array>
#include <deque>
#include <utility>
#include <vector>

#include "raylib.h"
enum class SNAKE_DIRECTION : int {
  LEFT = 0,
  RIGHT = 1,
  UP = 2,
  DOWN = 3,
  BOTTOM_LEFT = 4,
  BOTTOM_RIGHT = 5,
  TOP_LEFT = 6,
  TOP_RIGHT = 7,
};

inline constexpr std::array<Vector2, 4> DIRECTION_VECTORS{{
    {-1, 0},  // LEFT
    {1, 0},   // RIGHT
    {0, -1},  // UP
    {0, 1}    // DOWN
}};

class Snake {
 public:
  Snake();
  Snake(const Snake& other) = delete;
  Snake& operator=(const Snake& other) = delete;
  ~Snake();

  void DrawSnake() const;
  void Update();
  void CheckInput();
  void Reset();

  // Getters & Setters
  const Vector2 GetHead() const;
  const std::deque<Vector2> GetBodyPos() const;
  void setAddSegment(const bool addSegment);

 private:
  int m_length{1};
  bool m_addSegment{false};
  std::deque<std::pair<Vector2, SNAKE_DIRECTION>> body{
      {{6, 9}, SNAKE_DIRECTION::RIGHT},
      {{5, 9}, SNAKE_DIRECTION::RIGHT},
      {{4, 9}, SNAKE_DIRECTION::RIGHT},
  };
  SNAKE_DIRECTION m_direction{SNAKE_DIRECTION::DOWN};

  // Texture2D
  Texture2D m_texture_head_up;
  Texture2D m_texture_head_down;
  Texture2D m_texture_head_right;
  Texture2D m_texture_head_left;

  Texture2D m_texture_tail_up;
  Texture2D m_texture_tail_down;
  Texture2D m_texture_tail_right;
  Texture2D m_texture_tail_left;

  Texture2D m_texture_body_vertical;
  Texture2D m_texture_body_horizontal;
  Texture2D m_texture_body_bottomleft;
  Texture2D m_texture_body_bottomright;
  Texture2D m_texture_body_topleft;
  Texture2D m_texture_body_topright;
};

#endif
