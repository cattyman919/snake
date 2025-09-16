#include "game_loop.h"

#include <deque>
#include <memory>

#include "constants.h"
#include "food.h"
#include "raylib.h"
#include "raymath.h"
#include "utils.h"

double lastUpdateTime = 0;

bool eventTriggered(double interval) {
  double currentTime = GetTime();

  if (currentTime - lastUpdateTime >= interval) {
    lastUpdateTime = currentTime;
    return true;
  }
  return false;
}

GameLoop::GameLoop() {
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
  SetTargetFPS(60);

  InitWindow(2 * constants::offset + m_screenWidth,
             2 * constants::offset + m_screenHeight, "Snake Game");

  SetExitKey(KEY_NULL);

  // Load Keyboard UI Images
  Image image_up =
      LoadImage(ASSETS_PATH "images/ui/keyboard_arrow_up_outline.png");
  Image image_down =
      LoadImage(ASSETS_PATH "images/ui/keyboard_arrow_down_outline.png");
  Image image_right =
      LoadImage(ASSETS_PATH "images/ui/keyboard_arrow_right_outline.png");
  Image image_left =
      LoadImage(ASSETS_PATH "images/ui/keyboard_arrow_left_outline.png");

  m_tex_keyboard_arrow_up = LoadTextureFromImage(image_up);
  m_tex_keyboard_arrow_down = LoadTextureFromImage(image_down);
  m_tex_keyboard_arrow_right = LoadTextureFromImage(image_right);
  m_tex_keyboard_arrow_left = LoadTextureFromImage(image_left);

  // Scale Down Keyboard UI
  m_tex_keyboard_arrow_up.height *= .5;
  m_tex_keyboard_arrow_up.width *= .5;

  m_tex_keyboard_arrow_down.height *= .5;
  m_tex_keyboard_arrow_down.width *= .5;

  m_tex_keyboard_arrow_right.height *= .5;
  m_tex_keyboard_arrow_right.width *= .5;

  m_tex_keyboard_arrow_left.height *= .5;
  m_tex_keyboard_arrow_left.width *= .5;

  UnloadImage(image_up);
  UnloadImage(image_down);
  UnloadImage(image_right);
  UnloadImage(image_left);

  m_snake = std::make_unique<Snake>();

  m_food = std::make_unique<Food>();
  m_food->setPosition(m_food->GenerateRandomPos(m_snake->GetBody()));

  InitAudioDevice();
  eatSound = LoadSound(ASSETS_PATH "sounds/eat.mp3");
  wallSound = LoadSound(ASSETS_PATH "sounds/wall.mp3");
}

GameLoop::~GameLoop() {
  UnloadSound(eatSound);
  UnloadSound(wallSound);

  UnloadTexture(m_tex_keyboard_arrow_up);
  UnloadTexture(m_tex_keyboard_arrow_down);
  UnloadTexture(m_tex_keyboard_arrow_right);
  UnloadTexture(m_tex_keyboard_arrow_left);

  CloseWindow();
}

void GameLoop::DrawGrid() const {
  for (int x{0}; x <= m_screenWidth; x += constants::cellSize) {
    DrawLine(x, 0, x, m_screenHeight, LIGHTGRAY);
  }

  for (int y{0}; y <= m_screenHeight; y += constants::cellSize) {
    DrawLine(0, y, m_screenWidth, y, LIGHTGRAY);
  }
}
void GameLoop::setGameState(const GAME_STATE state) { this->gameState = state; }

void GameLoop::DrawKeyboardUI() const {
  DrawText("Move with", constants::offset + 250,
           constants::offset + 20 + constants::cellSize * constants::cellCount,
           30, color::darkGreen);

  DrawTexture(
      m_tex_keyboard_arrow_up, constants::offset + 500,
      constants::offset + 5 + constants::cellSize * constants::cellCount,
      WHITE);

  DrawTexture(
      m_tex_keyboard_arrow_down, constants::offset + 500,
      constants::offset + 35 + constants::cellSize * constants::cellCount,
      WHITE);

  constexpr int gap{30};
  DrawTexture(
      m_tex_keyboard_arrow_right, constants::offset + 500 + gap,
      constants::offset + 35 + constants::cellSize * constants::cellCount,
      WHITE);

  DrawTexture(
      m_tex_keyboard_arrow_left, constants::offset + 500 - gap,
      constants::offset + 35 + constants::cellSize * constants::cellCount,
      WHITE);
}

