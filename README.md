# sudoku-solver
## Solving sudoku puzzles in C

### How does it work?
Each puzzle is read in as a 2D array stored on the heap. 
Addtionally, three arrays are initialized that store which numbers are present
in each column, row, and square via a 16-bit number (of which 9 are used).

The rightmost digit in each of the arrays' numbers signals the presence of a 1,
the second-rightmost signals the presence of a 2, and so on.
```
9? 8? 7? 6? 5? 4? 3? 2? 1?
0  0  0  0  0  0  0  0  0
```

The slowest algorithm uses no heuristics; it always begins searching at (0, 0)
and looks for the first empty tile. From there is uses the corresponding
column, row, and square arrays to see which numbers are possible in the tile.
Each of those possible numbers is iterated through, and the function is 
recursively called until the puzzle is completely solved.

The faster algorithm jumps to the position it was already at when making the
recursive call, eliminating needless overlap in checking numbers.

The fastest algorithm first searches for the tile with the fewest options, then
iterates through those options, recursively calling from there. This results in 
a very significant speedup for more complex puzzles.
