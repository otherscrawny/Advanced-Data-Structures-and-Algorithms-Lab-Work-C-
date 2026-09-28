#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int x, y;
} Point;

int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
}

void convexHull(Point points[], int n)
{
    if (n < 3)
    {
        printf("Convex hull requires at least 3 points.\n");
        return;
    }

    int l = 0;
    for (int i = 1; i < n; i++)
    {
        if (points[i].x < points[l].x)
        {
            l = i;
        }
    }

    int p = l, q;
    printf("\nThe points in the Convex Hull are:\n");

    do
    {

        q = (p + 1) % n;
        for (int i = 0; i < n; i++)
        {
            if (orientation(points[p], points[i], points[q]) == 2)
            {
                q = i;
            }
        }

        printf("(%d, %d)\n", points[p].x, points[p].y);

        p = q;

    } while (p != l);
}

int main()
{
    int n;

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

    Point *points = (Point *)malloc(n * sizeof(Point));
    if (points == NULL)
    {
        printf("Memory allocation failed!\n");
        fclose(file);
        return 1;
    }

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

    fclose(file);

    convexHull(points, n);

    free(points);

    return 0;
}