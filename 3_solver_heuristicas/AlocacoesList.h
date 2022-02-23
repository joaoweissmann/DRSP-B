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

#ifndef ALOCACOES_LIST
#define ALOCACOES_LIST

#include <bits/stdc++.h>
#include "Alocacoes.h"
#include "CalculadorDeDesloc.h"
// #include "AlocacoesVector.h" // TODO: não pode?

class AlocacoesList: public Alocacoes
{
    private:
        std::map<Sonda, std::list<Alocacao>> _alocacoes;
    
    public:
        AlocacoesList(std::set<Sonda>);
        AlocacoesList(std::map<Sonda, std::list<Alocacao>>);
        AlocacoesList(std::map<Sonda, std::vector<Alocacao>>);
        // AlocacoesList copyFrom(AlocacoesList);
        // AlocacoesList copyFrom(AlocacoesVector);
        void print();

        int getNSondas();
        std::set<Sonda> getSondas();
        
        std::map<Sonda, std::vector<Alocacao>> getAlocacoes();
        std::vector<Alocacao> getAlocacoes(Sonda);
        
        int getNAlocacoes(Sonda);
        Alocacao getAlocacao(Sonda, int);
        Alocacao getAlocacao(Sonda, Projeto);
        int getAlocacaoIndex(Sonda, Projeto);
        
        void setAlocacoes(std::map<Sonda, std::vector<Alocacao>>);
        void setAlocacoes(Sonda, std::vector<Alocacao>);

        std::tuple<bool, int, Intervalo, int, int, int, int, int> buscarJanelaViavel(Sonda, Projeto, int);

        void inserirProjeto(Sonda, Projeto, int, Intervalo, int, int, int, int, int);

        bool removerProjeto(Sonda, Projeto);
};

#endif

