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
    while (count < nIter)
    {
        count++;

        // escolhe critério
        int criterio = (rand() % 4) + 1;
        construtor.setCriterio(criterio);

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
                                                                                                                int nIter, int modoDebug, std::set<int> vizinhancasinit, std::set<int> vizinhancasFinal, double nivelIntensifica)
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
                                        this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasinit);

        // decide se intensifica
        if (newFitness >= nivelIntensifica * bestFitness)
        {
            // realiza busca local intensificada
            std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaLocal(newAlocsMap, dataset, 
                                        this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasFinal);
        }
        
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
    // busca final
    //std::tie(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree) = movimentador.buscaLocal(bestAlocsMap, dataset, 
    //                                    this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasFinal);

    return std::make_tuple(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<int, std::map<Sonda, std::vector<Alocacao>>, double, double, int> ExecutadorDeMetaheuristicas::ILS(DadosDeEntrada dataset,
                                                                                                                int nIter, int modoDebug, std::set<int> vizinhancasinit, std::set<int> vizinhancasFinal, double aceitacaoLimite, double nivelIntensifica)
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
                                             this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasinit);

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

    int count = 0;
    while (count < nIter)
    {
        count++;

        // perturba solução
        partAlocsMap = movimentador.perturbaSolucao(newAlocsMap, dataset, this->_estrutura, this->_modoRealoc, 
                                                    this->_nivelPerturba, this->_modoPerturba, modoDebug, vizinhancasinit);

        // realiza busca local
        std::tie(partTempo, partAlocsMap, partFitness, partGastos, partTotalFree) = movimentador.buscaLocal(partAlocsMap, dataset, 
                                        this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasinit);

        // decide se intensifica
        if (partFitness >= nivelIntensifica * bestFitness)
        {
            // realiza busca local intensificada
            std::tie(partTempo, partAlocsMap, partFitness, partGastos, partTotalFree) = movimentador.buscaLocal(partAlocsMap, dataset, 
                                            this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasFinal);
        }

        // decide se aceita a nova solução
        if (partFitness >= aceitacaoLimite * newFitness)
        {
            newAlocsMap = partAlocsMap;
            newFitness = partFitness;
            newGastos = partGastos;
            newTempo = partTempo;
            newTotalFree = partTotalFree;
        }

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
    // realiza busca final
    //std::tie(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree) = movimentador.buscaLocal(bestAlocsMap, dataset, 
    //                                         this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasFinal);

    return std::make_tuple(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<int, std::map<Sonda, std::vector<Alocacao>>, double, double, int> ExecutadorDeMetaheuristicas::GRASPILS(DadosDeEntrada dataset,
                                                                                                        int nIter, int modoDebug,
                                                                                                        std::set<int> vizinhancasinit, std::set<int> vizinhancasFinal,
                                                                                                        double aceitacaoLimite, double nivelIntensifica)
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
                                             this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasinit);

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

    for (int i=0; i<nIter; i++)
    {
        // escolhe critério
        int criterio = (rand() % 4) + 1;
        construtor.setCriterio(criterio);

        // escolhe alpha
        int alphaIdx = rand() % alphas.size();
        double alpha = *std::next(alphas.begin(), alphaIdx);
        construtor.setAlpha(alpha);

        // constroi nova solução
        std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = construtor.ConstruirSolucao(dataset, modoDebug);

        // perturba solução
        newAlocsMap = movimentador.perturbaSolucao(newAlocsMap, dataset, this->_estrutura, this->_modoRealoc, 
                                                    this->_nivelPerturba, this->_modoPerturba, modoDebug, vizinhancasinit);

        // realiza busca local
        std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaLocal(newAlocsMap, dataset, 
                                        this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasinit);

        // decide se intensifica
        if (newFitness >= nivelIntensifica * bestFitness)
        {
            // realiza busca local intensificada
            std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaLocal(newAlocsMap, dataset, 
                                        this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasFinal);
        }
        
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
    // realiza busca final
    //std::tie(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree) = movimentador.buscaLocal(bestAlocsMap, dataset, 
    //                                         this->_estrutura, this->_modoRealoc, dataset.getDelta(), this->_modoBusca, modoDebug, vizinhancasFinal);

    return std::make_tuple(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

void ExecutadorDeMetaheuristicas::rodarVariosArquivos(const char * caminho, int nIter, int modoDebug,
                                                        std::set<int> vizinhancasinit, std::set<int> vizinhancasFinal,
                                                        double aceitacaoLimite, double nivelIntensifica)
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
        }
        closedir (dir);
    } 
    else 
    {
        perror ("opendir");
    }

    std::ofstream outfile;
    outfile.open("resultados_automaticos_MH.txt");

    std::string s1 = "instancia";
    for (std::vector<std::string>::iterator it=arquivos.begin(); it!=arquivos.end(); ++it)
    {
        std::string arquivo = *it;
        if (arquivo.find(s1) != std::string::npos)
        {
            std::string s2 = "/home/joaoweissmann/Documents/repos/synthetic_instance_generator/synthetic_instance_generator/1_gerador_instancias_sinteticas/instancias/";
            s2.append(*it);
            std::cout << "Rodando heurísticas para arquivo: " << s2 << std::endl;

            LeitorDeDados leitor;
            DadosDeEntrada dataset = leitor.lerDadosDeEntrada(s2);

            // inicializa variaveis a serem retornadas
            long long tempo;
            std::map<Sonda, std::vector<Alocacao>> alocsMap;
            double fitness;
            double gastos;
            int totalFree;

            // mult-start heuristic
            std::cout << "Rodando Mult-Start Heuristic" << std::endl;
            std::tie(tempo, alocsMap, fitness, gastos, totalFree) = this->multStartHeuristic(dataset, nIter, modoDebug);
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
                    << tempo << " "
                    << fitness << " "
                    << gastos << " "
                    <<  std::endl;

            // GRASP
            std::cout << "Rodando GRASP" << std::endl;
            std::tie(tempo, alocsMap, fitness, gastos, totalFree) = this->GRASP(dataset, nIter, modoDebug, vizinhancasinit, vizinhancasFinal, nivelIntensifica);
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
                    << tempo << " "
                    << fitness << " "
                    << gastos << " "
                    <<  std::endl;

            // ILS
            std::cout << "Rodando ILS" << std::endl;
            std::tie(tempo, alocsMap, fitness, gastos, totalFree) = this->ILS(dataset, nIter, modoDebug, vizinhancasinit, vizinhancasFinal, aceitacaoLimite, nivelIntensifica);
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
                    << tempo << " "
                    << fitness << " "
                    << gastos << " "
                    <<  std::endl;
        }
    }
    outfile.close();
}

