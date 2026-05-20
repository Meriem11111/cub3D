# cub3D

A raycasting 3D engine inspired by Wolfenstein 3D, built from scratch in C using the MinilibX graphics library as part of the 42 school curriculum.

---

## About

cub3D renders a first-person 3D view of a 2D map using the **DDA (Digital Differential Analysis)** raycasting algorithm. The player can navigate through the environment with keyboard controls, and walls are textured based on their facing direction (N/S/E/W).

---

## Features

- Raycasting engine with perspective-correct wall rendering
- Directional wall textures (North, South, East, West) loaded from `.xpm` files
- Configurable floor and ceiling colors via RGB values
- Minimap rendered in the top-left corner
- Player movement: walk forward/backward and strafe left/right
- Camera rotation: left and right arrow keys
- Map validation: border checks, character validation, texture and color parsing
- Clean exit on ESC or window close

---

## Map Format (`.cub`)

The scene description file must follow this format:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 80,50,30
C 90,90,100

1111111111
1000000001
100N000001
1111111111
```

**Elements:**
- `NO`, `SO`, `WE`, `EA` — paths to wall textures (`.xpm`)
- `F` — floor color as `R,G,B` (0–255)
- `C` — ceiling color as `R,G,B` (0–255)
- Map characters: `1` = wall, `0` = floor, `N/S/E/W` = player start position and direction

**Rules:**
- The map must be surrounded by walls (`1`)
- Exactly one player start position required
- No open spaces (zeros adjacent to spaces)

---

## Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate camera left |
| `→` | Rotate camera right |
| `ESC` | Exit |

---

## Build

```bash
make        # build
make clean  # remove object files
make fclean # remove object files and binary
make re     # full rebuild
```

**Dependencies:** MinilibX (`mlx_linux`), X11, Xext, math (`-lm`), zlib (`-lz`)

---

## Usage

```bash
./cub3D maps/map.cub
```

---

## Project Structure

```
cub3D/
├── main.c            # Entry point, map parsing, validation, window setup
├── raycast.c         # Raycasting engine, DDA, wall rendering, texture mapping
├── minimap1.c        # Minimap rendering
├── utils.c           # String utilities (strcmp, strncmp, strchar)
├── free.c            # Memory cleanup
├── ft_split.c        # String splitting utility
├── cub3d.h           # Main header, structs, prototypes
├── get_next_line/    # GNL implementation for file reading
├── textures/         # Wall textures (.xpm)
├── maps/             # Scene description files (.cub)
└── mlx_linux/        # MinilibX library
```

---

## Requirements

- GCC with C17 support
- Linux with X11
- MinilibX (included in `mlx_linux/`)
