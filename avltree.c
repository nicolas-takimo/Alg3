#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int valor;
    struct nodo *esq;
    struct nodo *dir;
    struct nodo *pai;
    int h;
} Nodo;

// Função para criar um novo nodo com o valor v
Nodo* criarNodo(int v) {
    Nodo *p = (Nodo*)malloc(sizeof(Nodo));
    p->valor = v;
    p->esq = NULL;
    p->dir = NULL;
    p->pai = NULL;
    p->h = 0;
    return p;
}

// Função de balanceamento: retorna o fator de balanceamento de um nó
int fb(Nodo *p) {
    int temp = 0;
    if (!p){
        return 0;
    }
    if (p) {
        if (!p->esq && p->dir) {
            p->h = p->dir->h + 1;
            return (temp - p->dir->h);
        } else if (p->esq && !p->dir) {
            p->h = p->esq->h + 1;
            return p->esq->h;
        } else if (!p->esq && !p->dir) {
            p->h = 1;
            return temp;
        } else if (p->esq->h >= p->dir->h) {
            p->h = p->esq->h + 1;
            return p->esq->h - p->dir->h;
        } else {
            p->h = p->dir->h + 1;
            return p->esq->h - p->dir->h;
        }
    }
}

// Rotação à direita de um nó (para balanceamento)
Nodo* rotDir(Nodo *raiz) {
    Nodo *p, *tempo;
    p = raiz->esq;
    tempo = p->dir;
    p->dir = raiz;
    raiz->esq = tempo;
    int f = fb(p->dir);
    f = fb(p);
    return p;
}

// Rotação à esquerda de um nó (para balanceamento)
Nodo* rotEsq(Nodo *raiz) {
    Nodo *p, *tempo;
    p = raiz->dir;
    tempo = p->esq;
    p->esq = raiz;
    raiz->dir = tempo;
    int f = fb(p->esq);
    f = fb(p);
    return p;
}

// Rotação à esquerda seguida de rotação à direita (para balanceamento)
Nodo* rotEsqDir(Nodo *raiz) {
    raiz->esq = rotEsq(raiz->esq);
    return rotDir(raiz);
}

// Rotação à direita seguida de rotação à esquerda (para balanceamento)
Nodo* rotDirEsq(Nodo *raiz) {
    raiz->dir = rotDir(raiz->dir);
    return rotEsq(raiz);
}

// Função de balanceamento para manter a árvore AVL balanceada após inserções e exclusões
Nodo* balancear(Nodo *raiz) {
    int fator_balanceamento;
    if (raiz) {
        fator_balanceamento = fb(raiz);
        if (fator_balanceamento > 1 && fb(raiz->esq) < 0) {
            raiz = rotEsqDir(raiz);
        } else if (fator_balanceamento > 1) {
            raiz = rotDir(raiz);
        } else if (fator_balanceamento < -1 && fb(raiz->dir) > 0) {
            raiz = rotDirEsq(raiz);
        } else if (fator_balanceamento < -1) {
            raiz = rotEsq(raiz);
        }
        fator_balanceamento = fb(raiz);
        return raiz;
    } else {
        return NULL;
    }
}

// Função recursiva para mostrar a árvore de forma indentada
void mostraArvore(Nodo *p, int nivel) {
    int i;
    if (p) {
        mostraArvore(p->dir, nivel + 1);
        printf("\n");
        for (i = 0; i < nivel; i++)
            printf("\t");
        printf("%i [%i|%i]\n", p->valor, p->h, fb(p));
        mostraArvore(p->esq, nivel + 1);
    }
}

// Inserir um novo nodo na árvore AVL
Nodo* inserirNodo(Nodo *raiz, int v) {
    if (!raiz) {
        raiz = criarNodo(v);
    } else {
        if (v <= raiz->valor) {
            raiz->esq = inserirNodo(raiz->esq, v);
            raiz->esq->pai = raiz;
        } else {
            raiz->dir = inserirNodo(raiz->dir, v);
            raiz->dir->pai = raiz;
        }
    }
    raiz = balancear(raiz);
    return raiz;
}

// Buscar um valor na árvore AVL
Nodo* buscar(Nodo *raiz, int v) {
    if (raiz) {
        if (v == raiz->valor) {
            return raiz;
        } else if (v < raiz->valor) {
            return buscar(raiz->esq, v);
        } else {
            return buscar(raiz->dir, v);
        }
    } else {
        return NULL;
    }
}

// Função auxiliar para encontrar o maior valor da subárvore esquerda (necessário para exclusão)
Nodo* maiorValorDaSubArvoreEsquerda(Nodo *n) {
    while (n && n->dir != NULL)
        n = n->dir;
    return n;
}

// Função para excluir um nodo da árvore AVL
Nodo* excluirNodo(Nodo *raiz, int v) {
    if (raiz == NULL)
        return raiz;
    if (v < raiz->valor)
        raiz->esq = excluirNodo(raiz->esq, v);
    else if (v > raiz->valor)
        raiz->dir = excluirNodo(raiz->dir, v);
    else {
        if (raiz->esq == NULL) {
            Nodo *aux = raiz->dir;
            free(raiz);
            return aux;
        } else if (raiz->dir == NULL) {
            Nodo *aux = raiz->esq;
            free(raiz);
            return aux;
        }
        Nodo *aux = maiorValorDaSubArvoreEsquerda(raiz->esq);
        raiz->valor = aux->valor;
        raiz->esq = excluirNodo(raiz->esq, aux->valor);
    }

    raiz = balancear(raiz);
    return raiz;
}

// Função para excluir um valor da árvore AVL
Nodo* excluir(Nodo *raiz, int v) {
    raiz = excluirNodo(raiz, v);
    return raiz;
}

// Função principal
int main() {
    Nodo *raiz = NULL, *aux = NULL;
    int op, v;

    do {
        mostraArvore(raiz, 0);
        printf("\n--------------------------------------------------\n");
        printf("1 - inserir novo nodo\n");
        printf("2 - excluir nodo\n");
        printf("3 - buscar nodo\n");
        printf("0 - sair\n");
        printf("opcao: ");
        scanf("%d", &op);

        switch (op) {
        case 1:
            printf("Informe o valor (int): ");
            scanf("%d", &v);
            raiz = inserirNodo(raiz, v);
            break;
        case 2:
            printf("Informe o valor (int): ");
            scanf("%d", &v);
            raiz = excluir(raiz, v);
            break;
        case 3:
            printf("Informe o valor (int): ");
            scanf("%d", &v);
            if (aux = buscar(raiz, v))
                printf("valor encontrado\n");
            else
                printf("valor nao pertence a arvore\n");
            break;
        case 0:
            printf("saindo...\n");
            break;
        default:
            printf("opcao invalida\n");
        }
        printf("\n\n\n");
    } while (op != 0);

    return 0;
}
