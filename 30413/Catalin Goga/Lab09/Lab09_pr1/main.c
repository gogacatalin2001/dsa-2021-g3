#include <stdio.h>
#include <stdlib.h>

#define MAXN 100
#define MINIMUM -1000000
void error(char *msg)
{
    printf(msg);
    exit(1);
}

int sum(int arr[], int start, int end)
{
    int sum = 0;
    for(int i = start; i <= end; i++)
        sum += arr[i];
    return sum;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int max3(int a, int b, int c)
{
    return max(max(a, b), c);
}

int maxMidSum(int arr[], int left, int mid, int right)
{
    // Include elements on left of mid.
    int sum = 0;
    int leftSum = MINIMUM;
    for (int i = mid; i >= left; i--) {
        sum = sum + arr[i];
        if (sum > leftSum)
            leftSum = sum;
    }

    // Include elements on right of mid
    sum = 0;
    int rightSum = MINIMUM;
    for (int i = mid + 1; i <= right; i++) {
        sum = sum + arr[i];
        if (sum > rightSum)
            rightSum = sum;
    }

    // Return sum of elements on left and right of mid
    return max3(leftSum + rightSum, leftSum, rightSum);
}

int maxSum(int arr[], int left, int right)
{
    if(left == right)
        return arr[left];
    // compute the mid index
    int mid = (left + right) / 2;
    // return max between side sums and mid sum
    return max3(maxSum(arr, left, mid), maxSum(arr, mid + 1, right), maxMidSum(arr, left, mid, right));
}

int main(int argc, char **argv)
{
    FILE *in, *out;
    if((in = fopen(argv[1], "r")) == NULL)
        error("Cannot open input file!");
    if((out = fopen(argv[2], "w")) == NULL)
        error("Cannot output input file!");

    int array[MAXN];
    // read array
    int n;// nb of elements
    fscanf(in, "%d", &n);
    for(int i = 0; i < n; i++)
        fscanf(in, "%d", &array[i]);
    fprintf(out, "%d", maxSum(array, 0, n-1));
    return 0;
}
