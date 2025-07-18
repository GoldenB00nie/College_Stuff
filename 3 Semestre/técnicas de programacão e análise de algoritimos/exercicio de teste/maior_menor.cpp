#include <stdio.h>

int main() {
    int n;
    do {
    scanf(" %d", &n);
    } while(n < 0 || n > 1000);
    
    int num1, num2, res[2 * n];
    for(int i = 0; i < 2 * n; i = i + 2) {
        scanf(" %d %d", &num1, &num2);
        if(num1 < num2) {
            res[i] = num2;
            res[i + 1] = num1;
        }
        else {
            res[i] = num1;
            res[i + 1] = num2;
        }
    }
    
    for(int i = 0; i < 2 * n; i = i + 2) {
        printf("%d %d\n", res[i], res[i + 1]);
    }


}