#include <stdio.h>
#include <stdlib.h>
// Structure to represent a 2D point
typedef struct
{
    int x, y;
} Point;

// To find orientation of ordered triplet (p, q, r).
// Returns:
// 0 -> Collinear
// 1 -> Clockwise
// 2 -> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
}

// Function to find and print the convex hull using Jarvis's Algorithm
void convexHull(Point points[], int n)
{
    if (n < 3)
    {
        printf("Convex hull requires at least 3 points.\n");
        return;
    }

    // Find the leftmost point
    int l = 0;
    for (int i = 1; i < n; i++)
    {
        if (points[i].x < points[l].x)
        {
            l = i;
        }
    }

    // Start from the leftmost point, keep moving counterclockwise
    // until we reach the starting point again.
    int p = l, q;
    printf("\nThe points in the Convex Hull are:\n");

    do
    {
        // Search for a point 'q' such that orientation(p, i, q)
        // is counterclockwise for all points 'i'.
        q = (p + 1) % n;
        for (int i = 0; i < n; i++)
        {
            if (orientation(points[p], points[i], points[q]) == 2)
            {
                q = i;
            }
        }

        // Print the current hull point
        printf("(%d, %d)\n", points[p].x, points[p].y);

        // Set p as q for the next iteration
        p = q;

    } while (p != l); // Loop until we loop back to the first point
}

int main()
{
    int n;

    // Open the text file for reading
    FILE *file = fopen("points.txt", "r");
    if (file == NULL)
    {
        printf("Error: Could not open file 'points.txt'.\n");
        return 1;
    }

    if (fscanf(file, "%d", &n) != 1 || n <= 0)
    {
        printf("Invalid or missing number of points in the file.\n");
        fclose(file);
        return 1;
    }

    // Dynamically allocate memory based on the number of points in the file
    Point *points = (Point *)malloc(n * sizeof(Point));
    if (points == NULL)
    {
        printf("Memory allocation failed!\n");
        fclose(file);
        return 1;
    }

    // Read coordinates from the file into the points array (FIXED)
    for (int i = 0; i < n; i++)
    {
        if (fscanf(file, "%d %d", &points[i].x, &points[i].y) != 2)
        {
            printf("Error reading coordinates for point %d.\n", i + 1);
            free(points);
            fclose(file);
            return 1;
        }
    }

    // Close the file after reading
    fclose(file);

    // Compute and print the convex hull
    convexHull(points, n);

    // Free allocated memory
    free(points);

    return 0;
}