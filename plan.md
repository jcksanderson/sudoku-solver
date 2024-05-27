# Method 1
- read in sudoku from file (.txt, start with just one)
- initialize arrays for each column, row, and square
    - use bitmasking to determine the numbers of each
- select top left-most undetermined tile
    - create for loop of possible values
        - if there's a conflict, continue
        - else, call the same top left-most selecting function on the next tile
        - keep doing this until the board is complete
