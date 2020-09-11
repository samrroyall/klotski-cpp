# Klotski Solver README

### Inputting blocks and board configurations

Create a TXT file called *blocks.txt* formatted as follows.

To add blocks, include lines in *blocks.txt* in one of the following two formats.
1. `x y r` will generate a block with *x* rows and *y* columns (square block of size 4) whose top-leftmost point is at board position (*x*,*y*).
2. `x y r c` will generate a block with *x* rows and *y* columns (horizontal block of size 2) whose top-leftmost point is at board position (*x*,*y*).

Additionally, the line `x y` will specify that for a board to be solved, the block of size 4 must have a top-leftmost point of (*x*,*y*).

### Possible Errors

Remember the following rules to avoid errors.
* There must be at least one block of size 4
* This solver uses a 5x4 board (in row-column format), so ensure that blocks are within bounds

### Usage

Build project and run `.\klotski.exe`!
