#include <stdio.h>
#include <windows.h>

/*
* 1. Escreva um programa que usa uma estrutura capaz de armazenar as notas das atividades práticas e a nota final dos alunos
* de uma disciplina a partir da seguinte fórmula expressa pela Equação abaixo:
*
* AV1 = ((AP1 + AP2 + AP3 + AP4) / 4) * 0.4 + (NP) * 0.6

* 2. Faça o cadastro de 10 alunos e mostre o resultado.

*/

// !                                                        Estruturas

struct Notas
{
    float AP1, AP2, AP3, AP4, NP, AV1;
    long int matricula;
} Alunos[10];


//! Fim de estruturas

//                                                          Funções

void inicializarNotas()
{
    for (int i = 0; i < 10; i++)
    {
        Alunos[i].AP1 = -1; Alunos[i].AP2 = -1; Alunos[i].AP3 = -1;
        Alunos[i].AP4 = -1; Alunos[i].NP = -1; Alunos[i].matricula = -1;
    }
}

void calcularNotaFinalAluno(int aluno)
{
    Alunos[aluno].AV1 = ((Alunos[aluno].AP1 + Alunos[aluno].AP2 + Alunos[aluno].AP3 + Alunos[aluno].AP4) / 4) * 0.4 + (Alunos[aluno].NP) * 0.6;
}

void limpar_terminal()                          // Função para limpar o terminal
{
    #if defined(_WIN32) || defined(_WIN64) // verifica se o sistema é windows 32 bits ou 64 bits
        system("cls"); // windows
    #else
        system("clear"); // linux e mac
    #endif
}

// Fim de funções

int main()
{
    inicializarNotas();
    limpar_terminal();
    SetConsoleOutputCP(CP_UTF8); // permite letras com acentos de aparecerem no terminal
    int vezAluno;

    for (vezAluno = 0; vezAluno < 10; vezAluno++)
    {
        printf("Bem vindo, professor. Crie agora a matrícula do aluno %d (pode conter até 10 números positivos): ", vezAluno + 1);
        scanf(" %ld", &Alunos[vezAluno].matricula);
        while (Alunos[vezAluno].matricula < 0)
            {printf("\n\nNúmero de matrícula inválida. Tente novamente: "); scanf(" %ld", &Alunos[vezAluno].matricula);}
        limpar_terminal();
        
        printf("Matrícula realizada. Insira as notas dos alunos abaixo (devem ser entre 0 a 10).\n\n");
        while (Alunos[vezAluno].AP1 < 0 || Alunos[vezAluno].AP1 > 10)
            {printf("AP 1: "); scanf(" %f", &Alunos[vezAluno].AP1); 
            if (Alunos[vezAluno].AP1 < 0 || Alunos[vezAluno].AP1 > 10) {printf("\nNota inválida. Tente novamente.\n"); Alunos[vezAluno].AP1 = 0;}}
        while (Alunos[vezAluno].AP2 < 0 || Alunos[vezAluno].AP2 > 10)
            {printf("AP 2: "); scanf(" %f", &Alunos[vezAluno].AP2); 
            if (Alunos[vezAluno].AP2 < 0 || Alunos[vezAluno].AP2 > 10) {printf("\nNota inválida. Tente novamente.\n"); Alunos[vezAluno].AP2 = 0;}}
        while (Alunos[vezAluno].AP3 < 0 || Alunos[vezAluno].AP3 > 10)
            {printf("AP 3: "); scanf(" %f", &Alunos[vezAluno].AP3); 
            if (Alunos[vezAluno].AP3 < 0 || Alunos[vezAluno].AP3 > 10) {printf("\nNota inválida. Tente novamente.\n"); Alunos[vezAluno].AP3 = 0;}}
        while (Alunos[vezAluno].AP4 < 0 || Alunos[vezAluno].AP4 > 10)
            {printf("AP 4: "); scanf(" %f", &Alunos[vezAluno].AP4); 
            if (Alunos[vezAluno].AP4 < 0 || Alunos[vezAluno].AP4 > 10) {printf("\nNota inválida. Tente novamente.\n"); Alunos[vezAluno].AP4 = 0;}}
        while (Alunos[vezAluno].NP < 0 || Alunos[vezAluno].NP > 10)
            {printf("NP: "); scanf(" %f", &Alunos[vezAluno].NP); 
            if (Alunos[vezAluno].NP < 0 || Alunos[vezAluno].NP > 10) {printf("\nNota inválida. Tente novamente.\n"); Alunos[vezAluno].NP = 0;}}
        calcularNotaFinalAluno(vezAluno);
        char aprovadoOuN[10] = "";
        if (Alunos[vezAluno].AV1 < 7)
            strcpy(aprovadoOuN, "Reprovado");
        else
            strcpy(aprovadoOuN, "Aprovado");
        getchar();
        limpar_terminal();

        printf("Todas as notas inseridas. Aqui as informações do aluno:\n\n");
        printf("Matrícula: \t\t%ld", Alunos[vezAluno].matricula);
        printf("\nNota da AV1: \t\t%.1f", Alunos[vezAluno].AV1);
        printf("\nSituação do aluno: \t%s", aprovadoOuN);
        printf("\n\n\n\n\nAperte <ENTER> para continuar."); getchar();
        limpar_terminal();
    }
}

