#include <stdio.h>
#include <limits.h>
int main() {
    int n, i;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];
    printf("Enter elements:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int smallest = INT_MAX;
    int second = INT_MAX;

    for(i = 0; i < n; i++) {
        if(a[i] < smallest) {
            second = smallest;
            smallest = a[i];
        }
        else if(a[i] < second && a[i] != smallest) {
            second = a[i];
        }
    }

    printf("Second smallest = %d", second);

    return 0;
}