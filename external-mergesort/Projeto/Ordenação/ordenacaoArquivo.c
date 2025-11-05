#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "ordenacao.h" 
/*
    Ordenação Externa em Arquivo Texto

    Autores: Guilherme Aredes, Carlos Eduardo, Marcos Felipe
*/

// ====================
// Função: dividirEmBlocosTxt
// Objetivo: dividir o arquivo original em blocos menores, ordenar cada bloco
// e salvar em arquivos temporários.
// ====================
int dividirEmBlocosTxt(const char* arquivoEntrada, int tam_bloco, int numerosPorLinha) {
    // Abre o arquivo original para leitura
    FILE* arquivo_in = fopen(arquivoEntrada, "r");
    if (arquivo_in == NULL) {
        printf("Erro ao abrir arquivo de entrada.\n");
        return 0;
    }

    // Aloca memória para um bloco de inteiros
    int* bloco_buf = (int*)malloc(tam_bloco * sizeof(int));
    if (bloco_buf == NULL) {
        printf("Erro de alocação de memória.\n");
        fclose(arquivo_in);
        return 0;
    }

    int valor;        // Para armazenar o número lido do arquivo
    int cont = 0;     // Contador de números no bloco atual
    int idx_bloco = 0; // Índice de blocos temporários gerados

    // ====================
    // Loop principal de leitura do arquivo
    // ====================
    while (fscanf(arquivo_in, "%d", &valor) == 1) {
        bloco_buf[cont++] = valor; // Adiciona valor ao bloco em memória

        // Se o bloco atingir o tamanho definido, processa ele
        if (cont == tam_bloco) {
            idx_bloco++;                 // Incrementa índice do bloco
            ordenacao(bloco_buf, cont);  // Ordena o bloco em memória

            char nomeBloco[50];
            sprintf(nomeBloco, "dados/bloco_%d.txt", idx_bloco);

            FILE* bloco_out = fopen(nomeBloco, "w");
            if (bloco_out == NULL) {
                printf("Erro ao criar %s\n", nomeBloco);
                free(bloco_buf);
                fclose(arquivo_in);
                return 0;
            }

            // ====================
            // Grava 50 números por linha, separados por espaço
            // ====================
            for (int i = 0; i < cont; i++) {
                fprintf(bloco_out, "%d", bloco_buf[i]);
                if ((i + 1) % numerosPorLinha == 0 || i == cont - 1)
                    fprintf(bloco_out, "\n"); // quebra de linha
                else
                    fprintf(bloco_out, " ");  // separa números na mesma linha
            }

            fclose(bloco_out);
            cont = 0; // reinicia contador para próximo bloco
        }
    }

    // ====================
    // Processa o último bloco (se não estiver completo)
    // ====================
    if (cont > 0) {
        idx_bloco++;
        ordenacao(bloco_buf, cont);

        char nomeBloco[50];
        sprintf(nomeBloco, "dados/bloco_%d.txt", idx_bloco);

        FILE* bloco_out = fopen(nomeBloco, "w");
        if (bloco_out == NULL) {
            printf("Erro ao criar %s\n", nomeBloco);
            free(bloco_buf);
            fclose(arquivo_in);
            return 0;
        }

        for (int i = 0; i < cont; i++) {
            fprintf(bloco_out, "%d", bloco_buf[i]);
            if ((i + 1) % numerosPorLinha == 0 || i == cont - 1)
                fprintf(bloco_out, "\n");
            else
                fprintf(bloco_out, " ");
        }

        fclose(bloco_out);
    }

    free(bloco_buf);  // libera memória
    fclose(arquivo_in);

    printf("Total de blocos criados: %d\n", idx_bloco);
    return idx_bloco; // retorna quantidade de blocos gerados
}

