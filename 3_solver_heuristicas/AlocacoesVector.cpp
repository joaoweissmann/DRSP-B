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
#include "AlocacoesVector.h"

AlocacoesVector::AlocacoesVector(std::set<Sonda> sondas)
{
    for (std::set<Sonda>::iterator itr=sondas.begin(); itr!=sondas.end(); ++itr)
    {
        _alocacoes.insert(std::pair<Sonda, std::vector<Alocacao>>(*itr, std::vector<Alocacao>()));
    }
}

AlocacoesVector::AlocacoesVector(std::map<Sonda, std::vector<Alocacao>> alocacoes)
{
    for (std::map<Sonda, std::vector<Alocacao>>::iterator itr=alocacoes.begin(); itr!=alocacoes.end(); ++itr)
    {
        _alocacoes.insert(std::pair<Sonda, std::vector<Alocacao>>(itr->first, itr->second));
    }
}

AlocacoesVector::AlocacoesVector(std::map<Sonda, std::list<Alocacao>> alocacoes)
{
    for (std::map<Sonda, std::list<Alocacao>>::iterator itr=alocacoes.begin(); itr!=alocacoes.end(); ++itr)
    {
        Sonda sonda = itr->first;
        std::list<Alocacao> listaAloc = itr->second;
        std::vector<Alocacao> vetorAloc;
        for (std::list<Alocacao>::iterator itr=listaAloc.begin(); itr!=listaAloc.end(); ++itr)
        {
            Alocacao x = *itr;
            vetorAloc.push_back(x);
        }
        _alocacoes.insert(std::pair<Sonda, std::vector<Alocacao>>(sonda, vetorAloc));
    }
}

/*
AlocacoesVector AlocacoesVector::copyFrom(AlocacoesVector alocacoes)
{
    AlocacoesVector x{alocacoes.getAlocacoes()};
    return x;
}

AlocacoesVector AlocacoesVector::copyFrom(AlocacoesList alocacoes)
{
    AlocacoesVector x{alocacoes.getAlocacoes()};
    return x;
}
*/

void AlocacoesVector::print()
{
    std::cout << std::endl;
    std::cout << "------------------ mostrando alocações ------------------" << std::endl;
    Sonda s{};
    int count = 0;
    for (std::map<Sonda, std::vector<Alocacao>>::iterator itr=_alocacoes.begin(); itr!=_alocacoes.end(); ++itr)
    {
        s.copyFrom(itr->first);
        std::cout << "Mostrando alocações da sonda" << s.getNome() << std::endl;
        s.print();
        count = 0;
        for (std::vector<Alocacao>::iterator itrv=itr->second.begin(); itrv!=itr->second.end(); ++itrv)
        {
            std::cout << "A alocação de índice " << count << " é: " << std::endl;
            (*itrv).print();
            count++;
        }
        count = 0;
    }
    std::cout << "------------------ alocações mostradas ------------------" << std::endl;
    std::cout << std::endl;
}

int AlocacoesVector::getNSondas()
{
    return _alocacoes.size();
}

std::set<Sonda> AlocacoesVector::getSondas()
{
    std::set<Sonda> sondas;

    for (std::map<Sonda, std::vector<Alocacao>>::iterator itr=_alocacoes.begin(); itr!=_alocacoes.end(); ++itr)
    {
        sondas.insert(itr->first);
    }

    return sondas;
}

std::map<Sonda, std::vector<Alocacao>> AlocacoesVector::getAlocacoes()
{
    return _alocacoes;
}

std::vector<Alocacao> AlocacoesVector::getAlocacoes(Sonda sonda)
{
    std::map<Sonda, std::vector<Alocacao>>::iterator itr = _alocacoes.find(sonda);
    if (itr == _alocacoes.end())
    {
        std::cout << "A sonda especificada não está nas alocações." << std::endl;
        std::vector<Alocacao> vetor;
        return vetor;
    }
    else
    {
        return itr->second;
    }
}
/*
void Alocacoes::setAlocacoes(std::map<Sonda, std::vector<Alocacao>>)
{
    // TODO
}

void Alocacoes::setAlocacoes(Sonda, std::vector<Alocacao>)
{
    // TODO
}

int Alocacoes::getNAlocacoes(Sonda)
{
    // TODO
}

Alocacao Alocacoes::getAlocacao(Sonda, int)
{
    // TODO
}

Alocacao Alocacoes::getAlocacao(Sonda, Projeto)
{
    // TODO
}

int Alocacoes::getAlocacaoIndex(Sonda, Projeto)
{
    // TODO
}

void Alocacoes::setAlocacao(Sonda, int, Alocacao)
{
    // TODO
}

void Alocacoes::setAlocacao(Sonda, Projeto, Alocacao)
{
    // TODO
}

int Alocacoes::getDesloc(Sonda, int)
{
    // TODO
}

int Alocacoes::getGapLeft(Sonda, int)
{
    // TODO
}

int Alocacoes::getGapRight(Sonda, int)
{
    // TODO
}

int Alocacoes::getFolgaLeft(Sonda, int)
{
    // TODO
}

int Alocacoes::getFolgaRight(Sonda, int)
{
    // TODO
}

bool Alocacoes::isPrimeiraAlocacao(Sonda, Projeto)
{
    // TODO
}

bool Alocacoes::isUltimaAlocacao(Sonda, Projeto)
{
    // TODO
}

bool Alocacoes::isEmpty(Sonda)
{
    // TODO
}

bool Alocacoes::isFeasible(Alocacao)
{
    // TODO
}

std::tuple<bool, int, Intervalo, int, int, int, int> Alocacoes::buscarJanelaViavel(Sonda, Projeto)
{
    // TODO
}

std::tuple<> Alocacoes::inserirProjeto(Sonda, Projeto, Intervalo, int, int, int, int, int)
{
    // TODO
}

std::tuple<> Alocacoes::removerProjeto(Sonda, int)
{
    // TODO
}

std::tuple<> Alocacoes::trocarProjetos(Sonda, int, Sonda, int)
{
    // TODO
}

*/