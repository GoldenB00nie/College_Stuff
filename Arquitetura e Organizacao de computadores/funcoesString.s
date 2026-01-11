    .data

    .text
    .globl mystrlen
    .globl mystrcpy
    .globl mystrcmp
    .globl mystrcat
    .globl mystrncmp

    # Funcoes implementadas em 64 bits. O strcat nao vai funcionar com RISC-V 32 bits

    # int mystrlen (const char* str);
    # Argumento:
        # a0: ponteiro para o início da string
    # Retorno:
        # a0: comprimento da string

mystrlen:
    mv t2, a0
    li t1, 0
    strlen_loop:
        lb t0, 0(a0)
        beq t0, x0, strlen_done
        addi a0, a0, 1
        addi t1, t1, 1
        jal x0, strlen_loop
    strlen_done:
    add a0, x0, t1
    ret # uma pseudo instrucao para retornar a funcao para o enderećo em 'ra'


    # char* mystrcpy (char* dest, const char* src)
    # Argumentos:
        # a0: destino da copia
        # a1: fonte para a copia
    # Retorno:
        # a0: inicio da string de destino

mystrcpy:
    mv t0, a0 # copia o endereco inicial
    strcpy_loop:
        lb t1, 0(a1)
        sb t1, 0(a0)
        addi a1, a1, 1
        addi a0, a0, 1
        bne t1, x0, strcpy_loop
    mv a0, t0 # recarrega o endereco inicial para o retorno
    ret


    # int mystrcmp (const char* str1, const char* str2)
    # Argumentos:
        # a0: string origem de comparacao
        # a1: string destino de comparacao
    # Retorno:
        # a0: inteiro comparativo
            # a0 = 0: str1 e str2 sao iguais
            # a0 > 0: str1 maior que str2
            # a0 < 0: str1 menor que str2

mystrcmp:
    strcmp_loop:
        lb t0, 0(a0)
        lb t1, 0(a1)
        bne t0, t1, strcmp_done
        beq t0, x0, strcmp_done
        addi a0, a0, 1
        addi a1, a1, 1
        jal x0, strcmp_loop
    strcmp_done:
        sub a0, t0, t1
        ret


    # char* mystrcat (char* dest, const char* src)
    # Argumentos:
        # a0: string de destino da concatenacao
        # a1: string origem da concatenacao
    # Retorno:
        # a0: string de destino completa
    
mystrcat:
    addi sp, sp, -32
    sd ra, 24(sp)
    sd a0, 16(sp)
    sd a1, 8(sp)
    call mystrlen
    
    mv t0, a0
    ld a0, 16(sp)
    ld a1, 8(sp)
    add a0, a0, t0
    call mystrcpy
    
    ld a0, 16(sp)
    ld ra, 24(sp)
    addi sp, sp, 32
    ret


    # int mystrncmp (const char* str1, const char* str2, int count)
    # Argumentos:
        # a0: string origem de comparacao
        # a1: string destino de comparacao
        # a2: inteiro com a contagem de caracteres a serem verificados
    # Retorno:
        # a0: inteiro comparativo até a contagem
            # a0 = 0: str1 e str2 sao iguais
            # a0 > 0: str1 maior que str2
            # a0 < 0: str1 menor que str2

mystrncmp:
    beq a2, x0, strncmp_zero
    strncmp_loop:
        lb t0, 0(a0)
        lb t1, 0(a1)
        bne t0, t1, strncmp_done
        beq t0, x0, strncmp_done
        addi a0, a0, 1
        addi a1, a1, 1
        addi a2, a2, -1
        bne a2, x0, strncmp_loop
    strncmp_done:
        sub a0, t0, t1
        ret
    strncmp_zero:
        li a0, 0
        ret
