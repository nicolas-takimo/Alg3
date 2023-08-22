#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int valor;
    struct nodo *esq;
    struct nodo *dir;
} Nodo;

Nodo* criarNodo(int v){
    Nodo *p = (Nodo*)malloc(sizeof(Nodo));
    p->valor = v;
    p->esq = NULL;
    p->dir = NULL;
    return p;
}

Nodo* inserirNodo(Nodo *p, int v){
    Nodo *novo = criarNodo(v);
    if(!p)
        return novo;
    else{
        if(v <= p->valor)
            p->esq = inserirNodo(p->esq,v);
        else
            p->dir = inserirNodo(p->dir,v);
        return p;
    }
}

void mostrar(Nodo *p, int nivel){
    int n = nivel;
    if(!p){
        while(n>0){
            printf("   ");
            n--;
        }
        printf("#\n");
    }else{
        while(n>0){
            printf("   ");
            n--;
        }
        printf("%i\n",p->valor);
        nivel++;
        mostrar(p->esq,nivel);
        mostrar(p->dir,nivel);
    }
}
void buscarNodo (Nodo *p, int v){
    if(!p){
      printf("valor nao pertence a arvore \n");
    }else if (v == p->valor){
        printf("valor encontrado\n");
    }else if(v < p->valor){
        buscarNodo(p->esq,v);
    }else if(v > p->valor)
        buscarNodo(p->dir,v);
}
Nodo* maiorValorDaSubArvoreEsquerda(Nodo *n) {
    while (n && n->dir != NULL)
        n = n->dir;
    return n;
}

Nodo* excluirNodo(Nodo *raiz, int v){
    if(raiz == NULL)
        return raiz;
    if(v < raiz->valor)
        raiz->esq = excluirNodo(raiz->esq, v);
    else if(v > raiz->valor)
        raiz->dir = excluirNodo(raiz->dir, v);
    else {
        if(raiz->esq == NULL){
            Nodo *aux = raiz->dir;
            free(raiz);
            return aux;
        }
        else if(raiz->dir == NULL){
            Nodo *aux = raiz->esq;
            free(raiz);
            return aux;
        }
        Nodo *aux = maiorValorDaSubArvoreEsquerda(raiz->esq);
        raiz->valor = aux->valor;
        raiz->esq = excluirNodo(raiz->esq, aux->valor);
    }
    return raiz;
}

int main(){
    Nodo *raiz = NULL;
    int v, op;
    op = 1;
    while(op!=0){
        mostrar(raiz, 0);
        printf("Opcoes:\n");
        printf("1 - inserir nodo\n");
        printf("2 - excluir nodo\n");
        printf("3 - buscar\n");
        printf("0 - sair\n");
        printf("op: ");
        scanf("%i", &op);

        switch(op){
        case 1:
            printf("Informe o valor (int): ");
            scanf("%i", &v);
            raiz = inserirNodo(raiz, v);
            break;
        case 2:
              printf("Informe o valor (int): ");
            scanf("%i", &v);
            raiz = excluirNodo(raiz, v);
            break;
        case 3:
            printf("Informe o valor (int): ");
            scanf("%i", &v);
            buscarNodo(raiz,v);
            break;
        case 0:
            printf("saindo...\n");
            break;
        default:
            printf("opcao invalida\n");
        }
        printf("\n\n\n\n\n");
    }
    return 0;
}
