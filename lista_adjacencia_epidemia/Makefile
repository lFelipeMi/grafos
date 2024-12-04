# Nome do arquivo fonte e do executável
SRC = luiz_lima_listaadjacencia_epidemia.c
EXEC = luiz_lima_listaadjacencia_epidemia

# Regras
all: $(EXEC)

$(EXEC): $(SRC)
	gcc -g -Wall -o $(EXEC) $(SRC)

clean:
	rm -f $(EXEC)

# Regra para executar o programa
run: $(EXEC)
	./$(EXEC)
