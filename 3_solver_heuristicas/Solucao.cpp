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
#include "Solucao.h"

Solucao::Solucao(int dataStructure, DadosDeEntrada dataset)
{
    std::vector<Sonda> sondasVector = dataset.getSondas();
    std::set<Sonda> sondas;
    for (std::vector<Sonda>::iterator it=sondasVector.begin(); it!=sondasVector.end(); ++it)
    {
        Sonda x = *it;
        sondas.insert(x);
    }

    this->_deltaT = dataset.getDelta();

    if (dataStructure == 1) // 1 -> vector
    {
        AlocacoesVector alocsVectorTemp{sondas};
        this->_alocsVector = alocsVectorTemp;
        this->_ptrAlocacoes = & this->_alocsVector;
    }
    else if (dataStructure == 2) // 2 -> list
    {
        AlocacoesList alocsListTemp{sondas};
        this->_alocsList = alocsListTemp;
        this->_ptrAlocacoes = & this->_alocsList;
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Estrutura de dados fornecida é inválida. Valor fornecido: " << dataStructure;
        std::cout << std::endl;
    }
    assert ( (dataStructure==1) || (dataStructure==2));
    
    this->_gastos = 0;
    this->_fitness = 0;
    this->_totalFree = dataset.getNPeriodos() * sondas.size();

    std::vector<Projeto> projetos = dataset.getProjetos();
    for (std::vector<Projeto>::iterator itr=projetos.begin(); itr!=projetos.end(); ++itr)
    {
        Projeto x = *itr;
        this->_projetosNaoAlocados.insert(x);
    }
}

Solucao::Solucao(std::map<Sonda, std::vector<Alocacao>> alocacoesIn, int dataStructure, DadosDeEntrada dataset)
{
    this->_deltaT = dataset.getDelta();

    if (dataStructure == 1) // 1 -> vector
    {
        AlocacoesVector alocsVectorTemp{alocacoesIn, this->_deltaT};
        this->_alocsVector = alocsVectorTemp;
        this->_ptrAlocacoes = & this->_alocsVector;
    }
    else if (dataStructure == 2) // 2 -> list
    {
        AlocacoesList alocsListTemp{alocacoesIn, this->_deltaT};
        this->_alocsList = alocsListTemp;
        this->_ptrAlocacoes = & this->_alocsList;
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Estrutura de dados fornecida é inválida. Valor fornecido: " << dataStructure;
        std::cout << std::endl;
    }
    assert ( (dataStructure==1) || (dataStructure==2));
    
    this->_gastos = 0;
    this->_fitness = 0;
    std::set<Sonda> sondas = this->_ptrAlocacoes->getSondas();
    this->_totalFree = dataset.getNPeriodos() * sondas.size();

    // inicializa conjunto de projetos usados
    for (std::map<Sonda, std::vector<Alocacao>>::iterator itrS=alocacoesIn.begin(); itrS!=alocacoesIn.end(); ++itrS)
    {
        Sonda sonda = itrS->first;
        for (std::vector<Alocacao>::iterator itrP=alocacoesIn[sonda].begin(); itrP!=alocacoesIn[sonda].end(); ++itrP)
        {
            Alocacao x = *itrP;
            this->_projetosAlocados.insert(x.getProjeto());
            
            // atualiza valores da solução
            // mapa projetos para alocações
            if (this->_mapProjeto2Alocacao.find(x.getProjeto()) == this->_mapProjeto2Alocacao.end())
            {
                this->_mapProjeto2Alocacao.insert(std::pair<Projeto, Alocacao>(x.getProjeto(), x));
            }
            else
            {
                std::cout << std::endl;
                std::cout << "Projeto alocado mais de uma vez! ============================ ERRO!";
                std::cout << std::endl;
            }
            // gastos
            this->_gastos += x.getProjeto().getCusto();
            // fitness
            this->_fitness += x.getProjeto().getMiVpl();
            // total free
            Intervalo intervalo = itrP->getIntervalo();
            this->_totalFree -= intervalo.getFinal() - intervalo.getInicio() + 1;
        }
    }

    // inicializa conjunto de projetos não usados
    std::vector<Projeto> projetos = dataset.getProjetos();
    for (std::vector<Projeto>::iterator itrP=projetos.begin(); itrP!=projetos.end(); ++itrP)
    {
        Projeto x = *itrP;
        std::set<Projeto>::iterator itrF = this->_projetosAlocados.find(x);
        if (itrF == this->_projetosAlocados.end())
        {
            this->_projetosNaoAlocados.insert(x);
        }
    }
}

std::set<Projeto> Solucao::getProjetosAlocados()
{
    return this->_projetosAlocados;
}

std::set<Projeto> Solucao::getProjetosNaoAlocados()
{
    return this->_projetosNaoAlocados;
}

std::map<Projeto, Alocacao> Solucao::getMapProjeto2Alocacao()
{
    return this->_mapProjeto2Alocacao;
}

double Solucao::getGastos()
{
    return this->_gastos;
}

double Solucao::getFitness()
{
    return this->_fitness;
}

