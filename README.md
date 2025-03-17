# Maze Game - 3D Raycasting Engine with SDL2

## Overview
Maze Game is an immersive 3D maze exploration experience built using C and SDL2. The game implements a raycasting engine to create convincing 3D visuals from a 2D map, similar to the technique pioneered by classic games like Wolfenstein 3D. Players navigate through corridors with textured walls, floors, and ceilings for a retro-inspired first-person adventure.

## Features
- **Immersive 3D Environment**: Experience pseudo-3D graphics rendered through an efficient raycasting engine
- **Fluid Movement System**: Navigate the maze with intuitive controls for movement and rotation
- **Atmospheric Design**: Explore detailed environments with textured surfaces
- **Performance Optimized**: Built with C for responsive gameplay even on modest hardware
- **Open Architecture**: Easily expandable codebase for adding new features
- **Code Quality**: Adheres to strict Betty coding standards for clean, consistent, and maintainable code

## Controls
| Key | Action |
|-----|--------|
| W | Move Forward |
| S | Move Backward |
| ← (Left Arrow) | Rotate Left |
| → (Right Arrow) | Rotate Right |
| Esc | Exit Game |

## Installation

### Requirements
- SDL2 library (`libsdl2-dev`)
- SDL2_image library (`libsdl2-image-dev`) if using textures
- GCC compiler
- Make

### Building from Source

1. Install the required dependencies:
   ```bash
   # For Debian/Ubuntu
   sudo apt install libsdl2-dev libsdl2-image-dev gcc make
   
   # For Fedora
   sudo dnf install SDL2-devel SDL2_image-devel gcc make
   
   # For macOS (using Homebrew)
   brew install sdl2 sdl2_image
   ```

2. Clone the repository:
   ```bash
   git clone https://github.com/M0imaritim/Maze.git
   cd Maze
   ```

3. Compile the game:
   ```bash
   make
   ```

4. Run the game:
   ```bash
   ./maze_game
   ```

## Project Structure
```
Maze/
│── inc/                    # Header files
│   ├── maze.h              # Maze definitions and functions
│   ├── player.h            # Player movement & rotation logic
│   └── texture.h           # Texture loading and management
│
│── src/                    # Source files
│   ├── main.c              # Entry point, game loop and rendering
│   ├── maze.c              # Maze drawing and management functions
│   ├── player.c            # Player movement and rotation implementation
│   ├── raycast.c           # Raycasting engine implementation
│   └── texture.c           # Texture handling functionality
│
│── assets/                 # Game assets (add this directory)
│   └── textures/           # Wall, floor and ceiling textures
│
│── Makefile                # Build configuration
└── README.md               # Project documentation
```

## How It Works

The game uses raycasting to create a 3D perspective from a 2D map grid:

1. For each vertical column of the screen, a ray is cast from the player's position
2. The ray extends until it hits a wall in the map
3. Based on the distance to the wall, the engine calculates how tall to draw the wall slice
4. Textures are mapped onto walls based on where the ray hit
5. This creates a convincing 3D effect without using actual 3D rendering techniques

## Code Standards

This project strictly follows the Betty coding style, which emphasizes:

- Consistent indentation and spacing
- Proper function and variable naming conventions
- Limited line length (80 characters max)
- Comprehensive documentation for functions
- Organized structure for header files
- Clear and maintainable code organization

All code adheres to the Betty style checker standards. To verify code compliance, use the Betty style checker available at: https://github.com/alx-tools/Betty

Contributors should install and run Betty before submitting pull requests to ensure code quality and consistency.

## Roadmap
- **Enhanced Visuals**
  - Implement dynamic lighting and shadows
  - Add more detailed textures and environment effects
  
- **Gameplay Expansion**
  - Introduce enemies and combat mechanics
  - Add collectible items and objectives
  
- **Technical Improvements**
  - Optimize collision detection for smoother movement
  - Implement a mini-map feature
  
- **Audio Implementation**
  - Add ambient background music
  - Implement spatial sound effects

## Contributing
Contributions are welcome! Feel free to fork this project and submit pull requests.

1. Fork the project
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request
6. Ensure your code passes all Betty style checks (https://github.com/alx-tools/Betty)

## Acknowledgments
- Developed by M0imaritim
- Inspired by classic raycasting games like Wolfenstein 3D
- Built with SDL2

---

*Happy maze exploring!*
