#include <stdio.h>
#include <stdlib.h>
#define MAXN 100

int readInput(FILE *in,int *a, int *b, int v[MAXN])
{
    fscanf(in, "%d %d", a, b);
    int i = 0;
    while(fscanf(in, " %d", &v[i]) != EOF)
        i++;
    return i;
}

void swap(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void sort(int n, int v[MAXN])
{
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j++)
            if(v[i] < v[j]) swap(&v[i], &v[j]);
}

int operations(int a, int b, int n, int v[MAXN])
{
    int nbOfOperations = 0;

    if(a == b)
        return 1;
    else if((n-1) > 0)
    {
        if((b-a) >= v[n-1])
        {
            printf("A = A + %d\n", v[n-1]);
            nbOfOperations += operations(a + v[n-1], b, n, v);
        }
        else
        {
            printf("n--\n");
            nbOfOperations += operations(a, b, n-1, v);
        }

    }
    return nbOfOperations;
}

int main(int argc, char **agrv)
{
    // open input and output files
    FILE *in, *out;
    if((in = fopen(agrv[1], "r")) == NULL)
    {
        printf("Can't open input file (%s)!", agrv[1]);
        exit(1);
    }
    if((out = fopen(agrv[2], "w")) == NULL)
    {
        printf("Can't open output file (%s)!", agrv[2]);
        exit(1);
    }

    // read the data
    int a, b, v[MAXN] = {0}, n;
    n = readInput(in, &a, &b, v);
    // sort the array
    sort(n, v);
    printf("A = %d ; B = %d;\n", a, b);
    printf("Required number of operations is: %d", operations(a, b, n, v));
    return 0;
}
