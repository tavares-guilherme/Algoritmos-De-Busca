#include "grafo.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cmath>
#include <map>

#define DEBUG 1

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
        cout << n1.x << "," << n1.y << ":\t"; 

        for(int j = 0 ; j < this->_arestas[i].size(); j++) {
            No n2 = this->_vertices[this->_arestas[i].at(j).first];
            cout << n2.x << "," << n2.y << " ";
        }
        cout << endl;
    }
}

void Grafo::inserirAresta(int v, int w, double p) {
    this->_arestas[v].push_back(make_pair(w, p));
}

double Grafo::distanciaEuclidiana(No n1, No n2) {
    return(sqrt((n1.x+n2.x)*(n1.x+n2.x) + (n1.y+n2.y)*(n1.y+n2.y)));
}

void realizaBusca(int n) {
    
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

int main() {
    Grafo g(10, 2);
}