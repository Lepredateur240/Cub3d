# GEMINI.md - Project Context

## Project Overview
**cub3D** is a 3D raycasting engine written in C, inspired by the classic game Wolfenstein 3D. It transforms a 2D map into a 3D perspective using the DDA (Digital Differential Analysis) algorithm. This project is a 42 school assignment, utilizing the **MacroLibX** graphics library.

## Key Technologies
- **Language:** C (C99/C11 standards, following 42 "Norme").
- **Graphics Library:** MacroLibX (SDL2-based).
- **Core Libraries:**
  - `libft`: Custom standard library replacement.
  - `ft_free`: Specialized memory management for structured freeing (e.g., `ft_ultimate_free`).
- **Dependencies:** SDL2 (required by MacroLibX).

## Architecture & Structure
The project is modularized into specialized components:
- **`src/main.c`**: Entry point and high-level game loop orchestration.
- **`src/init/`**: Handles initialization tasks:
  - `map.c`, `handle_map.c`, `verify_map.c`: Parsing and validating `.cub` files.
  - `map_texture.c`, `map_color.c`: Processing texture paths and floor/ceiling colors.
  - `init_mlx.c`, `init_image.c`: Graphics context setup and asset loading.
  - `spawn.c`: Setting player's initial position and direction based on the map.
- **`src/raystracing/`**: The core rendering engine:
  - `to_3d.c`: Implements the DDA algorithm for raycasting.
  - `draw.c`: Vertical line drawing and texture mapping logic.
- **`src/keyhook/`**: Manages player input and movement logic.
- **`src/on_event/`**: Handles window events, the main loop hook, and resource cleanup.
- **`includes/`**: Header files defining structures (`struct.h`), prototypes (`prototype.h`), and key mappings (`keypad.h`).

## Building and Running
### Build Commands
- `make`: Compiles the project and all sub-libraries (`libft`, `mlx`, `free`).
- `make clean`: Removes object files.
- `make fclean`: Removes object files and all compiled binaries/libraries.
- `make re`: Performs a full re-compilation.

### Running the Project
```bash
./cub3D <path_to_map.cub>
```
*Example:* `./cub3D a.cub`

## Development Conventions
- **Coding Style:** Strictly adheres to the 42 Norm (file headers, function limits, naming).
- **Memory Management:** Rigorous cleanup using `ft_ultimate_free` and `mlx_destroy_*` functions in `cleanup_and_exit`.
- **Map Format:** Requires a `.cub` file with:
  - Textures: `NO`, `SO`, `WE`, `EA` followed by file paths.
  - Colors: `F` (floor) and `C` (ceiling) in `R,G,B` format.
  - Map: Composed of `0` (empty), `1` (wall), and `N`/`S`/`E`/`W` (spawn point).

## Key Files for Investigation
- `includes/struct.h`: Main data structures for game state and raycasting.
- `src/raystracing/to_3d.c`: Core DDA raycasting logic.
- `src/init/map.c`: Main entry for parsing logic.
- `src/on_event/mlx_event.c`: Event loop and cleanup logic.
