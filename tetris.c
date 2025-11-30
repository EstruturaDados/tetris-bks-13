#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAP_QUEUE 5  // Capacidade da fila 
#define CAP_STACK 3  // Capacidade da pilha de reserva

// Estrutura que representa uma peça
typedef struct {
    char tipo; // Tipo das peças
    int id;    // Identificador da peça ID
} Peca;

//Variáveis da fila 
Peca fila[CAP_QUEUE];
int head = 0;   
int tail = 0;   // Índice da próxima posição livre que pode ser inserido
int qtd = 0;    // Quantidade de peças na fila

//Variáveis da pilha 
Peca pilha[CAP_STACK];
int top = 0;    // Quantidade de elementos na pilha

// Proximo id global das peças
int proximoId = 0;

// Gera aleatorio o proximo tipo de peça
char gerarTipo() {
    int r = rand() % 4;
    if (r == 0) return 'I';
    if (r == 1) return 'O';
    if (r == 2) return 'T';
    return 'L';
}

// Gera a nova pela com um id 
Peca gerarPeca() {
    Peca p;
    p.tipo = gerarTipo();
    p.id = proximoId++;
    return p;
}

// Valida se a fila está cheia
int filaCheia() {
    return qtd == CAP_QUEUE;
}

// Valida se a fila está vazia
int filaVazia() {
    return qtd == 0;
}

// Insere a peça no final da fila 
int enqueue(Peca p) {
    if (filaCheia()) return 0;
    fila[tail] = p;
    tail = (tail + 1) % CAP_QUEUE;
    qtd++;
    return 1;
}

// Remove a peça da frente da fila 
int dequeue(Peca *p) {
    if (filaVazia()) return 0;
    *p = fila[head];
    head = (head + 1) % CAP_QUEUE;
    qtd--;
    return 1;
}

// Adiciona uma peça na pilha
int push(Peca p) {
    if (top == CAP_STACK) return 0;
    pilha[top++] = p;
    return 1;
}

// Remove a peça do topo da pilha 
int pop(Peca *p) {
    if (top == 0) return 0;
    top--;
    *p = pilha[top];
    return 1;
}

// Mostra a fila de peças, o estado dela
void mostrarFila() {
    printf("\nFila de peças (%d/%d): ", qtd, CAP_QUEUE);
    if (filaVazia()) {
        printf("[vazia]\n");
        return;
    }
    int i = head;
    for (int k = 0; k < qtd; k++) {
        printf("[%c %d] ", fila[i].tipo, fila[i].id);
        i = (i + 1) % CAP_QUEUE;
    }
    printf("\n");
}

// Mostra a pilha de reserva o estado dela
void mostrarPilha() {
    printf("Pilha de reserva (Topo -> Base): ");
    if (top == 0) {
        printf("[vazia]\n");
        return;
    }
    for (int i = top - 1; i >= 0; i--) {
        printf("[%c %d] ", pilha[i].tipo, pilha[i].id);
    }
    printf("\n");
}

// Mostrado o estado da pilha e da fila juntos
void mostrarEstado() {
    mostrarFila();
    mostrarPilha();
}

// Funçao que preenche a fila ate ela ficar cheia
void preencherFilaAteCheia() {
    while (!filaCheia()) {
        enqueue(gerarPeca());
    }
}

// Inicia fila e pilha
void inicializar() {
    head = tail = qtd = 0;
    top = 0;
    proximoId = 0;
    preencherFilaAteCheia();
}

//Menu principal
int main(void) {
    srand((unsigned)time(NULL));
    inicializar();

    int opc;
    do {
        printf("\n================ Tetris Stack ================\n");
        mostrarEstado();
        printf("\nOpções:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &opc) != 1) {
            while (getchar() != '\n'); 
            printf("Entrada inválida. Tente novamente.\n");
            continue;
        }
        while (getchar() != '\n'); 

        if (opc == 1) { // Joga a peça
            Peca jogada;
            if (dequeue(&jogada)) {
                printf("\nVocê jogou a peça: [%c %d]\n", jogada.tipo, jogada.id);
            } else {
                printf("\nFila vazia - nada para jogar.\n");
            }
            preencherFilaAteCheia(); // Mantém fila sempre cheia
        }
        else if (opc == 2) { // Reservar peça
            if (top == CAP_STACK) {
                printf("\nPilha cheia - não é possível reservar mais peças.\n");
            } else {
                Peca mov;
                if (dequeue(&mov)) {
                    push(mov);
                    printf("\nPeça reservada: [%c %d]\n", mov.tipo, mov.id);
                } else {
                    printf("\nFila vazia - nada para reservar.\n");
                }
            }
            preencherFilaAteCheia();
        }
        else if (opc == 3) { // Usar peça reservada
            Peca usada;
            if (pop(&usada)) {
                printf("\nVocê usou a peça reservada: [%c %d]\n", usada.tipo, usada.id);
            } else {
                printf("\nPilha vazia - nenhuma peça para usar.\n");
            }
            preencherFilaAteCheia();
        }
        else if (opc == 0) {
            printf("\nSaindo...\n");
        }
        else {
            printf("\nOpção inválida.\n");
        }

    } while (opc != 0);

    return 0;
}
