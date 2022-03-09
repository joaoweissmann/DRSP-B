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
#include "ConstrutorHeuristico.h"

ConstrutorHeuristico::ConstrutorHeuristico()
{
    this->_alpha = 0.5;
    this->_criterio = 1;
    this->_estrutura = 1;
    this->_modoRealoc = 0;
}

ConstrutorHeuristico::ConstrutorHeuristico(double alpha, int criterio, int estrutura, int modoRealoc)
{
    if ( (alpha<0.0) || (alpha>1.0) )
    {
        std::cout << std::endl;
        std::cout << "Valor fornecido de alpha é inválido. Valor precisa ser entre 0 e 1. Valor fornecido: " << alpha;
        std::cout << std::endl;
    }
    else
    {
        this->_alpha = alpha;
    }
    assert ( (alpha>=0.0) && (alpha<=1.0) );

    if ( (criterio!=1) && (criterio!=2) && (criterio!=3) && (criterio!=4) )
    {
        std::cout << std::endl;
        std::cout << "Valor fornecido como critério é inválido. Valor deve ser 1, 2, 3 ou 4. Valor fornecido: " << criterio;
        std::cout << std::endl;
    }
    else
    {
        this->_criterio = criterio;
    }
    assert( (criterio==1) || (criterio==2) || (criterio==3) || (criterio==4) );

    if ( (estrutura!=1) && (estrutura!=2) )
    {
        std::cout << std::endl;
        std::cout << "Valor fornecido para estrutura é inválido. Valor deve ser 1 ou 2. Valor fornecido: " << estrutura;
        std::cout << std::endl;
    }
    else
    {
        this->_estrutura = estrutura;
    }
    assert( (estrutura==1) || (estrutura==2) );

    if ( (modoRealoc!=0) && (modoRealoc!=1) )
    {
        std::cout << std::endl;
        std::cout << "Valor fornecido para modo realocação é inválido. Valor deve ser 0 ou 1. Valor fornecido: " << modoRealoc;
        std::cout << std::endl;
    }
    else
    {
        this->_modoRealoc = modoRealoc;
    }
    assert( (modoRealoc==0) || (modoRealoc==1) );
}

double ConstrutorHeuristico::getAlpha()
{
    return this->_alpha;
}

int ConstrutorHeuristico::getCriterio()
{
    return this->_criterio;
}

int ConstrutorHeuristico::getEstrutura()
{
    return this->_estrutura;
}

int ConstrutorHeuristico::getModoRealoc()
{
    return this->_modoRealoc;
}

void ConstrutorHeuristico::setAlpha(double alpha)
{
    if ( (alpha<0.0) || (alpha>1.0) )
    {
        std::cout << std::endl;
        std::cout << "Valor fornecido de alpha é inválido. Valor precisa ser entre 0 e 1. Valor fornecido: " << alpha;
        std::cout << std::endl;
    }
    else
    {
        this->_alpha = alpha;
    }
    assert ( (alpha>=0.0) && (alpha<=1.0) );
}

void ConstrutorHeuristico::setCriterio(int criterio)
{
    if ( (criterio!=1) && (criterio!=2) && (criterio!=3) && (criterio!=4) )
    {
        std::cout << std::endl;
        std::cout << "Valor fornecido como critério é inválido. Valor deve ser 1, 2, 3 ou 4. Valor fornecido: " << criterio;
        std::cout << std::endl;
    }
    else
    {
        this->_criterio = criterio;
    }
    assert( (criterio==1) || (criterio==2) || (criterio==3) || (criterio==4) );
}

void ConstrutorHeuristico::setEstrutura(int estrutura)
{
    if ( (estrutura!=1) && (estrutura!=2) )
    {
        std::cout << std::endl;
        std::cout << "Valor fornecido para estrutura é inválido. Valor deve ser 1 ou 2. Valor fornecido: " << estrutura;
        std::cout << std::endl;
    }
    else
    {
        this->_estrutura = estrutura;
    }
    assert( (estrutura==1) || (estrutura==2) );
}

void ConstrutorHeuristico::setModoRealoc(int modoRealoc)
{
    if ( (modoRealoc!=0) && (modoRealoc!=1) )
    {
        std::cout << std::endl;
        std::cout << "Valor fornecido para modo realocação é inválido. Valor deve ser 0 ou 1. Valor fornecido: " << modoRealoc;
        std::cout << std::endl;
    }
    else
    {
        this->_modoRealoc = modoRealoc;
    }
    assert( (modoRealoc==0) || (modoRealoc==1) );
}

