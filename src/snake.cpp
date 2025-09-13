#include "snake.h"

#include <deque>
#include <iostream>

#include "constants.h"
#include "raylib.h"
#include "raymath.h"

using constants::cellSize;

void Snake::DrawSnake() const {
  for (const auto& [x, y] : body) {
    Rectangle segment{Rectangle{constants::offset + x * cellSize,
                                constants::offset + y * cellSize, cellSize,
                                cellSize}};
    DrawRectangleRounded(segment, 0.5, 6, color::darkGreen);
  }
}

void Snake::CheckInput() {
  if (IsKeyPressed(KEY_UP) && m_direction != SNAKE_DIRECTION::DOWN)
    m_direction = SNAKE_DIRECTION::UP;

  if (IsKeyPressed(KEY_DOWN) && m_direction != SNAKE_DIRECTION::UP)
    m_direction = SNAKE_DIRECTION::DOWN;

  if (IsKeyPressed(KEY_RIGHT) && m_direction != SNAKE_DIRECTION::LEFT)
    m_direction = SNAKE_DIRECTION::RIGHT;

  if (IsKeyPressed(KEY_LEFT) && m_direction != SNAKE_DIRECTION::RIGHT)
    m_direction = SNAKE_DIRECTION::LEFT;
}

void Snake::Update() {
  Vector2 direction{DIRECTION_VECTORS[static_cast<int>(m_direction)]};
  body.emplace_front(body.front() + direction);

  if (m_addSegment) {
    m_addSegment = false;
  } else {
    body.pop_back();
  }
}

void Snake::Reset() {
  body = {{6, 9}, {5, 9}, {4, 9}};
  m_direction = SNAKE_DIRECTION::RIGHT;
}

const Vector2 Snake::GetHead() const { return body.front(); }
const std::deque<Vector2> Snake::GetBody() const { return body; }
void Snake::setAddSegment(const bool addSegment) { m_addSegment = addSegment; }
