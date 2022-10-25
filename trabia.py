
from locale import atoi
import queue as Q
from heapq import *
from cmath import sqrt
import random

class Vertice:

    def __init__(self,coords,id) -> None:
        self.id = id
        self.coords = coords
        self.adj = dict()


def geo_distance(coord1: tuple, coord2: tuple):
    x = coord1[0] - coord2[0]
    y = coord1[1] - coord2[1]
    return sqrt((pow(x,2)+pow(y,2)))

# Retorna tupla de coordenadas do vertice
def get_random_vertice(limit):
    return (random.randrange(0,limit),random.randrange(0,limit))

def get_vertice(n,id):
    v = Vertice(coords=get_random_vertice(n),id=id)
    return v

def gera_vertices(n):
    vert = []
    
    for i in range(n):
        vert.append(get_vertice(n,i))

    return vert

def gera_arestas(lista_vert,k):
    for vertice in lista_vert:
        candidatos = random.choices(lista_vert,k=len(vertice.adj)-k)
        for cand in candidatos:
            vertice.adj.update({cand.id: geo_distance(vertice.coords,cand.coords)})
            #print(f"Vertice de coordenadas {vertice.coords} se conectou com vertice {cand.coords}, peso: {vertice.adj[cand.id]}")

def gera_grafo_knn(n, k):
    lista_vert = gera_vertices(n)
    gera_arestas(lista_vert, k)
    return lista_vert

# Best First
## Calcula a distância entre dois nós
def Eval(node, goal):
    distance = abs(node.posX - goal.posX) + abs(node.posY - goal.posY)
    return distance


def BestFirst(startNode, goalNode, verts):

    extensoes = 0
    currentNode = startNode
    path = []
    
    while True:

        extensoes += 1
        path.append(currentNode) # Adiciona o nó atual no vetor 'path'
        if geo_distance(currentNode.coords, goalNode.coords) == 0: # Se chegou no destino, retorna
            
            
            return path, extensoes

        
        nextEval = 10000
        nextNode = None
        
        # Para todos os vizinhos, verifica qual é o mais próximo ao destino
        for i in currentNode.adj:
            extensoes += 1

            # Se existir um nó mais próximo ao destino, define ele como o
            # próximo nó a ser visitado
            if geo_distance(verts[i].coords, goalNode.coords) < nextEval:
                nextNode = verts[i]
                nextEval = geo_distance(verts[i].coords, goalNode.coords)
        
        # Se existir um nó melhor, retorna o 'path' incompleto
        if nextEval >= geo_distance(currentNode.coords, goalNode.coords):
          return path, extensoes

        currentNode = nextNode


# Método responsável pelo DFS. Aplicação iterativa do algoritmo.
def DFS(n, initial, final, verts):
    
    extensoes = 0 # número de extensões do algoritmo
    stck = [] # stack
    path = []
    visited = [False] * n # vetor de visitados

    stck.append(initial) # adiciona o nó atual na stack
    visited[initial.id] = True # marca o nó atual como visitado
                
    # Enquanto a stack não estiver vazia
    while len(stck) != 0: 
        
        extensoes += 1
        initial = stck.pop() 
        visited[initial.id] = True 

        # Descomente a linha abaixo se desejar printar o caminho
        print(initial.coords[0], initial.coords[1])
        path.append(initial)

        # Verifica se o nó atual é o nó destino
        if initial.id == final.id: 
            print("DFS encontrou!")
            return extensoes, path

        # Adicionando vizinhos do nó atual na stack
        for v in initial.adj:
            extensoes += 1
            if visited[v] == False: 
                stck.append(verts[v]) 
                visited[v] = True

# Algoritmo de busca A* (A star)
def a_Star(n, start, end, verts):

    extensoes = 0
    path = []
    frontier = Q.PriorityQueue()
    frontier.put(start.id, 0)

    cost = [0.0] * len(n) # inserimos em cost, já que é o menor custo

    cost[start.id] = -1

    # Enquanto a fila não estiver vazia
    while not frontier.empty():

        extensoes += 1
        current = verts[frontier.get()]

        # Descomente abaixo se precisar imprimir o caminho
        # print(current.posX, current.posY)
        # path.append(current)

        # Verificando se chegou no final
        if current.id == end.id:
            # print("aStar encontrou!")
            return extensoes, path
        
        # Percorrendo vizinhos do atual
        for next in current.adj:
            
            extensoes += 1
            # 1 eh o custo do atual até chegar em qualquer um adjacente à ele
            new_cost = cost[current.id] + 1

            # se o custo até o próximo nó não foi calculado e guardado no vetor de custos 
            # ou se o que estiver no vetor de custo for maior do que o que foi calculado na iteração atual
            
            if cost[next] == 0.0 or new_cost < cost[next]:
                cost[next] = new_cost
                priority = new_cost + geo_distance(verts[next].coords, end.coords)
                
                frontier.put(verts[next], priority)
                path.append(current)
                
    return extensoes, path

# Método responsável pelo BFS. Aplicação iterativa do algoritmo.
def BFS(n, initial, final,verts):

    extensoes = 0 # número de extensões do algoritmo
    queue = [] # fila de prioridades
    path = []
    visited = [False] * n # vetor de visitados

    queue.append(initial) # adiciona o nó atual na fila
    visited[initial.id] = True # marca o nó atual como visitado
                
    # Enquanto a fila não estiver vazia
    while len(queue) != 0: 
        
        extensoes += 1
        initial = queue.pop(0) 
        visited[initial.id] = True 

        # Descomente a linha abaixo se desejar printar o caminho
        print(initial.coords[0], initial.coords[1])
        path.append(initial)

        # Verifica se o nó atual é o nó destino
        if initial.id == final.id: 
            print("BFS encontrou!")
            return extensoes, path

        # Adicionando vizinhos do nó atual na fila
        for v in initial.adj:
            extensoes += 1
            if visited[v] == False: 
                queue.append(verts[v]) 
                visited[v] = True