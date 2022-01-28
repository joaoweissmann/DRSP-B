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

#ifndef ALOCACOES_VECTOR
#define ALOCACOES_VECTOR

#include <bits/stdc++.h>
#include "Alocacoes.h"
// #include "AlocacoesList.h" // TODO: não pode?

class AlocacoesVector: public Alocacoes
{
    private:
        std::map<Sonda, std::vector<Alocacao>> _alocacoes;

    public:
        AlocacoesVector(std::set<Sonda>);
        AlocacoesVector(std::map<Sonda, std::vector<Alocacao>>);
        AlocacoesVector(std::map<Sonda, std::list<Alocacao>>);
        // AlocacoesVector copyFrom(AlocacoesVector);
        // AlocacoesVector copyFrom(AlocacoesList);
        void print();

        int getNSondas();
        std::set<Sonda> getSondas();
        
        std::map<Sonda, std::vector<Alocacao>> getAlocacoes();
        std::vector<Alocacao> getAlocacoes(Sonda);
        /*
        int getNAlocacoes(Sonda);
        Alocacao getAlocacao(Sonda, int);
        Alocacao getAlocacao(Sonda, Projeto);
        int getAlocacaoIndex(Sonda, Projeto);

        void setAlocacoes(std::map<Sonda, std::vector<Alocacao>>);
        void setAlocacoes(Sonda, std::vector<Alocacao>);

        void setAlocacao(Sonda, int, Alocacao);
        void setAlocacao(Sonda, Projeto, Alocacao);

        int getDesloc(Sonda, int);
        
        int getGapLeft(Sonda, int);
        int getGapRight(Sonda, int);

        int getFolgaLeft(Sonda, int);
        int getFolgaRight(Sonda, int);

        bool isPrimeiraAlocacao(Sonda, Projeto);
        bool isUltimaAlocacao(Sonda, Projeto);
        bool isEmpty(Sonda);
        bool isFeasible(Alocacao);

        std::tuple<bool, int, Intervalo, int, int, int, int> buscarJanelaViavel(Sonda, Projeto);

        std::tuple<> inserirProjeto(Sonda, Projeto, Intervalo, int, int, int, int, int);

        std::tuple<> removerProjeto(Sonda, int);

        std::tuple<> trocarProjetos(Sonda, int, Sonda, int);
        */
};

#endif

