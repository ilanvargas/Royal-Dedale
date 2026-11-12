# Royal Dédale

An exploration game written in C, inspired by *Blue Prince*. The player moves through a mansion by placing and crossing tiles to reach the exit, under a limited step budget.

Academic project — Bordeaux INP / ENSEIRB-MatMéca, semester 5 (2025-2026). [Project subject](https://www.labri.fr/perso/renault/working/teaching/projets/2025-26-S5-RoyalDedale.php).

## Gameplay

The board is a grid that stays hidden until tiles are placed. On each turn, the player either:

- **places a tile** adjacent to their position, picking from several drafted options, paying an opening cost in resources (steps, keys, gems, gold...); or
- **moves** to an already-open tile, paying its traversal cost.

The goal is to reach the exit tile before running out of steps, while passing through target tiles that reward resources. Random equipment (shovel, wallet, sneakers, hat) can be picked up during the game, each modifying cost or reward rules.

Two game modes are available:
- **Interactive** (`-i`): the player manually chooses moves and tile placements from the keyboard.
- **Automatic**: a pathfinding algorithm (Manhattan distance + shortest path) drives the player toward the nearest target.

## Architecture

The code is split into independent modules, each with a documented header (Doxygen-style):

| Module | Role |
|---|---|
| `resource.c/h`, `stash.c/h` | Game resources and stock management (add, subtract, compare) |
| `dir.c/h`, `location.c/h` | Cardinal directions and grid coordinates |
| `tile.c/h`, `tile_bis.c/h` | Tile generation and properties (opening/traversal costs) |
| `game.c/h` | Game state: board, player position, placement/movement logic |
| `target.c/h` | Target tiles, distance sorting, pathfinding |
| `equipement.c/h` | Equipment system with random effects |
| `tui.c/h` | Text-based board rendering (with optional color) |
| `main.c` | Game loop and command-line argument parsing |

Board size, resource count, and compilation flags are configurable through the `Makefile` (`BOARD_WIDTH`, `BOARD_HEIGHT`, `NUM_RESOURCES`, `COLOR_PRINTING_ENABLED`).

## Build and run

```bash
make                # builds the game (./project) and the tests (./tester)
./project [options]
make test            # runs the unit test suite
```

Options for `./project`:

| Option | Description |
|---|---|
| `-s <int>` | seed for the random tile generator |
| `-t <int>` | parameter passed to `init_tiles` |
| `-n <int>` | maximum number of turns |
| `-q <int>` | seed for the equipment generator |
| `-i` | interactive mode (manual control) |
| `-g` | graphical rendering of the board |
| `-b` | use the "base" game loop instead of the pathfinding-driven loop |

## Tests

Unit tests (`test/`) cover the `dir`, `location`, `resource`, `stash`, and `tile` modules, and run via `make test` after building.

## Report

A detailed report (context, architecture choices, lessons learned) is available in [`rapport/`](rapport/main.pdf).

## Authors

Built by **Ilan Vargas** and **Achraf Safi**, supervised by Tristan Riehs.
