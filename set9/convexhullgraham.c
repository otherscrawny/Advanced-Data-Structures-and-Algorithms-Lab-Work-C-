#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int x, y;
} Point;

Point p0;

void swap(Point *p1, Point *p2)
{
    Point temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int distSq(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
}

int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;

    return (o == 2) ? -1 : 1;
}

void grahamScan(Point points[], int n)
{
    if (n < 3)
    {
        printf("Convex hull requires at least 3 points.\n");
        return;
    }

    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++)
    {
        int y = points[i].y;
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x))
        {
            ymin = points[i].y;
            min = i;
        }
    }

    swap(&points[0], &points[min]);

    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(Point), compare);

    int m = 1;
    for (int i = 1; i < n; i++)
    {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
        {
            i++;
        }
        points[m] = points[i];
        m++;
    }

    if (m < 3)
    {
        printf("Convex hull not possible with these points.\n");
        return;
    }

    Point *stack = (Point *)malloc(m * sizeof(Point));
    if (stack == NULL)
    {
        printf("Memory allocation failed for stack!\n");
        return;
    }

    int top = -1;
    stack[++top] = points[0];
    stack[++top] = points[1];
    stack[++top] = points[2];

    for (int i = 3; i < m; i++)
    {
        while (top >= 1 && orientation(stack[top - 1], stack[top], points[i]) != 2)
        {
            top--;
        }
        stack[++top] = points[i];
    }

    printf("\nThe points in the Convex Hull are:\n");
    for (int i = 0; i <= top; i++)
    {
        printf("(%d, %d)\n", stack[i].x, stack[i].y);
    }

    free(stack);
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

    grahamScan(points, n);
    free(points);

    return 0;
}