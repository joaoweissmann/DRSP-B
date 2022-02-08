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
                desloc = calc.getDesloc(sonda, projeto);
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
                desloc = calc.getDesloc(sonda, projeto);
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
                desloc = calc.getDesloc(projPrev, projeto);
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
                desloc = calc.getDesloc(projPrev, projeto);
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
        _alocacoes.insert(std::pair<Sonda, std::vector<Alocacao>>(itr->first, itr->second));
    }
}

AlocacoesVector::AlocacoesVector(std::map<Sonda, std::list<Alocacao>> alocacoes)
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
                desloc = calc.getDesloc(sonda, projeto);
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
                desloc = calc.getDesloc(sonda, projeto);
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
                desloc = calc.getDesloc(projPrev, projeto);
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
                desloc = calc.getDesloc(projPrev, projeto);
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

int AlocacoesVector::getNAlocacoes(Sonda sonda)
{
    std::map<Sonda, std::vector<Alocacao>>::iterator it = _alocacoes.find(sonda);
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

Alocacao AlocacoesVector::getAlocacao(Sonda sonda, int idx)
{
    std::map<Sonda, std::vector<Alocacao>>::iterator it = _alocacoes.find(sonda);
    if (it == _alocacoes.end())
    {
        std::cout << "A sonda especificada não foi encontrada." << std::endl;
        Alocacao x{};
        return x;
    }

    int count = 0;
    std::vector<Alocacao>::iterator itr = _alocacoes[sonda].begin();
    for (std::vector<Alocacao>::iterator it = _alocacoes[sonda].begin(); it!=_alocacoes[sonda].end(); ++it)
    {
        if (count == idx)
        {
            Alocacao x = *it;
            return x;
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
        Alocacao x{};
        return x;
    }
}

Alocacao AlocacoesVector::getAlocacao(Sonda sonda, Projeto projeto)
{
    std::map<Sonda, std::vector<Alocacao>>::iterator it = _alocacoes.find(sonda);
    if (it == _alocacoes.end())
    {
        std::cout << "A sonda especificada não foi encontrada." << std::endl;
        Alocacao x{};
        return x;
    }

    std::vector<Alocacao>::iterator itr = _alocacoes[sonda].begin();
    for (std::vector<Alocacao>::iterator it = _alocacoes[sonda].begin(); it!=_alocacoes[sonda].end(); ++it)
    {
        Alocacao x = *it;
        if (projeto == x.getProjeto())
        {
            return x;
        }
        else
        {
            itr = it;
        }
    }
    if (itr == _alocacoes[sonda].end())
    {
        std::cout << "Alocação não encontrada." << std::endl;
        Alocacao x{};
        return x;
    }
}

int AlocacoesVector::getAlocacaoIndex(Sonda sonda, Projeto projeto)
{
    std::map<Sonda, std::vector<Alocacao>>::iterator it = _alocacoes.find(sonda);
    if (it == _alocacoes.end())
    {
        std::cout << "A sonda especificada não foi encontrada." << std::endl;
        return 0;
    }

    int count = 0;
    std::vector<Alocacao>::iterator itr = _alocacoes[sonda].begin();
    for (std::vector<Alocacao>::iterator it = _alocacoes[sonda].begin(); it!=_alocacoes[sonda].end(); ++it)
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

void AlocacoesVector::setAlocacoes(std::map<Sonda, std::vector<Alocacao>> alocacoes)
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
                desloc = calc.getDesloc(sonda, projeto);
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
                desloc = calc.getDesloc(sonda, projeto);
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
                desloc = calc.getDesloc(projPrev, projeto);
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
                desloc = calc.getDesloc(projPrev, projeto);
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
        _alocacoes.insert(std::pair<Sonda, std::vector<Alocacao>>(itr->first, itr->second));
    }
}

void AlocacoesVector::setAlocacoes(Sonda sonda, std::vector<Alocacao> alocacoes)
{
    std::map<Sonda, std::vector<Alocacao>>::iterator it = _alocacoes.find(sonda);
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
            desloc = calc.getDesloc(sonda, projeto);
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
            desloc = calc.getDesloc(sonda, projeto);
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
            desloc = calc.getDesloc(projPrev, projeto);
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
            desloc = calc.getDesloc(projPrev, projeto);
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

    _alocacoes.insert(std::pair<Sonda, std::vector<Alocacao>>(sonda, alocacoes));
}

/*
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