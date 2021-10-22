

#all: metaheuristicas
#
#metaheuristicas: main.cpp Testador.cpp Projeto.cpp 
#	g++ -o metaheuristicas main.cpp Testador.cpp Projeto.cpp
#
#clean:
#	rm -rf *.o *~ metaheuristicas

# ==============================================================

all: metaheuristicas

metaheuristicas: main.o Testador.o Projeto.o 
	g++ -o metaheuristicas main.o Testador.o Projeto.o

main.o: main.cpp Testador.h Projeto.h
	g++ -c -o main.o main.cpp

Testador.o: Testador.cpp Testador.h Projeto.h
	g++ -c -o Testador.o Testador.cpp

Projeto.o: Projeto.cpp Testador.h Projeto.h
	g++ -c -o Projeto.o Projeto.cpp

clean:
	rm -rf *.o *~ metaheuristicas

