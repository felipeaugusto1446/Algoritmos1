#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arvore {
    char valor;              
    struct arvore *esq;
    struct arvore *dir;
} arvore;

arvore* criaNo(char valor) {
    arvore *no = malloc(sizeof(arvore));
    no->valor = valor;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

void preOrdem(arvore *raiz) {
    if (raiz == NULL) return;
    printf("%c", raiz->valor);
    preOrdem(raiz->esq);
    preOrdem(raiz->dir);
}

void libera(arvore *raiz) {
    if (raiz == NULL) return;
    libera(raiz->esq);
    libera(raiz->dir);
    free(raiz);
}

void converte(char *str) {
    int tam = strlen(str);
    printf("%d\n", tam);

    char grupos[256];
    int n = 0;
    grupos[n++] = str[0];
    for (int i = 1; i < tam; i++) {
        if (str[i] != str[i - 1]) {
            grupos[n++] = str[i];
        }
    }

    arvore *folhas[256];
    for (int i = 0; i < n; i++) {
        folhas[i] = criaNo(grupos[i]);
    }

    int m = n;
    while (m > 1) {
        int k = 0;
        for (int i = 0; i < m; i += 2) {
            if (i + 1 < m) {
                arvore *pai = criaNo('*');
                pai->esq = folhas[i];
                pai->dir = folhas[i + 1];
                folhas[k++] = pai;
            } else {
                folhas[k++] = folhas[i];
            }
        }
        m = k;
    }

    preOrdem(folhas[0]);
    printf("\n");

    libera(folhas[0]);
}

int main(void) {
    char *str = NULL;
    scanf("%ms", &str);
    converte(str);
    free(str);
    return 0;
}
