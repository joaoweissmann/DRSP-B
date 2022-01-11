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
        
        // TODO: ajustar estrutura de dados
        // TODO: mudar para elementos da classe Alocacao
        // TODO: Como um set/map checa/compara objetos de uma classe definida pelo usuário?
        std::unordered_map<Sonda, std::list<Projeto>> _alocacoes;

        // TODO: ajustar estrutura de dados
        // TODO: Como um set/map checa/compara objetos de uma classe definida pelo usuário?
        std::unordered_set<Projeto> _projetosAlocados;

        // TODO: ajustar estrutura de dados
        std::vector<Projeto> _projetosNaoAlocados;

        // TODO: ajustar estrutura de dados
        std::unordered_set<int> _sondasDisponiveis;
        
        std::map<Sonda, int> _mapSonda2TotalFree;
        std::map<Sonda, int> _mapSonda2MaxFree;

        double _fitness;
        double _custo;
        int _totalFree;
        int _totalSetup;
        int _maxFree;

        bool feasible;
        
    public:
        // Function comments:
        // 
        // TODO
        Solucao(DadosDeEntrada);

        Solucao(DadosDeEntrada, std::map<int, std::list<int>>, std::map<int, int>, std::map<int, int>);

        // TODO: gets e sets

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
