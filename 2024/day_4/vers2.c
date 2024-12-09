#include <stdio.h>
#include <string.h>

#define ROWS 140
#define COLS 140

const int directions[8][2] = {
    {0, 1}, {0, -1},   // Horizontal: right, left
    {1, 0}, {-1, 0},   // Vertical: down, up
    {1, 1}, {-1, -1},  // Diagonal: down-right, up-left
    {1, -1}, {-1, 1}   // Diagonal: down-left, up-right
};

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

// Check if the word exists starting at (x, y) in the direction (dx, dy)
int searchWord(char matrix[ROWS][COLS], int rows, int cols, int x, int y, const char *word, int dx, int dy) {
    int len = strlen(word);

    for (int i = 0; i < len; i++) {
        int nx = x + i * dx;
        int ny = y + i * dy;

        // Check bounds
        if (nx < 0 || nx >= rows || ny < 0 || ny >= cols) {
            return 0; // Out of bounds
        }

        // Check character match
        if (matrix[nx][ny] != word[i]) {
            return 0; // Mismatch
        }
    }

    return 1; // Match found
}

// Count occurrences of a word in the matrix
int countWordOccurrences(char matrix[ROWS][COLS], int rows, int cols, const char *word) {
    int count = 0;

    // Iterate over all starting positions
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            // Try all directions from each starting position
            for (int d = 0; d < 8; d++) {
                int dx = directions[d][0];
                int dy = directions[d][1];

                if (searchWord(matrix, rows, cols, x, y, word, dx, dy)) {
                    count++;
                }
            }
        }
    }

    return count;
}

// Count total occurrences of all words
int countAllWords(char matrix[ROWS][COLS], int rows, int cols, const char *words[], int wordCount) {
    int totalOccurrences = 0;

    for (int i = 0; i < wordCount; i++) {
        totalOccurrences += countWordOccurrences(matrix, rows, cols, words[i]);
    }

    return totalOccurrences;
}

int main() {
    char matrix[ROWS][COLS];

    // Populate the matrix
    if (!populateMatrix(matrix, ROWS, COLS)) {
        printf("Failed to populate matrix. Exiting.\n");
        return 1;
    }

    const char *words[] = {"XMAS"};
    int wordCount = sizeof(words) / sizeof(words[0]);

    int totalOccurrences = countAllWords(matrix, ROWS, COLS, words, wordCount);
    printf("Total occurrences of all words: %d\n", totalOccurrences);

    return 0;
}

