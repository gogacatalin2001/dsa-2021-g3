#include <stdio.h>
#include <stdlib.h>

int moveRow[] = {-1,-1, 0}; /// move N, NE, E
int moveCol[] = { 0, 1, 1}; /// move N, NE, E
int counter = 0;

int checkMove(int n, int m, int i, int j)
{
    if((i > 0 && i < n) && (j > 0 && j < m))
        return 1; /// the move is correct
    return 0; /// the move is out of the matrix boundaries
}

int countPaths(int n, int m, int i, int j)
{

    if(i == 0 && j == m-1)
    {
        return 1;
    }
    else
    {
        for(int k = 0; k < 3; k++)
        {
            if(checkMove(n, m, i + moveRow[k], j + moveCol[k]) == 1)
            {
                i += moveRow[k];
                j += moveCol[k];
                counter = counter + countPaths(n, m, i, j);
            }
        }
        return 0;
    }

}
int main()
{

    int n,m;
    printf("Enter the matrix dimensions M and M: ");
    scanf("%d%d", &n, &m);
    countPaths(n, m, n-1, 0);
    printf("There are %d possible paths in a %d by %d matrix.", counter, n, m);

    printf("%d", checkMove(3, 3, 2, 0));
    return 0;
}
