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
        std::vector<Alocacao> vetor;
        _alocacoes.insert(std::pair<Sonda, std::vector<Alocacao>>(*itr, vetor));
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

    bool idxFound = false;
    int count = 0;
    for (std::vector<Alocacao>::iterator it = _alocacoes[sonda].begin(); it!=_alocacoes[sonda].end(); ++it)
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

Alocacao AlocacoesVector::getAlocacao(Sonda sonda, Projeto projeto)
{
    std::map<Sonda, std::vector<Alocacao>>::iterator it = _alocacoes.find(sonda);
    if (it == _alocacoes.end())
    {
        std::cout << "A sonda especificada não foi encontrada." << std::endl;
        Alocacao x{};
        return x;
    }

    bool projFound = false;
    for (std::vector<Alocacao>::iterator it = _alocacoes[sonda].begin(); it!=_alocacoes[sonda].end(); ++it)
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

    _alocacoes[sonda] = alocacoes;
}

std::tuple<bool, int, Intervalo, int, int> AlocacoesVector::buscarJanelaViavel(Sonda sonda, Projeto projeto)
{
    std::cout << std::endl;
    std::cout << "Buscando janela viável para o projeto " << projeto.getNome() << " na sonda " << sonda.getNome();
    std::cout << std::endl;

    std::cout << "Alocações atuais são:" << std::endl;
    this->print();

    // verifica se sonda existe
    std::map<Sonda, std::vector<Alocacao>>::iterator it = this->_alocacoes.find(sonda);
    if (it == this->_alocacoes.end())
    {
        std::cout << "Sonda não encontrada nas alocações." << std::endl;
        assert (it !=this->_alocacoes.end());
    }

    // inicializa valores que serão retornados
    CalculadorDeDesloc calc{};
    bool alocExiste = false;
    Intervalo intervaloAloc{};
    int posicaoAloc = -1;
    int deltaNext = 0;
    int numNexts = 0;

    std::cout << "Sonda empty: " << this->_alocacoes[sonda].empty() << std::endl;
    std::cout << "Sonda size: " << this->_alocacoes[sonda].size() << std::endl;

    // se o vetor de alocações está vazio
    if (this->_alocacoes[sonda].empty())
    {
        std::cout << std::endl;
        std::cout << "A sonda " << sonda.getNome() << " ainda NÃO TEM alocações.";
        std::cout << std::endl;

        // se é viável inserir projeto entre release e due
        double desloc = calc.getDesloc(sonda, projeto);
        if (projeto.getInicioJanela() + (int)desloc + projeto.getTempExec() - 1 <= projeto.getFinalJanela())
        {
            // escolhe intervalo
            int inicioIntervalo = projeto.getInicioJanela();
            int finalIntervalo = projeto.getInicioJanela() + (int)desloc + projeto.getTempExec() - 1;
            intervaloAloc.setIntervalo(inicioIntervalo, finalIntervalo);

            std::cout << std::endl;
            std::cout << "Inserção viável na sonda " << sonda.getNome() << " ainda sem alocações." << std::endl;
            std::cout << "Release do projeto: " << projeto.getInicioJanela() << std::endl;
            std::cout << "Início do intervalo: " << intervaloAloc.getInicio() << std::endl;
            std::cout << "setup: " << desloc << std::endl;
            std::cout << "proc: " << projeto.getTempExec() << std::endl;
            std::cout << "Final do intervalo: " << intervaloAloc.getFinal() << std::endl;
            std::cout << "Due do projeto: " << projeto.getFinalJanela() << std::endl;
            std::cout << std::endl;

            // alocar
            alocExiste = true;
            posicaoAloc = 0;
            deltaNext = 0;
            numNexts = 0;
        }
        else
        {
            std::cout << std::endl;
            std::cout << "Inserção NÃO viável na sonda " << sonda.getNome() << " ainda sem alocações.";
            std::cout << std::endl;

            alocExiste = false;
            posicaoAloc = -1;
            intervaloAloc.setIntervalo(0, 0);
            deltaNext = 0;
            numNexts = 0;
        }
        return std::make_tuple(alocExiste, posicaoAloc, intervaloAloc, deltaNext, numNexts);
    }
    // se já existem alocações no vetor
    else
    {
        std::cout << std::endl;
        std::cout << "A sonda " << sonda.getNome() << " JÁ TEM alocações.";
        std::cout << std::endl;

        // itera sob as alocações da sonda
        int count = -1;
        for (std::vector<Alocacao>::iterator itr=this->_alocacoes[sonda].begin(); itr!=this->_alocacoes[sonda].end(); ++itr)
        {
            count++;

            double desloc = 0;
            int gapInit = -1, gapFinal = -1;
            double oldDesloc = 0, newDesloc = 0;
            int deltaDesloc = 0;
            int dataMin = -1, dataMax = -1;
            int deltaDeslocEfetivo;
            bool janelaExiste = false;

            std::cout << std::endl;
            std::cout << "Verificando alocação de índice " << count << " da sonda " << sonda.getNome();
            std::cout << std::endl;

            // pega informações da janela que antecede a alocação corrente
            if (itr == this->_alocacoes[sonda].begin())
            {
                desloc = calc.getDesloc(sonda, projeto);

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
                desloc = calc.getDesloc((itr-1)->getProjeto(), projeto);

                // se existe janela
                if (itr->getIntervalo().getInicio() == (itr-1)->getIntervalo().getFinal() + 1)
                {
                    janelaExiste = false;
                }
                else
                {
                    janelaExiste = true;
                    gapInit = (itr-1)->getIntervalo().getFinal() + 1;
                    gapFinal = itr->getIntervalo().getInicio() - 1;
                }
            }
            if (janelaExiste)
            {
                std::cout << std::endl;
                std::cout << "Janela disponível: " << std::endl;
                std::cout << "Início: " << gapInit << ", e final: " << gapFinal << std::endl;
                std::cout << std::endl;
            }
            else
            {
                std::cout << std::endl;
                std::cout << "Janela NÃO disponível: " << std::endl;
                std::cout << std::endl;
                continue;
            }
            
            // verifica se a inserção do projeto altera o setup do projeto seguinte
            if (itr == this->_alocacoes[sonda].begin())
            {
                oldDesloc = calc.getDesloc(sonda, itr->getProjeto());
            }
            else
            {
                oldDesloc = calc.getDesloc((itr-1)->getProjeto(), itr->getProjeto());
            }
            newDesloc = calc.getDesloc(projeto, itr->getProjeto());
            deltaDesloc = (int)newDesloc - (int)oldDesloc;
            std::cout << std::endl << "Se o projeto " << projeto.getNome() << " for inserido na posição " << count
                      << ", o setup do projeto seguinte será alterado em: " << deltaDesloc << std::endl;
            
            // se tamanho do projeto cabe na janela, entre release e due
            dataMin = std::max(gapInit, projeto.getInicioJanela());
            dataMax = std::min(gapFinal, projeto.getFinalJanela());
            deltaDeslocEfetivo = std::min(deltaDesloc, 0);
            if (dataMin + (int)desloc + projeto.getTempExec() - 1 <= dataMax - deltaDeslocEfetivo)
            {
                std::cout << std::endl;
                std::cout << "Tamanho do projeto cabe na sonda " << sonda.getNome() << " posição " << count << std::endl;
                std::cout << "Release do projeto: " << projeto.getInicioJanela() << std::endl;
                std::cout << "Data mínima: " << dataMin << std::endl;
                std::cout << "setup: " << desloc << std::endl;
                std::cout << "proc: " << projeto.getTempExec() << std::endl;
                std::cout << "Data máxima: " << dataMax << std::endl;
                std::cout << "Due do projeto: " << projeto.getFinalJanela() << std::endl;
                std::cout << std::endl;

                // escolher intervalo
                int inicioIntervalo, finalIntervalo;
                inicioIntervalo = dataMin;
                finalIntervalo = inicioIntervalo + desloc + projeto.getTempExec() - 1;
                intervaloAloc.setIntervalo(inicioIntervalo, finalIntervalo);
                std::cout << std::endl;
                std::cout << "Intervalo escolhido: " << std::endl;
                std::cout << "Início do intervalo: " << intervaloAloc.getInicio() << std::endl;
                std::cout << "Final do intervalo: " << intervaloAloc.getFinal() << std::endl;
                std::cout << std::endl;

                // se não altera setup do projeto seguinte
                if (deltaDesloc == 0)
                {
                    std::cout << std::endl;
                    std::cout << "Inserção viável sem modificar setup do projeto seguinte";
                    std::cout << std::endl;

                    // alocar
                    alocExiste = true;
                    posicaoAloc = count;
                    deltaNext = 0;
                    numNexts = 0;

                    break;
                }
                // se altera setup do projeto seguinte para menos
                else if (deltaDesloc < 0)
                {
                    std::cout << std::endl;
                    std::cout << "Inserção viável modificando setup do projeto seguinte para menos. Valor: " << deltaDesloc;
                    std::cout << std::endl;

                    // alocar
                    alocExiste = true;
                    posicaoAloc = count;
                    deltaNext = deltaDesloc;
                    numNexts = 1;

                    break;
                }
                // se altera setup do projeto seguinte para mais
                else
                {
                    std::cout << std::endl;
                    std::cout << "O setup do projeto seguinte sofre modificação para mais, em caso de inserção.";
                    std::cout << "Tentando realocar diferença de desloc.";
                    std::cout << std::endl;

                    // tenta colocar diferença para trás
                    // tenta colocar diferença para frente
                }
            }
            else
            {
                std::cout << std::endl;
                std::cout << "Tamanho do projeto NÃO cabe na sonda. Tentar realocações.";
                std::cout << std::endl;

                // tenta realocar projetos vizinhos
            }
        }
        // se não conseguiu alocar, tenta na janela após a última alocação

        return std::make_tuple(alocExiste, posicaoAloc, intervaloAloc, deltaNext, numNexts);
    }
}

