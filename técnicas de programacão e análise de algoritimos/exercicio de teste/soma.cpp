#include <stdio.h>

int main() {
    int n;
    scanf(" %d", &n);

    int num1, num2, res[n];
    for(int i = 0; i < n; i ++) {
        scanf(" %d", &num1);
        scanf(" %d", &num2);
        if(num1 < 1 || num1 > 10000 || num2 < 1 || num2 > 10000) {
            i--;
            continue;
        }
        res[i] = num1 + num2;
    }

    for(int i = 0; i < n; i ++) {
        printf("%d\n", res[i]);
    }
}