#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAP 5  // Maximo de peças na fila

// Estrutura que representa uma peça
typedef struct {
    char tipo; // 'I','O','T','L'
    int id;    // Identificador único da peça
} Peca;

// Variáveis da fila circular
Peca fila[CAP];
int head = 0;     
int tail = 0;     // Indice da proxima posição que esta livre para poder inserir
int qtd = 0;      // Quantidade de peças na fila
int proximoId = 0; //O proximo id que vai ser gerado para uma peça

// Função para gerar um tipo aleatorio de peça
char gerarTipo() {
    int r = rand() % 4;
    if (r == 0) return 'I';
    if (r == 1) return 'O';
    if (r == 2) return 'T';
    return 'L';
}

// Valida se a fila está cheia
int filaCheia() {
    return qtd == CAP;
}

// Valida se a fila está vazia
int filaVazia() {
    return qtd == 0;
}

// Adiciona uma peça ao final da fila, faz validação se a operação deu certo ou retorna 0 se a fila estiver cheia
int enqueue(Peca p) {
    if (filaCheia()) return 0;
    fila[tail] = p;
    tail = (tail + 1) % CAP; // Atualiza o indicie de forma circular
    qtd++;
    return 1;
}

// Remove a peça da frente da fila 
int dequeue(Peca *p) {
    if (filaVazia()) return 0;
    *p = fila[head];
    head = (head + 1) % CAP;
    qtd--;
    return 1;
}

// Exibe as peças da fila na ordem do primeiro ate o ultimo
void mostrarFila() {
    printf("\nFila de Pecas: (%d/%d): ", qtd, CAP);
    if (filaVazia()) {
        printf("[vazia]\n");
        return;
    }
    int i = head;
    for (int k = 0; k < qtd; k++) {
        printf("[%c %d] ", fila[i].tipo, fila[i].id);
        i = (i + 1) % CAP;
    }
    printf("\n");
}

int main(void) {
    srand((unsigned)time(NULL));

    // Inicializa a fila com as peças automatica
    for (int i = 0; i < CAP; i++) {
        Peca p = { gerarTipo(), proximoId++ };
        enqueue(p);
    }

    int op;
    do {
        printf("\n============ Tetris Stack ============\n");
        mostrarFila();
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &op) != 1) { 
            while (getchar()!='\n'); // Limpa buffer
            op = -1; 
        }

        if (op == 1) {
            Peca r;
            if (dequeue(&r)) 
                printf("Você jogou: [%c %d]\n", r.tipo, r.id);
            else 
                printf("Fila vazia.\n");
        } 
        else if (op == 2) {
            Peca p = { gerarTipo(), proximoId++ };
            if (enqueue(p)) 
                printf("Inserida: [%c %d]\n", p.tipo, p.id);
            else 
                printf("Fila cheia.\n");
        } 
        else if (op == 0) {
            printf("Saindo...\n");
        } 
        else {
            printf("Opção inválida.\n");
        }

        while (getchar() != '\n'); 
    } while (op != 0);

    return 0;
}
