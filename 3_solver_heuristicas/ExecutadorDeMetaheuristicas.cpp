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
#include "ExecutadorDeMetaheuristicas.h"

ExecutadorDeMetaheuristicas::ExecutadorDeMetaheuristicas()
{
    this->_estrutura = 1;
    this->_modoRealoc = 1;
    this->_criterio = 1;
    this->_alpha = 0.9;
    this->_modoBusca = 14;
    this->_modoPerturba = 13;
    this->_nivelPerturba = 20;
}

ExecutadorDeMetaheuristicas::ExecutadorDeMetaheuristicas(int estrutura, int modoRealoc, int criterio, double alpha, int modoBusca, 
                                                         int modoPerturba, int nivelPerturba)
{
    this->_estrutura = estrutura;
    this->_modoRealoc = modoRealoc;
    this->_criterio = criterio;
    this->_alpha = alpha;
    this->_modoBusca = modoBusca;
    this->_modoPerturba = modoPerturba;
    this->_nivelPerturba = nivelPerturba;
}

std::tuple<int, std::map<Sonda, std::vector<Alocacao>>, double, double, int> ExecutadorDeMetaheuristicas::multStartHeuristic(DadosDeEntrada dataset, int nIter, int modoDebug)
{
    ConstrutorHeuristico construtor{this->_alpha, this->_criterio, this->_estrutura, this->_modoRealoc};

    // inicializa bests e constroi solução inicial
    long long bestTempo;
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap;
    double bestFitness;
    double bestGastos;
    int bestTotalFree;
    std::tie(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree) = construtor.ConstruirSolucao(dataset, modoDebug);

    // inicializa vetor de alphas
    std::vector<double> alphas;
    alphas.push_back(0.99);
    alphas.push_back(0.9);
    alphas.push_back(0.8);
    alphas.push_back(0.7);
    alphas.push_back(0.6);
    alphas.push_back(0.5);

    // inicializa valores intermediários
    long long newTempo;
    std::map<Sonda, std::vector<Alocacao>> newAlocsMap;
    double newFitness;
    double newGastos;
    int newTotalFree;

    int count = 0;
    while (count < nIter)
    {
        count++;

        // escolhe alpha
        int alphaIdx = rand() % alphas.size();
        double alpha = *std::next(alphas.begin(), alphaIdx);
        construtor.setAlpha(alpha);

        // constroi nova solução
        std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = construtor.ConstruirSolucao(dataset, modoDebug);

        // se for melhor que best, substitui
        if (newFitness > bestFitness)
        {
            bestAlocsMap = newAlocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;
        }
    }
    return std::make_tuple(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<int, std::map<Sonda, std::vector<Alocacao>>, double, double, int> ExecutadorDeMetaheuristicas::GRASP(DadosDeEntrada dataset,
                                                                                                                int nIter, int modoDebug)
{
    ConstrutorHeuristico construtor{this->_alpha, this->_criterio, this->_estrutura, this->_modoRealoc};
    MovimentadorEmVizinhancas movimentador{};

    // inicializa bests e constroi solução inicial
    long long bestTempo;
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap;
    double bestFitness;
    double bestGastos;
    int bestTotalFree;
    std::tie(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree) = construtor.ConstruirSolucao(dataset, modoDebug);

    // inicializa vetor de alphas
    std::vector<double> alphas;
    alphas.push_back(0.99);
    alphas.push_back(0.9);
    alphas.push_back(0.8);
    alphas.push_back(0.7);
    alphas.push_back(0.6);
    alphas.push_back(0.5);

    // inicializa valores intermediários
    long long newTempo;
    std::map<Sonda, std::vector<Alocacao>> newAlocsMap;
    double newFitness;
    double newGastos;
    int newTotalFree;

    int count = 0;
    while (count < nIter)
    {
        count++;

        // escolhe alpha
        int alphaIdx = rand() % alphas.size();
        double alpha = *std::next(alphas.begin(), alphaIdx);
        construtor.setAlpha(alpha);

        // constroi nova solução
        std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = construtor.ConstruirSolucao(dataset, modoDebug);

        // realiza busca local
        std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaLocal(newAlocsMap, dataset, 
                                        this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug);

        // se for melhor que best, substitui
        if (newFitness > bestFitness)
        {
            bestAlocsMap = newAlocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;
        }
    }
    return std::make_tuple(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<int, std::map<Sonda, std::vector<Alocacao>>, double, double, int> ExecutadorDeMetaheuristicas::ILS(DadosDeEntrada dataset,
                                                                                                                int nIter, int modoDebug)
{
    ConstrutorHeuristico construtor{this->_alpha, this->_criterio, this->_estrutura, this->_modoRealoc};
    MovimentadorEmVizinhancas movimentador{};

    // inicializa bests e constroi solução inicial
    long long bestTempo;
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap;
    double bestFitness;
    double bestGastos;
    int bestTotalFree;
    std::tie(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree) = construtor.ConstruirSolucao(dataset, modoDebug);

    // realiza busca local
    std::tie(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree) = movimentador.buscaLocal(bestAlocsMap, dataset, 
                                             this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug);

    // inicializa vetor de alphas
    std::vector<double> alphas;
    alphas.push_back(0.99);
    alphas.push_back(0.9);
    alphas.push_back(0.8);
    alphas.push_back(0.7);
    alphas.push_back(0.6);
    alphas.push_back(0.5);

    // inicializa valores intermediários
    long long newTempo;
    std::map<Sonda, std::vector<Alocacao>> newAlocsMap = bestAlocsMap;
    double newFitness;
    double newGastos;
    int newTotalFree;

    int count = 0;
    while (count < nIter)
    {
        count++;

        // perturba solução
        newAlocsMap = movimentador.perturbaSolucao(newAlocsMap, dataset, this->_estrutura, this->_modoRealoc, 
                                                    this->_nivelPerturba, this->_modoPerturba, modoDebug);

        // realiza busca local
        std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaLocal(newAlocsMap, dataset, 
                                        this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug);

        // se for melhor que best, substitui
        if (newFitness > bestFitness)
        {
            bestAlocsMap = newAlocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;
        }
    }
    return std::make_tuple(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

