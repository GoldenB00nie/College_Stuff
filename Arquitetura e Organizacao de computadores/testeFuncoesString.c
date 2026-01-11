#include <stdio.h>

extern int mystrlen(const char* str);
extern char* mystrcpy(char* dest, const char* src);
extern int mystrcmp(const char* str1, const char* str2);
extern char* mystrcat(char* dest, const char* src);
extern int mystrncmp(const char* str1, const char* str2, int count);

const char* comparaStrcmp(int output);

int main() {
    // Aluno: Guilherme de Oliveira Portas
    // As funcoes foram implementadas para RISC-V 64 bits. O strcat não vai funcionar com 32 bits.

    const char* minhaStr = "Hello, RISC-V!";
    int tamanhoStr = mystrlen(minhaStr);
    printf("\n\n========== strlen ===========\n");
    printf("\nString a ser medida: \"%s\"", minhaStr);
    printf("\nComprimento da string: %d", tamanhoStr);

    const char* strOrigemCpy = "String a ser copiada";
    char strDestinoCpy[50] = "Vazia";
    printf("\n\n========== strcpy ===========\n");
    printf("\nString a ser copiada: \"%s\"", strOrigemCpy);
    printf("\nString de destino a receber a copia: \"%s\"", strDestinoCpy);
    printf("\n");

    mystrcpy(strDestinoCpy, strOrigemCpy);
    printf("\nString de destino apos a copia: \"%s\"", strDestinoCpy);

    printf("\n\n========== strcmp ===========\n");
    const char* strOriginal = "Hello, World!";
    const char* strMaior = "Hello, Guilherme!";
    const char* strIgual = "Hello, World!";
    const char* strVazia = "";
    const char* strMenor = "Hello,Mundo!";
    printf("\nString original: \"%s\"", strOriginal);
    printf("\nString Maior: \"%s\"", strMaior);
    printf("\nString igual: \"%s\"", strIgual);
    printf("\nString vazia: \"%s\"", strVazia);
    printf("\nString menor: \"%s\"", strMenor);
    printf("\n");

    int res = mystrcmp(strOriginal, strIgual);
    printf("\nString original + string igual: (%d: %s)", res, comparaStrcmp(res));
    res = mystrcmp(strOriginal, strMaior);
    printf("\nString original + string Maior: (%d: %s)", res, comparaStrcmp(res));
    res = mystrcmp(strOriginal, strVazia);
    printf("\nString original + string vazia: (%d: %s)", res, comparaStrcmp(res));
    res = mystrcmp(strOriginal, strMenor);
    printf("\nString original + string menor: (%d: %s)", res, comparaStrcmp(res));

    printf("\n\n========== strcat ===========\n");
    const char* strOrigemCat = "Ola, eu fui concatenado";
    char strDestinoCat[150] = "Essa string sera concatenada. ";
    printf("\nString de origem da concatenacao: \"%s\"", strOrigemCat);
    printf("\nString de destino da concatenacao: \"%s\"", strDestinoCat);
    printf("\n");

    mystrcat(strDestinoCat, strOrigemCat);
    printf("\nString de destino apos a concatenacao: \"%s\"", strDestinoCat);

    printf("\n\n========== strncmp ===========\n");
    int qntChars = 6;
    printf("\nQuantidade de caracteres a serem verificados: %d", qntChars);
    printf("\nString original: \"%s\"", strOriginal);
    printf("\nString maior: \"%s\"", strMaior);
    printf("\nString igual: \"%s\"", strIgual);
    printf("\nString vazia: \"%s\"", strVazia);
    printf("\nString menor: \"%s\"", strMenor);
    printf("\n");

    res = mystrncmp(strOriginal, strIgual, qntChars);
    printf("\nString original + string igual: (%d: %s)", res, comparaStrcmp(res));
    res = mystrncmp(strOriginal, strMaior, qntChars);
    printf("\nString original + string Maior: (%d: %s)", res, comparaStrcmp(res));
    res = mystrncmp(strOriginal, strVazia, qntChars);
    printf("\nString original + string vazia: (%d: %s)", res, comparaStrcmp(res));
    res = mystrncmp(strOriginal, strMenor, qntChars);
    printf("\nString original + string menor: (%d: %s)", res, comparaStrcmp(res));
    printf("\n");
}

const char* comparaStrcmp(int output) {
    if(output == 0) return "As strings sao iguais";
    else if(output > 0) return "String 1 eh maior que string 2";
    else return "String 1 eh menor que string 2";
}