void GameLoop::DrawPlaying() const {
  ClearBackground(color::green);

  DrawRectangleLinesEx({constants::offset - 5, constants::offset - 5,
                        constants::cellSize * constants::cellCount + 10,
                        constants::cellSize * constants::cellCount + 10},
                       5, color::darkGreen);

  DrawText("Retro Snake", constants::offset - 5, 20, 40, color::darkGreen);
  DrawText(TextFormat("Score: %d", m_score), constants::offset - 5,
           constants::offset + 8 + constants::cellSize * constants::cellCount,
           40, color::darkGreen);

  DrawKeyboardUI();

  this->m_food->Draw();
  this->m_snake->DrawSnake();
}

void GameLoop::DrawGameOver() const {
  // Draw a semi-transparent background to dim the screen
  DrawRectangle(constants::offset, constants::offset, m_screenWidth,
                m_screenHeight, Fade(BLACK, 0.6f));

  static const char* gameOverText = "GAME OVER";
  static const char* restartText = "PRESS [ENTER] TO RESTART";

  int gameOverTextWidth = MeasureText(gameOverText, 60);
  int restartTextWidth = MeasureText(restartText, 20);

  DrawText(gameOverText,
           constants::offset + m_screenWidth / 2 - gameOverTextWidth / 2,
           constants::offset + m_screenHeight / 2 - 40, 60, RED);

  DrawText(restartText,
           constants::offset + m_screenWidth / 2 - restartTextWidth / 2,
           constants::offset + m_screenHeight / 2 + 30, 20, LIGHTGRAY);
}

void GameLoop::Run() {
  while (!WindowShouldClose() && !m_exitGame) {
    this->Update();
    this->Draw();
  }
}

void GameLoop::DrawMenu() const {
  static const char* titleText = "RETRO SNAKE";
  static const char* playText = "PLAY";
  static const char* exitText = "EXIT";

  int titleTextWidth{MeasureText(titleText, 80)};
  int playTextWidth{MeasureText(playText, 50)};
  int exitTextWidth{MeasureText(exitText, 50)};

  int space{120};

  ClearBackground(color::green);
  // Draw Background Frame
  DrawRectangleLinesEx({constants::offset - 5, constants::offset - 5,
                        constants::cellSize * constants::cellCount + 10,
                        constants::cellSize * constants::cellCount + 10},
                       5, color::darkGreen);

  DrawRectangle(0, 0, 2 * constants::offset + m_screenWidth,
                2 * constants::offset + m_screenHeight, Fade(BLACK, 0.6f));

  DrawText(titleText,
           constants::offset + m_screenWidth / 2 - titleTextWidth / 2,
           constants::offset + m_screenHeight / 2 - space - 20, 80, LIGHTGRAY);

  float buttonWidth{300};
  float buttonHeight{80};

  // Play Button
  Rectangle playButton{
      constants::offset + (float)m_screenWidth / 2 - buttonWidth / 2,
      constants::offset + (float)m_screenHeight / 2, buttonWidth, buttonHeight};

  DrawRectangleRounded(playButton, 0.3, 0,
                       m_selectedMenuItem == 0 ? LIME : color::darkGreen);
  DrawText(playText, playButton.x + playButton.width / 2 - playTextWidth / 2,
           playButton.y + 15, 50, WHITE);

  Rectangle exitButton{
      constants::offset + (float)m_screenWidth / 2 - buttonWidth / 2,
      constants::offset + (float)m_screenHeight / 2 + space, buttonWidth,
      buttonHeight};

  DrawRectangleRounded(exitButton, 0.3, 0,
                       m_selectedMenuItem == 1 ? RED : color::darkGreen);
  DrawText(exitText, exitButton.x + exitButton.width / 2 - exitTextWidth / 2,
           exitButton.y + 15, 50, WHITE);
}

