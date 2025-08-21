#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n, ponderado;
    printf("Numero de vertices: ");
    scanf("%d", &n);
    printf("Grafo ponderado? (1=sim, 0=nao): ");
    scanf("%d", &ponderado);

    srand(time(NULL));

    int maxArestas = n*(n-1)/2;
    int m = (rand() % (maxArestas - (n-1) + 1)) + (n-1);

    int grafo[n][n];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            grafo[i][j] = 0;

    // garantir conexidade criando uma "árvore"
    for(int i=1;i<n;i++) {
        int j = rand()%i;
        int peso = ponderado ? rand()%11 : 1;
        grafo[i][j] = grafo[j][i] = peso;
        m--;
    }

    // adicionar arestas extras
    while(m > 0) {
        int u = rand()%n;
        int v = rand()%n;
        if(u != v && grafo[u][v] == 0) {
            int peso = ponderado ? rand()%11 : 1;
            grafo[u][v] = grafo[v][u] = peso;
            m--;
        }
    }

    // imprime matriz de adjacencia
    printf("\nMatriz de adjacencia:\n");
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            printf("%2d ", grafo[i][j]);
        }
        printf("\n");
    }

    // gerar arquivo DOT
    FILE *f = fopen("grafo.dot", "w");
    if(!f) {
        printf("Erro ao criar arquivo DOT\n");
        return 1;
    }

    fprintf(f, "graph G {\n");
    fprintf(f, "  node [shape=circle, style=filled, color=lightblue];\n");

    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            if(grafo[i][j] != 0) {
                if(ponderado)
                    fprintf(f, "  %d -- %d [label=\"%d\"];\n", i, j, grafo[i][j]);
                else
                    fprintf(f, "  %d -- %d;\n", i, j);
            }
        }
    }

    fprintf(f, "}\n");
    fclose(f);

    // gerar imagem automaticamente
    int status = system("dot -Tpng grafo.dot -o grafo.png");
    if(status == 0)
        printf("\nImagem 'grafo.png' gerada com sucesso!\n");
    else
        printf("\nErro ao gerar a imagem. Verifique se o Graphviz está instalado.\n");

    return 0;
}
