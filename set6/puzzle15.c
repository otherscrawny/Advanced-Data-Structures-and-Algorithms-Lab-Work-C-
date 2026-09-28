#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4

// Function to calculate the number of misplaced tiles (heuristic h(x))
int calculateCost(int initial[N][N], int goal[N][N])
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (initial[i][j] && initial[i][j] != goal[i][j])
            {
                count++;
            }
        }
    }
    return count;
}

// Function to print the board matrix
void printMatrix(int mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%2d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Check if the board matches the goal
int isGoal(int mat[N][N], int goal[N][N])
{
    return memcmp(mat, goal, sizeof(int) * N * N) == 0;
}
void solvePuzzle(int initial[N][N], int goal[N][N])
{
    int current[N][N];
    memcpy(current, initial, sizeof(int) * N * N);

    int level = 0;

    // Simple iterative Branch and Bound simulation loop
    while (!isGoal(current, goal))
    {
        int x = -1, y = -1;

        // Find empty tile (0) coordinates
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (current[i][j] == 0)
                {
                    x = i;
                    y = j;
                }
            }
        }

        int minCost = 99999;
        int bestMat[N][N];

        // Possible moves: Up, Down, Left, Right
        int rowMove[] = {-1, 1, 0, 0};
        int colMove[] = {0, 0, -1, 1};

        int moved = 0;
        for (int i = 0; i < 4; i++)
        {
            int newX = x + rowMove[i];
            int newY = y + colMove[i];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N)
            {
                int temp[N][N];
                memcpy(temp, current, sizeof(int) * N * N);

                // Swap empty space with neighbor
                temp[x][y] = temp[newX][newY];
                temp[newX][newY] = 0;

                int h = calculateCost(temp, goal);
                int cost = (level + 1) + h; // C(x) = g(x) + h(x)

                if (cost < minCost)
                {
                    minCost = cost;
                    memcpy(bestMat, temp, sizeof(int) * N * N);
                    moved = 1;
                }
            }
        }

        if (!moved)
        {
            printf("No further optimal moves found.\n");
            break;
        }

        memcpy(current, bestMat, sizeof(int) * N * N);
        level++;

        printf("Step %d (Selected Cost: %d):\n", level, minCost);
        printMatrix(current);

        if (level > 20)
        { // Safety break for demonstration
            printf("Max search depth reached.\n");
            break;
        }
    }

    if (isGoal(current, goal))
    {
        printf("Puzzle solved successfully in %d moves!\n", level);
    }
}

int main()
{
    int initial[N][N];
    FILE *file = fopen("puzzle15.txt", "r");
    if (file == NULL)
    {
        printf("Error: Could not open puzzle15.txt\n");
        return 1;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (fscanf(file, "%d", &initial[i][j]) != 1)
            {
                printf("Error: Invalid data in puzzle15.txt\n");
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);

    // Goal configuration
    int goal[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}};

    printf("Initial State:\n");
    printMatrix(initial);

    printf("Goal State:\n");
    printMatrix(goal);

    // Call the solver function
    solvePuzzle(initial, goal);

    return 0;
}