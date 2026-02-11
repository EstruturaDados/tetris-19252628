#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_FILA 5 // Tamanho fixo conforme requisitos

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome;  // Tipo: 'I', 'O', 'T', 'L'
    int id;     // Identificador único
} Peca;

// Estrutura da Fila Circular para reaproveitamento de espaço
typedef struct {
    Peca pecas[MAX_FILA];
    int frente;
    int tras;
    int tamanho;
} FilaPecas;

// Contador global para IDs exclusivos
int contadorId = 0;

// Gera peças automaticamente com tipos específicos
Peca gerarPeca() {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = contadorId++;
    return nova;
}

// Inicializa a fila zerada
void inicializarFila(FilaPecas *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

// Insere nova peça ao final da fila (Enqueue)
void enqueue(FilaPecas *f) {
    if (f->tamanho < MAX_FILA) {
        Peca p = gerarPeca();
        f->tras = (f->tras + 1) % MAX_FILA; // Lógica circular
        f->pecas[f->tras] = p;
        f->tamanho++;
        printf("\n[+] Peça [%c %d] entrou na fila.\n", p.nome, p.id);
    } else {
        printf("\n[!] Fila cheia! Não há espaço para novas peças.\n");
    }
}

// Remove a peça da frente para "jogar" (Dequeue)
void dequeue(FilaPecas *f) {
    if (f->tamanho > 0) {
        Peca p = f->pecas[f->frente];
        f->frente = (f->frente + 1) % MAX_FILA; // Lógica circular
        f->tamanho--;
        printf("\n[-] Peça [%c %d] foi jogada!\n", p.nome, p.id);
    } else {
        printf("\n[!] Fila vazia! Nenhuma peça para jogar.\n");
    }
}

// Exibe o estado atual da fila formatado
void exibirFila(FilaPecas *f) {
    printf("\nFila de pecas: ");
    int idx = f->frente;
    for (int i = 0; i < f->tamanho; i++) {
        printf("[%c %d] ", f->pecas[idx].nome, f->pecas[idx].id);
        idx = (idx + 1) % MAX_FILA;
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    FilaPecas fila;
    int opcao;

    inicializarFila(&fila);

    // Inicializa a fila com 5 elementos conforme instrução
    for (int i = 0; i < MAX_FILA; i++) {
        Peca p = gerarPeca();
        fila.tras = (fila.tras + 1) % MAX_FILA;
        fila.pecas[fila.tras] = p;
        fila.tamanho++;
    }

    do {
        exibirFila(&fila);
        printf("\n1 - Jogar peca (dequeue)\n2 - Inserir nova peca (enqueue)\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: dequeue(&fila); break;
            case 2: enqueue(&fila); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}


