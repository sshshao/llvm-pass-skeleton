#include <stdio.h>

int main() {
    char board[9][9] = 
    {
        {"5","3",".",".","7",".",".",".","."},
        {"6",".",".","1","9","5",".",".","."},
        {".","9","8",".",".",".",".","6","."},
        {"8",".",".",".","6",".",".",".","3"},
        {"4",".",".","8",".","3",".",".","1"},
        {"7",".",".",".","2",".",".",".","6"},
        {".","6",".",".",".",".","2","8","."},
        {".",".",".","4","1","9",".",".","5"},
        {".",".",".",".","8",".",".","7","9"}
    };

    printf("Return value is %d", isValidSudoku(board));

    return 0;
}

int isValidSudoku(char** board) {
    for(int i = 0; i < 9; i++) {
        if(isPartialValid(board, i, 0, i, 8) == 0) {
            return 0;
        }
        if(isPartialValid(board, 0, i, 8, i) == 0) {
            return 0;
        }
    }
    for(int i = 0; i < 9; i += 3) {
        for(int j = 0; j < 9; j += 3) {
            if(isPartialValid(board, i, j, i+2, j+2) == 0) {
                return 0;
            }
        }
    }

    return 1;
}

int isPartialValid(char** board, int r1, int c1, int r2, int c2) {
    //Hashset for char '0'-'9'
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