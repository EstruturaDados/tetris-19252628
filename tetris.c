#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

// Estrutura da peça
typedef struct {
    char nome;
    int id;
} Peca;

// Estrutura da Fila Circular
typedef struct {
    Peca pecas[MAX_FILA];
    int frente, tras, tamanho;
} FilaPecas;

// Estrutura da Pilha de Reserva
typedef struct {
    Peca pecas[MAX_PILHA];
    int topo;
} PilhaReserva;

int contadorId = 0;

// Função para gerar peças automaticamente
Peca gerarPeca() {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = contadorId++;
    return nova;
}

// Inicializa as estruturas
void inicializar(FilaPecas *f, PilhaReserva *p) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
    p->topo = -1; // Pilha vazia começa em -1

    // Preenche a fila inicial com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        Peca nova = gerarPeca();
        f->tras = (f->tras + 1) % MAX_FILA;
        f->pecas[f->tras] = nova;
        f->tamanho++;
    }
}

// Mostra o estado da Fila e da Pilha
void exibirEstado(FilaPecas *f, PilhaReserva *p) {
    printf("\n--- ESTADO ATUAL ---");
    printf("\nFila de pecas: ");
    int idx = f->frente;
    for (int i = 0; i < f->tamanho; i++) {
        printf("[%c %d] ", f->pecas[idx].nome, f->pecas[idx].id);
        idx = (idx + 1) % MAX_FILA;
    }

    printf("\nPilha de Reserva (Topo -> Base): ");
    if (p->topo == -1) printf("[Vazia]");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->pecas[i].nome, p->pecas[i].id);
    }
    printf("\n--------------------\n");
}

// Ação 1: Jogar peca (Tira da fila e repõe no final)
void jogarPeca(FilaPecas *f) {
    Peca removida = f->pecas[f->frente];
    f->frente = (f->frente + 1) % MAX_FILA;
    f->tamanho--;
    printf("\n[-] Voce jogou a peca [%c %d]!", removida.nome, removida.id);

    // Repõe automaticamente para manter a fila cheia
    Peca nova = gerarPeca();
    f->tras = (f->tras + 1) % MAX_FILA;
    f->pecas[f->tras] = nova;
    f->tamanho++;
}

// Ação 2: Reservar peca (Fila -> Pilha)
void reservarPeca(FilaPecas *f, PilhaReserva *p) {
    if (p->topo < MAX_PILHA - 1) {
        // Tira da frente da fila
        Peca reserva = f->pecas[f->frente];
        f->frente = (f->frente + 1) % MAX_FILA;
        f->tamanho--;

        // Coloca no topo da pilha
        p->topo++;
        p->pecas[p->topo] = reserva;
        printf("\n[+] Peca [%c %d] movida para a reserva.", reserva.nome, reserva.id);

        // Repõe a fila
        Peca nova = gerarPeca();
        f->tras = (f->tras + 1) % MAX_FILA;
        f->pecas[f->tras] = nova;
        f->tamanho++;
    } else {
        printf("\n[!] Pilha de reserva cheia!");
    }
}

// Ação 3: Usar reserva (Tira do topo da pilha)
void usarReserva(PilhaReserva *p) {
    if (p->topo >= 0) {
        Peca removida = p->pecas[p->topo];
        p->topo--;
        printf("\n[*] Voce usou a peca reservada [%c %d]!", removida.nome, removida.id);
    } else {
        printf("\n[!] Nao ha pecas na reserva!");
    }
}

int main() {
    srand(time(NULL));
    FilaPecas fila;
    PilhaReserva pilha;
    int opcao;

    inicializar(&fila, &pilha);

    do {
        exibirEstado(&fila, &pilha);
        printf("\n1-Jogar peca\n2-Reservar peca\n3-Usar peca reservada\n0-Sair\nEscolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: jogarPeca(&fila); break;
            case 2: reservarPeca(&fila, &pilha); break;
            case 3: usarReserva(&pilha); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}



