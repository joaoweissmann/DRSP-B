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

void ExecutadorDeMetaheuristicas::setAlpha(double alpha)
{
    this->_alpha = alpha;
}

void ExecutadorDeMetaheuristicas::setNivelPerturba(int nivelPerturba)
{
    this->_nivelPerturba = nivelPerturba;
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> ExecutadorDeMetaheuristicas::multStartHeuristic(DadosDeEntrada dataset, int nIter, int modoDebug, int nIterConverge)
{
    auto start = std::chrono::high_resolution_clock::now();

    ConstrutorHeuristico construtor{this->_alpha, this->_criterio, this->_estrutura, this->_modoRealoc};

    // inicializa bests e constrói solução inicial
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
    int countConverge = 0;
    while (count < nIter)
    {
        count++;

        auto stopPart = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopPart - start);
        long long tempoPart = duration.count();
        if (tempoPart >= 1800000)
        {
            break;
        }

        // escolhe critério
        int criterio = (rand() % 4) + 1;
        construtor.setCriterio(criterio);

        // escolhe alpha
        int alphaIdx = rand() % alphas.size();
        double alpha = *std::next(alphas.begin(), alphaIdx);
        construtor.setAlpha(alpha);

        // constroi nova solução
        std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = construtor.ConstruirSolucao(dataset, modoDebug);

        if ((int)newFitness >= 1.01 * (int)bestFitness) 
        {
            countConverge = 0;
        }
        else
        {
            countConverge++;
        }

        // se for melhor que best, substitui
        if ((int)newFitness > (int)bestFitness)
        {
            bestAlocsMap = newAlocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;
        }
        
        if (countConverge >= nIterConverge)
        {
            break;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempoTotal = duration.count();
    return std::make_tuple(tempoTotal, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> ExecutadorDeMetaheuristicas::GRASP(DadosDeEntrada dataset,
                                                                                                                int nIter, int modoDebug, std::set<int> vizinhancasinit, std::set<int> vizinhancasFinal,
                                                                                                                int nivelIntensifica, int maxIterFO, int nIterConverge)
{
    int modoDebugAltoNivel = 0;

    if (modoDebugAltoNivel){
    std::cout << std::endl;
    std::cout << "Rodando GRASP";
    std::cout << std::endl;}

    auto start = std::chrono::high_resolution_clock::now();

    ConstrutorHeuristico construtor{this->_alpha, this->_criterio, this->_estrutura, this->_modoRealoc};
    MovimentadorEmVizinhancas movimentador{};

    // inicializa bests e constroi solução inicial
    long long bestTempo;
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap;
    double bestFitness;
    double bestGastos;
    int bestTotalFree;

    if (modoDebugAltoNivel){
    std::cout << std::endl;
    std::cout << "Construindo solução inicial";
    std::cout << std::endl;}

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

    // inicializa conjunto de ótimos locais
    std::set<int> otimosLocaisFitness;
    std::vector<std::pair<int, std::map<Sonda, std::vector<Alocacao>>>> otimosLocaisAlocs;

    int count = 0;
    int countConverge = 0;
    while (count < nIter)
    {
        count++;

        auto stopPart = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopPart - start);
        long long tempoPart = duration.count();
        if (tempoPart >= 1800000)
        {
            break;
        }

        if (modoDebugAltoNivel){
        std::cout << std::endl;
        std::cout << "Rodando iteração: " << count;
        std::cout << std::endl;}

        // escolhe critério
        int criterio = (rand() % 4) + 1;
        construtor.setCriterio(criterio);

        // escolhe alpha
        int alphaIdx = rand() % alphas.size();
        double alpha = *std::next(alphas.begin(), alphaIdx);
        construtor.setAlpha(alpha);

        // constroi nova solução
        std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = construtor.ConstruirSolucao(dataset, modoDebug);

        // realiza busca local
        std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaLocal(newAlocsMap, dataset, 
                                        this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasinit, maxIterFO);
        
        if (modoDebugAltoNivel){
        std::cout << std::endl;
        std::cout << "Novos valores após iteração: " << count << std::endl;
        std::cout << "best fitness: " << bestFitness << std::endl;
        std::cout << "new fitness: " << newFitness << std::endl;
        std::cout << std::endl;}

        // guarda ótimo local, se novo
        if (otimosLocaisFitness.find((int)newFitness) == otimosLocaisFitness.end())
        {
            if (modoDebugAltoNivel){
            std::cout << std::endl << "Guardando ótimo local" << std::endl;}

            otimosLocaisFitness.insert((int)newFitness);
            otimosLocaisAlocs.push_back(std::make_pair((int)newFitness, newAlocsMap));
        }

        if ((int)newFitness > 1.01 * (int)bestFitness) 
        {
            countConverge = 0;
        }
        else 
        {
            countConverge++;
        }

        // se for melhor que best, substitui
        if ((int)newFitness > (int)bestFitness)
        {
            if (modoDebugAltoNivel){
            std::cout << std::endl << "Substituindo best" << std::endl;}

            bestAlocsMap = newAlocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;
        }

        if (countConverge >= nIterConverge) 
        {
            break;
        }
    }

    if (modoDebugAltoNivel){
    std::cout << std::endl << "GRASP finalizado sem intensificações finais" << std::endl;}

    // faz busca final para os melhores ótimos locais
    struct sort_pred {
        bool operator()(const std::pair<int, std::map<Sonda, std::vector<Alocacao>>> &left, const std::pair<int, std::map<Sonda, std::vector<Alocacao>>> &right) {
            return left.first < right.first;
        }
    };
    std::sort(otimosLocaisAlocs.begin(), otimosLocaisAlocs.end(), sort_pred());

    int countOtimosLocais = 0;
    for (std::vector<std::pair<int, std::map<Sonda, std::vector<Alocacao>>>>::iterator it=otimosLocaisAlocs.begin(); it!=otimosLocaisAlocs.end(); ++it)
    {
        countOtimosLocais++;
        if (countOtimosLocais > nivelIntensifica)
        {
            break;
        }
        newAlocsMap = it->second;

        // realiza busca intensificada
        std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaLocal(newAlocsMap, dataset, 
                                        this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasFinal, maxIterFO);
        
        // se for melhor que best, substitui
        if ((int)newFitness > (int)bestFitness)
        {
            bestAlocsMap = newAlocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempoTotal = duration.count();

    if (modoDebugAltoNivel){
    std::cout << std::endl << "GRASP finalizado com intensificações finais" << std::endl;}

    return std::make_tuple(tempoTotal, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> ExecutadorDeMetaheuristicas::GRASPadaptativo(DadosDeEntrada dataset,
                                                                                                                int nIter, int modoDebug, std::set<int> vizinhancasinit, std::set<int> vizinhancasFinal,
                                                                                                                int nivelIntensifica, int nIterMelhora, double taxaAlpha, int nIterAlpha, int maxIterFO, int nIterConverge)
{
    int modoDebugAltoNivel = 0;

    if (modoDebugAltoNivel){
    std::cout << std::endl << "Rodando GRASP adaptativo" << std::endl;}

    auto start = std::chrono::high_resolution_clock::now();

    ConstrutorHeuristico construtor{this->_alpha, this->_criterio, this->_estrutura, this->_modoRealoc};
    MovimentadorEmVizinhancas movimentador{};

    // inicializa bests e constroi solução inicial
    long long bestTempo;
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap;
    double bestFitness;
    double bestGastos;
    int bestTotalFree;

    if (modoDebugAltoNivel){
    std::cout << std::endl << "Construindo solução inicial" << std::endl;}

    std::tie(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree) = construtor.ConstruirSolucao(dataset, modoDebug);

    // inicializa valores intermediários
    long long newTempo;
    std::map<Sonda, std::vector<Alocacao>> newAlocsMap;
    double newFitness;
    double newGastos;
    int newTotalFree;

    // inicializa conjunto de critérios
    std::set<int> criterios;
    criterios.insert(1);
    criterios.insert(2);
    criterios.insert(3);
    criterios.insert(4);
    criterios.erase(this->_criterio);

    // inicializa conjunto de ótimos locais
    std::set<int> otimosLocaisFitness;
    std::vector<std::pair<int, std::map<Sonda, std::vector<Alocacao>>>> otimosLocaisAlocs;

    // guarda alpha inicial
    double alphaInit = construtor.getAlpha();

    int count = 0;
    int countSemMelhora = 0;
    int countMudouAlpha = 0;
    int countConverge = 0;
    while (count < nIter)
    {
        count++;

        auto stopPart = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopPart - start);
        long long tempoPart = duration.count();
        if (tempoPart >= 1800000)
        {
            break;
        }

        if (modoDebugAltoNivel){
        std::cout << std::endl << "Rodando iteração: " << count << std::endl;}

        // constroi nova solução
        std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = construtor.ConstruirSolucao(dataset, modoDebug);

        // realiza busca local
        std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaLocal(newAlocsMap, dataset, 
                                        this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasinit, maxIterFO);
        
        if (modoDebugAltoNivel){
        std::cout << std::endl;
        std::cout << "Novos valores após iteração: " << count << std::endl;
        std::cout << "best fitness: " << bestFitness << std::endl;
        std::cout << "new fitness: " << newFitness << std::endl;
        std::cout << "Contagem sem melhorar FO: " << countSemMelhora << std::endl;
        std::cout << "Contagem mudou alpha: " << countMudouAlpha << std::endl;
        std::cout << std::endl;}

        // guarda ótimo local, se novo
        if (otimosLocaisFitness.find((int)newFitness) == otimosLocaisFitness.end())
        {
            if (modoDebugAltoNivel){
            std::cout << std::endl << "Guardando ótimo local" << std::endl;}

            otimosLocaisFitness.insert((int)newFitness);
            otimosLocaisAlocs.push_back(std::make_pair((int)newFitness, newAlocsMap));
        }

        if ((int)newFitness > 1.01 * (int)bestFitness) 
        {
            countConverge = 0;
        }
        else 
        {
            countConverge++;
        }

        // se for melhor que best, substitui
        if ((int)newFitness > (int)bestFitness)
        {
            if (modoDebugAltoNivel){
            std::cout << std::endl << "Atualizando best" << std::endl;}

            bestAlocsMap = newAlocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;

            countSemMelhora = 0;
            countMudouAlpha = 0;
            construtor.setAlpha(alphaInit);
        }
        else
        {
            countSemMelhora++;
            if (countSemMelhora > nIterMelhora)
            {
                if (modoDebugAltoNivel){
                std::cout << std::endl << "Alterando alpha para maior exploração" << std::endl;}

                double newAlpha = taxaAlpha * construtor.getAlpha();
                construtor.setAlpha(newAlpha);
                countSemMelhora = 0;
                countMudouAlpha++;
            }
            if (countMudouAlpha > nIterAlpha)
            {
                if (modoDebugAltoNivel){
                std::cout << std::endl << "Alterando critério guloso para maior exploração" << std::endl;}

                if (criterios.empty())
                {
                    criterios.insert(1);
                    criterios.insert(2);
                    criterios.insert(3);
                    criterios.insert(4);

                    int newCriterio = *criterios.begin();
                    criterios.erase(newCriterio);
                    construtor.setCriterio(newCriterio);
                    construtor.setAlpha(alphaInit);
                    countSemMelhora = 0;
                    countMudouAlpha = 0;
                }
                else
                {
                    int newCriterio = *criterios.begin();
                    criterios.erase(newCriterio);
                    construtor.setCriterio(newCriterio);
                    construtor.setAlpha(alphaInit);
                    countSemMelhora = 0;
                    countMudouAlpha = 0;
                }
            }
        }
        if (countConverge >= nIterConverge) 
        {
            break;
        }
    }

    if (modoDebugAltoNivel){
    std::cout << std::endl << "GRASP adaptativo finalizado sem intensificações finais" << std::endl;}

    // faz busca final para os melhores ótimos locais
    struct sort_pred {
        bool operator()(const std::pair<int, std::map<Sonda, std::vector<Alocacao>>> &left, const std::pair<int, std::map<Sonda, std::vector<Alocacao>>> &right) {
            return left.first < right.first;
        }
    };
    std::sort(otimosLocaisAlocs.begin(), otimosLocaisAlocs.end(), sort_pred());

    int countOtimosLocais = 0;
    for (std::vector<std::pair<int, std::map<Sonda, std::vector<Alocacao>>>>::iterator it=otimosLocaisAlocs.begin(); it!=otimosLocaisAlocs.end(); ++it)
    {
        countOtimosLocais++;
        if (countOtimosLocais > nivelIntensifica)
        {
            break;
        }
        newAlocsMap = it->second;

        // realiza busca intensificada
        std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaLocal(newAlocsMap, dataset, 
                                        this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasFinal, maxIterFO);
        
        // se for melhor que best, substitui
        if ((int)newFitness > (int)bestFitness)
        {
            bestAlocsMap = newAlocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempoTotal = duration.count();

    if (modoDebugAltoNivel){
    std::cout << std::endl << "GRASP adaptativo finalizado com intensificações finais" << std::endl;}

    return std::make_tuple(tempoTotal, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> ExecutadorDeMetaheuristicas::ILS(DadosDeEntrada dataset,
                                                                                                                int nIter, int modoDebug, std::set<int> vizinhancasinit, std::set<int> vizinhancasFinal, 
                                                                                                                double aceitacaoLimite, int nivelIntensifica, int maxIterFO, int nIterConverge)
{
    int modoDebugAltoNivel = 0;

    if (modoDebugAltoNivel){
    std::cout << std::endl << "Rodando ILS" << std::endl;}

    auto start = std::chrono::high_resolution_clock::now();

    ConstrutorHeuristico construtor{this->_alpha, this->_criterio, this->_estrutura, this->_modoRealoc};
    MovimentadorEmVizinhancas movimentador{};

    // inicializa bests e constroi solução inicial
    long long bestTempo;
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap;
    double bestFitness;
    double bestGastos;
    int bestTotalFree;

    if (modoDebugAltoNivel){
    std::cout << std::endl << "Construindo solução inicial" << std::endl;}

    std::tie(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree) = construtor.ConstruirSolucao(dataset, modoDebug);

    if (modoDebugAltoNivel){
    std::cout << std::endl << "Fazendo busca local inicial" << std::endl;}

    // realiza busca local
    std::tie(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree) = movimentador.buscaLocal(bestAlocsMap, dataset, 
                                             this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasinit, maxIterFO);

    // inicializa valores intermediários
    long long newTempo;
    std::map<Sonda, std::vector<Alocacao>> newAlocsMap = bestAlocsMap;
    double newFitness = bestFitness;
    double newGastos;
    int newTotalFree;
    long long partTempo;
    std::map<Sonda, std::vector<Alocacao>> partAlocsMap;
    double partFitness;
    double partGastos;
    int partTotalFree;

    // inicializa conjunto de ótimos locais
    std::set<int> otimosLocaisFitness;
    std::vector<std::pair<int, std::map<Sonda, std::vector<Alocacao>>>> otimosLocaisAlocs;

    int count = 0;
    int countConverge = 0;
    while (count < nIter)
    {
        count++;

        auto stopPart = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopPart - start);
        long long tempoPart = duration.count();
        if (tempoPart >= 1800000)
        {
            break;
        }

        if (modoDebugAltoNivel){
        std::cout << std::endl << "Rodando iteração: " << count << std::endl;}

        // perturba solução
        partAlocsMap = movimentador.perturbaSolucao(newAlocsMap, dataset, this->_estrutura, this->_modoRealoc, 
                                                    this->_nivelPerturba, this->_modoPerturba, modoDebug, vizinhancasinit);

        // realiza busca local
        std::tie(partTempo, partAlocsMap, partFitness, partGastos, partTotalFree) = movimentador.buscaLocal(partAlocsMap, dataset, 
                                        this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasinit, maxIterFO);

        if (modoDebugAltoNivel){
        std::cout << std::endl;
        std::cout << "Novos valores após iteração: " << count << std::endl;
        std::cout << "best fitness: " << bestFitness << std::endl;
        std::cout << "new fitness: " << newFitness << std::endl;
        std::cout << "part fitness: " << partFitness << std::endl;
        std::cout << std::endl;}

        // guarda ótimo local, se novo
        if (otimosLocaisFitness.find((int)newFitness) == otimosLocaisFitness.end())
        {
            if (modoDebugAltoNivel){
            std::cout << std::endl << "Guardando ótimo local" << std::endl;}

            otimosLocaisFitness.insert((int)newFitness);
            otimosLocaisAlocs.push_back(std::make_pair((int)newFitness, newAlocsMap));
        }

        // decide se aceita a nova solução
        if ((int)partFitness >= (int)(aceitacaoLimite * newFitness))
        {
            if (modoDebugAltoNivel){
            std::cout << std::endl << "Aceita solução nova" << std::endl;}

            newAlocsMap = partAlocsMap;
            newFitness = partFitness;
            newGastos = partGastos;
            newTempo = partTempo;
            newTotalFree = partTotalFree;

            if ((int)newFitness > 1.01 * (int)bestFitness) 
            {
                countConverge = 0;
            }
            else 
            {
                countConverge++;
            }
        }

        // se for melhor que best, substitui
        if ((int)newFitness > (int)bestFitness)
        {
            if (modoDebugAltoNivel){
            std::cout << std::endl << "Atualiza best" << std::endl;}

            bestAlocsMap = newAlocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;
        }
        if (countConverge >= nIterConverge) 
        {
            break;
        }
    }

    if (modoDebugAltoNivel){
    std::cout << std::endl << "ILS finalizado sem intensificações finais" << std::endl;}

    // faz busca final para os melhores ótimos locais
    struct sort_pred {
        bool operator()(const std::pair<int, std::map<Sonda, std::vector<Alocacao>>> &left, const std::pair<int, std::map<Sonda, std::vector<Alocacao>>> &right) {
            return left.first < right.first;
        }
    };
    std::sort(otimosLocaisAlocs.begin(), otimosLocaisAlocs.end(), sort_pred());

    int countOtimosLocais = 0;
    for (std::vector<std::pair<int, std::map<Sonda, std::vector<Alocacao>>>>::iterator it=otimosLocaisAlocs.begin(); it!=otimosLocaisAlocs.end(); ++it)
    {
        countOtimosLocais++;
        if (countOtimosLocais > nivelIntensifica)
        {
            break;
        }
        newAlocsMap = it->second;

        // realiza busca intensificada
        std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaLocal(newAlocsMap, dataset, 
                                        this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasFinal, maxIterFO);
        
        // se for melhor que best, substitui
        if ((int)newFitness > (int)bestFitness)
        {
            bestAlocsMap = newAlocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempoTotal = duration.count();

    if (modoDebugAltoNivel){
    std::cout << std::endl << "ILS finalizado com intensificações finais" << std::endl;}

    return std::make_tuple(tempoTotal, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> ExecutadorDeMetaheuristicas::ILSadaptativo(DadosDeEntrada dataset,
                                                                                                                int nIter, int modoDebug, std::set<int> vizinhancasinit, std::set<int> vizinhancasFinal, 
                                                                                                                double aceitacaoLimite, int nivelIntensifica, 
                                                                                                                int nIterMelhora, int taxaPerturba, double taxaAceitacao,
                                                                                                                int nIterRestart, double alphaRestart, int maxIterFO, int nIterConverge)
{
    int modoDebugAltoNivel = 0;

    if (modoDebugAltoNivel){
    std::cout << std::endl << "Rodando ILS adaptativo" << std::endl;}

    auto start = std::chrono::high_resolution_clock::now();

    ConstrutorHeuristico construtor{this->_alpha, this->_criterio, this->_estrutura, this->_modoRealoc};
    MovimentadorEmVizinhancas movimentador{};

    // inicializa bests e constroi solução inicial
    long long bestTempo;
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap;
    double bestFitness;
    double bestGastos;
    int bestTotalFree;

    if (modoDebugAltoNivel){
    std::cout << std::endl << "Construindo solução inicial" << std::endl;}

    std::tie(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree) = construtor.ConstruirSolucao(dataset, modoDebug);

    if (modoDebugAltoNivel){
    std::cout << std::endl << "Rodando busca local inicial" << std::endl;}

    // realiza busca local
    std::tie(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree) = movimentador.buscaLocal(bestAlocsMap, dataset, 
                                             this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasinit, maxIterFO);

    // inicializa valores intermediários
    long long newTempo;
    std::map<Sonda, std::vector<Alocacao>> newAlocsMap = bestAlocsMap;
    double newFitness = bestFitness;
    double newGastos;
    int newTotalFree;
    long long partTempo;
    std::map<Sonda, std::vector<Alocacao>> partAlocsMap;
    double partFitness;
    double partGastos;
    int partTotalFree;

    // guarda parâmetros iniciais do ILS
    double limiteAceitacaoInit = aceitacaoLimite;
    int nivelPerturbaInit = this->_nivelPerturba;

    // inicializa conjunto de ótimos locais
    std::set<int> otimosLocaisFitness;
    std::vector<std::pair<int, std::map<Sonda, std::vector<Alocacao>>>> otimosLocaisAlocs;

    int count = 0;
    int countSemMelhora = 0;
    int countRestart = 0;
    int countConverge = 0;
    while (count < nIter)
    {
        count++;

        auto stopPart = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopPart - start);
        long long tempoPart = duration.count();
        if (tempoPart >= 1800000)
        {
            break;
        }

        if (modoDebugAltoNivel){
        std::cout << std::endl << "Rodando iteração: " << count << std::endl;}

        // perturba solução
        partAlocsMap = movimentador.perturbaSolucao(newAlocsMap, dataset, this->_estrutura, this->_modoRealoc, 
                                                    this->_nivelPerturba, this->_modoPerturba, modoDebug, vizinhancasinit);

        // realiza busca local
        std::tie(partTempo, partAlocsMap, partFitness, partGastos, partTotalFree) = movimentador.buscaLocal(partAlocsMap, dataset, 
                                        this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasinit, maxIterFO);

        if (modoDebugAltoNivel){
        std::cout << std::endl;
        std::cout << "Novos valores após iteração: " << count << std::endl;
        std::cout << "best fitness: " << bestFitness << std::endl;
        std::cout << "new fitness: " << newFitness << std::endl;
        std::cout << "part fitness: " << partFitness << std::endl;
        std::cout << "count sem melhorar FO: " << countSemMelhora << std::endl;
        std::cout << "count para restart: " << countRestart << std::endl;
        std::cout << std::endl;}

        // guarda ótimo local, se novo
        if (otimosLocaisFitness.find((int)partFitness) == otimosLocaisFitness.end())
        {
            if (modoDebugAltoNivel){
            std::cout << std::endl << "Guardando ótimo local" << std::endl;}

            otimosLocaisFitness.insert((int)partFitness);
            otimosLocaisAlocs.push_back(std::make_pair((int)partFitness, partAlocsMap));
        }

        // decide se aceita a nova solução
        if ((int)partFitness >= (int)(aceitacaoLimite * newFitness))
        {
            if (modoDebugAltoNivel){
            std::cout << std::endl << "Aceita nova solução" << std::endl;}

            newAlocsMap = partAlocsMap;
            newFitness = partFitness;
            newGastos = partGastos;
            newTempo = partTempo;
            newTotalFree = partTotalFree;

            if ((int)newFitness > 1.01 * (int)bestFitness) 
            {
                countConverge = 0;
            }
            else 
            {
                countConverge++;
            }
        }

        // se for melhor que best, substitui
        if ((int)newFitness > (int)bestFitness)
        {
            if (modoDebugAltoNivel){
            std::cout << std::endl << "Atualiza best" << std::endl;}

            bestAlocsMap = newAlocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;

            countSemMelhora = 0;
            countRestart = 0;
            aceitacaoLimite = limiteAceitacaoInit;
            this->_nivelPerturba = nivelPerturbaInit;
        }
        else
        {
            countSemMelhora++;
            if (countSemMelhora > nIterMelhora)
            {
                if (modoDebugAltoNivel){
                std::cout << std::endl << "Alterando taxaAceitacao e nivelPerturba para mais exploração" << std::endl;}

                this->_nivelPerturba = this->_nivelPerturba + taxaPerturba;
                aceitacaoLimite = aceitacaoLimite * taxaAceitacao;
                countSemMelhora = 0;
                countRestart++;
            }
            if (countRestart > nIterRestart)
            {
                if (modoDebugAltoNivel){
                std::cout << std::endl << "Realizando restart" << std::endl;}

                countSemMelhora = 0;
                countRestart = 0;
                aceitacaoLimite = limiteAceitacaoInit;
                this->_nivelPerturba = nivelPerturbaInit;

                // restart
                construtor.setAlpha(alphaRestart);

                // constroi solução
                std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = construtor.ConstruirSolucao(dataset, modoDebug);

                // realiza busca local
                std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaLocal(newAlocsMap, dataset, 
                                                        this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasinit, maxIterFO);
            }
        }
        if (countConverge >= nIterConverge) 
        {
            break;
        }
    }

    if (modoDebugAltoNivel){
    std::cout << std::endl << "ILS adaptativo finalizado sem intensificações finais" << std::endl;}

    // faz busca final para os melhores ótimos locais
    struct sort_pred {
        bool operator()(const std::pair<int, std::map<Sonda, std::vector<Alocacao>>> &left, const std::pair<int, std::map<Sonda, std::vector<Alocacao>>> &right) {
            return left.first < right.first;
        }
    };
    std::sort(otimosLocaisAlocs.begin(), otimosLocaisAlocs.end(), sort_pred());

    int countOtimosLocais = 0;
    for (std::vector<std::pair<int, std::map<Sonda, std::vector<Alocacao>>>>::iterator it=otimosLocaisAlocs.begin(); it!=otimosLocaisAlocs.end(); ++it)
    {
        countOtimosLocais++;
        if (countOtimosLocais > nivelIntensifica)
        {
            break;
        }
        newAlocsMap = it->second;

        // realiza busca intensificada
        std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaLocal(newAlocsMap, dataset, 
                                        this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasFinal, maxIterFO);
        
        // se for melhor que best, substitui
        if ((int)newFitness > (int)bestFitness)
        {
            bestAlocsMap = newAlocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempoTotal = duration.count();

    if (modoDebugAltoNivel){
    std::cout << std::endl << "ILS adaptativo finalizado com intensificações finais" << std::endl;}

    return std::make_tuple(tempoTotal, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

void ExecutadorDeMetaheuristicas::rodarVariosArquivos(const char * caminho, int nIter, int modoDebug,
                                                        std::set<int> vizinhancasinit, std::set<int> vizinhancasFinal,
                                                        double aceitacaoLimite, int nivelIntensifica, 
                                                        int nIterMelhora, double taxaAlpha, int nIterAlpha,
                                                        int taxaPerturba, double taxaAceitacao,
                                                        int nIterRestart, double alphaRestart, int maxIterFO, int nIterConverge)
{
    DIR *dir; 
    struct dirent *diread;
    std::vector<std::string> arquivos;

    // armazenando nomes dos arquivos
    if ( (dir = opendir(caminho)) != nullptr ) 
    {
        while ( (diread = readdir(dir)) != nullptr ) 
        {
            arquivos.push_back(diread->d_name);
            //std::cout << diread->d_name << std::endl;
        }
        closedir (dir);
    } 
    else 
    {
        perror ("opendir");
    }

    std::ofstream outfile;
    outfile.open("resultados_automaticos_MH.txt");

    outfile << "Arquivo" << " " 
            << "Algoritmo" << " " 
            << "estrutura" << " "
            << "modoRealoc" << " "
            << "criterio" << " "
            << "alpha" << " "
            << "modoBusca" << " "
            << "modoPerturba" << " "
            << "nivelPerturba" << " "
            << "nIter" << " "
            << "aceitacaoLimite" << " "
            << "nivelIntensifica" << " "
            << "nIterMelhora" << " "
            << "taxaAlpha" << " "
            << "nIterAlpha" << " "
            << "taxaPerturba" << " "
            << "taxaAceitacao" << " "
            << "nIterRestart" << " "
            << "alphaRestart" << " "
            << "maxIterFO" << " "
            << "tempo" << " "
            << "fitness" << " "
            << "gastos" << " "
            <<  std::endl;

    std::string s1 = ".dat";
    int count_arquivos = 0;
    for (std::vector<std::string>::iterator it=arquivos.begin(); it!=arquivos.end(); ++it)
    {
        std::string arquivo = *it;
        if (arquivo.find(s1) != std::string::npos)
        {
            count_arquivos++;
            std::string s2 = "/home/joaoweissmann/Documents/repos/DRSP-B/1_gerador_instancias_sinteticas/instance_set_1/instancias/";
            s2.append(*it);
            std::cout << "(" << count_arquivos << "/" << arquivos.size() - 2 << ")" << "Rodando heurísticas para arquivo: " << s2 << std::endl;

            LeitorDeDados leitor;
            DadosDeEntrada dataset = leitor.lerDadosDeEntrada(s2);

            // inicializa variaveis a serem retornadas
            long long tempo;
            long long tempoMedio;
            std::map<Sonda, std::vector<Alocacao>> alocsMap;
            double fitness;
            double fitnessMedio;
            double gastos;
            double gastosMedio;
            int totalFree;

            int repetitionsMultiStart = 10; // DEFAULT É 10
            int repetitionsGRASP = 10; // DEFAULT É 10
            int repetitionsGRASPada = 10; // DEFAULT É 10
            int repetitionsILS = 10; // DEFAULT É 10
            int repetitionsILSada = 10; // DEFAULT É 10

            nIter = 1000 / (std::sqrt(dataset.getNProjetos() / 3));
            nIterConverge = nIter / 5;

            // mult-start heuristic
            std::cout << "Rodando Mult-Start Heuristic" << std::endl;

            tempoMedio = 0;
            fitnessMedio = 0;
            gastosMedio = 0;
            for (int repete=0; repete<repetitionsMultiStart; repete++)
            {
                std::tie(tempo, alocsMap, fitness, gastos, totalFree) = this->multStartHeuristic(dataset, nIter, modoDebug, nIterConverge);
                tempoMedio = tempoMedio + tempo;
                fitnessMedio = fitnessMedio + fitness;
                gastosMedio = gastosMedio + gastos;
            }
            tempoMedio = tempoMedio / std::max(repetitionsMultiStart, 1);
            fitnessMedio = fitnessMedio / std::max(repetitionsMultiStart, 1);
            gastosMedio = gastosMedio / std::max(repetitionsMultiStart, 1);

            outfile << s2 << " " 
                    << "Mult-Start" << " " 
                    << this->_estrutura << " "
                    << this->_modoRealoc << " "
                    << this->_criterio << " "
                    << this->_alpha << " "
                    << this->_modoBusca << " "
                    << this->_modoPerturba << " "
                    << this->_nivelPerturba << " "
                    << nIter << " "
                    << aceitacaoLimite << " "
                    << nivelIntensifica << " "
                    << nIterMelhora << " "
                    << taxaAlpha << " "
                    << nIterAlpha << " "
                    << taxaPerturba << " "
                    << taxaAceitacao << " "
                    << nIterRestart << " "
                    << alphaRestart << " "
                    << maxIterFO << " "
                    << tempoMedio << " "
                    << fitnessMedio << " "
                    << gastosMedio << " "
                    <<  std::endl;

            // GRASP
            std::cout << "Rodando GRASP" << std::endl;

            nIter = 1000 / (std::sqrt(dataset.getNProjetos() / 3));
            nIterConverge = nIter / 5;

            this->setAlpha(0.90);

            tempoMedio = 0;
            fitnessMedio = 0;
            gastosMedio = 0;
            for (int repete=0; repete<repetitionsGRASP; repete++)
            {
                std::tie(tempo, alocsMap, fitness, gastos, totalFree) = this->GRASP(dataset, nIter, modoDebug, vizinhancasinit, vizinhancasFinal, nivelIntensifica, maxIterFO, nIterConverge);
                tempoMedio = tempoMedio + tempo;
                fitnessMedio = fitnessMedio + fitness;
                gastosMedio = gastosMedio + gastos;
            }
            tempoMedio = tempoMedio / std::max(repetitionsGRASP, 1);
            fitnessMedio = fitnessMedio / std::max(repetitionsGRASP, 1);
            gastosMedio = gastosMedio / std::max(repetitionsGRASP, 1);
            
            outfile << s2 << " " 
                    << "GRASP" << " " 
                    << this->_estrutura << " "
                    << this->_modoRealoc << " "
                    << this->_criterio << " "
                    << this->_alpha << " "
                    << this->_modoBusca << " "
                    << this->_modoPerturba << " "
                    << this->_nivelPerturba << " "
                    << nIter << " "
                    << aceitacaoLimite << " "
                    << nivelIntensifica << " "
                    << nIterMelhora << " "
                    << taxaAlpha << " "
                    << nIterAlpha << " "
                    << taxaPerturba << " "
                    << taxaAceitacao << " "
                    << nIterRestart << " "
                    << alphaRestart << " "
                    << maxIterFO << " "
                    << tempoMedio << " "
                    << fitnessMedio << " "
                    << gastosMedio << " "
                    <<  std::endl;
            
            // GRASP adaptativo
            std::cout << "Rodando GRASP adaptativo" << std::endl;

            nIter = 1000 / (std::sqrt(dataset.getNProjetos() / 3));
            nIterConverge = nIter / 5;

            this->setAlpha(0.7);
            nIterMelhora = 20;
            taxaAlpha = 0.7;
            nIterAlpha = 20;

            tempoMedio = 0;
            fitnessMedio = 0;
            gastosMedio = 0;
            for (int repete=0; repete<repetitionsGRASPada; repete++)
            {
                std::tie(tempo, alocsMap, fitness, gastos, totalFree) = this->GRASPadaptativo(dataset, nIter, modoDebug, vizinhancasinit, vizinhancasFinal, nivelIntensifica, nIterMelhora, taxaAlpha, nIterAlpha, maxIterFO, nIterConverge);
                tempoMedio = tempoMedio + tempo;
                fitnessMedio = fitnessMedio + fitness;
                gastosMedio = gastosMedio + gastos;
            }
            tempoMedio = tempoMedio / std::max(repetitionsGRASPada, 1);
            fitnessMedio = fitnessMedio / std::max(repetitionsGRASPada, 1);
            gastosMedio = gastosMedio / std::max(repetitionsGRASPada, 1);

            outfile << s2 << " " 
                    << "GRASP_ada" << " " 
                    << this->_estrutura << " "
                    << this->_modoRealoc << " "
                    << this->_criterio << " "
                    << this->_alpha << " "
                    << this->_modoBusca << " "
                    << this->_modoPerturba << " "
                    << this->_nivelPerturba << " "
                    << nIter << " "
                    << aceitacaoLimite << " "
                    << nivelIntensifica << " "
                    << nIterMelhora << " "
                    << taxaAlpha << " "
                    << nIterAlpha << " "
                    << taxaPerturba << " "
                    << taxaAceitacao << " "
                    << nIterRestart << " "
                    << alphaRestart << " "
                    << maxIterFO << " "
                    << tempoMedio << " "
                    << fitnessMedio << " "
                    << gastosMedio << " "
                    <<  std::endl;

            // ILS
            std::cout << "Rodando ILS" << std::endl;

            nIter = 1000 / (std::sqrt(dataset.getNProjetos() / 3));
            nIterConverge = nIter / 5;

            this->setAlpha(0.9);
            this->setNivelPerturba(2);
            aceitacaoLimite = 1.0;

            tempoMedio = 0;
            fitnessMedio = 0;
            gastosMedio = 0;
            for (int repete=0; repete<repetitionsILS; repete++)
            {
                std::tie(tempo, alocsMap, fitness, gastos, totalFree) = this->ILS(dataset, nIter, modoDebug, vizinhancasinit, vizinhancasFinal, aceitacaoLimite, nivelIntensifica, maxIterFO, nIterConverge);
                tempoMedio = tempoMedio + tempo;
                fitnessMedio = fitnessMedio + fitness;
                gastosMedio = gastosMedio + gastos;
            }
            tempoMedio = tempoMedio / std::max(repetitionsILS, 1);
            fitnessMedio = fitnessMedio / std::max(repetitionsILS, 1);
            gastosMedio = gastosMedio / std::max(repetitionsILS, 1);

            outfile << s2 << " " 
                    << "ILS" << " " 
                    << this->_estrutura << " "
                    << this->_modoRealoc << " "
                    << this->_criterio << " "
                    << this->_alpha << " "
                    << this->_modoBusca << " "
                    << this->_modoPerturba << " "
                    << this->_nivelPerturba << " "
                    << nIter << " "
                    << aceitacaoLimite << " "
                    << nivelIntensifica << " "
                    << nIterMelhora << " "
                    << taxaAlpha << " "
                    << nIterAlpha << " "
                    << taxaPerturba << " "
                    << taxaAceitacao << " "
                    << nIterRestart << " "
                    << alphaRestart << " "
                    << maxIterFO << " "
                    << tempoMedio << " "
                    << fitnessMedio << " "
                    << gastosMedio << " "
                    <<  std::endl;
        
            // ILS adaptativo
            std::cout << "Rodando ILS adaptativo" << std::endl;

            nIter = 1000 / (std::sqrt(dataset.getNProjetos() / 3));
            nIterConverge = nIter / 5;

            this->setAlpha(0.8);
            this->setNivelPerturba(2);
            aceitacaoLimite = 1.0;
            nIterMelhora = 16;
            taxaPerturba = 4;
            taxaAceitacao = 0.8;
            nIterRestart = 15;
            alphaRestart = 0.9;

            tempoMedio = 0;
            fitnessMedio = 0;
            gastosMedio = 0;
            for (int repete=0; repete<repetitionsILSada; repete++)
            {
                std::tie(tempo, alocsMap, fitness, gastos, totalFree) = this->ILSadaptativo(dataset, nIter, modoDebug, vizinhancasinit, vizinhancasFinal, aceitacaoLimite, nivelIntensifica, nIterMelhora, taxaPerturba, taxaAceitacao, nIterRestart, alphaRestart, maxIterFO, nIterConverge);
                tempoMedio = tempoMedio + tempo;
                fitnessMedio = fitnessMedio + fitness;
                gastosMedio = gastosMedio + gastos;
            }
            tempoMedio = tempoMedio / std::max(repetitionsILSada, 1);
            fitnessMedio = fitnessMedio / std::max(repetitionsILSada, 1);
            gastosMedio = gastosMedio / std::max(repetitionsILSada, 1);
            
            outfile << s2 << " " 
                    << "ILS_ada" << " " 
                    << this->_estrutura << " "
                    << this->_modoRealoc << " "
                    << this->_criterio << " "
                    << this->_alpha << " "
                    << this->_modoBusca << " "
                    << this->_modoPerturba << " "
                    << this->_nivelPerturba << " "
                    << nIter << " "
                    << aceitacaoLimite << " "
                    << nivelIntensifica << " "
                    << nIterMelhora << " "
                    << taxaAlpha << " "
                    << nIterAlpha << " "
                    << taxaPerturba << " "
                    << taxaAceitacao << " "
                    << nIterRestart << " "
                    << alphaRestart << " "
                    << maxIterFO << " "
                    << tempoMedio << " "
                    << fitnessMedio << " "
                    << gastosMedio << " "
                    <<  std::endl;
        }
    }
    outfile.close();
}

