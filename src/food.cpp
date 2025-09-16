#include "food.h"

#include <deque>

#include "constants.h"
#include "raylib.h"
#include "utils.h"

// #define DEBUG

Food::Food() {
  Image image = LoadImage(ASSETS_PATH "images/apple.png");
  m_texture = LoadTextureFromImage(image);
  UnloadImage(image);
#ifdef DEBUG
  TraceLog(LOG_INFO, "Food Position {%f, %f}", m_position.x, m_position.y);
#endif
}

Food::~Food() { UnloadTexture(m_texture); }

void Food::Draw() {
  DrawTexture(m_texture, constants::offset + m_position.x * constants::cellSize,
              constants::offset + m_position.y * constants::cellSize, WHITE);
}

inline const Vector2 generateRandomCell() {
  float x{static_cast<float>(GetRandomValue(0, constants::cellCount - 1))};
  float y{static_cast<float>(GetRandomValue(0, constants::cellCount - 1))};
  return Vector2{x, y};
}

const Vector2 Food::GenerateRandomPos(
    const std::deque<Vector2>& snakeBody) const {
  Vector2 position{generateRandomCell()};

  while (ElementInDeque(position, snakeBody)) {
    position = generateRandomCell();
  }
  return position;
}

const Vector2 Food::getPosition() const { return m_position; }

void Food::setPosition(const Vector2& position) { m_position = position; }
