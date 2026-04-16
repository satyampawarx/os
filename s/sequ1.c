#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FILES 50
#define MAX_NAME 20

int *bitVector;
int n;   // number of disk blocks

struct Directory 
{
    char filename[MAX_NAME]; 
    int start;
    int length;
} dir[MAX_FILES];

int fileCount = 0;

/* Display Bit Vector */
void showBitVector() 
{
    printf("\nBit Vector:\n");
    for (int i = 0; i < n; i++)
     {
        printf("%d ", bitVector[i]);
    }
    printf("\n");
}

/* Create New File using Contiguous Allocation */
void createFile() 
{
    char name[MAX_NAME];
    int len;

    printf("\nEnter file name: ");
    scanf("%s", name);

    printf("Enter file length (number of blocks): ");
    scanf("%d", &len);

    if (len <= 0 || len > n) 
    {
        printf("Invalid file length!\n");
        return;
    }

    // Search for contiguous free blocks
    for (int i = 0; i <= n - len; i++) 
    {
        int j;
        for (j = 0; j < len; j++) 
        {
            if (bitVector[i + j] == 1)
                break;
        }

        if (j == len) 
        {
            // Allocate blocks
            for (j = 0; j < len; j++)
                bitVector[i + j] = 1;

            strcpy(dir[fileCount].filename, name);
            dir[fileCount].start = i;
            dir[fileCount].length = len;
            fileCount++;

            printf("File '%s' allocated successfully.\n", name);
            printf("Start Block: %d, Length: %d\n", i, len);
            return;
        }
    }

    printf("Not enough contiguous free space to allocate file.\n");
}

/* Show Directory */
void showDirectory() 
{
    if (fileCount == 0) 
    {
        printf("\nDirectory is empty.\n");
        return;
    }

    printf("\nDirectory Contents:\n");
    printf("Filename\tStart Block\tLength\n");
    for (int i = 0; i < fileCount; i++) 
    {
        printf("%s\t\t%d\t\t%d\n",
               dir[i].filename,
               dir[i].start,
               dir[i].length);
    }
}

/* Delete File */
void deleteFile() {
    char name[MAX_NAME];
    printf("\nEnter file name to delete: ");
    scanf("%s", name);

    for (int i = 0; i < fileCount; i++)
     {
        if (strcmp(dir[i].filename, name) == 0) 
        {
            // Free blocks
            for (int j = 0; j < dir[i].length; j++)
             {
                bitVector[dir[i].start + j] = 0;
            }

            // Shift directory entries
            for (int k = i; k < fileCount - 1; k++)
             {
                dir[k] = dir[k + 1];
            }

            fileCount--;
            printf("File '%s' deleted successfully.\n", name);
            return;
        }
    }

    printf("File not found.\n");
}

int main() 
{
    int choice;

    printf("Enter number of disk blocks: ");
    scanf("%d", &n);

    bitVector = (int *)malloc(n * sizeof(int));

    // Random initialization of bit vector
    srand(time(NULL));
    for (int i = 0; i < n; i++) 
    {
        bitVector[i] = rand() % 2;
    }

    do 
    {
        printf("\n--- Contiguous File Allocation Menu ---\n");
        printf("1. Show Bit Vector\n");
        printf("2. Create New File\n");
        printf("3. Show Directory\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: showBitVector(); break;
            case 2: createFile(); break;
            case 3: showDirectory(); break;
            case 4: deleteFile(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);

    free(bitVector);
    return 0;
}












