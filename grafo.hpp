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
    void realizaBusca(int n);

private:
    
    int _tam;
    
    vector<No>  _vertices; 
    // Par com o outro o outro vertice seguido do peso da aresta
    vector<pair<unsigned int, double> > *_arestas;
  
    void inserirAresta(int v, int w, double p);
    double distanciaEuclidiana(No n1, No n2);

    void gera_vertices(int n);
    void gera_arestas (int k);

    map<int, bool> dfsVisitados;
    

};

#endif