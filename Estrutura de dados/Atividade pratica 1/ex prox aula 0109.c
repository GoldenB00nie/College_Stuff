#include <stdio.h>

/*
Crie uma função que troque o valor de dois números inteiros passados por referência
*/

void trocarValores (int *ptrNumX, int *ptrNumY)
{
    int temp = *ptrNumX;
    *ptrNumX = *ptrNumY;
    *ptrNumY = temp;
    return;
}

int main()
{
    int NumX, NumY;
    printf("Insira um valor x: "); scanf(" %d", &NumX);
    printf("Agora insira um valor y: "); scanf(" %d", &NumY);
    trocarValores(&NumX, &NumY);

    printf("Depois da troca, x = %d e y = %d.", NumX, NumY);

}