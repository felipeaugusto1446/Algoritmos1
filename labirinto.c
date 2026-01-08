#include <stdio.h>
#include <stdlib.h>

#define MAX_CAP 1000000

typedef struct
{
    int x;
    int y;
} ponto;

typedef struct filaa
{
    int inicio;
    int final;
    ponto *valores;
} *fila;

fila criar_fila()
{
    fila F = (fila)malloc(sizeof(struct filaa));
    F->valores = (ponto *)malloc(sizeof(ponto) * MAX_CAP);
    F->inicio = 0;
    F->final = 0;
    return F;
}

void inserir_fila(fila F, ponto p)
{
    if ((F->final + 1) % MAX_CAP == F->inicio)
    {
        return;
    }
    F->valores[F->final] = p;
    F->final = (F->final + 1) % MAX_CAP;
}

ponto remover_fila(fila F)
{
    ponto p;
    p.x = -1;
    p.y = -1;

    if (F->inicio == F->final)
    {
        return p;
    }

    p = F->valores[F->inicio];
    F->inicio = (F->inicio + 1) % MAX_CAP;
    return p;
}

int fila_vazia(fila F)
{
    if (F->inicio == F->final)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void liberar_fila(fila F)
{
    free(F->valores);
    free(F);
}

void liberar_matriz_int(int **m, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(m[i]);
    }
    free(m);
}

void liberar_matriz_char(char **m, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(m[i]);
    }
    free(m);
}

void mapeia_labirinto(char **labirinto, int n)
{
    int **dist = (int **)malloc(sizeof(int *) * n);
    for (int y = 0; y < n; y++)
    {
        dist[y] = (int *)malloc(sizeof(int) * n);
    }

    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
        {
            dist[y][x] = -1;
        }
    }

    fila F = criar_fila();

    ponto inicio;
    inicio.x = 0;
    inicio.y = 0;
    dist[0][0] = 0;
    inserir_fila(F, inicio);

    while (!fila_vazia(F))
    {
        ponto p = remover_fila(F);
        int px = p.x;
        int py = p.y;
        int atual = dist[py][px];

        if (px - 1 >= 0)
        {
            if (labirinto[py][px - 1] == '0' && dist[py][px - 1] == -1)
            {
                dist[py][px - 1] = atual + 1;
                ponto aux = {px - 1, py};
                inserir_fila(F, aux);
            }
        }

        if (px + 1 < n)
        {
            if (labirinto[py][px + 1] == '0' && dist[py][px + 1] == -1)
            {
                dist[py][px + 1] = atual + 1;
                ponto aux = {px + 1, py};
                inserir_fila(F, aux);
            }
        }

        if (py - 1 >= 0)
        {
            if (labirinto[py - 1][px] == '0' && dist[py - 1][px] == -1)
            {
                dist[py - 1][px] = atual + 1;
                ponto aux = {px, py - 1};
                inserir_fila(F, aux);
            }
        }

        if (py + 1 < n)
        {
            if (labirinto[py + 1][px] == '0' && dist[py + 1][px] == -1)
            {
                dist[py + 1][px] = atual + 1;
                ponto aux = {px, py + 1};
                inserir_fila(F, aux);
            }
        }
    }

    liberar_fila(F);

    int sem_saida = n * n;
    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
        {
            if (labirinto[y][x] == 'X')
            {
                dist[y][x] = sem_saida;
            }
            else if (dist[y][x] == -1)
            {
                dist[y][x] = sem_saida;
            }
        }
    }

    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
        {
            printf("%d ", dist[y][x]);
        }
        printf("\n");
    }

    liberar_matriz_int(dist, n);
}

int main(void)
{
    int n;
    scanf("%d\n", &n);

    char **labirinto = (char **)malloc(sizeof(char *) * n);
    for (int y = 0; y < n; y++)
    {
        labirinto[y] = (char *)malloc(sizeof(char) * n);
    }

    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
        {
            do
            {
                scanf("%c", &labirinto[y][x]);
            } while (labirinto[y][x] == '\n' || labirinto[y][x] == '\r');
        }
    }

    mapeia_labirinto(labirinto, n);
    liberar_matriz_char(labirinto, n);
    return 0;
}