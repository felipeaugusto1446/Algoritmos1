#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAMANHO 200000

typedef struct maxheap {
  int * V;
  int n;
} maxheap;

typedef struct minheap {
  int * V;
  int n;
} minheap;

int pai(int i) { return ceil(i / 2.0) - 1; }
int esq(int i) { return 2 * i + 1; }
int dir(int i) { return 2 * i + 2; }

maxheap* cria_maxheap() {
  maxheap * H = (maxheap*) malloc(sizeof(maxheap));
  H->V = (int*) malloc(sizeof(int) * TAMANHO);
  H->n = 0;
  return H;
}

void sobe_maxheap(maxheap *H, int i) {
  if (i == 0) return;
  int p = pai(i);
  if (H->V[p] < H->V[i]) {
    int aux = H->V[p];
    H->V[p] = H->V[i];
    H->V[i] = aux;
    sobe_maxheap(H, p);
  }
}

void desce_maxheap(maxheap *H, int i) {
  int e = esq(i);
  int d = dir(i);
  if (e >= H->n) return;
  int imaior;
  if (d < H->n && H->V[d] > H->V[e]) imaior = d;
  else imaior = e;
  if (H->V[i] < H->V[imaior]) {
    int aux = H->V[i];
    H->V[i] = H->V[imaior];
    H->V[imaior] = aux;
    desce_maxheap(H, imaior);
  }
}

void insere_max(maxheap * H, int v) {
  if (H->n >= TAMANHO) return; 
  H->V[H->n] = v;
  H->n = H->n + 1;
  sobe_maxheap(H, H->n - 1);
}

int remove_max(maxheap * H) {
  if (H->n == 0) return -1;
  int maior = H->V[0];
  H->n = H->n - 1;
  H->V[0] = H->V[H->n];
  desce_maxheap(H, 0);
  return maior;
}

int topo_maxheap(maxheap * H) {
  if (H->n > 0) return H->V[0];
  return -1;
}

int tamanho_maxheap(maxheap * H) {
  return H->n;
}

void libera_maxheap(maxheap* H) {
  free(H->V);
  free(H);
}

minheap* cria_minheap() {
  minheap * H = (minheap*) malloc(sizeof(minheap));
  H->V = (int*) malloc(sizeof(int) * TAMANHO);
  H->n = 0;
  return H;
}

void sobe_minheap(minheap *H, int i) {
  if (i == 0) return;
  int p = pai(i);
  if (H->V[p] > H->V[i]) {
    int aux = H->V[p];
    H->V[p] = H->V[i];
    H->V[i] = aux;
    sobe_minheap(H, p);
  }
}

void desce_minheap(minheap *H, int i) {
  int e = esq(i);
  int d = dir(i);
  if (e >= H->n) return;
  int imenor;
  if (d < H->n && H->V[d] < H->V[e]) imenor = d;
  else imenor = e;
  if (H->V[i] > H->V[imenor]) {
    int aux = H->V[i];
    H->V[i] = H->V[imenor];
    H->V[imenor] = aux;
    desce_minheap(H, imenor);
  }
}

void insere_min(minheap * H, int v) {
  if (H->n >= TAMANHO) return; 
  H->V[H->n] = v;
  H->n = H->n + 1;
  sobe_minheap(H, H->n - 1);
}

int remove_min(minheap * H) {
  if (H->n == 0) return -1;
  int menor = H->V[0];
  H->n = H->n - 1;
  H->V[0] = H->V[H->n];
  desce_minheap(H, 0);
  return menor;
}

int topo_minheap(minheap * H) {
  if (H->n > 0) return H->V[0];
  return -1;
}

int tamanho_minheap(minheap * H) {
  return H->n;
}

void libera_minheap(minheap* H) {
  free(H->V);
  free(H);
}

int main(int argc, char* argv[]) {
  maxheap * maxH = cria_maxheap();
  minheap * minH = cria_minheap();
  int num;
  
  while (scanf("%d", &num) && num != -1) {
    insere_max(maxH, num);
    insere_min(minH, remove_max(maxH));
    
    if (tamanho_minheap(minH) > tamanho_maxheap(maxH)) {
      insere_max(maxH, remove_min(minH));
    }
    
    double mediana;
    if (tamanho_maxheap(maxH) > tamanho_minheap(minH)) {
      mediana = (double)topo_maxheap(maxH);
    } else {
      mediana = (topo_maxheap(maxH) + topo_minheap(minH)) / 2.0;
    }
    printf("Mediana: %.1f\n", mediana);
  }
  
  libera_maxheap(maxH);
  libera_minheap(minH);
  
  return 0;
}