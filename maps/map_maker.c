#include <stdio.h>

#define SIZE 20

int main() {
    int map[SIZE][SIZE];

    // Initialize the map with walls (1) and spaces (0)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == 0 || i == SIZE-1 || j == 0 || j == SIZE-1) {
                map[i][j] = 1; // Walls
            } else {
                map[i][j] = 0; // Spaces
            }
        }
    }

    // Print the map
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d", map[i][j]);
        }
        printf("\n");
    }

    return 0;
}