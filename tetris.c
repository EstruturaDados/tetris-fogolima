#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5  // Tamanho máximo da fila

// ----------------------------
// Estrutura que representa uma peça do Tetris
// ----------------------------
typedef struct {
    char nome;  // Tipo da peça (I, O, T, L, etc.)
    int id;     // Identificador único da peça
} Peca;

// ----------------------------
// Estrutura que representa a Fila de Peças (fila circular)
// ----------------------------
typedef struct {
    Peca pecas[TAM_FILA];
    int frente;   // Índice da primeira peça
    int tras;     // Índice da última peça
    int qtd;      // Quantidade atual de peças na fila
} Fila;

// ----------------------------
// Protótipos das funções
// ----------------------------
void inicializarFila(Fila *f);
int filaVazia(Fila *f);
int filaCheia(Fila *f);
void enfileirar(Fila *f, Peca nova);
Peca desenfileirar(Fila *f);
void exibirFila(Fila *f);
Peca gerarPeca(int id);

// ----------------------------
// Função principal
// ----------------------------
int main() {
    Fila fila;
    inicializarFila(&fila);

    int idGlobal = 0; // Controla IDs únicos para as peças
    int opcao;
    srand(time(NULL)); // Semente para gerar peças aleatórias

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        Peca nova = gerarPeca(idGlobal++);
        enfileirar(&fila, nova);
    }

    do {
        printf("\n==============================\n");
        printf("      FILA DE PEÇAS FUTURAS\n");
        printf("==============================\n");
        exibirFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (filaVazia(&fila)) {
                    printf("\n⚠️  Fila vazia! Nenhuma peça para jogar.\n");
                } else {
                    Peca jogada = desenfileirar(&fila);
                    printf("\n🧩 Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
                }
                break;

            case 2:
                if (filaCheia(&fila)) {
                    printf("\n⚠️  Fila cheia! Não é possível adicionar mais peças.\n");
                } else {
                    Peca nova = gerarPeca(idGlobal++);
                    enfileirar(&fila, nova);
                    printf("\n✅ Nova peça [%c %d] adicionada à fila!\n", nova.nome, nova.id);
                }
                break;

            case 0:
                printf("\nSaindo do jogo... 👋\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

// ----------------------------
// Função: inicializarFila
// Define a fila vazia
// ----------------------------
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->qtd = 0;
}

// ----------------------------
// Função: filaVazia
// Retorna 1 se estiver vazia, 0 caso contrário
// ----------------------------
int filaVazia(Fila *f) {
    return (f->qtd == 0);
}

// ----------------------------
// Função: filaCheia
// Retorna 1 se estiver cheia, 0 caso contrário
// ----------------------------
int filaCheia(Fila *f) {
    return (f->qtd == TAM_FILA);
}

// ----------------------------
// Função: enfileirar (enqueue)
// Adiciona nova peça ao final da fila circular
// ----------------------------
void enfileirar(Fila *f, Peca nova) {
    if (filaCheia(f)) {
        printf("Erro: fila cheia!\n");
        return;
    }
    f->tras = (f->tras + 1) % TAM_FILA;
    f->pecas[f->tras] = nova;
    f->qtd++;
}

// ----------------------------
// Função: desenfileirar (dequeue)
// Remove a peça da frente da fila e retorna
// ----------------------------
Peca desenfileirar(Fila *f) {
    Peca removida = {' ', -1};
    if (filaVazia(f)) {
        printf("Erro: fila vazia!\n");
        return removida;
    }
    removida = f->pecas[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->qtd--;
    return removida;
}

// ----------------------------
// Função: exibirFila
// Mostra todas as peças atuais da fila
// ----------------------------
void exibirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("\n[Fila vazia]\n");
        return;
    }

    printf("\nFila de peças:\n");
    for (int i = 0, j = f->frente; i < f->qtd; i++, j = (j + 1) % TAM_FILA) {
        printf("[%c %d] ", f->pecas[j].nome, f->pecas[j].id);
    }
    printf("\n");
}

// ----------------------------
// Função: gerarPeca
// Cria uma nova peça aleatória
// ----------------------------
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}