void AlocacoesVector::inserirProjeto(Sonda sonda, Projeto projeto, int posicaoAloc, Intervalo intervalo, 
                                     int deltaNext, int numNexts)
{
    std::cout << std::endl;
    std::cout << "Inserindo projeto " << projeto.getNome() << " na sonda " << sonda.getNome();
    std::cout << std::endl;

    // verificar se sonda existe nas alocações
    std::map<Sonda, std::vector<Alocacao>>::iterator it = this->_alocacoes.find(sonda);
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

    // fazer alterações, se tiver que fazer
    if (deltaNext < 0)
    {
        std::cout << std::endl;
        std::cout << "Fazendo modificação de setup no valor de " << deltaNext;
        std::cout << std::endl;

        // alterar setup do projeto seguinte: posterga início
        std::vector<Alocacao>::iterator itr = this->_alocacoes[sonda].begin() + posicaoAloc;
        Projeto projetoTemp = itr->getProjeto();
        Sonda sondaTemp = itr->getSonda();
        Intervalo intervaloTemp = itr->getIntervalo();
        intervaloTemp.setIntervalo(intervaloTemp.getInicio() - deltaNext, intervaloTemp.getFinal());
        itr->setAlocacao(projetoTemp, sondaTemp, intervaloTemp);
    }

    // cria a alocação
    Alocacao x{projeto, sonda, intervalo};

    // insere
    if (posicaoAloc == 999) // 999 é a posição que indica inserção no final
    {
        std::cout << std::endl;
        std::cout << "Inserindo no final.";
        std::cout << std::endl;

        this->_alocacoes[sonda].push_back(x);
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Inserindo na posição " << posicaoAloc;
        std::cout << std::endl;

        std::vector<Alocacao>::iterator posicao = std::next(this->_alocacoes[sonda].begin(), posicaoAloc);
        this->_alocacoes[sonda].insert(posicao, x);
    }
}

/*

std::tuple<> Alocacoes::removerProjeto(Sonda, int)
{
    // TODO
}

*/