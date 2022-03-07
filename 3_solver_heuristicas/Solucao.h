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

#ifndef SOLUCAO
#define SOLUCAO

#include <bits/stdc++.h>
#include "Alocacoes.h"
#include "AlocacoesVector.h"
#include "AlocacoesList.h"
#include "DadosDeEntrada.h"

class Solucao
{
    private:
        AlocacoesVector _alocsVector;
        AlocacoesList _alocsList;
        Alocacoes * _ptrAlocacoes;
        std::set<Projeto> _projetosAlocados;
        std::set<Projeto> _projetosNaoAlocados;
        std::map<Projeto, Alocacao> _mapProjeto2Alocacao;
        double _gastos;
        double _fitness;
        int _totalFree;
        int _deltaT;

    public:
        Solucao(int dataStructure, DadosDeEntrada dataset);
        Solucao(std::map<Sonda, std::vector<Alocacao>> alocacoesIn, int dataStructure, DadosDeEntrada dataset);

        std::set<Projeto> getProjetosAlocados();
        std::set<Projeto> getProjetosNaoAlocados();
        std::map<Projeto, Alocacao> getMapProjeto2Alocacao();
        double getGastos();
        double getFitness();
        int getTotalFree();
        std::map<Sonda, std::vector<Alocacao>> getAlocacoes();

        std::tuple<bool, int, Intervalo, int, int, int, int, int> buscarJanelaViavel(Sonda sonda, Projeto projeto, int modo);

        void inserirProjeto(Sonda sonda, Projeto projeto, int posicaoAloc, Intervalo intervalo, 
                                     int prevMinus, int currMinus, int currPlus, int nextPlus, int caso);
        
        bool removerProjeto(Sonda sonda, Projeto projeto, Intervalo intervalo);

        void print();
};

#endif
