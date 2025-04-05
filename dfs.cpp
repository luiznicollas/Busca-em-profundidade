#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

typedef struct {
	int numVertices;
	int numArestas;
	int ** matriz;
}Grafo;

void inicializaGrafo(Grafo * g ,int vertices){
	g->numVertices = vertices;
	g->numArestas = 0;
	g->matriz = (int**) malloc(sizeof(int*)*vertices);
	
	for(int i = 0;i<vertices;i++){
		g->matriz[i] = (int*) malloc(sizeof(int) * vertices);
		
	}
	
	for(int i =0;i<vertices;i++){
		for(int j = 0;j<vertices;j++){
			g->matriz[i][j] = 0;
		}
	}
	 cout << "grafo inicializado com vertices : " << g->numVertices << "\n";
	 
}





void imprimirGrafo(Grafo * g){
	cout << "Imprimindo grafo : ( " << "vertices : " << g->numVertices << " arestas : " << g->numArestas << ")\n";
	
	// char   beto[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
		
	for(int i =0;i<g->numVertices;i++){
		cout << "\t" << i;
		
	}
	cout << "\n";
	
	for(int i =0;i<g->numVertices;i++){
		cout << i;
		for(int j =0;j<g->numVertices;j++){
			cout << "\t" << g->matriz[i][j];
		}
		cout << "\n";
	}
}




void liberaGrafo(Grafo * g ){
	
	for(int i = 0;i<g->numVertices;i++){
	  free(g->matriz[i]);
	}
	
	free(g->matriz);
}
	
	
void insereAresta(Grafo * g,int v1,int v2){

	
	if(g->matriz[v1][v2] == 0){
		g->matriz[v1][v2] = 1;
		g->matriz[v2][v1] =1;
		g->numArestas++;
		
	}
	
	
}

void visitaDFSCores(Grafo* g, int atual, int* tempo, int* cor, int* tDescoberta, int* tTermino, int* anterior) {
    (*tempo)++;
    cor[atual] = 1; // CINZA
    tDescoberta[atual] = *tempo;

    for (int i = 0; i < g->numVertices; i++) {
        if (g->matriz[atual][i] == 1) { // Verifica se há uma aresta
            if (cor[i] == 0) { // BRANCO
                anterior[i] = atual;
                visitaDFSCores(g, i, tempo, cor, tDescoberta, tTermino, anterior);
            }
        }
    }

    cor[atual] = 2; // PRETO
    (*tempo)++;
    tTermino[atual] = *tempo;
}

void DFSCores(Grafo* g) {
   

    int* cor = (int*)malloc(sizeof(int) * g->numVertices);
    int* tDescoberta = (int*)malloc(sizeof(int) * g->numVertices);
    int* tTermino = (int*)malloc(sizeof(int) * g->numVertices);
    int* anterior = (int*)malloc(sizeof(int) * g->numVertices);
    int tempo = 0;

    for (int i = 0; i < g->numVertices; i++) {
        cor[i] = 0; // BRANCO
        tDescoberta[i] = -1;
        tTermino[i] = -1;
        anterior[i] = -1;
    }

    for (int i = 0; i < g->numVertices; i++) {
        if (cor[i] == 0) {
            visitaDFSCores(g, i, &tempo, cor, tDescoberta, tTermino, anterior);
        }
    }

    cout << "Resumo da Busca em Profundidade:\n";
    cout << "No\tAnterior\tDescoberta\tTermino\tCor\n";
    for (int i = 0; i < g->numVertices; i++) {
        cout << i << "\t" << anterior[i] << "\t\t" << tDescoberta[i] 
             << "\t\t" << tTermino[i] << "\t" << cor[i] << "\n";
    }

    free(cor);
    free(tDescoberta);
    free(tTermino);
    free(anterior);
}


void retornaGrauDoVertice(Grafo* g, int v) {
   

    int grau = 0; // Inicializa o grau como 0
    for (int x = 0; x < g->numVertices; x++) {
        if (g->matriz[v][x] == 1) {
            grau++; // Incrementa o grau para cada aresta conectada ao vértice v
        }
    }
    cout << " o grau do vertice " << v << " e : " << grau << endl;
}

void verificaVizinhos(Grafo* g, int v) {
 
    bool possuiVizinhos = false;

    cout << "Vizinhos do vertice " << v << ": ";
    for (int i = 0; i < g->numVertices; i++) {
        if (g->matriz[v][i] == 1) {
            possuiVizinhos = true;
            cout << i << " "; // Exibe o número do vértice vizinho
        }
    }

    if (possuiVizinhos == false) {
        cout << "Nenhum.\n";
    } else {
        cout << "\n";
    }
}


void conjuntosGrafos(Grafo * g){
	cout << "V = {";
	for(int i =0;i<g->numVertices;i++){
		cout << i << ",";
	}
	cout << "} ";
	
	
	cout << "A = { ";
	for(int i =0;i<g->numVertices;i++){
		for(int j=0;j<g->numVertices;j++){
			if(g->matriz[i][j] == 1 ){
				cout << "{" << i <<  "," << j << "}" << ",";
			}
		}
		
	}
	
	cout << "}";
	
}


void buscaDFS(Grafo *g, int atual, int destino, int *visitado, bool *encontrado) {
    // Marca o vértice atual como visitado
    visitado[atual] = 1;

    // Se o vértice atual for o destino, o caminho foi encontrado
    if (atual == destino) {
        *encontrado = true;
        return;
    }

    // Recursivamente visita os vizinhos
    for (int i = 0; i < g->numVertices; i++) {
        if (g->matriz[atual][i] == 1 && !visitado[i]) {
            buscaDFS(g, i, destino, visitado, encontrado);
            
        }
    }
}


void existe_caminho(Grafo *g, int origem, int destino) {
    int *visitado = (int*) malloc(sizeof(int) * g->numVertices);
    bool encontrado = false;

    // Inicializa todos os vértices como não visitados
    for (int i = 0; i < g->numVertices; i++) {
        visitado[i] = 0;
    }

    // Chama a função DFS para verificar o caminho
    buscaDFS(g, origem, destino, visitado, &encontrado);

    free(visitado);

    // Se o caminho foi encontrado, exibe a mensagem
    if (encontrado) {
        cout << "Caminho encontrado entre os vertices." << endl;
    } else {
        cout << "Não existe caminho entre os vertices." << endl;
    }
}




int main(){
	


	Grafo * grafinho = (Grafo*) malloc(sizeof(Grafo));
	inicializaGrafo(grafinho,7);
	
	insereAresta(grafinho,0,2);
	insereAresta(grafinho,0,6);
	insereAresta(grafinho,1,2);
	insereAresta(grafinho,0,2);
	insereAresta(grafinho,1,3);
	insereAresta(grafinho,2,0);
	insereAresta(grafinho,2,1);
	insereAresta(grafinho,2,3);
	insereAresta(grafinho,3,1);
	insereAresta(grafinho,3,4);
	insereAresta(grafinho,0,2);
	insereAresta(grafinho,6,0);
	
	
	
	DFSCores(grafinho);
	
	liberaGrafo(grafinho);
	
	
	return 0;
}