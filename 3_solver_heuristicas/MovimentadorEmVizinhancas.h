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
        std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> shift1x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc, 
                                                                 Alocacao alocacao1, Sonda sonda2, int modoDebug, double fitness, double gastos, int totalFree);
        std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> shift2x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2, Sonda sonda2, int modoDebug, double fitness, double gastos, int totalFree);
        std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> swap1x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2, int modoDebug, double fitness, double gastos, int totalFree);
        std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> swap2x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2, Alocacao alocacao3, int modoDebug, double fitness, double gastos, int totalFree);
        std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> swap2x2InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2, 
                                                                 Alocacao alocacao3, Alocacao alocacao4, int modoDebug, double fitness, double gastos, int totalFree);
        std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> reinsercao1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, int modoDebug, double fitness, double gastos, int totalFree);
        std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> reinsercao2InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2, int modoDebug, double fitness, double gastos, int totalFree);
        std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> inserirNovoFO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                             DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                             Sonda sonda1, Projeto projeto1, int modoDebug, double fitness, double gastos, int totalFree);
        std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> swap1x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                         DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                         Alocacao alocacao1, Projeto projeto1, int modoDebug, double fitness, double gastos, int totalFree);
        std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> swap2x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                         DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                         Alocacao alocacao1, Alocacao alocacao2, Projeto projeto1, int modoDebug, double fitness, double gastos, int totalFree);
        std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> swap1x2FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                         DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                         Alocacao alocacao1, Projeto projeto1, Projeto projeto2, int modoDebug, double fitness, double gastos, int totalFree);
        std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> swap2x2FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                         DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                         Alocacao alocacao1, Alocacao alocacao2, 
                                                         Projeto projeto1, Projeto projeto2, int modoDebug, double fitness, double gastos, int totalFree);

        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaShift1x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaShift2x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaSwap1x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaSwap2x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaSwap2x2InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaReinsercao1IntraRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaReinsercao2IntraRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaInserirNovoFO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaSwap1x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaSwap1x2FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaSwap2x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaSwap2x2FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaVND(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaRVND(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> buscaLocal(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int vizinhanca, int modoDebug);
        
        std::map<Sonda, std::vector<Alocacao>> perturbaShift1x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug);
        std::map<Sonda, std::vector<Alocacao>> perturbaShift2x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug);
        std::map<Sonda, std::vector<Alocacao>> perturbaSwap1x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug);
        std::map<Sonda, std::vector<Alocacao>> perturbaSwap2x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug);
        std::map<Sonda, std::vector<Alocacao>> perturbaSwap2x2InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug);
        std::map<Sonda, std::vector<Alocacao>> perturbaReinsercao1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug);
        std::map<Sonda, std::vector<Alocacao>> perturbaReinsercao2InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug);
        std::map<Sonda, std::vector<Alocacao>> perturbaInserirNovoFO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug);
        std::map<Sonda, std::vector<Alocacao>> perturbaSwap1x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug);
        std::map<Sonda, std::vector<Alocacao>> perturbaSwap2x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug);
        std::map<Sonda, std::vector<Alocacao>> perturbaSwap1x2FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug);
        std::map<Sonda, std::vector<Alocacao>> perturbaSwap2x2FO(std::map<Sonda, std::vector<Alocacao>> alocsMap,
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug);
        std::map<Sonda, std::vector<Alocacao>> perturbaAleatorio(std::map<Sonda, std::vector<Alocacao>> alocsMap,
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug);
        std::map<Sonda, std::vector<Alocacao>> perturbaSolucao(std::map<Sonda, std::vector<Alocacao>> alocsMap,
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, 
                                                                int k, int vizinhanca, int modoDebug);
};

#endif

