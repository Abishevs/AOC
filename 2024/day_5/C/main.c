#include <stdio.h>

typedef struct Page {
    // Size + null terminator
    char left[3];
    char right[3];
} Page;

void printElem(Page *page){
        printf("Left: %s Right: %s\n", page->left, page->right);
}

int main()
{
    FILE *fptr;
    char fileName[10] = "input.txt";
    Page pages[20];

    fptr = fopen(fileName,"r");

    if(fptr == NULL) {
        printf("File: '%s' not found.\n", fileName);
        return 1;
    }

    char input[300];
    int pos = 0;
    while(fgets(input, 300 ,  fptr)) 
    {
        if (input[0] == '\n')
        {
            break;
        }

        int delimilator = 0;
        int leftIndex = 0;
        int rightIndex = 0;

        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == '\n') {
                continue;
            } else if (input[i] == '|' ) {
                delimilator = 1;
                continue;
            }

            if (delimilator) {
                if (rightIndex < 2) {
                    pages[pos].right[rightIndex++] = input[i];
                }
            } else {
                if (leftIndex < 2) {
                    pages[pos].left[leftIndex++] = input[i];
                }
            }
            printf("Character: %c\n", input[i]);

        }
        printf("%s", input);
        
        // Ensure null termination
        pages[pos].left[2] = '\0';
        pages[pos].right[2] = '\0';
        pos++;
    };


    for (int i = 0; i < pos; i++)
    {
        printElem(&pages[i]);
    }

    fclose(fptr);
    return 0;
}
