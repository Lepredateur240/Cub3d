# GEMINI.md - Project Context

## Project Overview
**cub3D** is a 3D raycasting engine written in C, inspired by the classic game Wolfenstein 3D. It transforms a 2D map into a 3D perspective using the DDA (Digital Differential Analysis) algorithm. This project is likely a 42 school assignment, utilizing the **MacroLibX** graphics library.

## Key Technologies
- **Language:** C (Standard C99/C11, following 42 school "Norme" conventions).
- **Graphics Library:** MacroLibX (an SDL2-based graphics library for window and image management).
- **Core Libraries:**
  - `libft`: A custom standard library replacement.
  - `ft_free`: A specialized memory management library allowing structured freeing (e.g., `ft_ultimate_free("%i", map)`).
- **Dependencies:** SDL2 (required by MacroLibX).

## Architecture & Structure
The project is modularized into several key components:
- **`src/main.c`**: Orchestrates the high-level game loop and frame rendering.
- **`src/init/`**: Handles initialization tasks:
  - `map.c` & `handle_map.c`: Parsing and validating `.cub` configuration files.
  - `map_texture.c` & `map_color.c`: Loading texture paths and floor/ceiling colors.
  - `init_mlx.c` & `init_image.c`: Setting up the graphics context and loading assets.
  - `spawn.c`: Setting the player's initial position and direction.
- **`src/raystracing/`**: The core engine:
  - `to_3d.c`: Implements the DDA algorithm for raycasting.
  - `draw.c`: Handles vertical line drawing and texture mapping.
- **`src/keyhook/`**: Manages player input and movement logic.
- **`src/on_event/`**: Handles window events, the main loop hook, and resource cleanup.
- **`includes/`**: Contains structure definitions (`struct.h`), function prototypes (`prototype.h`), and key mappings (`keypad.h`).

## Building and Running
### Build Commands
- `make`: Compiles the project and all sub-libraries (`libft`, `mlx`, `free`).
- `make clean`: Removes object files.
- `make fclean`: Removes object files and the compiled binary/libraries.
- `make re`: Full re-compilation.

### Running the Project
```bash
./cub3D <path_to_map.cub>
```
*Example:* `./cub3D a.cub`

## Development Conventions
- **Coding Style:** Adheres to the 42 Norm (implied by file headers and structure).
- **Memory Management:** Rigorous cleanup is expected. Always use `ft_ultimate_free` or appropriate `mlx_destroy_*` functions in `cleanup_and_exit`.
- **Map Format:** Requires a `.cub` file containing texture paths (NO, SO, WE, EA), floor/ceiling colors (F, C), and a map composed of `0` (empty), `1` (wall), and spawning points (`N`, `S`, `E`, `W`).

## Key Files for Investigation
- `includes/struct.h`: Main data structures for game state, raycasting, and MLX.
- `src/raystracing/to_3d.c`: The raycasting logic implementation.
- `src/init/map.c`: The entry point for parsing map files.
