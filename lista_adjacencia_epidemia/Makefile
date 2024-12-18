# Nome do arquivo fonte e do executável
SRC = luiz_lima_listaadjacencia_epidemia.c
EXEC = luiz_lima_listaadjacencia_epidemia

all: $(EXEC)

$(EXEC): $(SRC)
	gcc -ggdb -Werror -pg -Wextra -std=gnu11 -Wno-unused-result -mglibc -Wuninitialized -march=x86-64 -Wpedantic -Wall -o $(EXEC) $(SRC)

run: $(EXEC)
	./$(EXEC)

clean:
	rm -vf $(EXEC) gmon.out

clean-saidas:
	rm -vf *.saida.*

# Regra para limpeza completa
clean-all: clean clean-saidas
