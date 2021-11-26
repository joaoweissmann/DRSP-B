// Copyright 2021 João Ricardo Weissmann Santos
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// File comments:
// 
// TODO

#ifndef SOLUCAO
#define SOLUCAO

#include <bits/stdc++.h>
#include "Sonda.h"
#include "Projeto.h"
#include "DadosDeEntrada.h"

// Class comments:
// 
// TODO
class Solucao
{
    private:
        // Variable comments:
        // 
        // TODO
        std::map<int, std::list<int>> _alocacoes;

        std::map<int, int> _mapProj2Inicio;
        std::map<int, int> _mapProj2Final;
        
        std::set<int, std::greater<int>> _projetosUsados;
        std::map<int, int> _mapProj2Sonda;

        std::map<int, int> _mapSonda2TotalFree;
        std::map<int, int> _mapSonda2MaxFree;

        double _fitness;
        double _custo;
        int _totalFree;
        int _totalSetup;
        int _maxFree;

        std::map<int, std::vector<int>> _candidatos;
        
        std::set<int, std::greater<int>> _sondasDisponiveis;
        
    public:
        // Function comments:
        // 
        // TODO
        Solucao(DadosDeEntrada);

        Solucao(DadosDeEntrada, std::map<int, std::list<int>>, std::map<int, int>, std::map<int, int>);

        std::map<int, std::list<int>> getAlocacoes();
        std::list<int> getAlocacoes(int);
        std::list<int> getAlocacoes(Sonda);
        int getAlocacao(int, int);
        int getAlocacao(Sonda, int);

        std::map<int, int> getMapProj2Inicio();
        int getInicioDeProjeto(int);
        int getInicioDeProjeto(Projeto);

        std::map<int, int> getMapProj2Final();
        int getFinalDeProjeto(int);
        int getFinalDeProjeto(Projeto);

        std::set<int, std::greater<int>> getProjetosUsados();
        bool getSeProjetoAlocado(int);
        bool getSeProjetoAlocado(Projeto);

        std::map<int, int> getMapProj2Sonda();
        int getSondaDeProjeto(int);
        int getSondaDeProjeto(Projeto);

        std::map<int, int> getMapSonda2TotalFree();
        int getTotalFree(int);
        int getTotalFree(Sonda);

        std::map<int, int> getMapSonda2MaxFree();
        int getMaxFree(int);
        int getMaxFree(Sonda);

        double getFitness();
        double getCusto();
        int getTotalFree();
        int getTotalSetup();
        int getMaxFree();

        std::map<int, std::vector<int>> getCandidatos();
        std::vector<int> getCandidatos(int);
        std::vector<int> getCandidatos(Sonda);
        
        std::set<int, std::greater<int>> getSondasDisponiveis();
        bool getSeSondaDisponivel(int);
        bool getSeSondaDisponivel(Sonda);

        void setAlocacoes(std::map<int, std::list<int>>);

        void setMapProj2Inicio(std::map<int, int>);
        void setInicioDeProjeto(Projeto);
        void setInicioDeProjeto(int);

        void setMapProj2Final(std::map<int, int>);
        void setFinalDeProjeto(Projeto);
        void setFinalDeProjeto(int);

        void inserirNoInicio(Sonda, Projeto, int, int);
        void inserirNoInicio(int, int, int, int);

        void inserirNoFinal(Sonda, Projeto, int, int);
        void inserirNoFinal(int, int, int, int);

        void inserirAposProjeto(Sonda, Projeto, Projeto, int, int);
        void inserirAposProjeto(int, int, int, int, int);

        void inserirAntesDeProjeto(Sonda, Projeto, Projeto, int, int);
        void inserirAntesDeProjeto(int, int, int, int, int);

        void inserirNoIndice(Sonda, int, Projeto, int, int);
        void inserirNoIndice(int, int, int, int, int);

        void removerProjeto(Sonda, Projeto);
        void removerProjeto(int, int);

        void removerPorIndice(Sonda, int);
        void removerPorIndice(int, int);

        void trocarProjetos(Sonda, Projeto, Projeto, int, int);
        void trocarProjetos(int, int, int, int, int);

        void print();
};

#endif
