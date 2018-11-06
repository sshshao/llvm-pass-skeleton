#include <stdio.h>

int isValidSudoku(char board[9][9]);
int isPartialValid(char board[9][9], int r1, int c1, int r2, int c2);

int main() {
    /*
    * This program detects whether a Sudoku board is valid or not
    * A slot filled by '.' means empty

    * Rule of Sudoku: Each row, column and 3-by-3 sub matrices must 
    * contain digits 1-9 without repetition
    * 
    */

    char board[9][9] = 
    {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    printf("Return value is %d", isValidSudoku(board));

    return 0;
}

int isPartialValid(char board[9][9], int r1, int c1, int r2, int c2) {
    /*
    * Check if sub-matrix (bounded by r1, c1, r2, c2) only contains 1-9 without repetition
    */
    int hashset[9];

    for(int i = r1; i <= r2; i++) {
        for(int j = c1; j <= c2; j++) {
            if(board[i][j] != '.') {
                int number = board[i][j] - '0';
                if(hashset[number] != 0) {
                    return 0;
                } else {
                    hashset[number] = 1;
                }
            }
        }
    }

    return 1;
}

int isValidSudoku(char board[9][9]) {
    /*
    * This function checks whether the given 9x9 matrix is a valid Sudoku or not
    * Assumes the input matrix is 9x9 and only contains character '1'-'9' and '.'
    */
 
    for(int i = 0; i < 9; i++) {
        if(isPartialValid(board, i, 0, i, 8) == 0) {
            return 0;
        }
        if(isPartialValid(board, 0, i, 8, i) == 0) {
            return 0;
        }
    }
    for(int i = 0; i < 9; i += 3) {
        int j = 0;
        while(j < 9) {
            if(isPartialValid(board, i, j, i+2, j+2) == 0) {
                return 0;
            }
            j += 3;
        }
    }

    return 1;
}