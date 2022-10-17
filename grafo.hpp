#ifndef __GRAFO
#define __GRAFO

#include <vector>
#include <map>

using namespace std;

class Grafo
{
public:
    struct No
    {
        int x, y;
        
        bool const operator==(const No& n) {
            return(x == n.x && y == n.y);
        }
    };

    Grafo(int n, int k);
    void exibeVertices();
    void exibeArestas();
    void realizaBusca(int b, int o, int d);

private:
    
    int _tam;
    
    vector<No>  _vertices; 
    // Par com o outro o outro vertice seguido do peso da aresta
    vector<pair<unsigned int, double> > *_arestas;
  
    void inserirAresta(int v, int w, double p);
    double distanciaEuclidiana(No n1, No n2);

    void gera_vertices(int n);
    void gera_arestas (int k);

    void exibeCaminho(vector<int> caminho, int origem, int no);

    void dfs(int origem, int dest, double dist);
    void bfs(int origem, int dest, double dist);

    void best_first(int atual, int destino, int n);

    // Marca os vértices visitados durante as buscas
    map<int, bool> visitados;
    

};

#endif