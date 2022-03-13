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
#include "VerificadorDeSolucao.h"

bool VerificadorDeSolucao::verificarFitness(Solucao s)
{
    double fitness = 0;
    std::map<Sonda, std::vector<Alocacao>> alocs = s.getAlocacoes();
    for (std::map<Sonda, std::vector<Alocacao>>::iterator it=alocs.begin(); it!=alocs.end(); ++it)
    {
        Sonda sonda = it->first;
        for (std::vector<Alocacao>::iterator itr=alocs[sonda].begin(); itr!=alocs[sonda].end(); ++itr)
        {
            Projeto x = (*itr).getProjeto();
            fitness += x.getMiVpl();
        }
    }
    bool result = fitness == s.getFitness();
    return (result);
}

bool VerificadorDeSolucao::verificarGastos(Solucao s)
{
    double gastos = 0;
    std::map<Sonda, std::vector<Alocacao>> alocs = s.getAlocacoes();
    for (std::map<Sonda, std::vector<Alocacao>>::iterator it=alocs.begin(); it!=alocs.end(); ++it)
    {
        Sonda sonda = it->first;
        for (std::vector<Alocacao>::iterator itr=alocs[sonda].begin(); itr!=alocs[sonda].end(); ++itr)
        {
            Projeto x = (*itr).getProjeto();
            gastos += x.getMiVpl();
        }
    }
    bool result = gastos == s.getFitness();
    return (result);
}

bool VerificadorDeSolucao::verificarTotalFree(Solucao s)
{
    double totalFree = 0;
    std::map<Sonda, std::vector<Alocacao>> alocs = s.getAlocacoes();
    for (std::map<Sonda, std::vector<Alocacao>>::iterator it=alocs.begin(); it!=alocs.end(); ++it)
    {
        Sonda sonda = it->first;
        for (std::vector<Alocacao>::iterator itr=alocs[sonda].begin(); itr!=alocs[sonda].end(); ++itr)
        {
            Projeto x = (*itr).getProjeto();
            totalFree += x.getMiVpl();
        }
    }
    bool result = totalFree == s.getFitness();
    return (result);
}

bool VerificadorDeSolucao::verificarUnicidadeProjetos(Solucao s)
{
    bool result = true;
    std::set<Projeto> projSet;
    std::map<Sonda, std::vector<Alocacao>> alocs = s.getAlocacoes();
    for (std::map<Sonda, std::vector<Alocacao>>::iterator it=alocs.begin(); it!=alocs.end(); ++it)
    {
        Sonda sonda = it->first;
        for (std::vector<Alocacao>::iterator itr=alocs[sonda].begin(); itr!=alocs[sonda].end(); ++itr)
        {
            Projeto x = (*itr).getProjeto();
            std::set<Projeto>::iterator itP = projSet.find(x);
            if (itP == projSet.end())
            {
                projSet.insert(x);
            }
            else
            {
                std::cout << std::endl;
                std::cout << "Projeto duplicado! ====================== ERRO!";
                std::cout << std::endl;
                result = false;
                break;
            }
        }
    }
    return result;
}

bool VerificadorDeSolucao::verificarTimeWindows(Solucao s)
{
    bool result = true;
    std::map<Sonda, std::vector<Alocacao>> alocs = s.getAlocacoes();
    for (std::map<Sonda, std::vector<Alocacao>>::iterator it=alocs.begin(); it!=alocs.end(); ++it)
    {
        Sonda sonda = it->first;
        for (std::vector<Alocacao>::iterator itr=alocs[sonda].begin(); itr!=alocs[sonda].end(); ++itr)
        {
            Projeto x = (*itr).getProjeto();
            Intervalo y = (*itr).getIntervalo();
            if ( ! ( (y.getInicio() >= x.getInicioJanela()) && (y.getFinal() <= x.getFinalJanela()) ) )
            {
                std::cout << std::endl;
                std::cout << "Projeto alocado fora da sua janela viável ================================= ERRO!";
                std::cout << std::endl;
                result = false;
                break;
            }
        }
    }
    return result;
}

bool VerificadorDeSolucao::verificarScheduling(Solucao s, DadosDeEntrada dataset)
{
    bool result = true;
    CalculadorDeDesloc calc{};
    std::map<Sonda, std::vector<Alocacao>> alocs = s.getAlocacoes();
    for (std::map<Sonda, std::vector<Alocacao>>::iterator it=alocs.begin(); it!=alocs.end(); ++it)
    {
        Sonda sonda = it->first;
        for (std::vector<Alocacao>::iterator itr=alocs[sonda].begin(); itr!=alocs[sonda].end(); ++itr)
        {
            Alocacao x = *itr;
            double setup;
            if (itr==alocs[sonda].begin())
            {
                setup = calc.getDesloc(sonda, x.getProjeto(), dataset.getDelta());
            }
            else
            {
                setup = calc.getDesloc(std::prev(itr,1)->getProjeto(), itr->getProjeto(), dataset.getDelta());
            }
            Intervalo y = itr->getIntervalo();
            int duracao = y.getFinal() - y.getInicio() + 1;
            if ( ! (duracao == (int)setup + x.getProjeto().getTempExec()) )
            {
                std::cout << std::endl;
                std::cout << "Duração do intervalo não corresponde ao setup + proc ========================== ERRO!" << std::endl;
                //std::cout << "(int)setup = " << (int)setup << std::endl;
                //std::cout << "tempExec = " << itr->getProjeto().getTempExec() << std::endl;
                //std::cout << "inicio do intervalo = " << y.getInicio() << std::endl;
                //std::cout << "final do intervalo = " << y.getFinal() << std::endl;
                //std::cout << "duração do intervalo = " << duracao << std::endl;
                result = false;
                break;
            }
        }
    }
    return result;
}

bool VerificadorDeSolucao::verificarContinuidadeTemporal(Solucao s)
{
    bool result = true;
    std::map<Sonda, std::vector<Alocacao>> alocs = s.getAlocacoes();
    for (std::map<Sonda, std::vector<Alocacao>>::iterator it=alocs.begin(); it!=alocs.end(); ++it)
    {
        Sonda sonda = it->first;
        for (std::vector<Alocacao>::iterator itr=alocs[sonda].begin(); itr!=alocs[sonda].end(); ++itr)
        {
            Intervalo x = itr->getIntervalo();
            if (itr != alocs[sonda].begin())
            {
                Intervalo y = std::prev(itr,1)->getIntervalo();
                if ( ! (y.getFinal() < x.getInicio()) )
                {
                    std::cout << std::endl;
                    std::cout << "Continuidade temporal incorreta ========================= ERRO!";
                    std::cout << std::endl;
                    result = false;
                    break;
                }
            }
        }
    }
    return result;
}

bool VerificadorDeSolucao::verificarSolucao(Solucao s, DadosDeEntrada dataset)
{
    bool b1 = verificarFitness(s);
    bool b2 = verificarGastos(s);
    bool b3 = verificarTotalFree(s);
    bool b4 = verificarUnicidadeProjetos(s);
    bool b5 = verificarContinuidadeTemporal(s);
    bool b6 = verificarScheduling(s, dataset);
    bool b7 = verificarTimeWindows(s);
    bool result = b1 && b2 && b3 && b4 && b5 && b6 && b7;
    return result;
}

