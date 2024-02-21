FLAGS= -g -std=c99 -Wall -Wextra -Werror -pedantic

all: exec
exec: dados.o verificar.o funcoesBanco.o
	gcc main.c dados.o verificar.o funcoesBanco.o -o exe $(FLAGS)
dados.o: funcoes/dados.c
	gcc funcoes/dados.c -c $(FLAGS)
verificar.o: funcoes/verificar.c
	gcc funcoes/verificar.c -c $(FLAGS)
funcoesBanco.o: funcoes/funcoesBanco.c
	gcc funcoes/funcoesBanco.c -c $(FLAGS)
clean:
	rm -rf *.o