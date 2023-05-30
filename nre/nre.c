#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 256


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
        return 1;
    }


  

    // Inicializa o mapa de memória
    unsigned char memory[MEMORY_SIZE];

    // Lê o payload do arquivo binário
  fread(memory, sizeof(unsigned char), MEMORY_SIZE, file);
  fclose(file);

  printf("\n\n");
  
  if (memory[0] != 42) {
        printf("Arquivo inválido\n");
        return 1;
    }
    // Variáveis de estado
    int accumulator = 0;
    accumulator = memory[1];
    int pc = 0;
    pc = memory[2];
    int flagN = 0;
    int flagZ = 0;
    unsigned char value;
    unsigned char address;
    unsigned char jumpAddress;
    
    // Executa as instruções
    short int flag = 1;
    while (flag) {
        switch (memory[pc]) {
        case 00:  // NOP
            // Não faz nada, apenas avança para a próxima instrução
            pc += 1;
            break;

        case 48:  // ADD
            // Soma o valor na posição de memória seguinte ao acumulador
            pc += 1;
            address = memory[pc];
            accumulator += memory[address];
            pc += 1;
            break;


        case 16:  // STA
            // Armazena o acumulador na posição de memória seguinte
            pc += 1;
            address = memory[pc];
            memory[address] = accumulator;
            pc += 1;
            break;

        case 32:  // LDA
            // Carrega o acumulador com o valor da posição de memória seguinte
            pc += 1;
            address = memory[pc];
            accumulator = memory[address];
            pc += 1;
            break;

        case 128:  // JMP
            // Salta para a posição de memória seguinte
            pc += 1;
            jumpAddress = memory[pc];
            pc = jumpAddress;
            break;

        case 144:  // JN
            // Salta para a posição de memória seguinte se o bit mais significativo do acumulador for 1 (negativo)
            pc += 1;
            jumpAddress = memory[pc];
            if (memory[0] >> 7 & 1) {
                pc = jumpAddress;
            } else {
                pc += 1;
            }
            break;
          

        case 160:  // JZ
            // Salta para a posição de memória seguinte se o acumulador for zero
            pc += 1;
            jumpAddress = memory[pc];
            if (memory[0] == 0) {
                pc = jumpAddress;
            } else {
                pc += 1;
            }
            break;
          
          case 240:  // HLT
            // Quebra o while
            flag = 0;
            break;
        default:
            // Instrução inválida
            printf("Instrução inválida: %u\n", memory[pc]);
            exit(1);
            break;
    }

        // Verifica se chegou ao fim do programa
        if (memory[pc] == 0) {
            break;
        }
        
        // Atualiza as flags N e Z
        flagN = (accumulator >> 7) & 1;
        flagZ = (accumulator == 0) ? 1 : 0;

     
    }

    // Imprime os resultados
    printf("Valor do Acumulador: %u\n", accumulator);
    printf("Valor do PC: %u\n", pc);
    printf("Flag N: %u\n", flagN);
    printf("Flag Z: %u\n", flagZ);

    // Imprime o mapa de memória completo
    printf("Mapa de memória completo:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
      if (memory [i + 1] == 0 && memory [i + 2] == 0 && memory[i+3] == 0 && memory[i]== 0){
        printf("[...]\n");
        break;
      }
        printf("%u: %u\n", i, memory[i]);
    }

    return 0;
}

