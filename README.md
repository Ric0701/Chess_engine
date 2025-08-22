# Chess_engine

A lightweight chess engine implemented in C. This project supports UCI and XBoard protocols, and includes modules for move generation, board evaluation, search algorithms, and bitboard utilities.

## Features

- **Move Generation**: Implements all standard chess moves including sliding and non-sliding pieces (see [`moveGen.c`](moveGen.c)).
- **Move Logic**: Handles castling, en passant, promotions, and move undo with detailed history (refer to [`makeMove.c`](makeMove.c)).
- **Board Representation**: Utilizes a 10x12 board array for efficient move calculations (see [`board.c`](board.c)).
- **Evaluation & Search**: Uses evaluation functions and search algorithms (see [`evaluate.c`](evaluate.c) and [`search.c`](search.c)).
- **UCI/XBoard Support**: Interfaces for chess engines to interact with GUI frontends (see [`uci.c`](uci.c) and [`xboard.c`](xboard.c)).
- **Bitboard Operations**: Includes helper functions for bitboard manipulation (see [`bitboard.c`](bitboard.c)).

## Getting Started

### Prerequisites

- GCC compiler (or any C compiler)
- Make utility

### Building the Engine

Open a terminal and run:

```
make
```

This uses the rules defined in the [Makefile](Makefile) to build the engine executable (`Mystery.exe`).

For debugging builds run:

```
make debug
```

### Running the Engine

After building, execute the engine from the command line:

```
./Mystery.exe
```

You can interact with the engine using UCI commands. For example, starting a UCI session:

```
uci
```

## Project Structure

- **Core Engine Files**: 
  - [`board.c`](board.c) – Board setup, FEN parsing, and position validation.
  - [`moveGen.c`](moveGen.c) – Move generation algorithms.
  - [`makeMove.c`](makeMove.c) – Making and undoing moves.
  - [`moveLogic.c`](moveLogic.c) – Special move logic.
  - [`search.c`](search.c) – Search and evaluation routines.
  - [`evaluate.c`](evaluate.c) – Evaluation of board positions.
- **Utilities**:
  - [`utility.c`](utility.c) – Additional helper functions.
  - [`hashKeys.c`](hashKeys.c) – Hash key generation for board positions.
  - [`pvtable.c`](pvtable.c) – Principal variation table handling.
- **Interfaces**:
  - [`uci.c`](uci.c) – UCI protocol handling.
  - [`xboard.c`](xboard.c) – XBoard protocol support.
  - [`io.c`](io.c) – Input/output routines.
- **Initialization**:
  - [`init.c`](init.c) – Initial setup of board arrays, bit masks, and hash keys.
- **Testing and Validation**:
  - [`validate.c`](validate.c) – Functions for board and move validation.
  - [`perfTest.c`](perfTest.c) – Performance testing routines.