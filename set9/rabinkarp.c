#include <stdio.h>
#include <string.h>

#define d 256

#define Q 101

void searchRabinKarp(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;

    for (i = 0; i < M - 1; i++)
    {
        h = (h * d) % Q;
    }

    for (i = 0; i < M; i++)
    {
        p = (d * p + pat[i]) % Q;
        t = (d * t + txt[i]) % Q;
    }

    int found = 0;
    for (i = 0; i <= N - M; i++)
    {

        if (p == t)
        {
            for (j = 0; j < M; j++)
            {
                if (txt[i + j] != pat[j])
                {
                    break;
                }
            }

            if (j == M)
            {
                printf("Pattern found at index %d\n", i);
                found = 1;
            }
        }

        if (i < N - M)
        {
            t = (d * (t - txt[i] * h) + txt[i + M]) % Q;

            if (t < 0)
            {
                t = (t + Q);
            }
        }
    }

    if (!found)
    {
        printf("Pattern not found in the text.\n");
    }
}

int main()
{
    char txt[1000];
    char pat[1000];

    printf("Enter the text string: ");
    if (fgets(txt, sizeof(txt), stdin) != NULL)
    {
        txt[strcspn(txt, "\n")] = 0;
    }

    printf("Enter the pattern to search: ");
    if (fgets(pat, sizeof(pat), stdin) != NULL)
    {
        pat[strcspn(pat, "\n")] = 0;
    }

    printf("\nSearching for pattern \"%s\" in text...\n", pat);
    searchRabinKarp(pat, txt);

    return 0;
}