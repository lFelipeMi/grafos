# Teoria dos Grafos

## Classificações

- **Vértices adjacentes**: Ligados por uma aresta.
- **Grau do vértice**: Quantidade de arestas que partem ou chegam ao vértice.
- **Laços/Loops**: Aresta que conecta um vértice a ele mesmo (ex.: A - A). Um laço conta como 2 graus.
- **Ordem do grafo**: Maior grau de um vértice no grafo.
- **Coloração**: Atribuição de cores aos vértices, garantindo que vértices adjacentes tenham cores distintas.
- **Número Cromático**: Número mínimo de cores necessárias para colorir o grafo.
- **Arestas paralelas/múltiplas**: Arestas que ligam o mesmo par de vértices, independentemente do sentido.

## Conceitos em Grafos

- **Passeios (ou Percursos)**: Sequência de vértices e arestas.
- **Trilhas (ou Cadeias)**: Passeios onde todas as arestas são distintas.
- **Caminhos**: Sequência de arestas que conecta um vértice de origem a um vértice de destino. Um caminho é **simples** se não passa pela mesma aresta mais de uma vez.
  - **Distância**: Comprimento do menor caminho entre dois vértices.
  - **Diâmetro**: Maior distância entre quaisquer pares de vértices no grafo.
- **Ciclos**: Caminhos que começam e terminam no mesmo vértice, sem repetir outros vértices. 
  - **Cintura (ou girth)**: Comprimento do menor ciclo em um grafo.
- **Circuitos**: Caminhos que começam e terminam no mesmo vértice.
- **Caminhos de Euler (Ponte de Königsberg)**:
  - Caminho ou circuito que contém todas as arestas do grafo.
  - Um multigrafo conexo tem um **circuito de Euler** se todos os vértices têm grau par.
  - Um multigrafo conexo tem um **caminho de Euler**, mas não um circuito, se tiver exatamente dois vértices de grau ímpar.
- **Caminhos Hamiltonianos**:
  - Caminho ou circuito que passa por todos os vértices exatamente uma vez.
  - Em um grafo simples com n vértices, sendo n >= 3, e todos os vértices com grau pelo menos n/2, então ele tem um circuito de Hamilton.
- **Isomorfismo**: Dois grafos são isomórficos se podem ser representados da mesma forma.

## Tipos de Grafos

- **Grafo Simples**: Sem arestas paralelas ou laços.
- **Multigrafo**: Contém arestas paralelas ou laços.
- **Grafo Não Direcionado**: Arestas indicam apenas conexão, sem direção (ex.: A - B).
- **Grafo Direcionado (Dígrafo)**: Arestas têm direção (ex.: A → B ≠ A ← B).
  - Graus de entrada e saída são considerados.
- **Grafo Conexo**: Quando existe um caminho entre todos os vértices.
  - Um grafo direcionado é **fortemente conexo** se há caminhos entre todos os vértices respeitando as direções das arestas.
  - É **fracamente conexo** se há caminhos ao ignorar as direções das arestas.
- **Grafo Planar**: Pode ser desenhado sem arestas que se cruzem. Pode ser colorido com no máximo 4 cores.
- **Grafo Regular**: Todos os vértices têm o mesmo grau.
- **Grafo Ponderado**: Cada aresta possui um peso ou custo.
- **Grafo Pn**: Grafo simples em forma de lista ligada (ex.: \(P_4 = a - b - c - d\)).
- **Grafo Cn**: Grafo simples cíclico (ex.: \(C_4 = a - b - c - d - a\)).
- **Grafo Kn**: Grafo simples completo, onde todos os vértices estão conectados entre si.
- **Grafo K-Partido**:
  - Grafo onde os vértices podem ser divididos em \(K\) conjuntos, e não há arestas entre vértices do mesmo conjunto.
  - É **bi-partido** se não possui ciclos de tamanho ímpar.
  - Pode ser colorido com \(K\) cores.
- **Subgrafo**: Grafo derivado do grafo original sem remover vértices ou arestas.
- **Subgrafo Gerador**: Subgrafo que contém todos os vértices do grafo original.
- **Árvores**: Grafos conexos sem circuitos simples.
  - **Árvore de Extensão**: Subgrafo gerador em forma de árvore.
  - **Árvore de Extensão Mínima**: Árvore de extensão com menor peso no grafo.
- **Grafo Euleriano**: Grafo conexo com uma trilha fechada que contém todas as arestas.
- **Grafo Hamiltoniano**: Grafo que contém uma trilha fechada passando uma vez por cada vértice.

## Representações de Grafos
![grafo_1](https://github.com/user-attachments/assets/3d0a4d2c-38db-47a6-b1b4-fb82509e2f1d)

### Lista de Adjacências
Cada vértice possui uma lista de adjacências indicando suas conexões:
```
1: 2 -> 4 -> 5
2: 1 -> 5
3: 4 -> 5
4: 1 -> 3
5: 1 -> 2 -> 3
```

### Matriz de Adjacências
Tabela que representa as conexões entre vértices:
```
     1  2  3  4  5

1    0  1  0  1  1
2    1  0  0  0  1
3    0  0  0  1  1
4    1  0  1  0  0
5    1  1  1  0  0
```
