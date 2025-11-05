# Makefile para o projeto external-mergesort
# Gera dois executáveis: `gerador` e `ordenacao`

CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11

SRCDIR_G = Gerador
SRCDIR_O = Ordenacao

GEN_SRC = $(SRCDIR_G)/gerador.c
GEN_BIN = gerador

OBJ = $(SRCDIR_O)/ordenacao.o $(SRCDIR_O)/ordenacaoArquivo.o
SORT_BIN = ordenacao

INCLUDES = -I$(SRCDIR_O)
RM = rm -f

.PHONY: all gerador ordenacao clean

all: $(GEN_BIN) $(SORT_BIN)

$(GEN_BIN): $(GEN_SRC)
	$(CC) $(CFLAGS) -o $@ $<

$(SRCDIR_O)/%.o: $(SRCDIR_O)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(SORT_BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(SRCDIR_O)/*.o $(GEN_BIN) $(SORT_BIN)
