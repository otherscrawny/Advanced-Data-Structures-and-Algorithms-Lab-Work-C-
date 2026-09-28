#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to compute the LPS (Longest Prefix Suffix) array
void computeLPSArray(char *pat, int M, int *lps)
{
    int len = 0; // Length of the previous longest prefix suffix
    lps[0] = 0;  // lps[0] is always 0
    int i = 1;

    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1]; // Fall back to previous prefix
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Function to implement KMP search algorithm
void KMPSearch(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);

    // Create lps[] to hold the longest prefix suffix values for the pattern
    int *lps = (int *)malloc(M * sizeof(int));
    if (lps == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    computeLPSArray(pat, M, lps);

    int i = 0; // Index for txt[]
    int j = 0; // Index for pat[]

    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        }
        else if (i < N && pat[j] != txt[i])
        {
            // Mismatch after j matches
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    free(lps); // Free dynamically allocated memory
}

int main()
{
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

    KMPSearch(pat, txt);

    return 0;
}