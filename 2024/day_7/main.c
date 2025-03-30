#include <stdio.h>
#include <ctype.h>

#define MAX_NUMBERS 1000
#define MAX_BUFFER 1000

unsigned long long find_combinations(
        unsigned long long* numbers,
        unsigned long long target,
        unsigned long long current_value,
        int num_count,
        int index
        ) {
    if (index == num_count) {
        if (current_value == target) {
            printf("Found valid combination: %llu\n", current_value);
            return numbers[0];
        }
        return 0;
    }

    unsigned long long current_number = numbers[index];

    // Option 1: Add the current number to the current value
    unsigned long long result = find_combinations(
            numbers,
            num_count,
            target,
            current_value + current_number,
            index + 1
            );

        if (result != 0) {
        return result;  // If a valid combination is found
    }

    // Option 2: Multiply the current number with the current value
    result = find_combinations(numbers,
            num_count,
            target,
            current_value * current_number,
            index + 1
            );

    if (result != 0) {
        return result;  // If a valid combination is found
    }
}

int main() {
    char buffer[MAX_BUFFER];
    unsigned long long numbers[MAX_NUMBERS];
    int num_count;
    unsigned long long sum = 0;

    // FILE *file = fopen("test.txt", "r"); 
    FILE *file = fopen("input.txt", "r"); 
    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        unsigned long long num = 0;
        num_count = 0;

        for (int i = 0; buffer[i] != '\0'; i++) {
            char c = buffer[i];

            // Build number
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
            }
            else {
                if (num != 0) {
                    // Store number
                    numbers[num_count++] = num;
                    num = 0;  // Reset number for the next one
                }
            }
        }

        // After the loop, check if there is a number left to add
        if (num != 0) {
            numbers[num_count++] = num;
        }

        sum += find_combinations(numbers, num_count, numbers[0], 0, 1);

        // Clear go next line
        num_count = 0;
    }

    printf("Sum is:\n%llu\n", sum);

    fclose(file);
    return 0;
}

