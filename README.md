# Retro Snake

A classic snake game built with C++ and the raylib library. This project features a retro aesthetic with a simple and intuitive menu, sound effects, and classic gameplay mechanics.

## About The Project

This project is a modern implementation of the classic Snake game, inspired by the tutorial from **Learn with Gergely**. The player controls a snake that grows in length by eating food. The game ends if the snake collides with the edges of the screen or its own body. It's built with a clean and modular C++ structure and uses CMake for easy building across multiple platforms.

### Key Features

- **Classic Gameplay**: Enjoy the timeless fun of Snake.
- **Main Menu**: A fully functional main menu with `Play` and `Exit` options.
- **Keyboard & Mouse Support**: Navigate the menu using arrow keys/Enter or the mouse.
- **Scoring System**: Keep track of your score as you eat food.
- **Pause & Game Over**: Pause the game at any time and see a clear "Game Over" screen upon losing.
- **Sound Effects**: Audio feedback for eating food and colliding with walls.
- **Retro Visuals**: Simple and clean graphics that hark back to the classic arcade era.

### Built With

- [C++](https://isocpp.org/)
- [raylib](https://www.raylib.com/) - A simple and easy-to-use library to enjoy video games programming.
- [CMake](https://cmake.org/) - For cross-platform building.

## Getting Started

To get a local copy up and running, follow these simple steps.

### Prerequisites

You will need a C++ compiler (like GCC, Clang, or MSVC) and CMake installed on your system.

- **CMake**
  ```
  [https://cmake.org/download/](https://cmake.org/download/)
  ```
- **For Linux Users**: You may need to install additional libraries for raylib.
  ```
  sudo apt-get install build-essential libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev
  ```

### Installation & Building

1.  **Clone the repo**
    ```
    git clone [https://github.com/your_username/your_repository.git](https://github.com/your_username/your_repository.git)
    cd your_repository
    ```
2.  **Run the Makefile**
    The provided `Makefile` simplifies the build process. It uses `ninja` to configure and build the project in the `build/` directory.

    ```
    make
    ```

    This command will compile the project and run the game executable.

3.  **Manual Build with CMake (Alternative)**
    If you prefer to build manually:
    ```
    # Create a build directory
    cmake -B build
    # Compile the project
    cmake --build build
    # Run the executable
    ./build/snake
    ```

## How to Play

- **Movement**: Use the **Arrow Keys** (`UP`, `DOWN`, `LEFT`, `RIGHT`) to control the snake's direction.
- **Menu Navigation**:
  - Use the **Arrow Keys** (`UP`, `DOWN`) to highlight an option.
  - Press **Enter** to select the highlighted option.
  - Alternatively, use the **Mouse** to hover and click on menu buttons.
- **Pause Game**: Press the **ESC** key during gameplay to pause. Press it again or select 'Play' to resume.
- **Restart Game**: After a "Game Over", press **Enter** to play again.

## License

Distributed under the MIT License. See `LICENSE` for more information.

## Acknowledgments

- Thanks to [raysan5](https://github.com/raysan5) for creating the amazing [raylib](https://github.com/raysan5/raylib) library.
- This project was based on the C++ Snake Game Tutorial by [Learn with Gergely on YouTube](https://www.youtube.com/watch?v=LGqsnM_WEK4).
