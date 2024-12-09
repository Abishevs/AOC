#include <stdio.h>
#include <string.h>

#define ROWS 10
#define COLS 10

// 1. Horisonatal XMAS or SAMX
// 2. Vertical XMAS or SAMX
// 3. Diogonal XMAS or SAMX
//

// Function to populate a matrix from user input
int populateMatrix(char matrix[][COLS], int rows, int cols) {
    char buffer[cols + 10];  // Input buffer
    int row = 0, col = 0;

    printf("Enter matrix rows. Press Enter on an empty line to finish:\n");
    while (fgets(buffer, sizeof(buffer), stdin)) {
        // Check if the line is empty (just '\n')
        if (buffer[0] == '\n') {
            break;
        }

        for (int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++) {
            if (row >= rows || col >= cols) {
                printf("Error: Exceeded maximum dimensions (%d rows x %d columns).\n", rows, cols);
                return 0; // Indicate failure
            }
            matrix[row][col++] = buffer[i];

            // Move to the next row if the current one is full
            if (col == cols) {
                row++;
                col = 0;
            }
        }

        // Move to the next row if there’s still space
        if (col != 0) {
            row++;
            col = 0;
        }
    }

    return 1; // Indicate success
}


int findHorXMAS(char matrix[ROWS][COLS], int x, int y)
{
    // X  check
    // Next M
    // Next A
    // Next S
    // IF XMAS is found its also SAMX
    // But written backwards

    int posM = y + 1;
    int posA = y + 2;
    int posS = y + 3;

    if (posM < COLS && posA < COLS && posS < COLS)
    {
        char M = matrix[x][posM];
        char A = matrix[x][posA];
        char S = matrix[x][posS];
        if (M == 'M' && A == 'A' && S == 'S')  return 1;
    } 

    return 0;

};

int findHorSAMX(char matrix[ROWS][COLS], int x, int y)
{
    // S  check
    // Next A
    // Next M
    // Next X

    int posA = y + 1;
    int posM = y + 2;
    int posX = y + 3;

    if (posA < COLS && posM < COLS && posX < COLS)
    {
        char A = matrix[x][posA];
        char M = matrix[x][posM];
        char X = matrix[x][posX];
        if ( A == 'A' && M == 'M' && X == 'X')  return 1;
    } 

    return 0;

};

int findVerticalXMAS(char matrix[ROWS][COLS], int x, int y)
{
    // X  check
    // Next M
    // Next A
    // Next S

    int posM = x + 1;
    int posA = x + 2;
    int posS = x + 3;

    if (posM < ROWS && posA < ROWS && posS < ROWS)
    {
        char M = matrix[x][posM];
        char A = matrix[x][posA];
        char S = matrix[x][posS];
        if (M == 'M' && A == 'A' && S == 'S')  return 1;
    } 

    return 0;

};

int findVerticalSAMX(char matrix[ROWS][COLS], int x, int y)
{
    // S  check
    // Next A
    // Next M
    // Next X

    int posA = x + 1;
    int posM = x + 2;
    int posX = x + 3;

    if (posA < ROWS && posM < ROWS && posX < ROWS)
    {
        char A = matrix[x][posA];
        char M = matrix[x][posM];
        char X = matrix[x][posX];
        if ( A == 'A' && M == 'M' && X == 'X')  return 1;
    } 

    return 0;

};

int findDioganalXMAS(char matrix[ROWS][COLS], int x, int y)
{
    int count = 0;
    // X  check
    // Next M
    // Next A
    // Next S

    // Right diogonal
    int posMx  = x + 1, posMy = y + 1;
    int posAx = x + 2, posAy = y + 2;
    int posSx = x + 3, posSy = y + 3;

    if (posMy < ROWS && posAy < ROWS && posSy < ROWS 
            &&
        posMx < COLS && posAx < COLS && posSx < COLS)
    {
        char M = matrix[posMx][posMy];
        char A = matrix[posAx][posAy];
        char S = matrix[posSx][posSy];
        if (M == 'M' && A == 'A' && S == 'S')  count += 1;
    } 

    // Left digonal
    posMx  = x - 1, posMy = y - 1;
    posAx = x - 2, posAy = y - 2;
    posSx = x - 3, posSy = y - 3;

    if (posMy < ROWS && posAy < ROWS && posSy < ROWS 
            &&
        posMx < COLS && posAx < COLS && posSx < COLS)
    {
        char M = matrix[posMx][posMy];
        char A = matrix[posAx][posAy];
        char S = matrix[posSx][posSy];
        if (M == 'M' && A == 'A' && S == 'S')  count += 1;
    } 

    return count;

};

int findDioganalSAMX(char matrix[ROWS][COLS], int x, int y)
{
    char base = matrix[x][y];
    int count = 0;

    int posAx  = x + 1, posAy = y + 1;
    int posMx = x + 2, posMy = y + 2;
    int posXx = x + 3, posXy = y + 3;

    if (posMy < ROWS && posAy < ROWS && posXy < ROWS 
            &&
        posMx < COLS && posAx < COLS && posXx < COLS)
    {
        char A = matrix[posAx][posAy];
        char M = matrix[posMx][posMy];
        char X = matrix[posXx][posXy];
        if (A == 'A' && M == 'M' && X == 'X')  count += 1;
    } 

    posAx  = x - 1, posAy = y - 1;
    posMx = x - 2, posMy = y - 2;
    posXx = x - 3, posXy = y - 3;

    if (posMy < ROWS && posAy < ROWS && posXy < ROWS 
            &&
        posMx < COLS && posAx < COLS && posXx < COLS)
    {
        char A = matrix[posAx][posAy];
        char M = matrix[posMx][posMy];
        char X = matrix[posXx][posXy];
        if (A == 'A' && M == 'M' && X == 'X')  count += 1;
    } 

    return count;

};


void part1(char matrix[ROWS][COLS])
{
    printf("\nParsed 2D Array:\n");
    int tot_sum = 0;
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++) 
        {
            char letter = matrix[i][j];
            printf("%c", letter);
            if (letter == 'X') // X-MAS
            {
                tot_sum += findHorXMAS(matrix, i, j);
                tot_sum += findVerticalXMAS(matrix, i, j);
                tot_sum += findDioganalXMAS(matrix, i, j);
                printf("Found letter: %c at x: %d y: %d\n", letter, i,j);
            } else if ( letter == 'S') // S-AMX
                tot_sum += findHorSAMX(matrix, i, j);
                tot_sum += findVerticalSAMX(matrix, i, j);
                tot_sum += findDioganalSAMX(matrix, i, j);
            {
            }
        }
        printf("\n");
    }
    printf("TOtal sum part1: %d", tot_sum);
}

int main() {
    char matrix[ROWS][COLS];  // 2D vector-like array
    
    // Populate the matrix
    if (!populateMatrix(matrix, ROWS, COLS)) {
        printf("Failed to populate matrix. Exiting.\n");
        return 1;
    }

    part1(matrix);


    return 0;
}

