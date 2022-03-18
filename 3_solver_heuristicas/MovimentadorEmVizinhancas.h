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

#ifndef MOVIMENTADOR_EM_VIZINHANCAS
#define MOVIMENTADOR_EM_VIZINHANCAS

#include <bits/stdc++.h>
#include "Solucao.h"

class MovimentadorEmVizinhancas
{
    public:
        std::map<Sonda, std::vector<Alocacao>> shift1x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc, 
                                                                 Alocacao alocacao1, Sonda sonda2);
        std::map<Sonda, std::vector<Alocacao>> shift2x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2, Sonda sonda2);
        std::map<Sonda, std::vector<Alocacao>> swap1x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2);
        std::map<Sonda, std::vector<Alocacao>> swap2x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2, Alocacao alocacao3);
        std::map<Sonda, std::vector<Alocacao>> swap2x2InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2, 
                                                                 Alocacao alocacao3, Alocacao alocacao4);
        std::map<Sonda, std::vector<Alocacao>> reinsercao1InterRota();
        std::map<Sonda, std::vector<Alocacao>> reinsercao2InterRota();
        std::map<Sonda, std::vector<Alocacao>> inserirNovoFO();
        std::map<Sonda, std::vector<Alocacao>> swap1x1FO();
        std::map<Sonda, std::vector<Alocacao>> swap2x1FO();
        std::map<Sonda, std::vector<Alocacao>> swap1x2FO();
        std::map<Sonda, std::vector<Alocacao>> swap2x2FO();

        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaShift1x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaShift2x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaSwap1x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaSwap2x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaSwap2x2InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaReinsercao1IntraRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaReinsercao2IntraRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaInserirNovoFO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaSwap1x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaSwap1x2FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaSwap2x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaSwap2x2FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT);
        
        void perturbaShift1x0InterRota();
        void perturbaShift2x0InterRota();
        void perturbaSwap1x1InterRota();
        void perturbaSwap2x1InterRota();
        void perturbaSwap2x2InterRota();
        void perturbaReinsercao1InterRota();
        void perturbaReinsercao2InterRota();
        void perturbaInserirNovoFO();
        void perturbaSwap1x1FO();
        void perturbaSwap2x1FO();
        void perturbaSwap1x2FO();
        void perturbaSwap2x2FO();
};

#endif

