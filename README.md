## YASC++ — raylib Edition

Yet Another Snake Clone, written in C++20 using [raylib](https://www.raylib.com/).

## Building

Requires [CMake](https://cmake.org/) 3.20 or later and a C++20 compiler. raylib is fetched automatically at configure time via CMake's FetchContent — no manual installs needed.

```bash
git clone https://github.com/yourusername/raylib_YASCpp.git
cd raylib_YASCpp
cmake -S . -B out
cmake --build out
```

The binary will be placed in `out/` (or your configured build directory).

## Controls

| Key | Action |
|---|---|
| W / ↑ | Move north |
| S / ↓ | Move south |
| A / ← | Move west |
| D / → | Move east |
| P | Pause |
| R | Restart (on death) |
| ESC | Return to menu (on death) |

## Dependencies

- [raylib 5.5](https://github.com/raysan5/raylib) — fetched automatically by CMake
