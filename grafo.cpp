#include "grafo.hpp"
#include <bits/stdc++.h>
#include <cmath>

#define DEBUG 1

typedef pair<int, double> pi;
Grafo::Grafo(int n, int k){

    this->_tam  = n;
    this->_arestas = new vector<pair<unsigned int, double> >[n];
    
    gera_vertices(n);
    gera_arestas(k);

    if(DEBUG){
        exibeVertices();
        exibeArestas();
    }

}

void Grafo::exibeVertices() {
    cout << "Vertices:\n";
    for(int i = 0; i < this->_vertices.size(); i++) {
        No n = this->_vertices[i];
        cout << "(" << n.x << "," << n.y << ")" << " "; 
    }
    cout << endl;
}

void Grafo::exibeArestas() {
    
    cout << "Arestas:\n";

    for(int i = 0; i < this->_tam; i++) {
        No n1 = this->_vertices[i];
        cout << "(" << n1.x << "," << n1.y << "):\t"; 

        for(int j = 0 ; j < this->_arestas[i].size(); j++) {
            No n2 = this->_vertices[this->_arestas[i].at(j).first];
            cout << "(" << n2.x << "," << n2.y << ", peso: " << this->_arestas[i].at(j).second << ") ";
        }
        cout << endl;
    }
}

void Grafo::realizaBusca(int b, int o, int d) {
    No no, nd;
    
    no = this->_vertices[o];
    nd = this->_vertices[d];
    cout << "(" << no.x << ", " << no.y << "),  Destino: (" << nd.x << ", " << nd.y << "). ";
 
    switch(b) {
        case(1):
            cout << "Realizando busca em profundidade.\n";
            this->dfs(o, d, 0);
            break;
        case(2):
            cout << "Realizando busca em largura.\n";
            this->bfs(o, d, 0);
            break;
        case(3):
            cout << "Realizando busca com best first.\n";
            this->best_first(o, d, this->_tam);
            break;
        default:
            cout << "Valor inválido.\n";
    }

    // Limpa o mapa de vértices visitados para a próxima busca
    this->visitados.clear();
}

void Grafo::inserirAresta(int v, int w, double p) {
    this->_arestas[v].push_back(make_pair(w, p));
}

double Grafo::distanciaEuclidiana(No n1, No n2) {
    return(sqrt((n1.x+n2.x)*(n1.x+n2.x) + (n1.y+n2.y)*(n1.y+n2.y)));
}

void Grafo::gera_vertices(int n) {

    srand(time(0));

    // Gera o conjunto de vertices aleatorios
    for(int i = 0; i < n; i++) {
        int found = 0;

        No aux;
        
        aux.x = rand()%n;
        aux.y = rand()%n;

        //Garante que o mesmo vértice não será gerado duas vezes
        for(int j = 0; j < this->_vertices.size(); j++) {
            if(this->_vertices[j] == aux) {
                found = 1;
                i--;
                break;
            }
        }
        
        if(!found) {
            this->_vertices.push_back(aux);
        }
    }
}

void Grafo::gera_arestas(int k) {

    srand(time(0));

    // Gera k arestas para cada vértice
    for(int i = 0; i < this->_vertices.size(); i++) {
        for(int j = 0; j < k; j++) {
            double peso;
            unsigned int v = i, found = 0;
            while(v == i || found) {

                // Impede a geração de arestas ambíguas
                v = rand()%(this->_tam);
                found = 0;
                
                for(int t = 0; t < this->_arestas[i].size(); t++) {
                    if(this->_arestas[i].at(t).first == v) {
                        
                        found = 1;
                        break;
                    }
                }
            }  
            peso = distanciaEuclidiana(this->_vertices[i], this->_vertices[v]);
            this->inserirAresta(i, v, peso);
        }
    }
}

void Grafo::dfs(int origem, int dest, double dist) {
    No n = this->_vertices[origem];

    if(origem == dest) {
        cout << "Destino encontrado: (" << n.x << ", " << n.y << "), distancia percorrida:" << dist << endl;
    }

    // Marca como visitado e printa o nó
    this->visitados[origem] = true;
    cout << "(" << n.x << ", " << n.y << "), distancia percorrida:" << dist << endl;
    
    // Percorre a lista de adjascencias
    for(int i = 0; i < this->_arestas[origem].size(); i++) {
        unsigned int v = this->_arestas[origem].at(i).first;
        if(!visitados[v]) {

            double d = distanciaEuclidiana(this->_vertices[origem], this->_vertices[v]);
            this->dfs(v, dest, dist + d);
        }
    }
}


void print(vector<int> parent, int s, int d)
{
   
  // The while loop will stop only when the
  // destination and the source node become equal
  while (s != d)
  {
 
        cout << d << " <- ";
        d = parent[d];
  }
  cout << d << endl;
}

void Grafo::bfs(int origem, int destino, double dist) {
    
    this->visitados[origem] = true;

    list<int> fila;
    fila.push_back(origem);

    while(!fila.empty()) {

        origem = fila.front();
        No n = this->_vertices[origem];
        cout << "(" << n.x << ", " << n.y << ") " << endl;
        fila.pop_front();

        for(int i = 0; i < this->_arestas[origem].size(); i++) {
            int aux = this->_arestas[origem].at(i).first;
            if(!this->visitados[aux]) {
                this->visitados[aux] = true;
                fila.push_back(aux);
            }
        }
    
    }

}

void Grafo::best_first(int atual, int destino, int n) {
    
    priority_queue<pi, vector<pi>, greater<pi> > pq;
    pq.push(make_pair(atual, 0.0));

    int aux = atual;
    this->visitados[aux] = true;

    while(!pq.empty()) {
        int x = pq.top().first;
        double d = pq.top().second;
        No n = this->_vertices[x];
        cout << "(" << n.x << ", " << n.y << ") dist: " << d << endl;

        pq.pop();
        // Achou o destino
        if(x == destino)
            break;

        for(int i = 0; i < this->_arestas[x].size(); i++) {
            
            if(!this->visitados[this->_arestas[x][i].first]) {
                this->visitados[this->_arestas[x][i].first] = true;
                pq.push(make_pair(this->_arestas[x][i].first, this->_arestas[x][i].second + d));
            }
        }
    }
}

int main() {
    
    Grafo g(10, 2);
    g.realizaBusca(3, 3, 0);   

    return 0;
}