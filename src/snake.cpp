#include "snake.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

#include "constants.h"
#include "raylib.h"
#include "raymath.h"

using constants::cellSize;

Snake::Snake() {
  Image snake_head_up_img = LoadImage(ASSETS_PATH "images/snake/head_up.png");
  Image snake_head_down_img =
      LoadImage(ASSETS_PATH "images/snake/head_down.png");
  Image snake_head_right_img =
      LoadImage(ASSETS_PATH "images/snake/head_right.png");
  Image snake_head_left_img =
      LoadImage(ASSETS_PATH "images/snake/head_left.png");

  Image snake_tail_up_img = LoadImage(ASSETS_PATH "images/snake/tail_up.png");
  Image snake_tail_down_img =
      LoadImage(ASSETS_PATH "images/snake/tail_down.png");
  Image snake_tail_right_img =
      LoadImage(ASSETS_PATH "images/snake/tail_right.png");
  Image snake_tail_left_img =
      LoadImage(ASSETS_PATH "images/snake/tail_left.png");

  Image snake_body_vertical_img =
      LoadImage(ASSETS_PATH "images/snake/body_vertical.png");

  Image snake_body_horizontal_img =
      LoadImage(ASSETS_PATH "images/snake/body_horizontal.png");

  Image snake_body_bottomleft_img =
      LoadImage(ASSETS_PATH "images/snake/body_bottomleft.png");
  Image snake_body_bottomright_img =
      LoadImage(ASSETS_PATH "images/snake/body_bottomright.png");
  Image snake_body_topleft_img =
      LoadImage(ASSETS_PATH "images/snake/body_topleft.png");
  Image snake_body_topright_img =
      LoadImage(ASSETS_PATH "images/snake/body_topright.png");

  m_texture_head_up = LoadTextureFromImage(snake_head_up_img);
  m_texture_head_down = LoadTextureFromImage(snake_head_down_img);
  m_texture_head_right = LoadTextureFromImage(snake_head_right_img);
  m_texture_head_left = LoadTextureFromImage(snake_head_left_img);

  UnloadImage(snake_head_up_img);
  UnloadImage(snake_head_down_img);
  UnloadImage(snake_head_right_img);
  UnloadImage(snake_head_left_img);

  m_texture_tail_up = LoadTextureFromImage(snake_tail_up_img);
  m_texture_tail_down = LoadTextureFromImage(snake_tail_down_img);
  m_texture_tail_right = LoadTextureFromImage(snake_tail_right_img);
  m_texture_tail_left = LoadTextureFromImage(snake_tail_left_img);

  UnloadImage(snake_tail_up_img);
  UnloadImage(snake_tail_down_img);
  UnloadImage(snake_tail_right_img);
  UnloadImage(snake_tail_left_img);

  m_texture_body_vertical = LoadTextureFromImage(snake_body_vertical_img);
  m_texture_body_horizontal = LoadTextureFromImage(snake_body_horizontal_img);
  m_texture_body_bottomleft = LoadTextureFromImage(snake_body_bottomleft_img);
  m_texture_body_bottomright = LoadTextureFromImage(snake_body_bottomright_img);
  m_texture_body_topleft = LoadTextureFromImage(snake_body_topleft_img);
  m_texture_body_topright = LoadTextureFromImage(snake_body_topright_img);

  UnloadImage(snake_body_horizontal_img);
  UnloadImage(snake_body_vertical_img);
  UnloadImage(snake_body_bottomleft_img);
  UnloadImage(snake_body_bottomright_img);
  UnloadImage(snake_body_topleft_img);
  UnloadImage(snake_body_topright_img);
}

Snake::~Snake() {
  UnloadTexture(m_texture_head_up);
  UnloadTexture(m_texture_head_down);
  UnloadTexture(m_texture_head_right);
  UnloadTexture(m_texture_head_left);

  UnloadTexture(m_texture_tail_up);
  UnloadTexture(m_texture_tail_down);
  UnloadTexture(m_texture_tail_right);
  UnloadTexture(m_texture_tail_left);

  UnloadTexture(m_texture_body_vertical);
  UnloadTexture(m_texture_body_horizontal);
  UnloadTexture(m_texture_body_topleft);
  UnloadTexture(m_texture_body_topright);
  UnloadTexture(m_texture_body_bottomleft);
  UnloadTexture(m_texture_body_bottomright);
}

