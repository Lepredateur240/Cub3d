# cub3D

*This project has been created as part of the 42 curriculum by masenche and algasnie.*

## Description
This project is inspired by the world-famous Wolfenstein 3D game, which is
considered the first FPS ever created. It will enable you to explore ray-casting. Your goal
will be to make a dynamic view inside a maze, where you will have to find your way.

## Instructions
### Compilation
To compile the mandatory part:
```make```

To compile with bonus features (like mouse rotation):
```make bonus```

To clean object files:
```make clean```

To perform a full cleanup:
```make fclean```

### Execution
Run the program with a valid `.cub` map file:
```./cub3D valid.cub```

## How it works

### 1. Parsing & Validation
The program begins by parsing the `.cub` file to extract:
- the textures paths for all orientations (NO, SO, WE, EA),
- the RGB colors for the floor (F) and ceiling (C).

After this settings the program extract the map layout and ensure the map is correct:
- Only one spawn for the player
- Enclosed by walls
- Only valid characters: 1 (Cube) and 0 (Floor)

### 2. Initialization
Unsig MacroLibX, the program initializes the windows and graphics context. 
Textures are loaded into memory.
The player initial position and direction avec set based on the map's spawn character (N, S, O, E)

### 3. Raycasting Engine (DDA)
The core of the rendering is the DDA (Digital Differential Analysis) algorithm.
- A ray is cast from the player's position in their view direction.
- The algorithm steps through the 2D grid until the ray hits a wall.
- Using the direct distance between the player and the wall would result in a distorted, spherical view known as the "fish-eye" effect. Instead, we use a camera plane that represents the screen; the distance is calculated between the camera plane and the wall using a perpendicular vector.
- This distance dictates the height of the wall slice drawn on the screen.

### 4. Rendering & Texturing
Once the distance and wall orientation are known, the rpogram maps the corresponding texture pixel to the vertical screen stripe. Floor and ceiling pixels are filled with the specified colors.

### 5. Event Handling
The program is looping listening for keyboard and mouse events to:
- Move the player (W, A, S, D).
- Rotate the camera (Left/Right arrows or Mouse). (BONUS)
- Exit the game (ESC or closing the window).

## Resources
* Raycasting tutorial: (https://lodev.org/cgtutor/raycasting.html)
* MacroLibX Documentation: (https://github.com/42-Paris/MacroLibX)
