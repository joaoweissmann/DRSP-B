# TODO: colocar variáveis guardando lista de arquivos
# TODO: colocar mais opções do compilador

all: metaheuristicas

metaheuristicas: main.o Testador.o Projeto.o Sonda.o CalculadorDeDesloc.o DadosDeEntrada.o LeitorDeDados.o
	g++ -o metaheuristicas main.o Testador.o Projeto.o Sonda.o CalculadorDeDesloc.o DadosDeEntrada.o LeitorDeDados.o

main.o: main.cpp Testador.h Projeto.h Sonda.h CalculadorDeDesloc.h DadosDeEntrada.h LeitorDeDados.h
	g++ -c -o main.o main.cpp

Testador.o: Testador.cpp Testador.h Projeto.h Sonda.h CalculadorDeDesloc.h DadosDeEntrada.h LeitorDeDados.h
	g++ -c -o Testador.o Testador.cpp

Projeto.o: Projeto.cpp Testador.h Projeto.h Sonda.h CalculadorDeDesloc.h DadosDeEntrada.h LeitorDeDados.h
	g++ -c -o Projeto.o Projeto.cpp

Sonda.o: Sonda.cpp Testador.h Projeto.h Sonda.h CalculadorDeDesloc.h DadosDeEntrada.h LeitorDeDados.h
	g++ -c -o Sonda.o Sonda.cpp

CalculadorDeDesloc.o: CalculadorDeDesloc.cpp Testador.h Projeto.h Sonda.h CalculadorDeDesloc.h DadosDeEntrada.h LeitorDeDados.h
	g++ -c -o CalculadorDeDesloc.o CalculadorDeDesloc.cpp

DadosDeEntrada.o: DadosDeEntrada.cpp Testador.h Projeto.h Sonda.h CalculadorDeDesloc.h DadosDeEntrada.h LeitorDeDados.h
	g++ -c -o DadosDeEntrada.o DadosDeEntrada.cpp

LeitorDeDados.o: LeitorDeDados.cpp Testador.h Projeto.h Sonda.h CalculadorDeDesloc.h DadosDeEntrada.h LeitorDeDados.h
	g++ -c -o LeitorDeDados.o LeitorDeDados.cpp

clean:
	rm -rf *.o *~ metaheuristicas
