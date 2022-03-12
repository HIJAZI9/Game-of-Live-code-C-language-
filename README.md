# Game-of-Live-code-C-language-

The bionic animation "Life" was created in 1970 by the British mathematician J.H. Conway invented. We consider a two-dimensional matrix with n*m elements (cells) of type char. If a cell contains a space, then it is "dead". It is a "living" cell if a "*" is entered in it. Several neighboring living cells form an organism.

A cell is surrounded by 8 neighboring cells unless they are at the edge of the matrix. To the shape of an organism in the
next generation, the following rules apply, which are based on the
apply to the entire matrix:

1. Has a living cell 0, 1 or more than 3 living neighboring cells, it dies of loneliness or overpopulation.
 
2. If a living cell has 2 or 3 living neighboring cells, then it continues to exist in the next generation.
 
3. If a dead cell is surrounded by exactly 3 living cells, then it becomes a new living cell.

This program, which allows you to understand the development of such an organism on the screen.

Depending on the user's desire, the initial state of the matrix loaded from a file or entered using a random number generator Initial state calculated. The user can decide whether a step-by-step processing (development) or a "flowing animation" it is asked for.

The user can choose between at least 3 files (i.e. at least 3 start states) via a menu. When the random number generator generates a starting state, the user can specify what percentage of the playing field is to be filled with living cells.
 
The user can edit start states in the work field and then save them under a file name of his choice.
