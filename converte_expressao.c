#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX 100


typedef struct pilhaa *pilha;

typedef struct elem {
    int c;
    struct elem* prox;
} elemento;

struct pilhaa {
    elemento* topo;
};

pilha cria_pilha() {
    pilha P = malloc(sizeof(struct pilhaa));
    P->topo = NULL;
    return P;
}

void empilhar(pilha P, char c) {
    elemento* e = (elemento*) malloc(sizeof(elemento));
    e->c = c;
    e->prox = P->topo;
    P->topo = e;
}

char desempilhar(pilha P) {
    if (P->topo == NULL) {
        printf("Erro: tentativa de desempilhar pilha vazia!\n");
        exit(1);
    }
    elemento* aux = P->topo;
    int caux = aux->c;
    P->topo = aux->prox;
    free(aux);
    return caux;
}

void liberar_elementos(elemento* e) {
    if (e == NULL) return;
    liberar_elementos(e->prox);
    free(e);
}

void liberar_pilha(pilha P) {
    liberar_elementos(P->topo);
    free(P);
}

int pilha_vazia(pilha P) {
    return (P->topo == NULL);
}



char* converte(char *str, int tam)
{
    int i,k=0;
    char aux;
    char* resp = malloc(sizeof(char)*(tam+1));
    pilha pilha_aux = cria_pilha();


    for(i=0;i<tam;i++)
    {
        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9'))
        {
            resp[k++] = str[i];
        }

        //Aqui se for um parenteses normal ele vai só colocar na pilha aux, pq é o primeiro no caso
        if(str[i] == '(')
        {
            empilhar(pilha_aux,str[i]);
        }

        //Aqui a gente verifica se é um ), se for, ele vai pegar todos os items da pilha aux e vai colocar na pilha resp até achar um (, pq ai começa outra "sessão de contas"
        //No final ele tira o ) pq ele já foi usado pra parentesar os termos, mas se caso ele for um '(', a expressão estará mal formulada e ele terminará o programa!
        if(str[i] == ')')
        {
            while(!pilha_vazia(pilha_aux) && pilha_aux->topo->c != '(')
            {
                aux = desempilhar(pilha_aux);
                resp[k++] = aux;
            }

            if(!pilha_vazia(pilha_aux) && pilha_aux->topo->c == '(')
            {
                desempilhar(pilha_aux);
            }else{
                printf("A expressão esta mal formulada");
                exit(1);
            }
        }

        //Aqui a gente verifica se é algum operador lógico do tipo + ou -, se for, a gente vai fazer a mesma coisa que quando é um ), mas vamos até a pilha esvaziar, pois são operadores de menor procedência
        if(str[i] == '+' || str[i] == '-')
        {
            while(!pilha_vazia(pilha_aux) && pilha_aux->topo->c != '(')
            {
                //aqui ele vai pegar os operadores que são de maior procedência como * e /, e mandar para já para a resposta, e isso garante que nenhum + ou - que são de menor procedencia fique na frente dos que tem maior procedência como * ou ^
                aux = desempilhar(pilha_aux);
                resp[k++] = aux;
            }
            //esse empilhar serve para colocar os operadores de volta na pilha aux para ele 
            empilhar(pilha_aux,str[i]);   
        }


        //Aqui a gente faz a mesma coisa de antes, coloca tudo da pilha_aux na pilha_resp até esvaziar, porque aí não tem mais nada a inserir na resposta, até achar um '(', porque aí vai ser outro bloco de conta, ou até achar um valor de menor precedência, no caso + ou -
        
        if(str[i] == '*' || str[i] == '/')
        {
            while(!pilha_vazia(pilha_aux) && pilha_aux->topo->c != '(' && (pilha_aux->topo->c == '*' || pilha_aux->topo->c == '/' || pilha_aux->topo->c == '^'))
            {
                aux = desempilhar(pilha_aux);
                resp[k++] = aux;
            }
             empilhar(pilha_aux,str[i]);
        }

        if(str[i] == '^')
        {
            empilhar(pilha_aux,str[i]);
        }
    
        
    }

    while (!pilha_vazia(pilha_aux))
    {
        aux = desempilhar(pilha_aux);
        if (aux == '(' || aux == ')') 
        {
            printf("Erro: expressao mal formulada (parenteses nao balanceados)\n");
            exit(1);
        }
        resp[k++] = aux;

    }

    resp[k] = '\0'; 
    return resp;
}

int main(int argc, char* argv[])
{
    char str[MAX];
    int tam;

    scanf(" %[^\n]",str);
    tam = strlen(str);
    
    char* posfixa = converte(str,tam);

    printf("%s\n",posfixa);

    free(posfixa);
    return 0;
}