void GameLoop::Draw() {
  BeginDrawing();
  switch (this->gameState) {
    case GAME_STATE::MENU:
      this->DrawMenu();
      break;
    case GAME_STATE::PLAYING:
      this->DrawPlaying();
      break;
    case GAME_STATE::PAUSED:
      this->DrawPlaying();
      this->DrawMenu();
      break;
    case GAME_STATE::GAMEOVER:
      this->DrawPlaying();
      this->DrawGameOver();
      break;
  }
  EndDrawing();
}

void GameLoop::UpdateMenu() {
  Vector2 mousePoint{GetMousePosition()};
  float buttonWidth{300};
  float buttonHeight{80};

  Rectangle playButton{
      constants::offset + (float)m_screenWidth / 2 - buttonWidth / 2,
      constants::offset + (float)m_screenHeight / 2, buttonWidth, buttonHeight};

  Rectangle exitButton{
      constants::offset + (float)m_screenWidth / 2 - buttonWidth / 2,
      constants::offset + (float)m_screenHeight / 2 + 120, buttonWidth,
      buttonHeight};

  if (CheckCollisionPointRec(mousePoint, playButton)) {
    m_selectedMenuItem = 0;
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
      gameState = GAME_STATE::PLAYING;
  } else if (CheckCollisionPointRec(mousePoint, exitButton)) {
    m_selectedMenuItem = 1;
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) m_exitGame = true;
  }

  if (IsKeyPressed(KEY_DOWN)) {
    m_selectedMenuItem = (m_selectedMenuItem + 1) % 2;
  }
  if (IsKeyPressed(KEY_UP)) {
    m_selectedMenuItem = (m_selectedMenuItem - 1 + 2) % 2;
  }

  if (IsKeyPressed(KEY_ENTER)) {
    if (m_selectedMenuItem == 0) {
      gameState = GAME_STATE::PLAYING;
    } else if (m_selectedMenuItem == 1) {
      m_exitGame = true;
    }
  }
}

void GameLoop::Update() {
  switch (this->gameState) {
    case GAME_STATE::MENU:
      this->UpdateMenu();
      break;
    case GAME_STATE::PLAYING:

      if (eventTriggered(.1)) {
        m_snake->Update();
      }

      m_snake->CheckInput();

      if (IsKeyPressed(KEY_ESCAPE)) {
        setGameState(GAME_STATE::PAUSED);
      }

      CheckCollisionFood();
      CheckCollisionEdges();
      CheckCollisionTail();

      break;
    case GAME_STATE::PAUSED:
      this->UpdateMenu();
      break;
    case GAME_STATE::GAMEOVER:
      if (IsKeyPressed(KEY_ENTER)) {
        setGameState(GAME_STATE::PLAYING);
      }
      break;
  }
}

void GameLoop::CheckCollisionFood() {
  if (m_snake->GetHead() == m_food->getPosition()) {
    m_food->setPosition(m_food->GenerateRandomPos(m_snake->GetBody()));
    m_snake->setAddSegment(true);
    m_score++;
    PlaySound(eatSound);
  }
}

void GameLoop::CheckCollisionTail() {
  std::deque<Vector2> headlessBody{m_snake->GetBody()};
  headlessBody.pop_front();

  if (ElementInDeque(m_snake->GetHead(), headlessBody)) {
    GameOver();
  }
}

void GameLoop::CheckCollisionEdges() {
  // Check Horizonal Edges
  if (m_snake->GetHead().x >= constants::cellCount ||
      m_snake->GetHead().x <= -1) {
    GameOver();
    return;
  }

  // Check Vertical Edges
  if (m_snake->GetHead().y >= constants::cellCount ||
      m_snake->GetHead().y <= -1) {
    GameOver();
    return;
  }
}

void GameLoop::GameOver() {
#ifdef DEBUG
  TraceLog(LOG_INFO, "Game Over");
#endif

  m_snake->Reset();
  m_food->setPosition(m_food->GenerateRandomPos(m_snake->GetBody()));
  m_score = 0;
  PlaySound(wallSound);

  this->setGameState(GAME_STATE::GAMEOVER);
}
