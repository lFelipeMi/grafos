Classificações:
	Vértices adjacentes: Ligamos por uma aresta

	Grau do vértice: Quantas arestas partem/chegam ao vértice

	Laços/loops: Liga um 	vértice nele mesmo (A - A). Um laço conta como 2 graus.

	Ordem do grafo: Maior grau de vértice

	Coloração: Atribui-se uma cor aos vértices de modo que vértices adjacentes tenham cores distintas.

	Número Cromático: Número mínimo de cores necessárias para colorir o grafo.

	Arestas paralelas/múltiplas: Ligam o mesmo par de vértice (Independente do sentido)
	

Conceitos em grafos:
	Passeios: É uma sequência de vértices e arestas.
	
	Trilhas: É um passeio em que todas as arestas são distintas.

Ciclos: Partem e terminam no mesmo vértice, sem repetir nenhum outro vértice.
	A cintura ou girth de um grafo é o comprimento do menor ciclo nele.
	
	Caminhos: Um caminho é uma sequência de arestas onde percorre de um vértice origem a um vértice destino.
	Um caminho é simples se não passar pela mesma aresta mais de uma vez.
	A distância entre dois vértices é o comprimento do caminho de menor distância.
	O diâmetro de um grafo é a maior distância considerando todos os pares de vértices no grafo.

	Circuitos: São caminhos que partem e terminam no mesmo vértice.

	Caminhos de Euler (Ponte de Königsberg): É um caminho ou circuito (simples) que contém todas as arestas do grafo.
	Um multigrafo conexo tem um Circuito de Euler se e somente se cada um dos seus vértices tiverem grau par.
	Um multigrafo conexo tem um Caminho de Euler, mas não um Circuito de Euler, se e somente se ele tiver exatamente dois vértices com grau ímpar.

	Caminhos Hamiltonianos: É um caminho ou circuito (simples) que passa por todos os vértices do grafo exatamente uma vez.
	Se um grafo simples com n vértices, sendo n >= 3, tiver todos os vértices com grau pelo menos n/2, então ele tem um circuito de Hamilton.
		
	Isomorfismo: Dois grafos são isomórficos se podem ser desenhados da mesma forma.



Tipos de grafos [G = (V, E)]: 
	Grafo Simples: Não possuem arestas paralelas. (Um par de vértice possui apenas uma aresta)

	Multigrafo: Possuem arestas paralelas ou laços. (Um par de vértice possui duas ou mais arestas)

	Grafo não direcionado: Arestas indicam apenas uma conexão, não denotando um sentido (A - B)
	
	Grafo direcionado (Ou dígrafo): Arestas indicam um sentido a ser percorrida (A -> B) != (A <- B). Os grafos direcionados possuem vértice com grau de entrada e de saída.

	Grafo Conexo: Existe um caminho entre todos os vértices do grafo.
Um grafo direcionado é dito fortemente conexo se ele possui um caminho entre todos os vértices respeitando os sentidos das arestas. Caso ele possua um caminho entre todos os vértices apenas se “desrespeitar” os sentidos ele é fracamente conexo.

Grafo Planar: É possível desenhar o grafo de forma que as arestas não se sobreponham. É possível colorir um grafo planar com no máximo 4 cores.

Grafo regular: Um grafo que todos os vértices possuem o mesmo grau

Grafo ponderado: Cada aresta possui um custo/peso

Grafo Pn: Grafo simples possui forma de uma lista ligada (P4 = a - b - c - d)

Grafo Cn: Grafo simples cíclico (P4 = a - b - c - d - a)

Grafo Kn: Grafo simples que todas os vértices estão ligados um com os outros.

Grafo K-Partido (Km,n…): Grafo simples que os vértices podem ser partidos em K grupos onde em cada grupo, os pontos finais das arestas terminam em outros grupos não possuindo arestas entre os vértices do seu grupo.
	Um Grafo é Bi-Partido se e somente se ele não tiver ciclos de tamanho ímpar.
	Um grafo K-Partido pode ser pintado com K cores.

Subgrafo: A partir de um subgrafo é possível gerar o grafo original sem tirar vértices ou arestas do subgrafo.

Subgrafo gerador ou grafo de extensão: É um subgrafo que contém todos os vértices do grafo original.

Árvores: É um grafo conexo que não contém um circuito simples.

Árvores de extensão: Mesmo conceito do grafo de extensão, mas o formato do subgrafo deve ser uma árvore.
Árvore de extensão mínima é a Árvore de extensão com menor peso no grafo. 

	Grafo Euleriano: Um grafo conectado G é dito Euleriano se existe uma trilha
fechada contendo cada uma das arestas de G.

	Grafo Hamiltoniano: Um grafo que contém uma trilha
fechada, passando exatamente uma única vez em cada um
dos vértices


	Representações: 
		
		Lista de Adjacências: Cada vértice possui uma lista de adjacências contendo suas ligações. 
		1: 2 -> 4 -> 5 -> Null
		2: 1 -> 5 -> Null
		3: 4 -> 5 -> Null
		4: 1 -> 3 -> Null
		5: 1 -> 2 -> 3 -> Null
		
		Matriz de Adjacências: Grafos simples não direcionados podem guardar apenas a parte superior ou inferior da diagonal principal, multigrafos não direcionados devem guardar também a diagonal principal.
		
		     1   2   3   4   5
		1   0   1   0   1   1
		2   1   0   0   0   0
		3   0   0   0   1   1
		4   1   0   1   0   0
		5   1   1   1   0   0


