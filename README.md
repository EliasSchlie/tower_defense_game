# Castle Defender

A turn-based terminal tower defense game written in C++. Defend your castle against waves of enemies by placing towers on a 20×20 grid.

## Gameplay

- Place up to 5 towers anywhere on the grid before the game starts
- Each turn, enemies spawn and advance toward the castle at the bottom
- Towers automatically attack nearby enemies
- Survive 5 waves — enemy health scales each wave (managed by an AI controller)
- Game ends when the castle's health hits zero or all waves are cleared

## Build & Run

```bash
g++ -std=c++17 src/*.cpp -o CastleDefender
./CastleDefender
```

Tested on macOS with Apple clang.

## Structure

`Game`, `Grid`, `Castle`, `Tower`, `Enemy`, `AI` — each component is its own `.cpp`/`.h` pair in `src/`.