// ====================
// Função: intercalarBlocosTxt
// Objetivo: realizar merge (intercalação) dos blocos ordenados
// e gerar arquivo final ordenado.
// ====================
void intercalarBlocosTxt(int qtdBlocos, const char* arquivoSaida, int numerosPorLinha) {
    FILE** blocos = (FILE**)malloc(qtdBlocos * sizeof(FILE*)); // ponteiros para arquivos de blocos
    int* valores = (int*)malloc(qtdBlocos * sizeof(int));       // valor atual de cada bloco
    int* ativo = (int*)malloc(qtdBlocos * sizeof(int));         // indica se o bloco ainda possui números

    if (!blocos || !valores || !ativo) {
        printf("Erro de alocação de memória.\n");
        return;
    }

    // ====================
    // Abre todos os blocos e lê o primeiro número de cada
    // ====================
    for (int i = 0; i < qtdBlocos; i++) {
        char nomeBloco[50];
        sprintf(nomeBloco, "dados/bloco_%d.txt", i + 1);
        blocos[i] = fopen(nomeBloco, "r");

        if (blocos[i] && fscanf(blocos[i], "%d", &valores[i]) == 1)
            ativo[i] = 1; // bloco ativo
        else
            ativo[i] = 0; // bloco vazio
    }

    FILE* saida = fopen(arquivoSaida, "w");
    if (!saida) {
        printf("Erro ao criar arquivo de saída.\n");
        for (int i = 0; i < qtdBlocos; i++)
            if (blocos[i]) fclose(blocos[i]);
        free(blocos);
        free(valores);
        free(ativo);
        return;
    }

    int contLinha = 0; // contador para controlar quebra de linha a cada 50 números

    // ====================
    // Loop de intercalação (merge)
    // ====================
    while (1) {
        int menor_valor = INT_MAX;
        int idx_menor = -1;

        // Encontra o menor valor entre os blocos ativos
        for (int i = 0; i < qtdBlocos; i++) {
            if (ativo[i] && valores[i] < menor_valor) {
                menor_valor = valores[i];
                idx_menor = i;
            }
        }

        if (idx_menor == -1)
            break; // nenhum bloco ativo -> fim do merge

        // Grava o menor valor no arquivo final
        fprintf(saida, "%d", menor_valor);
        contLinha++;
        if (contLinha % numerosPorLinha == 0)
            fprintf(saida, "\n"); // quebra de linha
        else
            fprintf(saida, " ");  // separa números na mesma linha

        // Lê o próximo número do mesmo bloco
        if (fscanf(blocos[idx_menor], "%d", &valores[idx_menor]) != 1) {
            ativo[idx_menor] = 0;   // bloco terminou
            fclose(blocos[idx_menor]);
        }
    }

    fclose(saida); // fecha arquivo final
    printf("Arquivo final ordenado salvo em: %s\n", arquivoSaida);

    // ====================
    // Remove arquivos temporários
    // ====================
    for (int i = 0; i < qtdBlocos; i++) {
        char nomeBloco[50];
        sprintf(nomeBloco, "dados/bloco_%d.txt", i + 1);
        remove(nomeBloco);
    }

    free(blocos);
    free(valores);
    free(ativo);
}

// ====================
// Função principal
// ====================
int main() {
    const char* arquivoEntrada = "dados/dados.txt";           // Arquivo gerado pelo gerador.c
    const char* arquivoSaida = "dados/dados_ordenados.txt";   // Arquivo final ordenado
    int tamanhoBloco = 1000000;  // 1 milhão de números por bloco (~10 MB)
    int numerosPorLinha = 50;    // Para manter o mesmo formato do gerador

    printf("=== Ordenação Externa (Texto, 50 números por linha) ===\n");
    printf("Lendo arquivo: %s\n", arquivoEntrada);

    // ====================
    // Divide em blocos, ordena cada bloco e grava temporários
    // ====================
    int qtdBlocos = dividirEmBlocosTxt(arquivoEntrada, tamanhoBloco, numerosPorLinha);

    // ====================
    // Intercala blocos ordenados e gera arquivo final
    // ====================
    intercalarBlocosTxt(qtdBlocos, arquivoSaida, numerosPorLinha);

    printf("Processo concluído com sucesso!\n");
    return 0;
}