int Solucao::getTotalFree()
{
    return this->_totalFree;
}

std::map<Sonda, std::vector<Alocacao>> Solucao::getAlocacoes()
{
    return this->_ptrAlocacoes->getAlocacoes();
}

std::set<Sonda> Solucao::getSondas()
{
    return this->_ptrAlocacoes->getSondas();
}

std::tuple<bool, int, Intervalo, int, int, int, int, int> Solucao::buscarJanelaViavel(Sonda sonda, Projeto projeto, int modo)
{
    return this->_ptrAlocacoes->buscarJanelaViavel(sonda, projeto, modo, this->_deltaT);
}

void Solucao::inserirProjeto(Sonda sonda, Projeto projeto, int posicaoAloc, Intervalo intervalo, 
                                     int prevMinus, int currMinus, int currPlus, int nextPlus, int caso)
{
    if (this->_projetosAlocados.find(projeto) == this->_projetosAlocados.end())
    {
        this->_projetosAlocados.insert(projeto);
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Projeto a ser inserido já está no conjunto de projetos alocados! ================== ERRO!";
        std::cout << std::endl;
    }

    if (this->_projetosNaoAlocados.find(projeto) == this->_projetosNaoAlocados.end())
    {
        std::cout << std::endl;
        std::cout << "Projeto a ser inserido não está no conjunto de projetos NÃO alocados! =============== ERRO!";
        std::cout << std::endl;
    }
    else
    {
        this->_projetosNaoAlocados.erase(projeto);
    }

    if (this->_mapProjeto2Alocacao.find(projeto) == this->_mapProjeto2Alocacao.end())
    {
        Alocacao alocacao{projeto, sonda, intervalo};
        this->_mapProjeto2Alocacao.insert(std::pair<Projeto, Alocacao>(projeto, alocacao));
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Projeto a ser inserido já está no mapa de projetos alocados! ======================== ERRO!";
        std::cout << std::endl;
    }

    this->_gastos += projeto.getCusto();
    this->_fitness += projeto.getMiVpl();
    this->_totalFree -= intervalo.getFinal() - intervalo.getInicio() + 1;

    this->_ptrAlocacoes->inserirProjeto(sonda, projeto, posicaoAloc, intervalo, 
                                        prevMinus, currMinus, currPlus, nextPlus, caso);
}

bool Solucao::removerProjeto(Sonda sonda, Projeto projeto, Intervalo intervalo)
{
    bool result = this->_ptrAlocacoes->removerProjeto(sonda, projeto, this->_deltaT);

    if (result)
    {
        if (this->_projetosAlocados.find(projeto) == this->_projetosAlocados.end())
        {
            std::cout << std::endl;
            std::cout << "Projeto a ser removido não está no conjunto de alocados! ========================= ERRO!";
            std::cout << std::endl;
        }
        else
        {
            this->_projetosAlocados.erase(projeto);
        }

        if (this->_projetosNaoAlocados.find(projeto) == this->_projetosNaoAlocados.end())
        {
            this->_projetosNaoAlocados.insert(projeto);
        }
        else
        {
            std::cout << std::endl;
            std::cout << "Projeto a ser removido já está no conjunto de NÃO alocados! ======================= ERRO!";
            std::cout << std::endl;
        }

        if (this->_mapProjeto2Alocacao.find(projeto) == this->_mapProjeto2Alocacao.end())
        {
            std::cout << std::endl;
            std::cout << "Projeto a ser removido não está no mapa de alocados! ============================ ERRO!";
            std::cout << std::endl;
        }
        else
        {
            this->_mapProjeto2Alocacao.erase(projeto);
        }

        this->_gastos -= projeto.getCusto();
        this->_fitness -= projeto.getMiVpl();
        this->_totalFree += intervalo.getFinal() - intervalo.getInicio() + 1;
    }
    else
    {
        //std::cout << std::endl;
        //std::cout << "Não é possível fazer a remoção do projeto.";
        //std::cout << std::endl;
    }

    return result;
}

void Solucao::print()
{
    std::cout << std::endl;

    std::cout << "A solução tem: " << std::endl;
    std::cout << "fitness: " << this->_fitness << std::endl;
    std::cout << "gastos: " << this->_gastos << std::endl;
    std::cout << "total free: " << this->_totalFree << std::endl;

    std::cout << "Projetos alocados: ";
    for (std::set<Projeto>::iterator itr=this->_projetosAlocados.begin(); itr!=this->_projetosAlocados.end(); ++itr)
    {
        Projeto x = *itr;
        std::cout << x.getNome() << ", ";
    } std::cout << std::endl;

    std::cout << "Projetos não alocados: ";
    for (std::set<Projeto>::iterator itr=this->_projetosNaoAlocados.begin(); itr!=this->_projetosNaoAlocados.end(); ++itr)
    {
        Projeto x = *itr;
        std::cout << x.getNome() << ", ";
    } std::cout << std::endl;

    std::cout << "Alocações:" << std::endl;
    AlocacoesVector alocs{this->_ptrAlocacoes->getAlocacoes(), this->_deltaT};
    alocs.print();

    std::cout << std::endl;
}

