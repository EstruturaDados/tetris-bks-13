#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAP_QUEUE 5   // Capacidade da fila 
#define CAP_STACK 3   // Capacidade da pilha de reserva

// Estrutura que representa uma peça
typedef struct {
    char tipo;   // Tipo das peças
    int id;     // Identificador da peça ID
} Peca;

//Variáveis da fila 
typedef struct {
    Peca itens[CAP_QUEUE];
    int inicio;  // Aponta para a primeira peça que sera removida
    int fim;     // Índice da próxima posição livre que pode ser inserido
    int qtd;     // Quantidade de peças na fila
} Fila;

// Inicializa a fila com peças aleatórias
void inicializarFila(Fila *f);

// Insere peça no fim da fila
int enqueue(Fila *f, Peca p);

// Remove peça da frente da fila
int dequeue(Fila *f, Peca *p);

//Variaveis da pilha
typedef struct {
    Peca itens[CAP_STACK]; //Array que ira armazenas as peças da pilha 
    int topo; //Indice do topo
} Pilha;

// Inicializa pilha vazia
void inicializarPilha(Pilha *p);

// Adiciona peça no topo da pilha
int push(Pilha *p, Peca x);

// Remove peça do topo da pilha
int pop(Pilha *p, Peca *x);


int proximoId = 0; // O id global das peças
char tipos[4] = {'I', 'O', 'T', 'L'}; // Quais sao os tipos das peças

// Gera um tipo aleatório
char gerarTipo() {
    int r = rand() % 4;
    return tipos[r];
}

// Gera uma nova peça com ID 
Peca gerarPeca() {
    Peca p;
    p.tipo = gerarTipo();
    p.id = proximoId++;
    return p;
}

// Preenche a fila até ficar cheia
void preencherFilaAteCheia(Fila *f) {
    while (f->qtd < CAP_QUEUE) {
        enqueue(f, gerarPeca());
    }
}

// Mostra estado atual da fila e pilha
void mostrarEstado(Fila *f, Pilha *p) {
    printf("\n===== ESTADO ATUAL =====\n");
    
    // Fila
    printf("Fila de peças: ");
    if (f->qtd == 0) {
        printf("[vazia]\n");
    } else {
        int idx = f->inicio;
        for (int i = 0; i < f->qtd; i++) {
            printf("[%c %d] ", f->itens[idx].tipo, f->itens[idx].id);
            idx = (idx + 1) % CAP_QUEUE;
        }
        printf("\n");
    }

    // Pilha
    printf("Pilha de reserva (Topo -> Base): ");
    if (p->topo == -1) {
        printf("[vazia]\n");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c %d] ", p->itens[i].tipo, p->itens[i].id);
        }
        printf("\n");
    }
    printf("=========================\n");
}

// Troca peça da frente da fila com topo da pilha
void trocarPecaAtual(Fila *f, Pilha *p) {
    if (f->qtd == 0 || p->topo == -1) {
        printf("\nNão é possível trocar: fila ou pilha vazia!\n");
        return;
    }
    Peca temp = f->itens[f->inicio];
    f->itens[f->inicio] = p->itens[p->topo];
    p->itens[p->topo] = temp;
    printf("\nTroca realizada entre frente da fila e topo da pilha!\n");
}

// Troca múltipla: 3 primeiros da fila com 3 da pilha
void trocaMultipla(Fila *f, Pilha *p) {
    // Verifica se há pelo menos 3 peças na fila e na pilha
    if (f->qtd < 3 || p->topo < 2) {
        printf("\nNão é possível realizar a troca múltipla: faltam peças.\n");
        return;
    }

    // Índice inicial da fila
    int idxFila = f->inicio;

    // Troca as 3 primeiras peças da fila com as 3 do topo da pilha
    for (int i = 0; i < 3; i++) {
        Peca temp = f->itens[idxFila];
        f->itens[idxFila] = p->itens[p->topo - i];
        p->itens[p->topo - i] = temp;
        idxFila = (idxFila + 1) % CAP_QUEUE;
    }

    printf("\nTroca realizada entre os 3 primeiros da fila e os 3 da pilha.\n");

    // Exibe novo estado 
    printf("\n=== Novo Estado ===\n\n");

    // Fila
    printf("Fila de Peças: ");
    idxFila = f->inicio;
    for (int i = 0; i < f->qtd; i++) {
        printf("[%c %d] ", f->itens[idxFila].tipo, f->itens[idxFila].id);
        idxFila = (idxFila + 1) % CAP_QUEUE;
    }
    printf("\n");

    // Pilha
    printf("Pilha de Reserva (Topo -> Base): ");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->itens[i].tipo, p->itens[i].id);
    }
    printf("\n");
}
//Funções da fila circular
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
    preencherFilaAteCheia(f);
}
// Adiciona peça no fim da fila circular 
int enqueue(Fila *f, Peca p) {
    if (f->qtd == CAP_QUEUE) return 0;
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % CAP_QUEUE;
    f->qtd++;
    return 1;
}
// Remove a peça da frente da fila circular
int dequeue(Fila *f, Peca *p) {
    if (f->qtd == 0) return 0;
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % CAP_QUEUE;
    f->qtd--;
    return 1;
}

// Funções da pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int push(Pilha *p, Peca x) {
    if (p->topo == CAP_STACK - 1) return 0;
    p->topo++;
    p->itens[p->topo] = x;
    return 1;
}

int pop(Pilha *p, Peca *x) {
    if (p->topo == -1) return 0;
    *x = p->itens[p->topo];
    p->topo--;
    return 1;
}

// Menu principal
int main(void) {
    srand((unsigned)time(NULL));

    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int opc;
    do {
        mostrarEstado(&fila, &pilha);

        printf("\nOpções:\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Enviar peça da fila para reserva (pilha)\n");
        printf("3 - Usar peça da reserva\n");
        printf("4 - Trocar peça da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 peças da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &opc) != 1) {
            while (getchar() != '\n'); 
            printf("Entrada inválida!\n");
            continue;
        }

        if (opc == 1) { // Jogar peça
            Peca jogada;
            if (dequeue(&fila, &jogada)) {
                printf("\nVocê jogou a peça: [%c %d]\n", jogada.tipo, jogada.id);
                preencherFilaAteCheia(&fila);
            } else {
                printf("\nFila vazia!\n");
            }
        }
        else if (opc == 2) { // Reservar peça
            if (fila.qtd == 0) {
                printf("\nFila vazia - nada para reservar.\n");
            } else if (pilha.topo == CAP_STACK - 1) {
                printf("\nPilha cheia - não é possível reservar mais peças.\n");
            } else {
                Peca mov;
                dequeue(&fila, &mov);
                push(&pilha, mov);
                printf("\nPeça reservada: [%c %d]\n", mov.tipo, mov.id);
                preencherFilaAteCheia(&fila);
            }
        }
        else if (opc == 3) { // Usar peça reservada
            Peca usada;
            if (pop(&pilha, &usada)) {
                printf("\nVocê usou a peça reservada: [%c %d]\n", usada.tipo, usada.id);
            } else {
                printf("\nPilha vazia!\n");
            }
        }
        else if (opc == 4) { // Trocar peça atual
            trocarPecaAtual(&fila, &pilha);
        }
        else if (opc == 5) { // Troca múltipla
            trocaMultipla(&fila, &pilha);
        }
        else if (opc == 0) {
            printf("\nSaindo...\n");
        }
        else {
            printf("\nOpção inválida!\n");
        }

    } while (opc != 0);

    return 0;
}
