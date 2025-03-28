Maze Game (3D Raycasting with SDL2)
Overview
Maze Game is a simple 3D maze exploration game built using C and SDL2. It implements a raycasting engine to simulate 3D graphics, inspired by classic games like Wolfenstein 3D. The player can move through a maze, exploring walls, floors, and ceilings.

Features
🏃 Player Movement: Move forward and backward using W and S keys.
🔄 Smooth Rotation: Use Left Arrow (←) and Right Arrow (→) to rotate the player's view.
🏰 Maze Rendering: A predefined map structure with walls, a floor, and a ceiling.
🔦 Raycasting Engine: Generates a pseudo-3D effect using raycasting.
🎨 Textures (Optional): Load and display textures for walls, floors, and ceilings.
Controls
Key Action
W Move Forward
S Move Backward
← (Left Arrow) Rotate Left
→ (Right Arrow) Rotate Right
Esc Exit Game
Installation & Compilation
Requirements
SDL2 (libsdl2-dev)
SDL2_image (libsdl2-image-dev, if using textures)
GCC Compiler
Compile the Game
Run the following command to build the project:

sh
Copy
Edit
make
Run the Game
After compilation, launch the game with:

sh
Copy
Edit
./maze_game
Project Structure
bash
Copy
Edit
Maze/
│── inc/ # Header files
│ ├── maze.h # Maze functions
│ ├── player.h # Player movement & rotation
│ ├── texture.h # Texture loading (if used)
│── src/ # Source files
│ ├── main.c # Game loop and rendering
│ ├── maze.c # Maze drawing functions
│ ├── player.c # Player movement and rotation
│ ├── raycast.c # Raycasting logic
│ ├── texture.c # Texture handling (if applicable)
│── Makefile # Build system
│── README.md # Project documentation
Future Improvements
🚀 More advanced textures
🔫 Enemies & combat mechanics
🔄 Smoother movement & collision handling
🎵 Background music & sound effects
Contributors
Developed by M0imaritim
Feel free to contribute or fork this project!
