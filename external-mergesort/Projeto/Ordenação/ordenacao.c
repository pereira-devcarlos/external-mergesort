#include "ordenacao.h"

// ====================
// Função de partição do QuickSort
// ====================
int particiona(int *vetor, int inicio, int fim) {
    int pivo = vetor[fim];    // escolhe último elemento como pivô
    int i = inicio - 1;       // índice do menor elemento

    for (int j = inicio; j < fim; j++) {
        if (vetor[j] <= pivo) {
            i++;
            // troca vetor[i] e vetor[j]
            int temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
        }
    }

    // coloca o pivô na posição correta
    int temp = vetor[i + 1];
    vetor[i + 1] = vetor[fim];
    vetor[fim] = temp;

    return i + 1;
}

// ====================
// QuickSort recursivo
// ====================
void quicksort(int *vetor, int inicio, int fim) {
    if (inicio < fim) {
        int p = particiona(vetor, inicio, fim);
        quicksort(vetor, inicio, p - 1);
        quicksort(vetor, p + 1, fim);
    }
}

// ====================
// Função pública chamada pelo ordenacaoArquivo.c
// ====================
void ordenacao(int *vetor, int n) {
    quicksort(vetor, 0, n - 1);
}
