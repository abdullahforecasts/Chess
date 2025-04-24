# Chess

![Chess](https://img.shields.io/badge/Chess-C%2B%2B-ff69b4.svg)

## Table of Contents
- [Description](#description)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Controls](#controls)
- [Requirements](#requirements)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [Author](#author)

## Description
**Chess** is a feature-rich, click-based two-player chess game implemented using **Object-Oriented Programming in C++**, with a graphical user interface built using the **Raylib** library. The game supports all classical rules including **check**, **checkmate**, **stalemate**, **castling**, **en passant**, **piece capturing**, and **promotion**.

At game launch, users can choose to start a new game or load a previously saved game state from a text file. Gameplay is intuitive and visually clear, providing real-time feedback using color-coded highlights:
- Selected piece: Yellow background
- Legal moves: Green background
- Capturable opponents: Red background

## Features

### Game Mechanics
- ✅ Fully functional 2-player Chess with all standard rules
- ♟️ Pieces: Pawn, Knight, Bishop, Rook, Queen, King
- 🧠 Implements:
  - Check / Checkmate / Stalemate detection
  - Castling
  - En Passant
  - Promotion
- 💾 Load game from a file
- 🖱️ Click-based interaction with visual highlights

### Visual UI
- Built with **Raylib**
- Board Color: Beige & Purple
- White & Black pieces with PNG images
- Real-time color feedback:
  - Yellow: Selected piece
  - Green: Valid moves
  - Red: Capturable pieces

## Installation

### Clone the Repository
```bash
git clone https://github.com/abdullahforecasts/Chess.git
cd Chess
```

### Compile the Project (Raylib required)
Make sure **Raylib** is installed properly on your system.

#### Windows (g++)
```bash
g++ bscs24009_main.cpp BSCS24009_*.cpp -o chess -lraylib -lopengl32 -lgdi32 -lwinmm
```

#### Linux
```bash
g++ bscs24009_main.cpp BSCS24009_*.cpp -o chess -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

### Run the Executable
```bash
./chess
```

## Usage

- Launch the game
- Choose:
  - Start a new game
  - Load a game from file (`grid.txt`)
- Click a piece to see its valid moves
- Play turn by turn (White starts first)
- Game will notify you on **Check**, **Checkmate**, or **Stalemate**

## Controls

| Action                   | Control                     |
|--------------------------|-----------------------------|
| Select piece             | Left click on a piece       |
| View legal moves         | Highlights green            |
| Capture opponent         | Click red-highlighted box   |
| Save/load game           | Done via file (`grid.txt`)  |

## Requirements

- C++ compiler (g++ recommended)
- [Raylib](https://www.raylib.com/) graphics library
- PNG support for piece images
- Operating System: Windows / Linux

## Project Structure
```
Chess/
├── bscs24009_main.cpp          # Main driver
├── BSCS24009_head.h            # Shared headers
├── BSCS24009_piece.cpp/.h      # Base class
├── BSCS24009_king.cpp/.h       # King logic
├── BSCS24009_queen.cpp/.h      # Queen logic
├── BSCS24009_rook.cpp/.h       # Rook logic
├── BSCS24009_bishop.cpp/.h     # Bishop logic
├── BSCS24009_knight.cpp/.h     # Knight logic
├── BSCS24009_pawn.cpp/.h       # Pawn logic
├── BSCS24009_board.cpp/.h      # Board management
├── grid.txt                    # Save/load game state
├── kingB.png                   # Black King image
├── kingW.png                   # White King image
├── ...                         # Other piece images
└── README.md                   # Documentation
```

## Contributing
Contributions are welcome! Feel free to fork the repository and submit a pull request with improvements, bug fixes, or features.

## Author
[Abdullah](https://github.com/abdullahforecasts)

Enjoy the Game ♟️  
Happy Coding! 🎮

