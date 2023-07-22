#include <stdio.h>
#include <stdlib.h>

struct MemoryBlock {
    void* address;
    size_t size;
    struct MemoryBlock* next;
};

struct MemoryBlock* allocatedMemoryList = NULL;

void* customMalloc(size_t size) {
    void* address = malloc(size);
    if (address == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    struct MemoryBlock* newBlock = (struct MemoryBlock*)malloc(sizeof(struct MemoryBlock));
    if (newBlock == NULL) {
        printf("Memory allocation failed.\n");
        free(address);
        return NULL;
    }

    newBlock->address = address;
    newBlock->size = size;
    newBlock->next = allocatedMemoryList;
    allocatedMemoryList = newBlock;

    return address;
}

void customFree(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    struct MemoryBlock* prev = NULL;
    struct MemoryBlock* current = allocatedMemoryList;
    while (current != NULL) {
        if (current->address == ptr) {
            if (prev == NULL) {
                allocatedMemoryList = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            free(ptr);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Invalid or unallocated memory block.\n");
}

#define MEMORY_SIZE 100
#define CONSOLE_WIDTH 100

char memory[MEMORY_SIZE];

void visualizeMemory() {
    printf("Memory Visualization:\n");

    for (int i = 0; i < MEMORY_SIZE; i++) {
        char c = '.';
        for (struct MemoryBlock* current = allocatedMemoryList; current != NULL; current = current->next) {
            char* blockStart = (char*)current->address;
            char* blockEnd = blockStart + current->size;
            if (memory + i >= blockStart && memory + i < blockEnd) {
                c = '*';
                break;
            }
        }
        printf("%c", c);
    }

    printf("\n\n");
}

// void visualizeMemory() {
//     printf("Memory Visualization:\n");

//     int blocksPerChar = MEMORY_SIZE / CONSOLE_WIDTH;

//     for (int i = 0; i < MEMORY_SIZE; i += blocksPerChar) {
//         int allocatedBytes = 0;
//         int j;

//         for (struct MemoryBlock* current = allocatedMemoryList; current != NULL; current = current->next) {
//             char* blockStart = (char*)current->address;
//             char* blockEnd = blockStart + current->size;

//             for (j = i; j < i + blocksPerChar; j++) {
//                 if (memory + j >= blockStart && memory + j < blockEnd) {
//                     allocatedBytes++;
//                 }
//             }
//         }

//         for (j = i; j < i + blocksPerChar; j++) {
//             if (allocatedBytes > 0) {
//                 printf("*");
//                 allocatedBytes--;
//             } else {
//                 printf("-");
//             }
//         }
//     }

//     printf("\n\n");
// }

int main() {
    char* str1 = (char*)customMalloc(10 * sizeof(char));
    char* str2 = (char*)customMalloc(5 * sizeof(char));
    int* nums = (int*)customMalloc(3 * sizeof(int));

    visualizeMemory();

    customFree(str1);
    visualizeMemory();

    char* str3 = (char*)customMalloc(20 * sizeof(char));
    visualizeMemory();

    customFree(nums);
    customFree(str2);
    customFree(str3);
    visualizeMemory();

    #ifdef _WIN32
        system("pause");
    #else
        getchar();
    #endif

    return 0;
}
