#include <stdio.h>
#include <string.h>

#define d 256 // Number of characters in the input alphabet

// q is a prime number used for hashing to minimize collisions
#define Q 101

// Function to implement Rabin-Karp search
void searchRabinKarp(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0; // Hash value for pattern
    int t = 0; // Hash value for text
    int h = 1;

    // The value of h would be "pow(d, M-1) % Q"
    for (i = 0; i < M - 1; i++)
    {
        h = (h * d) % Q;
    }

    // Calculate the hash value for pattern and the first window of text
    for (i = 0; i < M; i++)
    {
        p = (d * p + pat[i]) % Q;
        t = (d * t + txt[i]) % Q;
    }

    // Slide the pattern over text one by one
    int found = 0;
    for (i = 0; i <= N - M; i++)
    {

        // Check the hash values of current window of text and pattern.
        // If the hash values match, then only check characters one by one.
        if (p == t)
        {
            // Check for characters one by one
            for (j = 0; j < M; j++)
            {
                if (txt[i + j] != pat[j])
                {
                    break;
                }
            }

            // If p == t and pat[0...M-1] = txt[i...i+M-1]
            if (j == M)
            {
                printf("Pattern found at index %d\n", i);
                found = 1;
            }
        }

        // Calculate hash value for the next window of text: Remove leading digit,
        // add trailing digit
        if (i < N - M)
        {
            t = (d * (t - txt[i] * h) + txt[i + M]) % Q;

            // We might get negative values of t, converting it to positive
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
    // Buffers to store user input
    char txt[1000];
    char pat[1000];

    printf("Enter the text string: ");
    // Read a line of text, handling spaces
    if (fgets(txt, sizeof(txt), stdin) != NULL)
    {
        // Remove trailing newline character if present
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