std::tuple<Solucao, int> ConstrutorHeuristico::ConstruirSolucao(DadosDeEntrada dataset)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << std::endl;
    std::cout << "Construindo solução ===================================================";
    std::cout << std::endl;

    // inicializa solução
    Solucao solucao{this->_estrutura, dataset};

    std::cout << "Mostrando solução inicial " << std::endl;
    solucao.print();

    // inicializa vetor de projetos não alocados
    std::vector<Projeto> projetos = dataset.getProjetos();

    // calcula critério guloso e guarda num vetor de tupla
    std::vector<std::pair<double, Projeto>> candidatos;
    for (std::vector<Projeto>::iterator itrP=projetos.begin(); itrP!=projetos.end(); ++itrP)
    {
        Projeto x = *itrP;

        // calcula critério
        double y;
        if (this->_criterio == 1)
        {
            y = x.getMiVpl() / x.getCusto();
        }
        else if (this->_criterio == 2)
        {
            y = x.getMiVpl();
        }
        else if (this->_criterio == 3)
        {
            y = x.getMiVpl() / x.getTempExec();
        }
        else if (this->_criterio == 4)
        {
            y = - x.getTempExec();
        }
        else
        {
            std::cout << std::endl;
            std::cout << "Critério inválido! ====================================== ERRO!";
            std::cout << std::endl;
        }
        candidatos.push_back(std::make_pair(y, x));
    }

    // ordena candidatos pelo critério guloso (crescente)
    std::sort(candidatos.begin(), candidatos.end());

    // inicializa sondas
    std::vector<Sonda> sondas = dataset.getSondas();

    // enquanto nenhuma restrição for alcançada
    while ( (dataset.getCapitalTotal() < solucao.getGastos()) && (!candidatos.empty()))
    {
        std::cout << std::endl;
        std::cout << "Mostrando projetos candidatos ordenados (nome, critério): ";
        for (std::vector<std::pair<double, Projeto>>::iterator itP=candidatos.begin(); itP!=candidatos.end(); ++itP)
        {
            std::cout << "(" << (*itP).second.getNome() << ", " << (*itP).first << ")";
        }
        std::cout << std::endl;

        // escolhe projeto
        double sMin = candidatos[0].first;
        double sMax = candidatos[candidatos.size() - 1].first;
        double cutoff = sMin + this->_alpha*(sMax - sMin);
        int posMax = candidatos.size() - 1;
        int posMin = -1;
        for (std::vector<std::pair<double, Projeto>>::iterator itP=candidatos.begin(); itP!=candidatos.end(); ++itP)
        {
            posMin++;
            double x = (*itP).first;
            if (x >= cutoff)
            {
                break;
            }
        }
        Projeto projeto{};
        if ((posMin >= 0) && (posMin <= posMax))
        {
            int projIdx = rand()%(posMax - posMin + 1) + posMin;
            projeto = candidatos[projIdx].second;
            
            std::cout << std::endl;
            std::cout << "Projeto escolhido (nome, critério): (" << projeto.getNome() << ", " 
                                                                  << candidatos[projIdx].first << ")";
            std::cout << std::endl;

            candidatos.erase(std::next(candidatos.begin(), projIdx));
        }
        else
        {
            std::cout << std::endl;
            std::cout << "Posições inválidas! ================================ ERRO!" << std::endl;
            std::cout << "posição mínima: " << posMin << std::endl;
            std::cout << "posição máxima: " << posMax << std::endl;
            assert((posMin >= 0) && (posMin <= posMax));
        }

        // se projeto não aumenta função objetivo, pular
        if (projeto.getMiVpl() <= 0)
        {
            continue;
        }

        // se inserir projeto ultrapassa restrição de gastos, pular
        if (projeto.getCusto() + solucao.getGastos() > dataset.getCapitalTotal())
        {
            continue;
        }

        // para cada sonda
        for (std::vector<Sonda>::iterator itrS=sondas.begin(); itrS!=sondas.end(); ++itrS)
        {
            // buscar janela viável
            Sonda sonda = *itrS;

            std::cout << std::endl;
            std::cout << "Buscando janela viável para o projeto " << projeto.getNome() << " na sonda " << sonda.getNome();
            std::cout << std::endl;

            int modo = this->_modoRealoc;
            bool alocExiste = false;
            int posicaoAloc = -1;
            Intervalo intervaloAloc{};
            int prevMinus = 0;
            int currMinus = 0;
            int currPlus = 0;
            int nextPlus = 0;
            int caso = 0;
            std::tie(alocExiste, posicaoAloc, intervaloAloc, prevMinus, currMinus, currPlus, nextPlus, caso) = 
                                                                    solucao.buscarJanelaViavel(sonda, projeto, modo);

            // mostra resultados da busca
            std::cout << "Janela viável encontrada? " << alocExiste << std::endl;
            std::cout << "Posição para alocação: " << posicaoAloc << std::endl;
            std::cout << "prevMinus: " << prevMinus << std::endl;
            std::cout << "currMinus: " << currMinus << std::endl;
            std::cout << "currPlus: " << currPlus << std::endl;
            std::cout << "nextPlus: " << nextPlus << std::endl;
            std::cout << "Intervalo para alocação: " << std::endl;
            intervaloAloc.print();

            // se viável, insere
            if (alocExiste)
            {
                solucao.inserirProjeto(sonda, projeto, posicaoAloc, intervaloAloc, prevMinus, 
                                                currMinus, currPlus, nextPlus, caso);
                
                std::cout << "Mostrando alocações após inserção do projeto " << projeto.getNome() << std::endl;
                solucao.print();
            }
        }
    }

    std::cout << std::endl;
    std::cout << "Solução construída =============================================";
    std::cout << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();

    return std::make_tuple(solucao, tempo);
}

std::tuple<Solucao, int> ConstrutorHeuristico::ConstruirSolucao(DadosDeEntrada dataset, std::map<Sonda, std::vector<Alocacao>> alocacoes)
{
    // TODO
}

