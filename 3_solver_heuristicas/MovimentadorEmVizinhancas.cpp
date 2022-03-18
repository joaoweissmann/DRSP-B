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

#include <bits/stdc++.h>
#include "MovimentadorEmVizinhancas.h"

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::shift1x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, DadosDeEntrada dataset, 
                                                  int estrutura, int modoRealoc, Alocacao alocacao1, Sonda sonda2)
{
    Sonda sonda1 = alocacao1.getSonda();
    Projeto projeto1 = alocacao1.getProjeto();
    Intervalo intervalo1 = alocacao1.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // remove projeto
    bool removed = false;
    removed = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1);
    if (removed)
    {
        // faz busca
        bool alocExiste = false;
        int posicaoAloc = -1;
        Intervalo intervaloAloc{};
        int prevMinus = 0;
        int currMinus = 0;
        int currPlus = 0;
        int nextPlus = 0;
        int caso = 0;
        std::tie(alocExiste, posicaoAloc, intervaloAloc, prevMinus, currMinus, currPlus, nextPlus, caso) = 
                                                    solucaoLocal.buscarJanelaViavel(sonda2, projeto1, modoRealoc);
        // se viável, insere     
        if (alocExiste)
        {
            solucaoLocal.inserirProjeto(sonda2, projeto1, posicaoAloc, intervaloAloc, prevMinus, 
                                            currMinus, currPlus, nextPlus, caso);
        }
    }
    std::map<Sonda, std::vector<Alocacao>> alocsReturn = solucaoLocal.getAlocacoes();
    return alocsReturn;
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::shift2x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                         DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                         Alocacao alocacao1, Alocacao alocacao2, Sonda sonda2)
{
    Sonda sonda1 = alocacao1.getSonda();
    Projeto projeto1 = alocacao1.getProjeto();
    Intervalo intervalo1 = alocacao1.getIntervalo();
    Projeto projeto2 = alocacao2.getProjeto();
    Intervalo intervalo2 = alocacao2.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // remover projeto1 da sonda1
    bool removed1 = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1);
    
    // remover projeto2 da sonda1
    bool removed2 = solucaoLocal.removerProjeto(sonda1, projeto2, intervalo2);
    
    if (removed1 && removed2)
    {
        // inserir projeto1 na sonda2
        // faz busca
        bool alocExiste1 = false;
        int posicaoAloc1 = -1;
        Intervalo intervaloAloc1{};
        int prevMinus1 = 0;
        int currMinus1 = 0;
        int currPlus1 = 0;
        int nextPlus1 = 0;
        int caso1 = 0;
        std::tie(alocExiste1, posicaoAloc1, intervaloAloc1, prevMinus1, currMinus1, currPlus1, nextPlus1, caso1) = 
                                                    solucaoLocal.buscarJanelaViavel(sonda2, projeto1, modoRealoc);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda2
            solucaoLocal.inserirProjeto(sonda2, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1);
            
            // inserir projeto2 na sonda2
            // faz busca
            bool alocExiste2 = false;
            int posicaoAloc2 = -1;
            Intervalo intervaloAloc2{};
            int prevMinus2 = 0;
            int currMinus2 = 0;
            int currPlus2 = 0;
            int nextPlus2 = 0;
            int caso2 = 0;
            std::tie(alocExiste2, posicaoAloc2, intervaloAloc2, prevMinus2, currMinus2, currPlus2, nextPlus2, caso2) = 
                                                        solucaoLocal.buscarJanelaViavel(sonda2, projeto2, modoRealoc);
            if (alocExiste2)
            {
                // inserir projeto2 na sonda2
                solucaoLocal.inserirProjeto(sonda2, projeto2, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                            currMinus2, currPlus2, nextPlus2, caso2);
            }
        }
    }
    std::map<Sonda, std::vector<Alocacao>> alocsReturn = solucaoLocal.getAlocacoes();
    return alocsReturn;
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::swap1x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2)
{
    Sonda sonda1 = alocacao1.getSonda();
    Projeto projeto1 = alocacao1.getProjeto();
    Intervalo intervalo1 = alocacao1.getIntervalo();
    Sonda sonda2 = alocacao2.getSonda();
    Projeto projeto2 = alocacao2.getProjeto();
    Intervalo intervalo2 = alocacao2.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // remover projeto1 da sonda1
    bool removed1 = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1);

    // remover projeto2 da sonda2
    bool removed2 = solucaoLocal.removerProjeto(sonda2, projeto2, intervalo2);

    if (removed1 && removed2)
    {
        // inserir projeto1 na sonda2
        // faz busca
        bool alocExiste1 = false;
        int posicaoAloc1 = -1;
        Intervalo intervaloAloc1{};
        int prevMinus1 = 0;
        int currMinus1 = 0;
        int currPlus1 = 0;
        int nextPlus1 = 0;
        int caso1 = 0;
        std::tie(alocExiste1, posicaoAloc1, intervaloAloc1, prevMinus1, currMinus1, currPlus1, nextPlus1, caso1) = 
                                                    solucaoLocal.buscarJanelaViavel(sonda2, projeto1, modoRealoc);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda2
            solucaoLocal.inserirProjeto(sonda2, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1);
            
            // inserir projeto2 na sonda1
            // faz busca
            bool alocExiste2 = false;
            int posicaoAloc2 = -1;
            Intervalo intervaloAloc2{};
            int prevMinus2 = 0;
            int currMinus2 = 0;
            int currPlus2 = 0;
            int nextPlus2 = 0;
            int caso2 = 0;
            std::tie(alocExiste2, posicaoAloc2, intervaloAloc2, prevMinus2, currMinus2, currPlus2, nextPlus2, caso2) = 
                                                        solucaoLocal.buscarJanelaViavel(sonda1, projeto2, modoRealoc);
            if (alocExiste2)
            {
                // inserir projeto2 na sonda1
                solucaoLocal.inserirProjeto(sonda1, projeto2, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                            currMinus2, currPlus2, nextPlus2, caso2);
            }
        }
    }
    std::map<Sonda, std::vector<Alocacao>> alocsReturn = solucaoLocal.getAlocacoes();
    return alocsReturn;
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::swap2x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2, Alocacao alocacao3)
{
    Sonda sonda1 = alocacao1.getSonda();
    Sonda sonda2 = alocacao3.getSonda();
    Projeto projeto1 = alocacao1.getProjeto();
    Projeto projeto2 = alocacao2.getProjeto();
    Projeto projeto3 = alocacao3.getProjeto();
    Intervalo intervalo1 = alocacao1.getIntervalo();
    Intervalo intervalo2 = alocacao2.getIntervalo();
    Intervalo intervalo3 = alocacao3.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // remover projeto1 da sonda1
    bool removed1 = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1);

    // remover projeto2 da sonda1
    bool removed2 = solucaoLocal.removerProjeto(sonda1, projeto2, intervalo2);

    // remover projeto3 da sonda2
    bool removed3 = solucaoLocal.removerProjeto(sonda2, projeto3, intervalo3);

    if (removed1 && removed2 && removed3)
    {
        // inserir projeto1 na sonda2
        // faz busca
        bool alocExiste1 = false;
        int posicaoAloc1 = -1;
        Intervalo intervaloAloc1{};
        int prevMinus1 = 0;
        int currMinus1 = 0;
        int currPlus1 = 0;
        int nextPlus1 = 0;
        int caso1 = 0;
        std::tie(alocExiste1, posicaoAloc1, intervaloAloc1, prevMinus1, currMinus1, currPlus1, nextPlus1, caso1) = 
                                                    solucaoLocal.buscarJanelaViavel(sonda2, projeto1, modoRealoc);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda2
            solucaoLocal.inserirProjeto(sonda2, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1);

            // inserir projeto2 na sonda2
            // faz busca
            bool alocExiste2 = false;
            int posicaoAloc2 = -1;
            Intervalo intervaloAloc2{};
            int prevMinus2 = 0;
            int currMinus2 = 0;
            int currPlus2 = 0;
            int nextPlus2 = 0;
            int caso2 = 0;
            std::tie(alocExiste2, posicaoAloc2, intervaloAloc2, prevMinus2, currMinus2, currPlus2, nextPlus2, caso2) = 
                                                        solucaoLocal.buscarJanelaViavel(sonda2, projeto2, modoRealoc);
            if (alocExiste2)
            {
                // inserir projeto2 na sonda2
                solucaoLocal.inserirProjeto(sonda2, projeto2, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                        currMinus2, currPlus2, nextPlus2, caso2);

                // inserir projeto3 na sonda1
                // faz busca
                bool alocExiste3 = false;
                int posicaoAloc3 = -1;
                Intervalo intervaloAloc3{};
                int prevMinus3 = 0;
                int currMinus3 = 0;
                int currPlus3 = 0;
                int nextPlus3 = 0;
                int caso3 = 0;
                std::tie(alocExiste3, posicaoAloc3, intervaloAloc3, prevMinus3, currMinus3, currPlus3, nextPlus3, caso3) = 
                                                            solucaoLocal.buscarJanelaViavel(sonda1, projeto3, modoRealoc);
                if (alocExiste3)
                {
                    // inserir projeto3 na sonda1
                    solucaoLocal.inserirProjeto(sonda1, projeto3, posicaoAloc3, intervaloAloc3, prevMinus3, 
                                        currMinus3, currPlus3, nextPlus3, caso3);
                }
            }
        }
    }
    std::map<Sonda, std::vector<Alocacao>> alocsReturn = solucaoLocal.getAlocacoes();
    return alocsReturn;
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::swap2x2InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2, 
                                                                 Alocacao alocacao3, Alocacao alocacao4)
{
    Sonda sonda1 = alocacao1.getSonda();
    Sonda sonda2 = alocacao3.getSonda();
    Projeto projeto1 = alocacao1.getProjeto();
    Projeto projeto2 = alocacao2.getProjeto();
    Projeto projeto3 = alocacao3.getProjeto();
    Projeto projeto4 = alocacao4.getProjeto();
    Intervalo intervalo1 = alocacao1.getIntervalo();
    Intervalo intervalo2 = alocacao2.getIntervalo();
    Intervalo intervalo3 = alocacao3.getIntervalo();
    Intervalo intervalo4 = alocacao4.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // remover projeto1 da sonda1
    bool removed1 = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1);

    // remover projeto2 da sonda1
    bool removed2 = solucaoLocal.removerProjeto(sonda1, projeto2, intervalo2);

    // remover projeto3 da sonda2
    bool removed3 = solucaoLocal.removerProjeto(sonda2, projeto3, intervalo3);

    // remover projeto4 da sonda2
    bool removed4 = solucaoLocal.removerProjeto(sonda2, projeto4, intervalo3);

    if (removed1 && removed2 && removed3 && removed4)
    {
        // inserir projeto1 na sonda2
        // faz busca
        bool alocExiste1 = false;
        int posicaoAloc1 = -1;
        Intervalo intervaloAloc1{};
        int prevMinus1 = 0;
        int currMinus1 = 0;
        int currPlus1 = 0;
        int nextPlus1 = 0;
        int caso1 = 0;
        std::tie(alocExiste1, posicaoAloc1, intervaloAloc1, prevMinus1, currMinus1, currPlus1, nextPlus1, caso1) = 
                                                    solucaoLocal.buscarJanelaViavel(sonda2, projeto1, modoRealoc);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda2
            solucaoLocal.inserirProjeto(sonda2, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1);

            // inserir projeto2 na sonda2
            // faz busca
            bool alocExiste2 = false;
            int posicaoAloc2 = -1;
            Intervalo intervaloAloc2{};
            int prevMinus2 = 0;
            int currMinus2 = 0;
            int currPlus2 = 0;
            int nextPlus2 = 0;
            int caso2 = 0;
            std::tie(alocExiste2, posicaoAloc2, intervaloAloc2, prevMinus2, currMinus2, currPlus2, nextPlus2, caso2) = 
                                                        solucaoLocal.buscarJanelaViavel(sonda2, projeto2, modoRealoc);
            if (alocExiste2)
            {
                // inserir projeto2 na sonda2
                solucaoLocal.inserirProjeto(sonda2, projeto2, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                        currMinus2, currPlus2, nextPlus2, caso2);

                // inserir projeto3 na sonda1
                // faz busca
                bool alocExiste3 = false;
                int posicaoAloc3 = -1;
                Intervalo intervaloAloc3{};
                int prevMinus3 = 0;
                int currMinus3 = 0;
                int currPlus3 = 0;
                int nextPlus3 = 0;
                int caso3 = 0;
                std::tie(alocExiste3, posicaoAloc3, intervaloAloc3, prevMinus3, currMinus3, currPlus3, nextPlus3, caso3) = 
                                                            solucaoLocal.buscarJanelaViavel(sonda1, projeto3, modoRealoc);
                if (alocExiste3)
                {
                    // inserir projeto3 na sonda1
                    solucaoLocal.inserirProjeto(sonda1, projeto3, posicaoAloc3, intervaloAloc3, prevMinus3, 
                                        currMinus3, currPlus3, nextPlus3, caso3);
                    
                    // inserir projeto4 na sonda1
                    // faz busca
                    bool alocExiste4 = false;
                    int posicaoAloc4 = -1;
                    Intervalo intervaloAloc4{};
                    int prevMinus4 = 0;
                    int currMinus4 = 0;
                    int currPlus4 = 0;
                    int nextPlus4 = 0;
                    int caso4 = 0;
                    std::tie(alocExiste4, posicaoAloc4, intervaloAloc4, prevMinus4, currMinus4, currPlus4, nextPlus4, caso4) = 
                                                                solucaoLocal.buscarJanelaViavel(sonda1, projeto4, modoRealoc);
                    if (alocExiste4)
                    {
                        // inserir projeto4 na sonda1
                        solucaoLocal.inserirProjeto(sonda1, projeto4, posicaoAloc4, intervaloAloc4, prevMinus4, 
                                        currMinus4, currPlus4, nextPlus4, caso4);
                    }
                }
            }
        }
    }
    std::map<Sonda, std::vector<Alocacao>> alocsReturn = solucaoLocal.getAlocacoes();
    return alocsReturn;
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaShift1x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, DadosDeEntrada dataset, 
                                                  int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações    
    for (std::set<Sonda>::iterator itS1 = sondas.begin(); itS1 != sondas.end(); ++itS1)
    {
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1 = alocsMap[sonda1].begin(); itA1 != alocsMap[sonda1].end(); ++itA1)
        {
            Alocacao alocacao1 = *itA1;
            Projeto projeto1 = (*itA1).getProjeto();
            Intervalo intervalo1 = (*itA1).getIntervalo();
            for (std::set<Sonda>::iterator itS2 = sondas.begin(); itS2 != sondas.end(); ++itS2)
            {
                Sonda sonda2 = *itS2;
                if (sonda1 == sonda2)
                {
                    continue;
                }

                // realiza movimento
                std::map<Sonda, std::vector<Alocacao>> alocsMapAlt = shift1x0InterRota(alocsMap, dataset, estrutura, 
                                                                                       modoRealoc, alocacao1, sonda2);

                // instancia solução local
                Solucao solucaoLocal{alocsMapAlt, estrutura, dataset};

                // se for melhor que best
                if (solucaoLocal.getFitness() >= bestFitness)
                {
                    if (solucaoLocal.getTotalFree() > bestTotalFree)
                    {
                        bestAlocsMap = solucaoLocal.getAlocacoes();
                        bestFitness = solucaoLocal.getFitness();
                        bestGastos = solucaoLocal.getGastos();
                        bestTotalFree = solucaoLocal.getTotalFree();
                    }
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaShift2x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            Alocacao alocacao1 = *itA1;
            Projeto projeto1 = (*itA1).getProjeto();
            Intervalo intervalo1 = (*itA1).getIntervalo();
            for (std::vector<Alocacao>::iterator itA2=alocsMap[sonda1].begin(); itA2!=alocsMap[sonda1].end(); ++itA2)
            {
                Alocacao alocacao2 = *itA2;
                Projeto projeto2 = (*itA2).getProjeto();
                Intervalo intervalo2 = (*itA2).getIntervalo();
                if (projeto1 == projeto2)
                {
                    continue;
                }
                for (std::set<Sonda>::iterator itS2=sondas.begin(); itS2!=sondas.end(); ++itS2)
                {
                    Sonda sonda2 = *itS2;
                    if (sonda1 == sonda2)
                    {
                        continue;
                    }
                    // realiza movimento
                    std::map<Sonda, std::vector<Alocacao>> alocsMapAlt = shift2x0InterRota(alocsMap, dataset, estrutura, 
                                                                                    modoRealoc, alocacao1, alocacao2, sonda2);

                    // instancia solução local
                    Solucao solucaoLocal{alocsMapAlt, estrutura, dataset};

                    // se for melhor que best
                    if (solucaoLocal.getFitness() >= bestFitness)
                    {
                        if (solucaoLocal.getTotalFree() > bestTotalFree)
                        {
                            bestAlocsMap = solucaoLocal.getAlocacoes();
                            bestFitness = solucaoLocal.getFitness();
                            bestGastos = solucaoLocal.getGastos();
                            bestTotalFree = solucaoLocal.getTotalFree();
                        }
                    }
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaSwap1x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            Alocacao alocacao1 = *itA1;
            for (std::set<Sonda>::iterator itS2=sondas.begin(); itS2!=sondas.end(); ++itS2)
            {
                Sonda sonda2 = *itS2;
                if (alocsMap[sonda2].empty())
                {
                    continue;
                }
                if (sonda1 == sonda2)
                {
                    continue;
                }
                for (std::vector<Alocacao>::iterator itA2=alocsMap[sonda2].begin(); itA2!=alocsMap[sonda2].end(); ++itA2)
                {
                    Alocacao alocacao2 = *itA2;

                    // realiza movimento
                    std::map<Sonda, std::vector<Alocacao>> alocsMapAlt = swap1x1InterRota(alocsMap, dataset, estrutura, 
                                                                                        modoRealoc, alocacao1, alocacao2);

                    // instancia solução local
                    Solucao solucaoLocal{alocsMapAlt, estrutura, dataset};

                    // se for melhor que best
                    if (solucaoLocal.getFitness() >= bestFitness)
                    {
                        if (solucaoLocal.getTotalFree() > bestTotalFree)
                        {
                            bestAlocsMap = solucaoLocal.getAlocacoes();
                            bestFitness = solucaoLocal.getFitness();
                            bestGastos = solucaoLocal.getGastos();
                            bestTotalFree = solucaoLocal.getTotalFree();
                        }
                    }
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaSwap2x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            Alocacao alocacao1 = *itA1;
            for (std::vector<Alocacao>::iterator itA2=alocsMap[sonda1].begin(); itA2!=alocsMap[sonda1].end(); ++itA2)
            {
                Alocacao alocacao2 = *itA2;
                if (alocacao1 == alocacao2)
                {
                    continue;
                }
                for (std::set<Sonda>::iterator itS2=sondas.begin(); itS2!=sondas.end(); ++itS2)
                {
                    Sonda sonda2 = *itS2;
                    if (alocsMap[sonda2].empty())
                    {
                        continue;
                    }
                    for (std::vector<Alocacao>::iterator itA3=alocsMap[sonda2].begin(); itA3!=alocsMap[sonda2].end(); ++itA3)
                    {
                        Alocacao alocacao3 = *itA3;

                        // realiza movimento
                        std::map<Sonda, std::vector<Alocacao>> alocsMapAlt = swap2x1InterRota(alocsMap, dataset, estrutura, 
                                                                                            modoRealoc, 
                                                                                            alocacao1, alocacao2, alocacao3);

                        // instancia solução local
                        Solucao solucaoLocal{alocsMapAlt, estrutura, dataset};

                        // se for melhor que best
                        if (solucaoLocal.getFitness() >= bestFitness)
                        {
                            if (solucaoLocal.getTotalFree() > bestTotalFree)
                            {
                                bestAlocsMap = solucaoLocal.getAlocacoes();
                                bestFitness = solucaoLocal.getFitness();
                                bestGastos = solucaoLocal.getGastos();
                                bestTotalFree = solucaoLocal.getTotalFree();
                            }
                        }
                    }
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaSwap2x2InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            Alocacao alocacao1 = *itA1;
            for (std::vector<Alocacao>::iterator itA2=alocsMap[sonda1].begin(); itA2!=alocsMap[sonda1].end(); ++itA2)
            {
                Alocacao alocacao2 = *itA2;
                if (alocacao1 == alocacao2)
                {
                    continue;
                }
                for (std::set<Sonda>::iterator itS2=sondas.begin(); itS2!=sondas.end(); ++itS2)
                {
                    Sonda sonda2 = *itS2;
                    if (alocsMap[sonda2].empty())
                    {
                        continue;
                    }
                    for (std::vector<Alocacao>::iterator itA3=alocsMap[sonda2].begin(); itA3!=alocsMap[sonda2].end(); ++itA3)
                    {
                        Alocacao alocacao3 = *itA3;
                        for (std::vector<Alocacao>::iterator itA4=alocsMap[sonda2].begin(); itA4!=alocsMap[sonda2].end(); ++itA4)
                        {
                            Alocacao alocacao4 = *itA4;
                            if (alocacao3 == alocacao4)
                            {
                                continue;
                            }

                            // realiza movimento
                            std::map<Sonda, std::vector<Alocacao>> alocsMapAlt = swap2x2InterRota(alocsMap, dataset, estrutura, 
                                                                                                modoRealoc, 
                                                                                                alocacao1, alocacao2, 
                                                                                                alocacao3, alocacao4);

                            // instancia solução local
                            Solucao solucaoLocal{alocsMapAlt, estrutura, dataset};

                            // se for melhor que best
                            if (solucaoLocal.getFitness() >= bestFitness)
                            {
                                if (solucaoLocal.getTotalFree() > bestTotalFree)
                                {
                                    bestAlocsMap = solucaoLocal.getAlocacoes();
                                    bestFitness = solucaoLocal.getFitness();
                                    bestGastos = solucaoLocal.getGastos();
                                    bestTotalFree = solucaoLocal.getTotalFree();
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaReinsercao1IntraRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações    
    // TODO

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaReinsercao2IntraRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações    
    // TODO

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaInserirNovoFO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações    
    // TODO

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaSwap1x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações    
    // TODO

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaSwap1x2FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações    
    // TODO

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaSwap2x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações    
    // TODO

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaSwap2x2FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações    
    // TODO

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

