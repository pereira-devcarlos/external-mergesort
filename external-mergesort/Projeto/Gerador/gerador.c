#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    const long long totalNumeros = 1610612736LL;  // ≈ 10 GB de inteiros
    const int tamBloco = 1000000;                 // Quantos números gerar por vez (~10 MB)
    const int numerosPorLinha = 50;               // Quantos números colocar em cada linha do arquivo

    // Aloca memória para um bloco de números
    int *bloco = malloc(tamBloco * sizeof(int));
    if (bloco == NULL) {
        printf("Erro: não foi possível alocar memória!\n");
        return 1;
    }

    // Abre o arquivo de saída em modo texto
    FILE *arq = fopen("dados/dados.txt", "w");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo!\n");
        free(bloco);
        return 1;
    }

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    long long gerados = 0;  // contador total de números gerados

    // Loop principal: gerar números em blocos
    while (gerados < totalNumeros) {
        int qtd = tamBloco;
        if (totalNumeros - gerados < tamBloco)
            qtd = (int)(totalNumeros - gerados);  // Ajuste para o último bloco

        // Gera números aleatórios para este bloco
        for (int i = 0; i < qtd; i++) {
            bloco[i] = rand() % 1000000 + 1;
        }

        // Escreve números no arquivo, 50 por linha
        for (int i = 0; i < qtd; i++) {
            fprintf(arq, "%d", bloco[i]);
            if ((i + 1) % numerosPorLinha == 0 || i == qtd - 1)
                fprintf(arq, "\n");  // Quebra de linha a cada 50 números ou no final
            else
                fprintf(arq, " ");   // Espaço entre números
        }

        gerados += qtd;

        // Mensagem de progresso a cada 100 milhões de números
        if (gerados % 100000000 == 0)
            printf("Gerados %lld números...\n", gerados);
    }

    // Fecha arquivo e libera memória
    fclose(arq);
    free(bloco);

    printf("Arquivo de números gerado com sucesso: dados/dados.txt\n");
    printf("Total de números: %lld\n", totalNumeros);

    return 0;
}
