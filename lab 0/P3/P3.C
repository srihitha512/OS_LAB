#include <stdio.h>

int main() {
    int r, c, i, j;

    printf("Enter rows and columns: ");
    scanf("%d %d", &r, &c);

    int a[r][c];

    printf("Enter elements:\n");
    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    for(i = 0; i < r; i++) {
        int rowSum = 0;
        for(j = 0; j < c; j++) {
            rowSum = rowSum + a[i][j];
        }
        printf("Sum of row %d = %d\n", i+1, rowSum);
    }

    for(j = 0; j < c; j++) {
        int colSum = 0;
        for(i = 0; i < r; i++) {
            colSum = colSum + a[i][j];
        }
        printf("Sum of column %d = %d\n", j+1, colSum);
    }

    return 0;
}