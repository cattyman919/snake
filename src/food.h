#ifndef FOOD_H
#define FOOD_H

#include <deque>
#include <vector>

#include "constants.h"
#include "raylib.h"

class Food {
 public:
  Food();
  Food(const Food& other) = delete;
  Food& operator=(const Food& other) = delete;
  ~Food();

  void Draw();

  const Vector2 GenerateRandomPos(
      const std::deque<Vector2>& snakeBody_pos) const;

  const Vector2 getPosition() const;
  void setPosition(const Vector2& position);

 private:
  Vector2 m_position;
  Texture2D m_texture;
};

#endif
