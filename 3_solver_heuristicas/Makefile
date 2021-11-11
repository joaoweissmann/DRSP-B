

objects = main.o Testador.o Projeto.o Sonda.o CalculadorDeDesloc.o DadosDeEntrada.o LeitorDeDados.o

headers = Testador.h Projeto.h Sonda.h CalculadorDeDesloc.h DadosDeEntrada.h LeitorDeDados.h

CFLAGS = -std=c++11 -O2 -Wall

all: metaheuristicas

metaheuristicas: $(objects)
	g++ -o metaheuristicas $(CFLAGS) $(objects)

main.o: main.cpp $(headers)
	g++ -c -o main.o $(CFLAGS) main.cpp

Testador.o: Testador.cpp $(headers)
	g++ -c -o Testador.o $(CFLAGS) Testador.cpp

Projeto.o: Projeto.cpp $(headers)
	g++ -c -o Projeto.o $(CFLAGS) Projeto.cpp

Sonda.o: Sonda.cpp $(headers)
	g++ -c -o Sonda.o $(CFLAGS) Sonda.cpp

CalculadorDeDesloc.o: CalculadorDeDesloc.cpp $(headers)
	g++ -c -o CalculadorDeDesloc.o $(CFLAGS) CalculadorDeDesloc.cpp

DadosDeEntrada.o: DadosDeEntrada.cpp $(headers)
	g++ -c -o DadosDeEntrada.o $(CFLAGS) DadosDeEntrada.cpp

LeitorDeDados.o: LeitorDeDados.cpp $(headers)
	g++ -c -o LeitorDeDados.o $(CFLAGS) LeitorDeDados.cpp

clean:
	rm -rf *.o *~ metaheuristicas
