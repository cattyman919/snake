#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <memory>

#include "constants.h"
#include "food.h"
#include "raylib.h"
#include "snake.h"
enum class GAME_STATE { MENU, PLAYING, PAUSED, GAMEOVER };

class GameLoop {
 public:
  GameLoop();
  GameLoop(const GameLoop& other) = delete;
  GameLoop& operator=(const GameLoop& other) = delete;
  ~GameLoop();

  void Run();
  void GameOver();

  // Getter & Setter
  inline void setGameState(const GAME_STATE state);

 private:
  // Private Variables
  GAME_STATE gameState{GAME_STATE::MENU};

  // Objects
  // Snake m_snake{};
  std::unique_ptr<Snake> m_snake;
  std::unique_ptr<Food> m_food;
  int m_score{0};
  Sound eatSound;
  Sound wallSound;
  int m_selectedMenuItem{0};
  bool m_exitGame{false};

  // Constants Config
  const int m_screenWidth{constants::cellCount * constants::cellSize};
  const int m_screenHeight{constants::cellCount * constants::cellSize};
  const int m_gridWidth{m_screenWidth / constants::cellSize};
  const int m_gridHeight{m_screenHeight / constants::cellSize};

  // Keyboard Texture UI
  Texture2D m_tex_keyboard_arrow_up;
  Texture2D m_tex_keyboard_arrow_right;
  Texture2D m_tex_keyboard_arrow_down;
  Texture2D m_tex_keyboard_arrow_left;

  // Main Draw Method
  void Draw();

  // Draw Methods
  void DrawPlaying() const;
  void DrawMenu() const;
  void DrawGameOver() const;
  void DrawGrid() const;
  void DrawKeyboardUI() const;

  // Update Method
  void Update();
  void UpdateMenu();

  // Collisions Method
  void CheckCollisionFood();
  void CheckCollisionEdges();
  void CheckCollisionTail();
};

#endif
