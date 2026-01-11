#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

double benchmark(long long arrSize, short type) {
    clock_t start, end;
    long long soma = 0;

    int *arr1 = malloc(arrSize * sizeof(int));
    for (long long i = 0; i < arrSize; i++)
        arr1[i] = i;

    if(type == 0) {
        start = clock();
        for (long long i = 0; i < arrSize; i++)
            soma += arr1[i];
        end = clock();

    }
    else {
        int *arr2 = malloc(arrSize * sizeof(int));
        for (long long i = 0; i < arrSize; i++)
            arr2[i] = i;

        shuffle(arr2, arrSize);

        start = clock();
        for (long long i = 0; i < arrSize; i++)
            soma += arr1[arr2[i]];
        end = clock();

        free(arr2);
    }

    free(arr1);
    printf("Soma: %lld\n", soma);
    return (double)(end - start) / CLOCKS_PER_SEC;
}


int main() {
    long long testes[] = {1e5, 1e6, 1e7};
    int qntTestes = 3;
    double res, somaSeq = 0, somaRand = 0;

    printf("===== Benchmark de acesso ah memoria em C ====\n\n");
    for (int i = 0; i < qntTestes; i++) {
        printf("\tTestando com %lld numeros\n\n", testes[i % 3]);

        res = benchmark(testes[i % 3], 0);
        printf("Tempo do acesso sequencial: %.6f\n", res);
        somaSeq += res;

        res = benchmark(testes[i % 3], 1);
        printf("Tempo do acesso randomico: %.6f\n\n", res);
        somaRand += res;
    }

    double mediaSeq = somaSeq / qntTestes, mediaRand = somaRand /qntTestes;
    printf("Media do acesso sequencial: %.6f\n", mediaSeq);
    printf("Media do acesso randomico: %.6f\n", mediaRand);

    return 0;
}