void Snake::DrawSnake() const {
  for (const auto& [pos, dir] : body) {
    if (body.front().first == pos) {  // Head
      switch (m_direction) {
        case SNAKE_DIRECTION::LEFT:
          DrawTexture(m_texture_head_left, constants::offset + pos.x * cellSize,
                      constants::offset + pos.y * cellSize, WHITE);
          break;
        case SNAKE_DIRECTION::RIGHT:
          DrawTexture(m_texture_head_right,
                      constants::offset + pos.x * cellSize,
                      constants::offset + pos.y * cellSize, WHITE);
          break;
        case SNAKE_DIRECTION::UP:
          DrawTexture(m_texture_head_up, constants::offset + pos.x * cellSize,
                      constants::offset + pos.y * cellSize, WHITE);
          break;
        case SNAKE_DIRECTION::DOWN:
          DrawTexture(m_texture_head_down, constants::offset + pos.x * cellSize,
                      constants::offset + pos.y * cellSize, WHITE);
          break;
        default:
          DrawTexture(m_texture_head_down, constants::offset + pos.x * cellSize,
                      constants::offset + pos.y * cellSize, WHITE);
          break;
      }

    } else if (body.back().first == pos) {  // Tail
      switch (dir) {
        case SNAKE_DIRECTION::LEFT:
          DrawTexture(m_texture_tail_right,
                      constants::offset + pos.x * cellSize,
                      constants::offset + pos.y * cellSize, WHITE);
          break;
        case SNAKE_DIRECTION::RIGHT:
          DrawTexture(m_texture_tail_left, constants::offset + pos.x * cellSize,
                      constants::offset + pos.y * cellSize, WHITE);
          break;
        case SNAKE_DIRECTION::UP:
        case SNAKE_DIRECTION::TOP_LEFT:
        case SNAKE_DIRECTION::TOP_RIGHT:
          DrawTexture(m_texture_tail_down, constants::offset + pos.x * cellSize,
                      constants::offset + pos.y * cellSize, WHITE);
          break;
        case SNAKE_DIRECTION::DOWN:
        case SNAKE_DIRECTION::BOTTOM_LEFT:
        case SNAKE_DIRECTION::BOTTOM_RIGHT:
          DrawTexture(m_texture_tail_up, constants::offset + pos.x * cellSize,
                      constants::offset + pos.y * cellSize, WHITE);
          break;
      }
    } else {  // Body
      switch (dir) {
        case SNAKE_DIRECTION::LEFT:
        case SNAKE_DIRECTION::RIGHT:
          DrawTexture(m_texture_body_horizontal,
                      constants::offset + pos.x * cellSize,
                      constants::offset + pos.y * cellSize, WHITE);
          break;
        case SNAKE_DIRECTION::UP:
        case SNAKE_DIRECTION::DOWN:
          DrawTexture(m_texture_body_vertical,
                      constants::offset + pos.x * cellSize,
                      constants::offset + pos.y * cellSize, WHITE);
          break;
        case SNAKE_DIRECTION::BOTTOM_LEFT:
          DrawTexture(m_texture_body_bottomleft,
                      constants::offset + pos.x * cellSize,
                      constants::offset + pos.y * cellSize, WHITE);
          break;
        case SNAKE_DIRECTION::BOTTOM_RIGHT:
          DrawTexture(m_texture_body_bottomright,
                      constants::offset + pos.x * cellSize,
                      constants::offset + pos.y * cellSize, WHITE);
          break;
        case SNAKE_DIRECTION::TOP_LEFT:
          DrawTexture(m_texture_body_topleft,
                      constants::offset + pos.x * cellSize,
                      constants::offset + pos.y * cellSize, WHITE);
          break;
        case SNAKE_DIRECTION::TOP_RIGHT:
          DrawTexture(m_texture_body_topright,
                      constants::offset + pos.x * cellSize,
                      constants::offset + pos.y * cellSize, WHITE);
          break;
      }
      // Rectangle segment{Rectangle{constants::offset + pos.x * cellSize,
      //                             constants::offset + pos.y * cellSize,
      //                             cellSize, cellSize}};
      // DrawRectangleRounded(segment, 0.5, 6, color::darkGreen);
    }
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
  static SNAKE_DIRECTION last_direction{m_direction};

  Vector2 direction{DIRECTION_VECTORS[static_cast<int>(m_direction)]};
  if (m_direction != last_direction) {  // Sharp Turns
    switch (last_direction) {
      case SNAKE_DIRECTION::LEFT:
        if (m_direction == SNAKE_DIRECTION::UP) {
          body.front().second = SNAKE_DIRECTION::TOP_RIGHT;
        } else if (m_direction == SNAKE_DIRECTION::DOWN) {
          body.front().second = SNAKE_DIRECTION::BOTTOM_RIGHT;
        }
        break;
      case SNAKE_DIRECTION::RIGHT:
        if (m_direction == SNAKE_DIRECTION::UP) {
          body.front().second = SNAKE_DIRECTION::TOP_LEFT;
        } else if (m_direction == SNAKE_DIRECTION::DOWN) {
          body.front().second = SNAKE_DIRECTION::BOTTOM_LEFT;
        }
        break;
      case SNAKE_DIRECTION::UP:
        if (m_direction == SNAKE_DIRECTION::RIGHT) {
          body.front().second = SNAKE_DIRECTION::BOTTOM_RIGHT;
        } else if (m_direction == SNAKE_DIRECTION::LEFT) {
          body.front().second = SNAKE_DIRECTION::BOTTOM_LEFT;
        }
        break;
      case SNAKE_DIRECTION::DOWN:
        if (m_direction == SNAKE_DIRECTION::RIGHT) {
          body.front().second = SNAKE_DIRECTION::TOP_RIGHT;
        } else if (m_direction == SNAKE_DIRECTION::LEFT) {
          body.front().second = SNAKE_DIRECTION::TOP_LEFT;
        }
      default:
        break;
    }
  }
  body.emplace_front(
      std::make_pair(body.front().first + direction, m_direction));

  last_direction = m_direction;

  if (m_addSegment) {
    m_addSegment = false;
  } else {
    body.pop_back();
  }
}

void Snake::Reset() {
  body = {
      {{6, 9}, SNAKE_DIRECTION::RIGHT},
      {{5, 9}, SNAKE_DIRECTION::RIGHT},
      {{4, 9}, SNAKE_DIRECTION::RIGHT},
  };
  m_direction = SNAKE_DIRECTION::RIGHT;
}

const Vector2 Snake::GetHead() const { return body.front().first; }
const std::deque<Vector2> Snake::GetBodyPos() const {
  std::deque<Vector2> snake_body_pos;

  std::transform(body.begin(), body.end(), std::back_inserter(snake_body_pos),
                 [](const auto& pair) { return pair.first; });

  return snake_body_pos;
}
void Snake::setAddSegment(const bool addSegment) { m_addSegment = addSegment; }
