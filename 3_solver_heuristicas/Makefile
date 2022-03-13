# Copyright 2021 João Ricardo Weissmann Santos
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

objects = main.o Testador.o Projeto.o Sonda.o CalculadorDeDesloc.o DadosDeEntrada.o LeitorDeDados.o Intervalo.o \
Alocacao.o AlocacoesVector.o AlocacoesList.o Solucao.o ConstrutorHeuristico.o VerificadorDeSolucao.o

headers = Testador.h Projeto.h Sonda.h CalculadorDeDesloc.h DadosDeEntrada.h LeitorDeDados.h Intervalo.h Alocacao.h Alocacoes.h \
AlocacoesVector.h AlocacoesList.h Solucao.h ConstrutorHeuristico.h VerificadorDeSolucao.h

CFLAGS = -std=c++11 -O2 # -Wall

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

Intervalo.o: Intervalo.cpp $(headers)
	g++ -c -o Intervalo.o $(CFLAGS) Intervalo.cpp

Alocacao.o: Alocacao.cpp $(headers)
	g++ -c -o Alocacao.o $(CFLAGS) Alocacao.cpp

AlocacoesVector.o: AlocacoesVector.cpp $(headers)
	g++ -c -o AlocacoesVector.o $(CFLAGS) AlocacoesVector.cpp

AlocacoesList.o: AlocacoesList.cpp $(headers)
	g++ -c -o AlocacoesList.o $(CFLAGS) AlocacoesList.cpp

Solucao.o: Solucao.cpp $(headers)
	g++ -c -o Solucao.o $(CFLAGS) Solucao.cpp

ConstrutorHeuristico.o: ConstrutorHeuristico.cpp $(headers)
	g++ -c -o ConstrutorHeuristico.o $(CFLAGS) ConstrutorHeuristico.cpp

VerificadorDeSolucao.o: VerificadorDeSolucao.cpp $(headers)
	g++ -c -o VerificadorDeSolucao.o $(CFLAGS) VerificadorDeSolucao.cpp

clean:
	rm -rf *.o *~ metaheuristicas

