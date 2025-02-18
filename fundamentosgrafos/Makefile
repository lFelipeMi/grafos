CC = gcc

CFLAGS = -Wall -Wextra -g

TARGET = luiz_lima_fundamentosgrafos
OBJS = luiz_lima_fundamentosgrafos.o grafo.o listaC.o

all: $(TARGET)

$(TARGET): $(OBJS)
	gcc -g -ggdb -o $(TARGET) $(OBJS)

luiz_lima_fundamentosgrafos.o: luiz_lima_fundamentosgrafos.c grafo.h listaC.h
	$(CC) $(CFLAGS) -c luiz_lima_fundamentosgrafos.c

grafo.o: grafo.c grafo.h listaC.h
	$(CC) $(CFLAGS) -c grafo.c

listaC.o: listaC.c listaC.h
	$(CC) $(CFLAGS) -c listaC.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

