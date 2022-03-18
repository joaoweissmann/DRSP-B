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
#include "AlocacoesList.h"

AlocacoesList::AlocacoesList()
{
    Sonda s{};
    std::list<Alocacao> lista;
    this->_alocacoes.insert(std::pair<Sonda, std::list<Alocacao>>(s, lista));
}

AlocacoesList::AlocacoesList(std::set<Sonda> sondas)
{
    for(std::set<Sonda>::iterator itr = sondas.begin(); itr != sondas.end(); ++itr)
    {
        std::list<Alocacao> lista;
        _alocacoes.insert(std::pair<Sonda, std::list<Alocacao>>(*itr, lista));
    }
}

AlocacoesList::AlocacoesList(std::map<Sonda, std::list<Alocacao>> alocacoes, int deltaT)
{
    // checar interceção
    bool feasible = true; 
    for (std::map<Sonda, std::list<Alocacao>>::iterator its=alocacoes.begin(); its!=alocacoes.end(); ++its)
    {
        Sonda sonda{};
        sonda = its->first;
        for (std::list<Alocacao>::iterator itv1=alocacoes[sonda].begin(); itv1 != alocacoes[sonda].end(); ++itv1)
        {
            Alocacao aloc{};
            aloc = *itv1;
            for (std::list<Alocacao>::iterator itv2=alocacoes[sonda].begin(); itv2 != alocacoes[sonda].end(); ++itv2)
            {
                Alocacao alocX{};
                alocX = *itv2;
                if (aloc == alocX)
                {
                    continue;
                }
                if (!((aloc.getIntervalo().getFinal() < alocX.getIntervalo().getInicio()) 
                    ||
                    (aloc.getIntervalo().getInicio() > alocX.getIntervalo().getFinal())))
                    {
                        std::cout << std::endl;
                        std::cout << "Alocações não viáveis, pois existe interceção.";
                        std::cout << "Interceção entre as alocações dos projetos" << aloc.getProjeto().getNome() << " e "
                                                                                  << alocX.getProjeto().getNome() << " na sonda "
                                                                                  << sonda.getNome();
                        std::cout << std::endl;
                        feasible = false;
                        break;
                    }
            }
            if (!feasible)
            {
                break;
            }
        }
        if (!feasible)
        {
            break;
        }
    }
    assert (feasible);

    // checar continuidade e tamanho das alocações
    for (std::map<Sonda, std::list<Alocacao>>::iterator its = alocacoes.begin(); its != alocacoes.end(); ++its)
    {
        Sonda sonda = its->first;
        for (std::list<Alocacao>::iterator itv = alocacoes[sonda].begin(); itv != alocacoes[sonda].end(); ++itv)
        {
            Alocacao aloc = *itv;
            Projeto projeto = aloc.getProjeto();
            Intervalo intervalo = aloc.getIntervalo();
            CalculadorDeDesloc calc{};
            double desloc;
            if ( (itv == alocacoes[sonda].begin()) && (std::next(itv,1) == alocacoes[sonda].end()) )
            {
                // alocacao única
                desloc = calc.getDesloc(sonda, projeto, deltaT);
                if ( !(intervalo.getInicio() + (int)desloc + projeto.getTempExec() - 1 == intervalo.getFinal()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois tamanho da alocação não está correto.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << "origem" << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
            }
            if ( (itv == alocacoes[sonda].begin()) && !(std::next(itv,1) == alocacoes[sonda].end()) )
            {
                // alocação begin, mas existe uma próxima alocação
                desloc = calc.getDesloc(sonda, projeto, deltaT);
                if ( !(intervalo.getInicio() + (int)desloc + projeto.getTempExec() - 1 == intervalo.getFinal()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois tamanho da alocação não está correto.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << "origem" << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
                Alocacao alocNext = *(std::next(itv));
                Intervalo intervaloNext = alocNext.getIntervalo();
                if ( !(intervalo.getFinal() < intervaloNext.getInicio()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois continuidade temporal não está correta.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << "origem" << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
            }
            if ( !(itv == alocacoes[sonda].begin()) && (std::next(itv) == alocacoes[sonda].end()) )
            {
                // última alocação, mas existe alocação prévia
                Alocacao alocPrev = *(std::prev(itv));
                Projeto projPrev = alocPrev.getProjeto();
                desloc = calc.getDesloc(projPrev, projeto, deltaT);
                if ( !(intervalo.getInicio() + (int)desloc + projeto.getTempExec() - 1 == intervalo.getFinal()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois tamanho da alocação não está correto.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
                Intervalo intervaloPrev = alocPrev.getIntervalo();
                if ( !(intervaloPrev.getFinal() < intervalo.getInicio()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois continuidade temporal não está correta.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
            }
            if ( !(itv == alocacoes[sonda].begin()) && !(std::next(itv) == alocacoes[sonda].end()) )
            {
                // existe alocação prévia e próxima
                Alocacao alocPrev = *(std::prev(itv));
                Alocacao alocNext = *(std::next(itv));
                Projeto projPrev = alocPrev.getProjeto();
                Projeto projNext = alocNext.getProjeto();
                Intervalo intervaloPrev = alocPrev.getIntervalo();
                Intervalo intervaloNext = alocNext.getIntervalo();
                desloc = calc.getDesloc(projPrev, projeto, deltaT);
                if ( !(intervalo.getInicio() + (int)desloc + projeto.getTempExec() - 1 == intervalo.getFinal()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois tamanho da alocação não está correto.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
                if ( !(intervaloPrev.getFinal() < intervalo.getInicio()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois continuidade temporal não está correta.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
                if ( !(intervalo.getFinal() < intervaloNext.getInicio()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois continuidade temporal não está correta.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
            }
        }
        if (!feasible)
        {
            break;
        }
    }
    assert (feasible);

    for(std::map<Sonda, std::list<Alocacao>>::iterator itr=alocacoes.begin(); itr!=alocacoes.end(); ++itr)
    {
        _alocacoes.insert(std::pair<Sonda, std::list<Alocacao>>(itr->first, itr->second));
    }
}

AlocacoesList::AlocacoesList(std::map<Sonda, std::vector<Alocacao>> alocacoes, int deltaT)
{
    // checar interceção
    bool feasible = true; 
    for (std::map<Sonda, std::vector<Alocacao>>::iterator its=alocacoes.begin(); its!=alocacoes.end(); ++its)
    {
        Sonda sonda{};
        sonda = its->first;
        for (std::vector<Alocacao>::iterator itv1=alocacoes[sonda].begin(); itv1 != alocacoes[sonda].end(); ++itv1)
        {
            Alocacao aloc{};
            aloc = *itv1;
            for (std::vector<Alocacao>::iterator itv2=alocacoes[sonda].begin(); itv2 != alocacoes[sonda].end(); ++itv2)
            {
                Alocacao alocX{};
                alocX = *itv2;
                if (aloc == alocX)
                {
                    continue;
                }
                if (!((aloc.getIntervalo().getFinal() < alocX.getIntervalo().getInicio()) 
                    ||
                    (aloc.getIntervalo().getInicio() > alocX.getIntervalo().getFinal())))
                    {
                        std::cout << std::endl;
                        std::cout << "Alocações não viáveis, pois existe interceção.";
                        std::cout << "Interceção entre as alocações dos projetos" << aloc.getProjeto().getNome() << " e "
                                                                                  << alocX.getProjeto().getNome() << " na sonda "
                                                                                  << sonda.getNome();
                        std::cout << std::endl;
                        feasible = false;
                        break;
                    }
            }
            if (!feasible)
            {
                break;
            }
        }
        if (!feasible)
        {
            break;
        }
    }
    assert (feasible);

    // checar continuidade e tamanho das alocações
    for (std::map<Sonda, std::vector<Alocacao>>::iterator its = alocacoes.begin(); its != alocacoes.end(); ++its)
    {
        Sonda sonda = its->first;
        for (std::vector<Alocacao>::iterator itv = alocacoes[sonda].begin(); itv != alocacoes[sonda].end(); ++itv)
        {
            Alocacao aloc = *itv;
            Projeto projeto = aloc.getProjeto();
            Intervalo intervalo = aloc.getIntervalo();
            CalculadorDeDesloc calc{};
            double desloc;
            if ( (itv == alocacoes[sonda].begin()) && (itv+1 == alocacoes[sonda].end()) )
            {
                // alocacao única
                desloc = calc.getDesloc(sonda, projeto, deltaT);
                if ( !(intervalo.getInicio() + (int)desloc + projeto.getTempExec() - 1 == intervalo.getFinal()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois tamanho da alocação não está correto.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << "origem" << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
            }
            if ( (itv == alocacoes[sonda].begin()) && !(itv+1 == alocacoes[sonda].end()) )
            {
                // alocação begin, mas existe uma próxima alocação
                desloc = calc.getDesloc(sonda, projeto, deltaT);
                if ( !(intervalo.getInicio() + (int)desloc + projeto.getTempExec() - 1 == intervalo.getFinal()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois tamanho da alocação não está correto.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << "origem" << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
                Alocacao alocNext = *(itv+1);
                Intervalo intervaloNext = alocNext.getIntervalo();
                if ( !(intervalo.getFinal() < intervaloNext.getInicio()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois continuidade temporal não está correta.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << "origem" << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
            }
            if ( !(itv == alocacoes[sonda].begin()) && (itv+1 == alocacoes[sonda].end()) )
            {
                // última alocação, mas existe alocação prévia
                Alocacao alocPrev = *(itv-1);
                Projeto projPrev = alocPrev.getProjeto();
                desloc = calc.getDesloc(projPrev, projeto, deltaT);
                if ( !(intervalo.getInicio() + (int)desloc + projeto.getTempExec() - 1 == intervalo.getFinal()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois tamanho da alocação não está correto.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
                Intervalo intervaloPrev = alocPrev.getIntervalo();
                if ( !(intervaloPrev.getFinal() < intervalo.getInicio()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois continuidade temporal não está correta.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
            }
            if ( !(itv == alocacoes[sonda].begin()) && !(itv+1 == alocacoes[sonda].end()) )
            {
                // existe alocação prévia e próxima
                Alocacao alocPrev = *(itv-1);
                Alocacao alocNext = *(itv+1);
                Projeto projPrev = alocPrev.getProjeto();
                Projeto projNext = alocNext.getProjeto();
                Intervalo intervaloPrev = alocPrev.getIntervalo();
                Intervalo intervaloNext = alocNext.getIntervalo();
                desloc = calc.getDesloc(projPrev, projeto, deltaT);
                if ( !(intervalo.getInicio() + (int)desloc + projeto.getTempExec() - 1 == intervalo.getFinal()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois tamanho da alocação não está correto.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
                if ( !(intervaloPrev.getFinal() < intervalo.getInicio()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois continuidade temporal não está correta.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
                if ( !(intervalo.getFinal() < intervaloNext.getInicio()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois continuidade temporal não está correta.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
            }
        }
        if (!feasible)
        {
            break;
        }
    }
    assert (feasible);

    for (std::map<Sonda, std::vector<Alocacao>>::iterator itr=alocacoes.begin(); itr!=alocacoes.end(); ++itr)
    {
        Sonda sonda = itr->first;
        std::vector<Alocacao> vetorAloc = itr->second;
        std::list<Alocacao> listAloc;
        for (std::vector<Alocacao>::iterator it=vetorAloc.begin(); it!=vetorAloc.end(); ++it)
        {
            Alocacao x = *it;
            listAloc.push_back(x);
        }
        _alocacoes.insert(std::pair<Sonda, std::list<Alocacao>>(sonda, listAloc));
    }
}

/*
AlocacoesList AlocacoesList::copyFrom(AlocacoesVector alocacoes)
{
    AlocacoesList x{alocacoes.getAlocacoes()};
    return x;
}

AlocacoesList AlocacoesList::copyFrom(AlocacoesList alocacoes)
{
    AlocacoesList x{alocacoes.getAlocacoes()};
    return x;
}
*/

void AlocacoesList::print()
{
    std::cout << std::endl;
    std::cout << "------------------ mostrando alocações ------------------" << std::endl;
    Sonda s{};
    int count = 0;
    for (std::map<Sonda, std::list<Alocacao>>::iterator itr=_alocacoes.begin(); itr!=_alocacoes.end(); ++itr)
    {
        s.copyFrom(itr->first);
        std::cout << "Mostrando alocações da sonda" << s.getNome() << std::endl;
        s.print();
        count = 0;
        for (std::list<Alocacao>::iterator itrl=itr->second.begin(); itrl!=itr->second.end(); ++itrl)
        {
            std::cout << "A alocação de índice " << count << " é: " << std::endl;
            (*itrl).print();
            count++;
        }
        count = 0;
    }
    std::cout << "------------------ alocações mostradas ------------------" << std::endl;
    std::cout << std::endl;
}

int AlocacoesList::getNSondas()
{
    return _alocacoes.size();
}

std::set<Sonda> AlocacoesList::getSondas()
{
    std::set<Sonda> sondas;

    for (std::map<Sonda, std::list<Alocacao>>::iterator itr=_alocacoes.begin(); itr!=_alocacoes.end(); ++itr)
    {
        sondas.insert(itr->first);
    }

    return sondas;
}

std::map<Sonda, std::vector<Alocacao>> AlocacoesList::getAlocacoes()
{
    std::map<Sonda, std::vector<Alocacao>> alocsNew;

    for (std::map<Sonda, std::list<Alocacao>>::iterator it=_alocacoes.begin(); it!=_alocacoes.end(); ++it)
    {
        Sonda sonda = it->first;
        std::vector<Alocacao> vetor;
        alocsNew.insert(std::pair<Sonda, std::vector<Alocacao>>(sonda, vetor));
        std::list<Alocacao> listAlocs = it->second;
        for (std::list<Alocacao>::iterator itr=listAlocs.begin(); itr!=listAlocs.end(); ++itr)
        {
            Alocacao x = *itr;
            alocsNew[sonda].push_back(x);
        }
    }

    return alocsNew;
}

std::vector<Alocacao> AlocacoesList::getAlocacoes(Sonda sonda)
{
    std::map<Sonda, std::list<Alocacao>>::iterator itr = _alocacoes.find(sonda);
    if (itr == _alocacoes.end())
    {
        std::cout << "A sonda especificada não está nas alocações." << std::endl;
        std::vector<Alocacao> vetor;
        return vetor;
    }
    else
    {
        std::vector<Alocacao> vetor;
        std::list<Alocacao> alocSonda = itr->second;
        for (std::list<Alocacao>::iterator it = alocSonda.begin(); it != alocSonda.end(); ++it)
        {
            Alocacao x = *it;
            vetor.push_back(x);
        }
        return vetor;
    }
}

int AlocacoesList::getNAlocacoes(Sonda sonda)
{
    std::map<Sonda, std::list<Alocacao>>::iterator it = _alocacoes.find(sonda);
    if (it == _alocacoes.end())
    {
        std::cout << "A sonda especificada não foi encontrada." << std::endl;
        return 0;
    }
    else
    {
        return it->second.size();
    }
}

Alocacao AlocacoesList::getAlocacao(Sonda sonda, int idx)
{
    std::map<Sonda, std::list<Alocacao>>::iterator it = _alocacoes.find(sonda);
    if (it == _alocacoes.end())
    {
        std::cout << "A sonda especificada não foi encontrada." << std::endl;
        Alocacao x{};
        return x;
    }

    bool idxFound = false;
    int count = 0;
    for (std::list<Alocacao>::iterator it = _alocacoes[sonda].begin(); it!=_alocacoes[sonda].end(); ++it)
    {
        if (count == idx)
        {
            idxFound = true;
            Alocacao x = *it;
            return x;
        }
        count++;
    }
    if (!idxFound)
    {
        std::cout << "Alocação não encontrada." << std::endl;
        Alocacao x{};
        return x;
    }
}

Alocacao AlocacoesList::getAlocacao(Sonda sonda, Projeto projeto)
{
    std::map<Sonda, std::list<Alocacao>>::iterator it = _alocacoes.find(sonda);
    if (it == _alocacoes.end())
    {
        std::cout << "A sonda especificada não foi encontrada." << std::endl;
        Alocacao x{};
        return x;
    }

    bool projFound = false;
    for (std::list<Alocacao>::iterator it = _alocacoes[sonda].begin(); it!=_alocacoes[sonda].end(); ++it)
    {
        Alocacao x = *it;
        if (projeto == x.getProjeto())
        {
            projFound = true;
            return x;
        }
    }
    if (!projFound)
    {
        std::cout << "Alocação não encontrada." << std::endl;
        Alocacao x{};
        return x;
    }
}

int AlocacoesList::getAlocacaoIndex(Sonda sonda, Projeto projeto)
{
    std::map<Sonda, std::list<Alocacao>>::iterator it = _alocacoes.find(sonda);
    if (it == _alocacoes.end())
    {
        std::cout << "A sonda especificada não foi encontrada." << std::endl;
        return 0;
    }

    int count = 0;
    std::list<Alocacao>::iterator itr = _alocacoes[sonda].begin();
    for (std::list<Alocacao>::iterator it = _alocacoes[sonda].begin(); it!=_alocacoes[sonda].end(); ++it)
    {
        Alocacao x = *it;
        if (projeto == x.getProjeto())
        {
            return count;
        }
        else
        {
            itr = it;
        }
        count++;
    }
    if (itr == _alocacoes[sonda].end())
    {
        std::cout << "Alocação não encontrada." << std::endl;
        return 0;
    }
}

void AlocacoesList::setAlocacoes(std::map<Sonda, std::vector<Alocacao>> alocacoes, int deltaT)
{
    _alocacoes.clear();

    // checar interceção
    bool feasible = true; 
    for (std::map<Sonda, std::vector<Alocacao>>::iterator its=alocacoes.begin(); its!=alocacoes.end(); ++its)
    {
        Sonda sonda{};
        sonda = its->first;
        for (std::vector<Alocacao>::iterator itv1=alocacoes[sonda].begin(); itv1 != alocacoes[sonda].end(); ++itv1)
        {
            Alocacao aloc{};
            aloc = *itv1;
            for (std::vector<Alocacao>::iterator itv2=alocacoes[sonda].begin(); itv2 != alocacoes[sonda].end(); ++itv2)
            {
                Alocacao alocX{};
                alocX = *itv2;
                if (aloc == alocX)
                {
                    continue;
                }
                if (!((aloc.getIntervalo().getFinal() < alocX.getIntervalo().getInicio()) 
                    ||
                    (aloc.getIntervalo().getInicio() > alocX.getIntervalo().getFinal())))
                    {
                        std::cout << std::endl;
                        std::cout << "Alocações não viáveis, pois existe interceção.";
                        std::cout << "Interceção entre as alocações dos projetos" << aloc.getProjeto().getNome() << " e "
                                                                                  << alocX.getProjeto().getNome() << " na sonda "
                                                                                  << sonda.getNome();
                        std::cout << std::endl;
                        feasible = false;
                        break;
                    }
            }
            if (!feasible)
            {
                break;
            }
        }
        if (!feasible)
        {
            break;
        }
    }
    assert (feasible);

    // checar continuidade e tamanho das alocações
    for (std::map<Sonda, std::vector<Alocacao>>::iterator its = alocacoes.begin(); its != alocacoes.end(); ++its)
    {
        Sonda sonda = its->first;
        for (std::vector<Alocacao>::iterator itv = alocacoes[sonda].begin(); itv != alocacoes[sonda].end(); ++itv)
        {
            Alocacao aloc = *itv;
            Projeto projeto = aloc.getProjeto();
            Intervalo intervalo = aloc.getIntervalo();
            CalculadorDeDesloc calc{};
            double desloc;
            if ( (itv == alocacoes[sonda].begin()) && (itv+1 == alocacoes[sonda].end()) )
            {
                // alocacao única
                desloc = calc.getDesloc(sonda, projeto, deltaT);
                if ( !(intervalo.getInicio() + (int)desloc + projeto.getTempExec() - 1 == intervalo.getFinal()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois tamanho da alocação não está correto.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << "origem" << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
            }
            if ( (itv == alocacoes[sonda].begin()) && !(itv+1 == alocacoes[sonda].end()) )
            {
                // alocação begin, mas existe uma próxima alocação
                desloc = calc.getDesloc(sonda, projeto, deltaT);
                if ( !(intervalo.getInicio() + (int)desloc + projeto.getTempExec() - 1 == intervalo.getFinal()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois tamanho da alocação não está correto.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << "origem" << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
                Alocacao alocNext = *(itv+1);
                Intervalo intervaloNext = alocNext.getIntervalo();
                if ( !(intervalo.getFinal() < intervaloNext.getInicio()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois continuidade temporal não está correta.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << "origem" << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
            }
            if ( !(itv == alocacoes[sonda].begin()) && (itv+1 == alocacoes[sonda].end()) )
            {
                // última alocação, mas existe alocação prévia
                Alocacao alocPrev = *(itv-1);
                Projeto projPrev = alocPrev.getProjeto();
                desloc = calc.getDesloc(projPrev, projeto, deltaT);
                if ( !(intervalo.getInicio() + (int)desloc + projeto.getTempExec() - 1 == intervalo.getFinal()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois tamanho da alocação não está correto.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
                Intervalo intervaloPrev = alocPrev.getIntervalo();
                if ( !(intervaloPrev.getFinal() < intervalo.getInicio()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois continuidade temporal não está correta.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
            }
            if ( !(itv == alocacoes[sonda].begin()) && !(itv+1 == alocacoes[sonda].end()) )
            {
                // existe alocação prévia e próxima
                Alocacao alocPrev = *(itv-1);
                Alocacao alocNext = *(itv+1);
                Projeto projPrev = alocPrev.getProjeto();
                Projeto projNext = alocNext.getProjeto();
                Intervalo intervaloPrev = alocPrev.getIntervalo();
                Intervalo intervaloNext = alocNext.getIntervalo();
                desloc = calc.getDesloc(projPrev, projeto, deltaT);
                if ( !(intervalo.getInicio() + (int)desloc + projeto.getTempExec() - 1 == intervalo.getFinal()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois tamanho da alocação não está correto.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
                if ( !(intervaloPrev.getFinal() < intervalo.getInicio()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois continuidade temporal não está correta.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
                if ( !(intervalo.getFinal() < intervaloNext.getInicio()) )
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois continuidade temporal não está correta.";
                    std::cout << "Alocação incorreta: " << std::endl;
                    std::cout << "Sonda " << sonda.getNome() << std::endl;
                    std::cout << "Projeto " << projeto.getNome() << std::endl;
                    std::cout << "Início " << intervalo.getInicio() << std::endl;
                    std::cout << "Final " << intervalo.getFinal() << std::endl;
                    std::cout << "desloc " << desloc << std::endl;
                    std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                    std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
            }
        }
        if (!feasible)
        {
            break;
        }
    }
    assert (feasible);

    for (std::map<Sonda, std::vector<Alocacao>>::iterator itr=alocacoes.begin(); itr!=alocacoes.end(); ++itr)
    {
        Sonda sonda = itr->first;
        std::vector<Alocacao> vetorAloc = itr->second;
        std::list<Alocacao> listAloc;
        for (std::vector<Alocacao>::iterator it=vetorAloc.begin(); it!=vetorAloc.end(); ++it)
        {
            Alocacao x = *it;
            listAloc.push_back(x);
        }
        _alocacoes.insert(std::pair<Sonda, std::list<Alocacao>>(sonda, listAloc));
    }
}

void AlocacoesList::setAlocacoes(Sonda sonda, std::vector<Alocacao> alocacoes, int deltaT)
{
    std::map<Sonda, std::list<Alocacao>>::iterator it = _alocacoes.find(sonda);
    if (it == _alocacoes.end())
    {
        std::cout << "A sonda especificada não foi encontrada." << std::endl;
    }

    _alocacoes[sonda].clear();

    // checar interceção
    bool feasible = true; 
    for (std::vector<Alocacao>::iterator itv1=alocacoes.begin(); itv1 != alocacoes.end(); ++itv1)
    {
        Alocacao aloc{};
        aloc = *itv1;
        for (std::vector<Alocacao>::iterator itv2=alocacoes.begin(); itv2 != alocacoes.end(); ++itv2)
        {
            Alocacao alocX{};
            alocX = *itv2;
            if (aloc == alocX)
            {
                continue;
            }
            if (!((aloc.getIntervalo().getFinal() < alocX.getIntervalo().getInicio()) 
                ||
                (aloc.getIntervalo().getInicio() > alocX.getIntervalo().getFinal())))
                {
                    std::cout << std::endl;
                    std::cout << "Alocações não viáveis, pois existe interceção.";
                    std::cout << "Interceção entre as alocações dos projetos" << aloc.getProjeto().getNome() << " e "
                                                                                << alocX.getProjeto().getNome() << " na sonda "
                                                                                << sonda.getNome();
                    std::cout << std::endl;
                    feasible = false;
                    break;
                }
        }
        if (!feasible)
        {
            break;
        }
    }
    assert (feasible);

    // checar continuidade e tamanho das alocações
    for (std::vector<Alocacao>::iterator itv = alocacoes.begin(); itv != alocacoes.end(); ++itv)
    {
        Alocacao aloc = *itv;
        Projeto projeto = aloc.getProjeto();
        Intervalo intervalo = aloc.getIntervalo();
        CalculadorDeDesloc calc{};
        double desloc;
        if ( (itv == alocacoes.begin()) && (itv+1 == alocacoes.end()) )
        {
            // alocacao única
            desloc = calc.getDesloc(sonda, projeto, deltaT);
            if ( !(intervalo.getInicio() + (int)desloc + projeto.getTempExec() - 1 == intervalo.getFinal()) )
            {
                std::cout << std::endl;
                std::cout << "Alocações não viáveis, pois tamanho da alocação não está correto.";
                std::cout << "Alocação incorreta: " << std::endl;
                std::cout << "Sonda " << sonda.getNome() << std::endl;
                std::cout << "Projeto " << projeto.getNome() << std::endl;
                std::cout << "Início " << intervalo.getInicio() << std::endl;
                std::cout << "Final " << intervalo.getFinal() << std::endl;
                std::cout << "desloc " << desloc << std::endl;
                std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                std::cout << "alocação prev " << "origem" << std::endl;
                std::cout << std::endl;
                feasible = false;
                break;
            }
        }
        if ( (itv == alocacoes.begin()) && !(itv+1 == alocacoes.end()) )
        {
            // alocação begin, mas existe uma próxima alocação
            desloc = calc.getDesloc(sonda, projeto, deltaT);
            if ( !(intervalo.getInicio() + (int)desloc + projeto.getTempExec() - 1 == intervalo.getFinal()) )
            {
                std::cout << std::endl;
                std::cout << "Alocações não viáveis, pois tamanho da alocação não está correto.";
                std::cout << "Alocação incorreta: " << std::endl;
                std::cout << "Sonda " << sonda.getNome() << std::endl;
                std::cout << "Projeto " << projeto.getNome() << std::endl;
                std::cout << "Início " << intervalo.getInicio() << std::endl;
                std::cout << "Final " << intervalo.getFinal() << std::endl;
                std::cout << "desloc " << desloc << std::endl;
                std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                std::cout << "alocação prev " << "origem" << std::endl;
                std::cout << std::endl;
                feasible = false;
                break;
            }
            Alocacao alocNext = *(itv+1);
            Intervalo intervaloNext = alocNext.getIntervalo();
            if ( !(intervalo.getFinal() < intervaloNext.getInicio()) )
            {
                std::cout << std::endl;
                std::cout << "Alocações não viáveis, pois continuidade temporal não está correta.";
                std::cout << "Alocação incorreta: " << std::endl;
                std::cout << "Sonda " << sonda.getNome() << std::endl;
                std::cout << "Projeto " << projeto.getNome() << std::endl;
                std::cout << "Início " << intervalo.getInicio() << std::endl;
                std::cout << "Final " << intervalo.getFinal() << std::endl;
                std::cout << "desloc " << desloc << std::endl;
                std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                std::cout << "alocação prev " << "origem" << std::endl;
                std::cout << std::endl;
                feasible = false;
                break;
            }
        }
        if ( !(itv == alocacoes.begin()) && (itv+1 == alocacoes.end()) )
        {
            // última alocação, mas existe alocação prévia
            Alocacao alocPrev = *(itv-1);
            Projeto projPrev = alocPrev.getProjeto();
            desloc = calc.getDesloc(projPrev, projeto, deltaT);
            if ( !(intervalo.getInicio() + (int)desloc + projeto.getTempExec() - 1 == intervalo.getFinal()) )
            {
                std::cout << std::endl;
                std::cout << "Alocações não viáveis, pois tamanho da alocação não está correto.";
                std::cout << "Alocação incorreta: " << std::endl;
                std::cout << "Sonda " << sonda.getNome() << std::endl;
                std::cout << "Projeto " << projeto.getNome() << std::endl;
                std::cout << "Início " << intervalo.getInicio() << std::endl;
                std::cout << "Final " << intervalo.getFinal() << std::endl;
                std::cout << "desloc " << desloc << std::endl;
                std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                std::cout << std::endl;
                feasible = false;
                break;
            }
            Intervalo intervaloPrev = alocPrev.getIntervalo();
            if ( !(intervaloPrev.getFinal() < intervalo.getInicio()) )
            {
                std::cout << std::endl;
                std::cout << "Alocações não viáveis, pois continuidade temporal não está correta.";
                std::cout << "Alocação incorreta: " << std::endl;
                std::cout << "Sonda " << sonda.getNome() << std::endl;
                std::cout << "Projeto " << projeto.getNome() << std::endl;
                std::cout << "Início " << intervalo.getInicio() << std::endl;
                std::cout << "Final " << intervalo.getFinal() << std::endl;
                std::cout << "desloc " << desloc << std::endl;
                std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                std::cout << std::endl;
                feasible = false;
                break;
            }
        }
        if ( !(itv == alocacoes.begin()) && !(itv+1 == alocacoes.end()) )
        {
            // existe alocação prévia e próxima
            Alocacao alocPrev = *(itv-1);
            Alocacao alocNext = *(itv+1);
            Projeto projPrev = alocPrev.getProjeto();
            Projeto projNext = alocNext.getProjeto();
            Intervalo intervaloPrev = alocPrev.getIntervalo();
            Intervalo intervaloNext = alocNext.getIntervalo();
            desloc = calc.getDesloc(projPrev, projeto, deltaT);
            if ( !(intervalo.getInicio() + (int)desloc + projeto.getTempExec() - 1 == intervalo.getFinal()) )
            {
                std::cout << std::endl;
                std::cout << "Alocações não viáveis, pois tamanho da alocação não está correto.";
                std::cout << "Alocação incorreta: " << std::endl;
                std::cout << "Sonda " << sonda.getNome() << std::endl;
                std::cout << "Projeto " << projeto.getNome() << std::endl;
                std::cout << "Início " << intervalo.getInicio() << std::endl;
                std::cout << "Final " << intervalo.getFinal() << std::endl;
                std::cout << "desloc " << desloc << std::endl;
                std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                std::cout << std::endl;
                feasible = false;
                break;
            }
            if ( !(intervaloPrev.getFinal() < intervalo.getInicio()) )
            {
                std::cout << std::endl;
                std::cout << "Alocações não viáveis, pois continuidade temporal não está correta.";
                std::cout << "Alocação incorreta: " << std::endl;
                std::cout << "Sonda " << sonda.getNome() << std::endl;
                std::cout << "Projeto " << projeto.getNome() << std::endl;
                std::cout << "Início " << intervalo.getInicio() << std::endl;
                std::cout << "Final " << intervalo.getFinal() << std::endl;
                std::cout << "desloc " << desloc << std::endl;
                std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                std::cout << std::endl;
                feasible = false;
                break;
            }
            if ( !(intervalo.getFinal() < intervaloNext.getInicio()) )
            {
                std::cout << std::endl;
                std::cout << "Alocações não viáveis, pois continuidade temporal não está correta.";
                std::cout << "Alocação incorreta: " << std::endl;
                std::cout << "Sonda " << sonda.getNome() << std::endl;
                std::cout << "Projeto " << projeto.getNome() << std::endl;
                std::cout << "Início " << intervalo.getInicio() << std::endl;
                std::cout << "Final " << intervalo.getFinal() << std::endl;
                std::cout << "desloc " << desloc << std::endl;
                std::cout << "tempExec " << projeto.getTempExec() << std::endl;
                std::cout << "alocação prev " << projPrev.getNome() << std::endl;
                std::cout << std::endl;
                feasible = false;
                break;
            }
        }
    }
    assert (feasible);

    std::list<Alocacao> alocsList;
    for (std::vector<Alocacao>::iterator it=alocacoes.begin(); it!=alocacoes.end(); ++it)
    {
        Alocacao x = *it;
        alocsList.push_back(x);
    }
    _alocacoes[sonda] = alocsList;
}

std::tuple<bool, int, Intervalo, int, int, int, int, int> AlocacoesList::buscarJanelaViavel(Sonda sonda, Projeto projeto, 
                                                                                            int modo, int deltaT)
{
    //std::cout << std::endl;
    //std::cout << "Buscando janela viável para o projeto " << projeto.getNome() << " na sonda " << sonda.getNome();
    //std::cout << std::endl;

    //std::cout << "Informações do projeto: " << std::endl;
    //std::cout << "Release date: " << projeto.getInicioJanela() << std::endl;
    //std::cout << "Due date: " << projeto.getFinalJanela() << std::endl;

    // std::cout << "Alocações atuais são:" << std::endl;
    // this->print();

    // verifica se sonda existe
    std::map<Sonda, std::list<Alocacao>>::iterator it = this->_alocacoes.find(sonda);
    if (it == this->_alocacoes.end())
    {
        std::cout << "Sonda não encontrada nas alocações." << std::endl;
        assert (it !=this->_alocacoes.end());
    }

    // inicializa valores que serão retornados
    bool alocExiste = false;
    Intervalo intervaloAloc{};
    int posicaoAloc = -1;
    int prevMinus = 0;
    int currMinus = 0;
    int currPlus = 0;
    int nextPlus = 0;
    int caso = 0;

    CalculadorDeDesloc calc{};

    // std::cout << "Sonda empty: " << this->_alocacoes[sonda].empty() << std::endl;
    // std::cout << "Sonda size: " << this->_alocacoes[sonda].size() << std::endl;

    // se o vetor de alocações está vazio
    if (this->_alocacoes[sonda].empty())
    {
        //std::cout << std::endl;
        //std::cout << "A sonda " << sonda.getNome() << " ainda NÃO TEM alocações.";
        //std::cout << std::endl;

        // se é viável inserir projeto entre release e due
        double desloc = calc.getDesloc(sonda, projeto, deltaT);
        if (projeto.getInicioJanela() + (int)desloc + projeto.getTempExec() - 1 <= projeto.getFinalJanela())
        {
            // escolhe intervalo
            int inicioIntervalo = projeto.getInicioJanela();
            int finalIntervalo = projeto.getInicioJanela() + (int)desloc + projeto.getTempExec() - 1;
            intervaloAloc.setIntervalo(inicioIntervalo, finalIntervalo);

            //std::cout << std::endl;
            //std::cout << "Inserção viável na sonda " << sonda.getNome() << " ainda sem alocações." << std::endl;
            //std::cout << "Release do projeto: " << projeto.getInicioJanela() << std::endl;
            //std::cout << "Início do intervalo: " << intervaloAloc.getInicio() << std::endl;
            //std::cout << "setup: " << desloc << std::endl;
            //std::cout << "proc: " << projeto.getTempExec() << std::endl;
            //std::cout << "Final do intervalo: " << intervaloAloc.getFinal() << std::endl;
            //std::cout << "Due do projeto: " << projeto.getFinalJanela() << std::endl;
            //std::cout << std::endl;

            // alocar
            alocExiste = true;
            caso = 1;
            posicaoAloc = 0;
            prevMinus = 0;
            currMinus = 0;
            currPlus = 0;
            nextPlus = 0;
        }
        else
        {
            //std::cout << std::endl;
            //std::cout << "Inserção NÃO viável na sonda " << sonda.getNome() << " ainda sem alocações.";
            //std::cout << std::endl;

            alocExiste = false;
            caso = 0;
            posicaoAloc = -1;
            intervaloAloc.setIntervalo(0, 0);
            prevMinus = 0;
            currMinus = 0;
            currPlus = 0;
            nextPlus = 0;
        }
        return std::make_tuple(alocExiste, posicaoAloc, intervaloAloc, prevMinus, currMinus, currPlus, nextPlus, caso);
    }
    // se já existem alocações no vetor
    else
    {
        //std::cout << std::endl;
        //std::cout << "A sonda " << sonda.getNome() << " JÁ TEM alocações.";
        //std::cout << std::endl;

        // itera sob as alocações da sonda
        int count = -1;
        for (std::list<Alocacao>::iterator itr=this->_alocacoes[sonda].begin(); itr!=this->_alocacoes[sonda].end(); ++itr)
        {
            count++;

            double desloc = 0;
            int gapInit = -1, gapFinal = -1;
            double oldDesloc = 0, newDesloc = 0;
            int deltaDesloc = 0;
            int dataMin = -1, dataMax = -1;
            int deltaDeslocEfetivo;
            bool janelaExiste = false;

            //std::cout << std::endl;
            //std::cout << "Verificando alocação de índice " << count << " da sonda " << sonda.getNome();
            //std::cout << std::endl;

            // pega informações da janela que antecede a alocação corrente
            if (itr == this->_alocacoes[sonda].begin())
            {
                desloc = calc.getDesloc(sonda, projeto, deltaT);

                // se existe janela
                if (itr->getIntervalo().getInicio() == 0)
                {
                    janelaExiste = false;
                }
                else
                {
                    janelaExiste = true;
                    gapInit = 0;
                    gapFinal = itr->getIntervalo().getInicio() - 1;
                }
            }
            else
            {
                desloc = calc.getDesloc((std::prev(itr, 1))->getProjeto(), projeto, deltaT);

                // se existe janela
                if (itr->getIntervalo().getInicio() == (std::prev(itr, 1))->getIntervalo().getFinal() + 1)
                {
                    janelaExiste = false;
                }
                else
                {
                    janelaExiste = true;
                    gapInit = (std::prev(itr, 1))->getIntervalo().getFinal() + 1;
                    gapFinal = itr->getIntervalo().getInicio() - 1;
                }
            }
            if (janelaExiste)
            {
                //std::cout << std::endl;
                //std::cout << "Janela disponível: " << std::endl;
                //std::cout << "Início: " << gapInit << ", e final: " << gapFinal << std::endl;
                //std::cout << std::endl;
            }
            else
            {
                //std::cout << std::endl;
                //std::cout << "Janela NÃO disponível: " << std::endl;
                //std::cout << std::endl;
                continue;
            }
            
            // verifica se a inserção do projeto altera o setup do projeto seguinte
            if (itr == this->_alocacoes[sonda].begin())
            {
                oldDesloc = calc.getDesloc(sonda, itr->getProjeto(), deltaT);
            }
            else
            {
                oldDesloc = calc.getDesloc((std::prev(itr, 1))->getProjeto(), itr->getProjeto(), deltaT);
            }
            newDesloc = calc.getDesloc(projeto, itr->getProjeto(), deltaT);
            deltaDesloc = (int)newDesloc - (int)oldDesloc;
            //std::cout << std::endl << "Se o projeto " << projeto.getNome() << " for inserido na posição " << count
            //          << ", o setup do projeto seguinte será alterado em: " << deltaDesloc << std::endl;
            
            // se tamanho do projeto cabe na janela, entre release e due
            dataMin = std::max(gapInit, projeto.getInicioJanela());
            dataMax = std::min(gapFinal, projeto.getFinalJanela());
            deltaDeslocEfetivo = std::min(deltaDesloc, 0);
            if (dataMin + (int)desloc + projeto.getTempExec() - 1 <= dataMax - deltaDeslocEfetivo)
            {
                //std::cout << std::endl;
                //std::cout << "Tamanho do projeto cabe na sonda.";
                //std::cout << std::endl;

                // escolher intervalo
                int inicioIntervalo, finalIntervalo;
                inicioIntervalo = dataMin;
                finalIntervalo = inicioIntervalo + desloc + projeto.getTempExec() - 1;
                intervaloAloc.setIntervalo(inicioIntervalo, finalIntervalo);
                //std::cout << std::endl;
                //std::cout << "Intervalo escolhido: " << std::endl;
                //std::cout << "Início do intervalo: " << intervaloAloc.getInicio() << std::endl;
                //std::cout << "Final do intervalo: " << intervaloAloc.getFinal() << std::endl;
                //std::cout << std::endl;

                // se não altera setup do projeto seguinte
                if (deltaDesloc == 0)
                {
                    //std::cout << std::endl;
                    //std::cout << "Inserção viável sem modificar setup do projeto seguinte";
                    //std::cout << std::endl;

                    // alocar
                    alocExiste = true;
                    caso = 2;
                    posicaoAloc = count;
                    prevMinus = 0;
                    currMinus = 0;
                    currPlus = 0;
                    nextPlus = 0;

                    break;
                }
                // se altera setup do projeto seguinte para menos
                else if (deltaDesloc < 0)
                {
                    //std::cout << std::endl;
                    //std::cout << "Inserção viável modificando setup do projeto seguinte para menos. Valor: " << deltaDesloc;
                    //std::cout << std::endl;

                    // alocar
                    alocExiste = true;
                    caso = 3;
                    posicaoAloc = count;
                    prevMinus = 0;
                    currMinus = deltaDesloc;
                    currPlus = 0;
                    nextPlus = 0;

                    break;
                }
                // se altera setup do projeto seguinte para mais
                else
                {
                    // tenta colocar diferença para trás e/ou colocar diferença para frente
                    //std::cout << std::endl;
                    //std::cout << "O setup do projeto seguinte sofre modificação para mais, em caso de inserção.";
                    //std::cout << "Tentando realocar diferença de desloc.";
                    //std::cout << std::endl;

                    // verifica quanto espaço livre tenho para frente, sem realocações
                    int deltaLeftDisp=0, deltaRightDisp=0, temp1=0, temp2=0;
                    if (std::next(itr, 1) == this->_alocacoes[sonda].end())
                    {
                        deltaRightDisp = itr->getProjeto().getFinalJanela() - itr->getIntervalo().getFinal();
                    }
                    else
                    {
                        temp1 = itr->getProjeto().getFinalJanela();
                        temp2 = std::next(itr, 1)->getIntervalo().getInicio() - 1;
                        deltaRightDisp = std::min(temp1, temp2) - itr->getIntervalo().getFinal();
                    }
                    //std::cout << "Espaço disponível para frente, sem realocações: " << deltaRightDisp << std::endl;

                    // verifica quanto espaço livre tenho para trás, sem realocações
                    temp1 = itr->getProjeto().getInicioJanela();
                    temp2 = intervaloAloc.getFinal() + 1;
                    deltaLeftDisp = itr->getIntervalo().getInicio() - std::max(temp1, temp2);
                    //std::cout << "Espaço disponível para trás, sem realocações: " << deltaLeftDisp << std::endl;

                    // se chegar só para trás basta
                    if (deltaLeftDisp >= deltaDesloc)
                    {
                        //std::cout << std::endl;
                        //std::cout << "Apenas chegar para trás, basta. Espaço disponível: " << deltaLeftDisp;
                        //std::cout << std::endl;

                        // alocar
                        alocExiste = true;
                        caso = 4;
                        posicaoAloc = count;
                        prevMinus = 0;
                        currMinus = deltaDesloc;
                        currPlus = 0;
                        nextPlus = 0;

                        break;
                    }
                    // se chegar para trás e para frente basta
                    else if (deltaLeftDisp + deltaRightDisp >= deltaDesloc)
                    {
                        //std::cout << std::endl;
                        //std::cout << "Chegar para trás e para frente, basta." << std::endl;
                        //std::cout << "Espaço disponível para trás: " << deltaLeftDisp << std::endl;
                        //std::cout << "Espaço disponível para frente: " << deltaRightDisp << std::endl;

                        // alocar
                        alocExiste = true;
                        caso = 4;
                        posicaoAloc = count;
                        prevMinus = 0;
                        currMinus = deltaLeftDisp;
                        currPlus = deltaDesloc - deltaLeftDisp;
                        nextPlus = 0;

                        break;
                    }
                    // senão, se está no modo realocar
                    else if (modo == 1)
                    {
                        //std::cout << std::endl;
                        //std::cout << "Espaços disponíveis sem realocações são insuficientes.";
                        //std::cout << std::endl;

                        // verifica quanto posso chegar o next para frente
                        int deltaNextDisp = 0;
                        if (std::next(itr, 1) == this->_alocacoes[sonda].end())
                        {
                            deltaNextDisp = 0;
                        }
                        else
                        {
                            std::list<Alocacao>::iterator itrNext = std::next(itr, 1);
                            if (std::next(itrNext, 1) == this->_alocacoes[sonda].end())
                            {
                                deltaNextDisp = itrNext->getProjeto().getFinalJanela() - itrNext->getIntervalo().getFinal();
                            }
                            else
                            {
                                temp1 = itrNext->getProjeto().getFinalJanela();
                                temp2 = std::next(itrNext, 1)->getIntervalo().getInicio() - 1;
                                deltaNextDisp = std::min(temp1, temp2) - itrNext->getIntervalo().getFinal();
                            }
                        }
                        //std::cout << std::endl;
                        //std::cout << "Espaço disponível para frente realocando o próximo projeto: " << deltaNextDisp;
                        //std::cout << std::endl;

                        // verifica se chegar para trás e para frente basta, considerando delta next
                        if ( (deltaLeftDisp + deltaRightDisp + deltaNextDisp) >= deltaDesloc)
                        {
                            //std::cout << std::endl;
                            //std::cout << "Chegar para trás, para frente, e postergar o next basta." << std::endl;
                            //std::cout << "Espaço disponível para trás: " << deltaLeftDisp << std::endl;
                            //std::cout << "Espaço disponível para frente: " << deltaRightDisp << std::endl;
                            //std::cout << "Espaço disponível para realocar next: " << deltaNextDisp << std::endl;

                            // alocar
                            alocExiste = true;
                            caso = 4;
                            posicaoAloc = count;
                            prevMinus = 0;
                            currMinus = deltaLeftDisp;
                            currPlus = deltaRightDisp;
                            nextPlus = deltaDesloc - (deltaLeftDisp + deltaRightDisp);
                            currPlus += nextPlus;

                            break;
                        }
                        else
                        {
                            //std::cout << std::endl;
                            //std::cout << "Inserção inviável, mesmo com realocações.";
                            //std::cout << std::endl;
                        }
                    }
                    // senão, não dá mesmo
                    else
                    {
                        //std::cout << std::endl;
                        //std::cout << "Inserção não viável, por conta do aumento de setup." << deltaLeftDisp;
                        //std::cout << std::endl;
                    }
                }
            }
            else if (modo == 1)
            {
                // tenta realocar projetos vizinhos
                //std::cout << std::endl;
                //std::cout << "Tamanho do projeto NÃO cabe na sonda. Tentar realocações.";
                //std::cout << std::endl;

                // quanto de espaço é necessário? considerar deltaDesloc negativo
                int deltaNecessario = ((int)desloc + projeto.getTempExec()) - (dataMax - dataMin + 1 - deltaDeslocEfetivo);
                //std::cout << std::endl;
                //std::cout << "É preciso abrir um espaço de tamanho: " << deltaNecessario;
                //std::cout << std::endl;

                int deltaPrevDisp = 0;
                // quanto posso chegar o prev para trás?
                if (itr == this->_alocacoes[sonda].begin())
                {
                    deltaPrevDisp = 0;
                }
                else
                {
                    std::list<Alocacao>::iterator itrPrev = std::prev(itr, 1);
                    if (itrPrev == this->_alocacoes[sonda].begin())
                    {
                        deltaPrevDisp = itrPrev->getIntervalo().getInicio() - itrPrev->getProjeto().getInicioJanela();
                    }
                    else
                    {
                        int temp1 = 0, temp2 = 0;
                        temp1 = itrPrev->getProjeto().getInicioJanela();
                        temp2 = std::prev(itrPrev, 1)->getIntervalo().getFinal() + 1;
                        deltaPrevDisp = itrPrev->getIntervalo().getInicio() - std::max(temp1, temp2);
                    }
                }
                //std::cout << std::endl;
                //std::cout << "Espaço disponível realocando projeto anterior: " << deltaPrevDisp;
                //std::cout << std::endl;

                int deltaCurrDisp = 0;
                // quanto posso chegar o curr para frente?
                if (std::next(itr, 1) == this->_alocacoes[sonda].end())
                {
                    deltaCurrDisp = itr->getProjeto().getFinalJanela() - itr->getIntervalo().getFinal();
                }
                else
                {
                    int temp1 = 0, temp2 = 0;
                    temp1 = itr->getProjeto().getFinalJanela();
                    temp2 = std::next(itr, 1)->getIntervalo().getInicio() - 1;
                    deltaCurrDisp = std::min(temp1, temp2) - itr->getIntervalo().getFinal();
                }
                //std::cout << std::endl;
                //std::cout << "Espaço disponível realocando projeto posterior: " << deltaCurrDisp;
                //std::cout << std::endl;

                // se deltaDesloc é positivo, verificar viabilidade de aumentar o curr para frente e descontar valor
                bool deltaViavel = true;
                if (deltaDesloc > 0)
                {
                    if (deltaCurrDisp >= deltaDesloc)
                    {
                        deltaViavel = true;
                        deltaCurrDisp -= deltaDesloc;
                    }
                    else
                    {
                        deltaViavel = false;
                    }
                }

                // se for viável fazer modificações
                if (deltaViavel)
                {
                    // atualiza informações da janela
                    dataMin = std::max(gapInit - deltaPrevDisp, projeto.getInicioJanela());
                    dataMax = std::min(gapFinal + deltaCurrDisp, projeto.getFinalJanela());

                    // verifica se, com realocações, projeto cabe
                    if (dataMin + (int)desloc + projeto.getTempExec() - 1 <= dataMax - deltaDeslocEfetivo)
                    {
                        //std::cout << std::endl;
                        //std::cout << "Tamanho do projeto cabe na sonda, com realocações.";
                        //std::cout << std::endl;

                        // escolher intervalo
                        int inicioIntervalo = -1, finalIntervalo = -1;
                        if (deltaPrevDisp >= deltaNecessario)
                        {
                            inicioIntervalo = std::max((gapInit-deltaNecessario), projeto.getInicioJanela());
                        }
                        else if ( (deltaPrevDisp + deltaCurrDisp) >= deltaNecessario)
                        {
                            inicioIntervalo = std::max((gapInit-deltaPrevDisp), projeto.getInicioJanela());
                        }
                        finalIntervalo = inicioIntervalo + desloc + projeto.getTempExec() - 1;
                        intervaloAloc.setIntervalo(inicioIntervalo, finalIntervalo);
                        //std::cout << std::endl;
                        //std::cout << "Intervalo escolhido: " << std::endl;
                        //std::cout << "Início do intervalo: " << intervaloAloc.getInicio() << std::endl;
                        //std::cout << "Final do intervalo: " << intervaloAloc.getFinal() << std::endl;
                        //std::cout << std::endl;

                        // alocar
                        alocExiste = true;
                        caso = 5;
                        posicaoAloc = count;

                        if (deltaPrevDisp >= deltaNecessario)
                        {
                            prevMinus = deltaNecessario;
                            currMinus = 0;
                            currPlus = 0;
                            nextPlus = deltaDesloc; // OBS: para poder retornar só o quanto muda de desloc no curr
                        }
                        else if ( (deltaPrevDisp + deltaCurrDisp) >= deltaNecessario)
                        {
                            prevMinus = deltaPrevDisp;
                            currMinus = 0;
                            currPlus = deltaNecessario - deltaPrevDisp;
                            nextPlus = deltaDesloc; // OBS: para poder retornar só o quanto muda de desloc no curr
                        }

                        break;
                    }
                    else
                    {
                        //std::cout << std::endl;
                        //std::cout << "Tamanho do projeto NÃO cabe na janela, mesmo com realocações.";
                        //std::cout << std::endl;
                    }
                }
                else
                {
                    //std::cout << std::endl;
                    //std::cout << "Não é possível abrir o espaço necessário, pois o aumento do desloc é inviável.";
                    //std::cout << std::endl;
                }
            }
            else
            {
                //std::cout << std::endl;
                //std::cout << "Tamanho do projeto NÃO cabe na janela.";
                //std::cout << std::endl;
            }
        }
        // se ainda não conseguiu alocar, tenta na janela após a última alocação
        if (alocExiste == false)
        {
            //std::cout << std::endl;
            //std::cout << "Alocação ainda não viável. Tentando na ÚLTIMA janela.";
            //std::cout << std::endl;

            int gapInit = -1, gapFinal = -1;
            int dataMin = -1, dataMax = -1;
            bool janelaExiste = false;
            double desloc;

            // verifica se existe janela após última alocação
            std::list<Alocacao>::iterator itr = std::prev(this->_alocacoes[sonda].end(), 1);
            if (itr->getIntervalo().getFinal() < projeto.getFinalJanela())
            {
                //std::cout << std::endl;
                //std::cout << "Existe janela após última alocação e antes da due do projeto a ser alocado.";
                //std::cout << std::endl;

                janelaExiste = true;

                // pega informações da janela
                gapInit = itr->getIntervalo().getFinal() + 1;
                gapFinal = projeto.getFinalJanela();
            }
            else
            {
                //std::cout << std::endl;
                //std::cout << "NÃO existe janela após última alocação e antes da due do projeto a ser alocado.";
                //std::cout << std::endl;

                janelaExiste = false;
            }
            if (janelaExiste)
            {
                //std::cout << std::endl;
                //std::cout << "Janela após última alocação disponível: " << std::endl;
                //std::cout << "Início: " << gapInit << ", e final: " << gapFinal << std::endl;
                //std::cout << std::endl;

                // calcula setup, caso projeto seja inserido
                desloc = calc.getDesloc(itr->getProjeto(), projeto, deltaT);

                // verifica se projeto cabe na janela
                dataMin = std::max(gapInit, projeto.getInicioJanela());
                dataMax = std::min(gapFinal, projeto.getFinalJanela());
                if (dataMin + (int)desloc + projeto.getTempExec() - 1 <= dataMax)
                {
                    //std::cout << std::endl;
                    //std::cout << "Tamanho do projeto cabe na janela após última alocação. Inserção viável.";
                    //std::cout << std::endl;

                    alocExiste = true;
                    caso = 6;
                    posicaoAloc = 999;
                    int inicioIntervalo = dataMin;
                    int finalIntervalo = inicioIntervalo + (int)desloc + projeto.getTempExec() - 1; 
                    intervaloAloc.setIntervalo(inicioIntervalo, finalIntervalo);
                    prevMinus = 0;
                    currMinus = 0;
                    currPlus = 0;
                    nextPlus = 0;
                }
                else if (modo == 1)
                {
                    int deltaNecessario = ((int)desloc + projeto.getTempExec()) - (dataMax - dataMin + 1);

                    //std::cout << std::endl;
                    //std::cout << "Tamanho do projeto NÃO cabe na janela após última alocação. Tentando realocações.";
                    //std::cout << std::endl;

                    // verifica espaço realocando projeto anterior
                    int deltaDisponivel;
                    if (itr == this->_alocacoes[sonda].begin())
                    {
                        deltaDisponivel = itr->getIntervalo().getInicio() - itr->getProjeto().getInicioJanela();
                    }
                    else
                    {
                        int temp1, temp2;
                        temp1 = itr->getProjeto().getInicioJanela();
                        temp2 = std::prev(itr, 1)->getIntervalo().getFinal() + 1;
                        deltaDisponivel = itr->getIntervalo().getInicio() - std::max(temp1, temp2);
                    }
                    //std::cout << std::endl;
                    //std::cout << "O espaço disponível ao realocar o projeto anterior é: " << deltaDisponivel;
                    //std::cout << std::endl;

                    // atualiza valores da janela considerando o delta de realocação
                    dataMin = std::max(gapInit - deltaDisponivel, projeto.getInicioJanela());

                    // verifica se projeto cabe na janela alterada
                    if (dataMin + (int)desloc + projeto.getTempExec() - 1 <= dataMax)
                    {
                        //std::cout << std::endl;
                        //std::cout << "Inserção viável com alteração da janela.";
                        //std::cout << std::endl;

                        alocExiste = true;
                        caso = 6;
                        posicaoAloc = 999;
                        int inicioIntervalo = gapInit - deltaNecessario;
                        int finalIntervalo = inicioIntervalo + (int)desloc + projeto.getTempExec() - 1; 
                        intervaloAloc.setIntervalo(inicioIntervalo, finalIntervalo);
                        prevMinus = 0;
                        currMinus = deltaNecessario;
                        currPlus = 0;
                        nextPlus = 0;
                    }
                    else
                    {
                        //std::cout << std::endl;
                        //std::cout << "Inserção NÃO viável mesmo com alteração da janela.";
                        //std::cout << std::endl;
                    }
                }
                else
                {
                    //std::cout << std::endl;
                    //std::cout << "Tamanho do projeto NÃO cabe na janela após última alocação.";
                    //std::cout << std::endl;
                }
            }
            else
            {
                //std::cout << std::endl;
                //std::cout << "Janela após última alocação NÃO disponível: " << std::endl;
                //std::cout << std::endl;
            }
        }
        return std::make_tuple(alocExiste, posicaoAloc, intervaloAloc, prevMinus, currMinus, currPlus, nextPlus, caso);
    }
}

void AlocacoesList::inserirProjeto(Sonda sonda, Projeto projeto, int posicaoAloc, Intervalo intervalo, 
                                     int prevMinus, int currMinus, int currPlus, int nextPlus, int caso)
{
    //std::cout << std::endl;
    //std::cout << "Inserindo projeto " << projeto.getNome() << " na sonda " << sonda.getNome();
    //std::cout << std::endl;

    // verificar se sonda existe nas alocações
    std::map<Sonda, std::list<Alocacao>>::iterator it = this->_alocacoes.find(sonda);
    if (it == this->_alocacoes.end())
    {
        std::cout << std::endl;
        std::cout << "Sonda não encontrada nas alocações.";
        std::cout << std::endl;

        assert (it != this->_alocacoes.end());
    }

    // verificar se posição é viável
    if (posicaoAloc != 999) // 999 é a posição que indica inserção no final
    {
        if ( !(posicaoAloc <= this->_alocacoes[sonda].size() - 1) )
        {
            std::cout << std::endl;
            std::cout << "Posição inválida para inserção" << std::endl;
            std::cout << "Valor informado: " << posicaoAloc;
            std::cout << std::endl;

            assert(posicaoAloc <= this->_alocacoes[sonda].size() - 1);
        }
    }

    // verificar caso entre 1 e 6
    if ((caso < 1) || (caso > 6))
    {
        std::cout << std::endl;
        std::cout << "Caso para inserção inválido." << std::endl;
        std::cout << "Valor informado: " << caso;
        std::cout << std::endl;

        assert ((caso>=1) && (caso<=6));
    }

    // fazer alterações, se tiver que fazer
    if (caso == 1)
    {
        if ( (prevMinus!=0) || (currMinus!=0) || (currPlus!=0) || (nextPlus!=0) )
        {
            std::cout << std::endl;
            std::cout << "Valores fornecidos não representam caso 1.";
            std::cout << "prevMinus: " << prevMinus << std::endl;
            std::cout << "currMinus: " << currMinus << std::endl;
            std::cout << "currPlus: " << currPlus << std::endl;
            std::cout << "nextPlus: " << nextPlus << std::endl;
            std::cout << std::endl;
        }
        assert ( (prevMinus==0) && (currMinus==0) && (currPlus==0) && (nextPlus==0) );
    }
    else if (caso == 2)
    {
        if ( (prevMinus!=0) || (currMinus!=0) || (currPlus!=0) || (nextPlus!=0) )
        {
            std::cout << std::endl;
            std::cout << "Valores fornecidos não representam caso 2.";
            std::cout << "prevMinus: " << prevMinus << std::endl;
            std::cout << "currMinus: " << currMinus << std::endl;
            std::cout << "currPlus: " << currPlus << std::endl;
            std::cout << "nextPlus: " << nextPlus << std::endl;
            std::cout << std::endl;
        }
        assert ( (prevMinus==0) && (currMinus==0) && (currPlus==0) && (nextPlus==0) );
    }
    else if (caso == 3)
    {
        if ( (prevMinus!=0) || (currMinus>=0) || (currPlus!=0) || (nextPlus!=0) )
        {
            std::cout << std::endl;
            std::cout << "Valores fornecidos não representam caso 3.";
            std::cout << "prevMinus: " << prevMinus << std::endl;
            std::cout << "currMinus: " << currMinus << std::endl;
            std::cout << "currPlus: " << currPlus << std::endl;
            std::cout << "nextPlus: " << nextPlus << std::endl;
            std::cout << std::endl;
        }
        assert ( (prevMinus==0) && (currMinus<0) && (currPlus==0) && (nextPlus==0) );

        // caso: cabe na janela e deltaSetup é menor que zero
        //std::cout << std::endl;
        //std::cout << "Fazendo modificação de setup no valor de " << currMinus;
        //std::cout << std::endl;

        // alterar setup do projeto seguinte: posterga início
        std::list<Alocacao>::iterator itr = std::next(this->_alocacoes[sonda].begin(), posicaoAloc);
        Projeto projetoTemp = itr->getProjeto();
        Sonda sondaTemp = itr->getSonda();
        Intervalo intervaloTemp = itr->getIntervalo();
        intervaloTemp.setIntervalo(intervaloTemp.getInicio() - currMinus, intervaloTemp.getFinal());
        itr->setAlocacao(projetoTemp, sondaTemp, intervaloTemp);
    }
    else if (caso == 4)
    {
        if ( (prevMinus!=0) || (currMinus<0) || (currPlus<0) || (nextPlus<0) )
        {
            std::cout << std::endl;
            std::cout << "Valores fornecidos não representam caso 4.";
            std::cout << "prevMinus: " << prevMinus << std::endl;
            std::cout << "currMinus: " << currMinus << std::endl;
            std::cout << "currPlus: " << currPlus << std::endl;
            std::cout << "nextPlus: " << nextPlus << std::endl;
            std::cout << std::endl;
        }
        assert ( (prevMinus==0) && (currMinus>=0) && (currPlus>=0) && (nextPlus>=0) );

        // caso: cabe na janela e deltaSetup é maior que zero
        std::list<Alocacao>::iterator itr = std::next(this->_alocacoes[sonda].begin(), posicaoAloc);
        
        Projeto projetoTemp = itr->getProjeto();
        Sonda sondaTemp = itr->getSonda();
        Intervalo intervaloTemp = itr->getIntervalo();
        intervaloTemp.setIntervalo(intervaloTemp.getInicio() - currMinus, intervaloTemp.getFinal() + currPlus);
        itr->setAlocacao(projetoTemp, sondaTemp, intervaloTemp);

        if (nextPlus > 0)
        {
            std::list<Alocacao>::iterator itrNext = std::next(itr, 1);
            projetoTemp = itrNext->getProjeto();
            sondaTemp = itrNext->getSonda();
            intervaloTemp = itrNext->getIntervalo();
            intervaloTemp.setIntervalo(intervaloTemp.getInicio() + nextPlus, intervaloTemp.getFinal() + nextPlus);
            itrNext->setAlocacao(projetoTemp, sondaTemp, intervaloTemp);
        }
    }
    else if (caso == 5)
    {
        if ( (prevMinus<0) || (currMinus!=0) || (currPlus<0))
        {
            std::cout << std::endl;
            std::cout << "Valores fornecidos não representam caso 5.";
            std::cout << "prevMinus: " << prevMinus << std::endl;
            std::cout << "currMinus: " << currMinus << std::endl;
            std::cout << "currPlus: " << currPlus << std::endl;
            std::cout << "nextPlus: " << nextPlus << std::endl;
            std::cout << std::endl;
        }
        assert ( (prevMinus>=0) && (currMinus==0) && (currPlus>=0));

        // caso: realocando projetos vizinhos
        std::list<Alocacao>::iterator itr = std::next(this->_alocacoes[sonda].begin(), posicaoAloc);

        // realocar curr
        Projeto projetoTemp = itr->getProjeto();
        Sonda sondaTemp = itr->getSonda();
        Intervalo intervaloTemp = itr->getIntervalo();
        intervaloTemp.setIntervalo(intervaloTemp.getInicio() + currPlus, intervaloTemp.getFinal() + currPlus);
        // modificar deltaDesloc no curr
        if (nextPlus < 0)
        {
            intervaloTemp.setIntervalo(intervaloTemp.getInicio() - nextPlus, intervaloTemp.getFinal());
        }
        else if (nextPlus > 0)
        {
            intervaloTemp.setIntervalo(intervaloTemp.getInicio(), intervaloTemp.getFinal() + nextPlus); 
        }
        itr->setAlocacao(projetoTemp, sondaTemp, intervaloTemp);

        // realocar prev
        if (prevMinus > 0)
        {
            std::list<Alocacao>::iterator itrPrev = std::prev(itr, 1);
            projetoTemp = itrPrev->getProjeto();
            sondaTemp = itrPrev->getSonda();
            intervaloTemp = itrPrev->getIntervalo();
            intervaloTemp.setIntervalo(intervaloTemp.getInicio() - prevMinus, intervaloTemp.getFinal() - prevMinus);
            itrPrev->setAlocacao(projetoTemp, sondaTemp, intervaloTemp);
        }
    }
    else if (caso == 6)
    {
        if ( (prevMinus!=0) || (currMinus<0) || (currPlus!=0) || (nextPlus!=0) )
        {
            std::cout << std::endl;
            std::cout << "Valores fornecidos não representam caso 6.";
            std::cout << "prevMinus: " << prevMinus << std::endl;
            std::cout << "currMinus: " << currMinus << std::endl;
            std::cout << "currPlus: " << currPlus << std::endl;
            std::cout << "nextPlus: " << nextPlus << std::endl;
            std::cout << std::endl;
        }
        assert ( (prevMinus==0) && (currMinus>=0) && (currPlus==0) && (nextPlus==0) );

        // caso: última janela, alterando última alocação
        if (currMinus > 0)
        {
            std::list<Alocacao>::iterator itr = std::prev(this->_alocacoes[sonda].end(), 1);
            Projeto projetoTemp = itr->getProjeto();
            Sonda sondaTemp = itr->getSonda();
            Intervalo intervaloTemp = itr->getIntervalo();
            intervaloTemp.setIntervalo(intervaloTemp.getInicio() - currMinus, intervaloTemp.getFinal() - currMinus);
            itr->setAlocacao(projetoTemp, sondaTemp, intervaloTemp);
        }
    }

    // cria a alocação
    Alocacao x{projeto, sonda, intervalo};

    // insere
    if (posicaoAloc == 999) // 999 é a posição que indica inserção no final
    {
        //std::cout << std::endl;
        //std::cout << "Inserindo no final.";
        //std::cout << std::endl;

        this->_alocacoes[sonda].push_back(x);
    }
    else
    {
        //std::cout << std::endl;
        //std::cout << "Inserindo na posição " << posicaoAloc;
        //std::cout << std::endl;

        std::list<Alocacao>::iterator posicao = std::next(this->_alocacoes[sonda].begin(), posicaoAloc);
        this->_alocacoes[sonda].insert(posicao, x);
    }
}

bool AlocacoesList::removerProjeto(Sonda sonda, Projeto projeto, int deltaT)
{
    // verificar se sonda existe
    std::map<Sonda, std::list<Alocacao>>::iterator it = this->_alocacoes.find(sonda);
    if (it == this->_alocacoes.end())
    {
        std::cout << std::endl;
        std::cout << "Sonda não existe nas alocações.";
        std::cout << std::endl;
    }
    assert (it != this->_alocacoes.end());

    // verificar se projeto existe na sonda
    bool projetoExiste = false;
    std::list<Alocacao>::iterator posicao;
    for (std::list<Alocacao>::iterator itr=this->_alocacoes[sonda].begin(); itr!=this->_alocacoes[sonda].end(); ++itr)
    {
        Projeto x = itr->getProjeto();
        if (x == projeto)
        {
            projetoExiste = true;
            posicao = itr;
            break;
        }
    }
    if (projetoExiste == false)
    {
        std::cout << std::endl;
        std::cout << "Projeto não encontrado nas alocações da sonda.";
        std::cout << std::endl;
    }
    assert (projetoExiste);

    // se projeto é a última alocação
    if (std::next(posicao, 1) == this->_alocacoes[sonda].end())
    {
        //std::cout << std::endl;
        //std::cout << "Removendo última alocação.";
        //std::cout << std::endl;

        // remove
        this->_alocacoes[sonda].erase(posicao);

        return true;
    }
    // se tiver alguma alocação posterior
    else
    {
        // verifica mudança de setup
        CalculadorDeDesloc calc{};
        double oldDesloc=0, newDesloc=0;
        int deltaDesloc=0;
        oldDesloc = calc.getDesloc(projeto, std::next(posicao, 1)->getProjeto(), deltaT);
        if (posicao == this->_alocacoes[sonda].begin())
        {
            newDesloc = calc.getDesloc(sonda, std::next(posicao, 1)->getProjeto(), deltaT);
        }
        else
        {
            newDesloc = calc.getDesloc(std::prev(posicao, 1)->getProjeto(), std::next(posicao, 1)->getProjeto(), deltaT);
        }
        deltaDesloc = (int)newDesloc - (int)oldDesloc;

        if (deltaDesloc == 0)
        {
            //std::cout << std::endl;
            //std::cout << "Removendo alocação com deltaSetup: " << deltaDesloc;
            //std::cout << std::endl;

            // remove
            this->_alocacoes[sonda].erase(posicao);

            return true;
        }
        else if (deltaDesloc < 0)
        {
            //std::cout << std::endl;
            //std::cout << "Removendo alocação com deltaSetup: " << deltaDesloc;
            //std::cout << std::endl;

            // altera projeto seguinte
            std::list<Alocacao>::iterator itrNext = std::next(posicao, 1);
            Projeto projetoTemp = itrNext->getProjeto();
            Sonda sondaTemp = itrNext->getSonda();
            Intervalo intervaloTemp = itrNext->getIntervalo();
            intervaloTemp.setIntervalo(intervaloTemp.getInicio() - deltaDesloc, intervaloTemp.getFinal());
            itrNext->setAlocacao(projetoTemp, sondaTemp, intervaloTemp);

            // remove
            this->_alocacoes[sonda].erase(posicao);

            return true;
        }
        else
        {
            std::list<Alocacao>::iterator itrNext = std::next(posicao, 1);
            int deltaLeftDisp=0, deltaRightDisp=0;

            // verifica quanto de espaço tenho para trás do next
            if (posicao == this->_alocacoes[sonda].begin())
            {
                deltaLeftDisp = itrNext->getIntervalo().getInicio() - itrNext->getProjeto().getInicioJanela();
            }
            else
            {
                int temp1 = itrNext->getProjeto().getInicioJanela();
                int temp2 = std::prev(posicao, 1)->getIntervalo().getFinal() + 1;
                deltaLeftDisp = itrNext->getIntervalo().getInicio() - std::max(temp1, temp2);
            }

            // verifica quanto de espaço tenho para frente do next
            if (std::next(itrNext, 1) == this->_alocacoes[sonda].end())
            {
                deltaRightDisp = itrNext->getProjeto().getFinalJanela() - itrNext->getIntervalo().getFinal();
            }
            else
            {
                int temp1 = itrNext->getProjeto().getFinalJanela();
                int temp2 = std::next(itrNext, 1)->getIntervalo().getInicio() - 1;
                deltaRightDisp = std::min(temp1, temp2) - itrNext->getIntervalo().getFinal();
            }

            // se espaço para trás basta
            if (deltaLeftDisp >= deltaDesloc)
            {
                //std::cout << std::endl;
                //std::cout << "deltaSetup positivo>: " << deltaDesloc << std::endl;
                //std::cout << "Espaço disponível para trás é suficiente: " << deltaLeftDisp << std::endl;
                //std::cout << "Removendo projeto alterando próxima alocação" << std::endl;

                Projeto projetoTemp = itrNext->getProjeto();
                Sonda sondaTemp = itrNext->getSonda();
                Intervalo intervaloTemp = itrNext->getIntervalo();
                intervaloTemp.setIntervalo(intervaloTemp.getInicio() - deltaDesloc, intervaloTemp.getFinal());
                itrNext->setAlocacao(projetoTemp, sondaTemp, intervaloTemp);

                this->_alocacoes[sonda].erase(posicao);

                return true;
            }
            else if ( (deltaLeftDisp + deltaRightDisp) >= deltaDesloc)
            {
                //std::cout << std::endl;
                //std::cout << "deltaSetup positivo>: " << deltaDesloc << std::endl;
                //std::cout << "Espaço disponível para trás e para frente são suficientes."<< std::endl;
                //std::cout << "Espaço disponível para trás: " << deltaLeftDisp << std::endl;
                //std::cout << "Espaço disponível para frente: " << deltaRightDisp << std::endl;
                //std::cout << "Removendo projeto alterando próxima alocação" << std::endl;

                Projeto projetoTemp = itrNext->getProjeto();
                Sonda sondaTemp = itrNext->getSonda();
                Intervalo intervaloTemp = itrNext->getIntervalo();
                intervaloTemp.setIntervalo(intervaloTemp.getInicio() - deltaLeftDisp, 
                                           intervaloTemp.getFinal() + (deltaDesloc - deltaLeftDisp));
                itrNext->setAlocacao(projetoTemp, sondaTemp, intervaloTemp);

                this->_alocacoes[sonda].erase(posicao);

                return true;
            }
            else
            {
                std::cout << std::endl;
                std::cout << "Remoção não é viável, pois deltaSetup: " << deltaDesloc;
                std::cout << std::endl;

                return false;
            }
        }
    }
}

