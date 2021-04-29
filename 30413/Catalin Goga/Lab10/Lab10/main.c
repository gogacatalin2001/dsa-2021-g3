#include <stdio.h>
#include <stdlib.h>

#define MAXN 100
#define MAXVAL 1000000
int minCost(int x, int y, int n, int m, int mat[MAXN][MAXN])
{
    int minVal = MAXVAL;
    // moving directions vectors (left, left upper diagonal, up)
    int iDir[] = {0 ,-1,-1};
    int jDir[] = {-1,-1, 0};
    // compute the minimum value for the current (x,y) position
    // on all the possible ways (left, left upper diagonal, up)
    for(int k = 0; k < 2; k++)
    {
        int i = x + iDir[k];
        int j = y + jDir[k];
        if(mat[i][j] < minVal)
            minVal = mat[i][j];
    }

    return minVal;
}

int solution(int n, int m, int mat[MAXN][MAXN])
{
    int solMat[MAXN][MAXN] = {0};
    solMat[0][0] = mat[0][0];
    //printf("%d ", mat[0][0]);
    // compute the first row
    for(int j = 1; j < m; j++)
    {
        solMat[0][j] = mat[0][j] + solMat[0][j-1];
        //printf("%d ",solMat[0][j]);
    }
    //printf("\n");
    // compute the first coloumn
    for(int i = 1; i < n; i++)
    {
        solMat[i][0] = mat[i][0] + solMat[i-1][0];
        //printf("%d\n", solMat[i][0]);
    }


    // compute the rest of the matrix
    for(int i = 1; i < n; i++)
        for(int j = 1; j < m; j++)
        {
            solMat[i][j] = minCost(i, j, n, m, solMat) + mat[i][j];
            //printf("%d ", solMat[i][j]);
        }

    return solMat[n-1][m-1];// return the solution
}

int main(int argc, char **argv)
{
    FILE *in;
    int n, m;
    int mat[MAXN][MAXN] = {0};

    // open the input file
    if((in = fopen(argv[1],"r")) == NULL)
    {
        printf("Couldn't open input file!");
        exit(1);
    }

    // read the matrix
    fscanf(in, "%d%d", &n, &m);
    for(int i = 0; i < n; i++)
        for(int j = 0; j <m; j++)
            fscanf(in, "%d", &mat[i][j]);

    // build the solution matrix
    printf("The shortest path has the cost: %d", solution(n, m, mat));

    return 0;
}
