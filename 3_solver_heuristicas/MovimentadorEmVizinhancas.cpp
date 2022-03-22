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
#include "MovimentadorEmVizinhancas.h"

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::shift1x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, DadosDeEntrada dataset, 
                                                  int estrutura, int modoRealoc, Alocacao alocacao1, Sonda sonda2)
{
    Sonda sonda1 = alocacao1.getSonda();
    Projeto projeto1 = alocacao1.getProjeto();
    Intervalo intervalo1 = alocacao1.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // remove projeto
    bool removed = false;
    removed = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1);
    if (removed)
    {
        // faz busca
        bool alocExiste = false;
        int posicaoAloc = -1;
        Intervalo intervaloAloc{};
        int prevMinus = 0;
        int currMinus = 0;
        int currPlus = 0;
        int nextPlus = 0;
        int caso = 0;
        std::tie(alocExiste, posicaoAloc, intervaloAloc, prevMinus, currMinus, currPlus, nextPlus, caso) = 
                                                    solucaoLocal.buscarJanelaViavel(sonda2, projeto1, modoRealoc);
        // se viável, insere     
        if (alocExiste)
        {
            solucaoLocal.inserirProjeto(sonda2, projeto1, posicaoAloc, intervaloAloc, prevMinus, 
                                            currMinus, currPlus, nextPlus, caso);
        }
    }
    std::map<Sonda, std::vector<Alocacao>> alocsReturn = solucaoLocal.getAlocacoes();
    return alocsReturn;
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::shift2x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                         DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                         Alocacao alocacao1, Alocacao alocacao2, Sonda sonda2)
{
    Sonda sonda1 = alocacao1.getSonda();
    Projeto projeto1 = alocacao1.getProjeto();
    Intervalo intervalo1 = alocacao1.getIntervalo();
    Projeto projeto2 = alocacao2.getProjeto();
    Intervalo intervalo2 = alocacao2.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // remover projeto1 da sonda1
    bool removed1 = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1);
    
    // remover projeto2 da sonda1
    bool removed2 = solucaoLocal.removerProjeto(sonda1, projeto2, intervalo2);
    
    if (removed1 && removed2)
    {
        // inserir projeto1 na sonda2
        // faz busca
        bool alocExiste1 = false;
        int posicaoAloc1 = -1;
        Intervalo intervaloAloc1{};
        int prevMinus1 = 0;
        int currMinus1 = 0;
        int currPlus1 = 0;
        int nextPlus1 = 0;
        int caso1 = 0;
        std::tie(alocExiste1, posicaoAloc1, intervaloAloc1, prevMinus1, currMinus1, currPlus1, nextPlus1, caso1) = 
                                                    solucaoLocal.buscarJanelaViavel(sonda2, projeto1, modoRealoc);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda2
            solucaoLocal.inserirProjeto(sonda2, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1);
            
            // inserir projeto2 na sonda2
            // faz busca
            bool alocExiste2 = false;
            int posicaoAloc2 = -1;
            Intervalo intervaloAloc2{};
            int prevMinus2 = 0;
            int currMinus2 = 0;
            int currPlus2 = 0;
            int nextPlus2 = 0;
            int caso2 = 0;
            std::tie(alocExiste2, posicaoAloc2, intervaloAloc2, prevMinus2, currMinus2, currPlus2, nextPlus2, caso2) = 
                                                        solucaoLocal.buscarJanelaViavel(sonda2, projeto2, modoRealoc);
            if (alocExiste2)
            {
                // inserir projeto2 na sonda2
                solucaoLocal.inserirProjeto(sonda2, projeto2, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                            currMinus2, currPlus2, nextPlus2, caso2);
            }
        }
    }
    std::map<Sonda, std::vector<Alocacao>> alocsReturn = solucaoLocal.getAlocacoes();
    return alocsReturn;
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::swap1x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2)
{
    Sonda sonda1 = alocacao1.getSonda();
    Projeto projeto1 = alocacao1.getProjeto();
    Intervalo intervalo1 = alocacao1.getIntervalo();
    Sonda sonda2 = alocacao2.getSonda();
    Projeto projeto2 = alocacao2.getProjeto();
    Intervalo intervalo2 = alocacao2.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // remover projeto1 da sonda1
    bool removed1 = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1);

    // remover projeto2 da sonda2
    bool removed2 = solucaoLocal.removerProjeto(sonda2, projeto2, intervalo2);

    if (removed1 && removed2)
    {
        // inserir projeto1 na sonda2
        // faz busca
        bool alocExiste1 = false;
        int posicaoAloc1 = -1;
        Intervalo intervaloAloc1{};
        int prevMinus1 = 0;
        int currMinus1 = 0;
        int currPlus1 = 0;
        int nextPlus1 = 0;
        int caso1 = 0;
        std::tie(alocExiste1, posicaoAloc1, intervaloAloc1, prevMinus1, currMinus1, currPlus1, nextPlus1, caso1) = 
                                                    solucaoLocal.buscarJanelaViavel(sonda2, projeto1, modoRealoc);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda2
            solucaoLocal.inserirProjeto(sonda2, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1);
            
            // inserir projeto2 na sonda1
            // faz busca
            bool alocExiste2 = false;
            int posicaoAloc2 = -1;
            Intervalo intervaloAloc2{};
            int prevMinus2 = 0;
            int currMinus2 = 0;
            int currPlus2 = 0;
            int nextPlus2 = 0;
            int caso2 = 0;
            std::tie(alocExiste2, posicaoAloc2, intervaloAloc2, prevMinus2, currMinus2, currPlus2, nextPlus2, caso2) = 
                                                        solucaoLocal.buscarJanelaViavel(sonda1, projeto2, modoRealoc);
            if (alocExiste2)
            {
                // inserir projeto2 na sonda1
                solucaoLocal.inserirProjeto(sonda1, projeto2, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                            currMinus2, currPlus2, nextPlus2, caso2);
            }
        }
    }
    std::map<Sonda, std::vector<Alocacao>> alocsReturn = solucaoLocal.getAlocacoes();
    return alocsReturn;
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::swap2x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2, Alocacao alocacao3)
{
    Sonda sonda1 = alocacao1.getSonda();
    Sonda sonda2 = alocacao3.getSonda();
    Projeto projeto1 = alocacao1.getProjeto();
    Projeto projeto2 = alocacao2.getProjeto();
    Projeto projeto3 = alocacao3.getProjeto();
    Intervalo intervalo1 = alocacao1.getIntervalo();
    Intervalo intervalo2 = alocacao2.getIntervalo();
    Intervalo intervalo3 = alocacao3.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // remover projeto1 da sonda1
    bool removed1 = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1);

    // remover projeto2 da sonda1
    bool removed2 = solucaoLocal.removerProjeto(sonda1, projeto2, intervalo2);

    // remover projeto3 da sonda2
    bool removed3 = solucaoLocal.removerProjeto(sonda2, projeto3, intervalo3);

    if (removed1 && removed2 && removed3)
    {
        // inserir projeto1 na sonda2
        // faz busca
        bool alocExiste1 = false;
        int posicaoAloc1 = -1;
        Intervalo intervaloAloc1{};
        int prevMinus1 = 0;
        int currMinus1 = 0;
        int currPlus1 = 0;
        int nextPlus1 = 0;
        int caso1 = 0;
        std::tie(alocExiste1, posicaoAloc1, intervaloAloc1, prevMinus1, currMinus1, currPlus1, nextPlus1, caso1) = 
                                                    solucaoLocal.buscarJanelaViavel(sonda2, projeto1, modoRealoc);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda2
            solucaoLocal.inserirProjeto(sonda2, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1);

            // inserir projeto2 na sonda2
            // faz busca
            bool alocExiste2 = false;
            int posicaoAloc2 = -1;
            Intervalo intervaloAloc2{};
            int prevMinus2 = 0;
            int currMinus2 = 0;
            int currPlus2 = 0;
            int nextPlus2 = 0;
            int caso2 = 0;
            std::tie(alocExiste2, posicaoAloc2, intervaloAloc2, prevMinus2, currMinus2, currPlus2, nextPlus2, caso2) = 
                                                        solucaoLocal.buscarJanelaViavel(sonda2, projeto2, modoRealoc);
            if (alocExiste2)
            {
                // inserir projeto2 na sonda2
                solucaoLocal.inserirProjeto(sonda2, projeto2, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                        currMinus2, currPlus2, nextPlus2, caso2);

                // inserir projeto3 na sonda1
                // faz busca
                bool alocExiste3 = false;
                int posicaoAloc3 = -1;
                Intervalo intervaloAloc3{};
                int prevMinus3 = 0;
                int currMinus3 = 0;
                int currPlus3 = 0;
                int nextPlus3 = 0;
                int caso3 = 0;
                std::tie(alocExiste3, posicaoAloc3, intervaloAloc3, prevMinus3, currMinus3, currPlus3, nextPlus3, caso3) = 
                                                            solucaoLocal.buscarJanelaViavel(sonda1, projeto3, modoRealoc);
                if (alocExiste3)
                {
                    // inserir projeto3 na sonda1
                    solucaoLocal.inserirProjeto(sonda1, projeto3, posicaoAloc3, intervaloAloc3, prevMinus3, 
                                        currMinus3, currPlus3, nextPlus3, caso3);
                }
            }
        }
    }
    std::map<Sonda, std::vector<Alocacao>> alocsReturn = solucaoLocal.getAlocacoes();
    return alocsReturn;
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::swap2x2InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2, 
                                                                 Alocacao alocacao3, Alocacao alocacao4)
{
    Sonda sonda1 = alocacao1.getSonda();
    Sonda sonda2 = alocacao3.getSonda();
    Projeto projeto1 = alocacao1.getProjeto();
    Projeto projeto2 = alocacao2.getProjeto();
    Projeto projeto3 = alocacao3.getProjeto();
    Projeto projeto4 = alocacao4.getProjeto();
    Intervalo intervalo1 = alocacao1.getIntervalo();
    Intervalo intervalo2 = alocacao2.getIntervalo();
    Intervalo intervalo3 = alocacao3.getIntervalo();
    Intervalo intervalo4 = alocacao4.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // remover projeto1 da sonda1
    bool removed1 = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1);

    // remover projeto2 da sonda1
    bool removed2 = solucaoLocal.removerProjeto(sonda1, projeto2, intervalo2);

    // remover projeto3 da sonda2
    bool removed3 = solucaoLocal.removerProjeto(sonda2, projeto3, intervalo3);

    // remover projeto4 da sonda2
    bool removed4 = solucaoLocal.removerProjeto(sonda2, projeto4, intervalo3);

    if (removed1 && removed2 && removed3 && removed4)
    {
        // inserir projeto1 na sonda2
        // faz busca
        bool alocExiste1 = false;
        int posicaoAloc1 = -1;
        Intervalo intervaloAloc1{};
        int prevMinus1 = 0;
        int currMinus1 = 0;
        int currPlus1 = 0;
        int nextPlus1 = 0;
        int caso1 = 0;
        std::tie(alocExiste1, posicaoAloc1, intervaloAloc1, prevMinus1, currMinus1, currPlus1, nextPlus1, caso1) = 
                                                    solucaoLocal.buscarJanelaViavel(sonda2, projeto1, modoRealoc);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda2
            solucaoLocal.inserirProjeto(sonda2, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1);

            // inserir projeto2 na sonda2
            // faz busca
            bool alocExiste2 = false;
            int posicaoAloc2 = -1;
            Intervalo intervaloAloc2{};
            int prevMinus2 = 0;
            int currMinus2 = 0;
            int currPlus2 = 0;
            int nextPlus2 = 0;
            int caso2 = 0;
            std::tie(alocExiste2, posicaoAloc2, intervaloAloc2, prevMinus2, currMinus2, currPlus2, nextPlus2, caso2) = 
                                                        solucaoLocal.buscarJanelaViavel(sonda2, projeto2, modoRealoc);
            if (alocExiste2)
            {
                // inserir projeto2 na sonda2
                solucaoLocal.inserirProjeto(sonda2, projeto2, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                        currMinus2, currPlus2, nextPlus2, caso2);

                // inserir projeto3 na sonda1
                // faz busca
                bool alocExiste3 = false;
                int posicaoAloc3 = -1;
                Intervalo intervaloAloc3{};
                int prevMinus3 = 0;
                int currMinus3 = 0;
                int currPlus3 = 0;
                int nextPlus3 = 0;
                int caso3 = 0;
                std::tie(alocExiste3, posicaoAloc3, intervaloAloc3, prevMinus3, currMinus3, currPlus3, nextPlus3, caso3) = 
                                                            solucaoLocal.buscarJanelaViavel(sonda1, projeto3, modoRealoc);
                if (alocExiste3)
                {
                    // inserir projeto3 na sonda1
                    solucaoLocal.inserirProjeto(sonda1, projeto3, posicaoAloc3, intervaloAloc3, prevMinus3, 
                                        currMinus3, currPlus3, nextPlus3, caso3);
                    
                    // inserir projeto4 na sonda1
                    // faz busca
                    bool alocExiste4 = false;
                    int posicaoAloc4 = -1;
                    Intervalo intervaloAloc4{};
                    int prevMinus4 = 0;
                    int currMinus4 = 0;
                    int currPlus4 = 0;
                    int nextPlus4 = 0;
                    int caso4 = 0;
                    std::tie(alocExiste4, posicaoAloc4, intervaloAloc4, prevMinus4, currMinus4, currPlus4, nextPlus4, caso4) = 
                                                                solucaoLocal.buscarJanelaViavel(sonda1, projeto4, modoRealoc);
                    if (alocExiste4)
                    {
                        // inserir projeto4 na sonda1
                        solucaoLocal.inserirProjeto(sonda1, projeto4, posicaoAloc4, intervaloAloc4, prevMinus4, 
                                        currMinus4, currPlus4, nextPlus4, caso4);
                    }
                }
            }
        }
    }
    std::map<Sonda, std::vector<Alocacao>> alocsReturn = solucaoLocal.getAlocacoes();
    return alocsReturn;
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::reinsercao1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1)
{
    Sonda sonda1 = alocacao1.getSonda();
    Projeto projeto1 = alocacao1.getProjeto();
    Intervalo intervalo1 = alocacao1.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // remover projeto1 da sonda1
    bool removed1 = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1);

    if (removed1)
    {
        // inserir projeto1 na sonda1
        bool alocExiste1 = false;
        int posicaoAloc1 = -1;
        Intervalo intervaloAloc1{};
        int prevMinus1 = 0;
        int currMinus1 = 0;
        int currPlus1 = 0;
        int nextPlus1 = 0;
        int caso1 = 0;
        std::tie(alocExiste1, posicaoAloc1, intervaloAloc1, prevMinus1, currMinus1, currPlus1, nextPlus1, caso1) = 
                                                    solucaoLocal.buscarJanelaViavel(sonda1, projeto1, modoRealoc);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda1
            solucaoLocal.inserirProjeto(sonda1, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1);
        }
    }
    std::map<Sonda, std::vector<Alocacao>> alocsReturn = solucaoLocal.getAlocacoes();
    return alocsReturn;
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::reinsercao2InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                 DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2)
{
    Sonda sonda1 = alocacao1.getSonda();
    Projeto projeto1 = alocacao1.getProjeto();
    Projeto projeto2 = alocacao2.getProjeto();
    Intervalo intervalo1 = alocacao1.getIntervalo();
    Intervalo intervalo2 = alocacao2.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // remover projeto1 da sonda1
    bool removed1 = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1);

    // remover projeto2 da sonda1
    bool removed2 = solucaoLocal.removerProjeto(sonda1, projeto2, intervalo2);

    if (removed1 && removed2)
    {
        // inserir projeto2 na sonda1
        // fazer busca
        bool alocExiste1 = false;
        int posicaoAloc1 = -1;
        Intervalo intervaloAloc1{};
        int prevMinus1 = 0;
        int currMinus1 = 0;
        int currPlus1 = 0;
        int nextPlus1 = 0;
        int caso1 = 0;
        std::tie(alocExiste1, posicaoAloc1, intervaloAloc1, prevMinus1, currMinus1, currPlus1, nextPlus1, caso1) = 
                                                    solucaoLocal.buscarJanelaViavel(sonda1, projeto2, modoRealoc);
        if (alocExiste1)
        {
            solucaoLocal.inserirProjeto(sonda1, projeto2, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1);
            
            // inserir projeto1 na sonda1
            // fazer busca
            bool alocExiste2 = false;
            int posicaoAloc2 = -1;
            Intervalo intervaloAloc2{};
            int prevMinus2 = 0;
            int currMinus2 = 0;
            int currPlus2 = 0;
            int nextPlus2 = 0;
            int caso2 = 0;
            std::tie(alocExiste2, posicaoAloc2, intervaloAloc2, prevMinus2, currMinus2, currPlus2, nextPlus2, caso2) = 
                                                        solucaoLocal.buscarJanelaViavel(sonda1, projeto1, modoRealoc);
            if (alocExiste2)
            {
                // inserir projeto1 na sonda1
                solucaoLocal.inserirProjeto(sonda1, projeto1, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                        currMinus2, currPlus2, nextPlus2, caso2);
            }
        }
    }
    std::map<Sonda, std::vector<Alocacao>> alocsReturn = solucaoLocal.getAlocacoes();
    return alocsReturn;
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::inserirNovoFO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                             DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                             Sonda sonda1, Projeto projeto1)
{
    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // check de gastos
    double custoProjetado = solucaoLocal.getGastos() + projeto1.getCusto();
    if (custoProjetado > dataset.getCapitalTotal())
    {
        return alocsMap;
    }

    // inserir projeto1 na sonda1
    // fazer busca
    bool alocExiste1 = false;
    int posicaoAloc1 = -1;
    Intervalo intervaloAloc1{};
    int prevMinus1 = 0;
    int currMinus1 = 0;
    int currPlus1 = 0;
    int nextPlus1 = 0;
    int caso1 = 0;
    std::tie(alocExiste1, posicaoAloc1, intervaloAloc1, prevMinus1, currMinus1, currPlus1, nextPlus1, caso1) = 
                                                solucaoLocal.buscarJanelaViavel(sonda1, projeto1, modoRealoc);
    if (alocExiste1)
    {
        // inserir projeto1 na sonda1
        solucaoLocal.inserirProjeto(sonda1, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1);
    }
    std::map<Sonda, std::vector<Alocacao>> alocsReturn = solucaoLocal.getAlocacoes();
    return alocsReturn;
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::swap1x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                         DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                         Alocacao alocacao1, Projeto projeto1)
{
    Sonda sonda1 = alocacao1.getSonda();
    Projeto projeto2 = alocacao1.getProjeto();
    Intervalo intervalo2 = alocacao1.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // check de gastos
    double custoProjetado = solucaoLocal.getGastos() - alocacao1.getProjeto().getCusto() + projeto1.getCusto();
    if (custoProjetado > dataset.getCapitalTotal())
    {
        return alocsMap;
    }

    // remover projeto2 da sonda1
    bool removed2 = solucaoLocal.removerProjeto(sonda1, projeto2, intervalo2);

    if (removed2)
    {
        // inserir projeto1 na sonda1
        // fazer busca
        bool alocExiste1 = false;
        int posicaoAloc1 = -1;
        Intervalo intervaloAloc1{};
        int prevMinus1 = 0;
        int currMinus1 = 0;
        int currPlus1 = 0;
        int nextPlus1 = 0;
        int caso1 = 0;
        std::tie(alocExiste1, posicaoAloc1, intervaloAloc1, prevMinus1, currMinus1, currPlus1, nextPlus1, caso1) = 
                                                    solucaoLocal.buscarJanelaViavel(sonda1, projeto1, modoRealoc);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda1
            solucaoLocal.inserirProjeto(sonda1, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                            currMinus1, currPlus1, nextPlus1, caso1);
        }
    }
    std::map<Sonda, std::vector<Alocacao>> alocsReturn = solucaoLocal.getAlocacoes();
    return alocsReturn;
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::swap2x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                         DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                         Alocacao alocacao1, Alocacao alocacao2, Projeto projeto1)
{
    Sonda sonda1 = alocacao1.getSonda();
    Projeto projeto2 = alocacao1.getProjeto();
    Projeto projeto3 = alocacao2.getProjeto();
    Intervalo intervalo2 = alocacao1.getIntervalo();
    Intervalo intervalo3 = alocacao2.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // check de gastos
    double custoProjetado = solucaoLocal.getGastos() 
                            - alocacao1.getProjeto().getCusto() - alocacao2.getProjeto().getCusto() 
                            + projeto1.getCusto();
    if (custoProjetado > dataset.getCapitalTotal())
    {
        return alocsMap;
    }

    // remover projeto2 da sonda1
    bool removed2 = solucaoLocal.removerProjeto(sonda1, projeto2, intervalo2);

    // remover projeto3 da sonda1
    bool removed3 = solucaoLocal.removerProjeto(sonda1, projeto3, intervalo3);

    if (removed2 && removed3)
    {
        // inserir projeto1 na sonda1
        // fazer busca
        bool alocExiste1 = false;
        int posicaoAloc1 = -1;
        Intervalo intervaloAloc1{};
        int prevMinus1 = 0;
        int currMinus1 = 0;
        int currPlus1 = 0;
        int nextPlus1 = 0;
        int caso1 = 0;
        std::tie(alocExiste1, posicaoAloc1, intervaloAloc1, prevMinus1, currMinus1, currPlus1, nextPlus1, caso1) = 
                                                    solucaoLocal.buscarJanelaViavel(sonda1, projeto1, modoRealoc);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda1
            solucaoLocal.inserirProjeto(sonda1, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                            currMinus1, currPlus1, nextPlus1, caso1);
        }
    }
    std::map<Sonda, std::vector<Alocacao>> alocsReturn = solucaoLocal.getAlocacoes();
    return alocsReturn;
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::swap1x2FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                         DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                         Alocacao alocacao1, Projeto projeto1, Projeto projeto2)
{
    Sonda sonda1 = alocacao1.getSonda();
    Projeto projeto3 = alocacao1.getProjeto();
    Intervalo intervalo3 = alocacao1.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // check de gastos
    double custoProjetado = solucaoLocal.getGastos() 
                            - alocacao1.getProjeto().getCusto() 
                            + projeto1.getCusto() + projeto2.getCusto();
    if (custoProjetado > dataset.getCapitalTotal())
    {
        return alocsMap;
    }

    // remover projeto3 da sonda1
    bool removed3 = solucaoLocal.removerProjeto(sonda1, projeto3, intervalo3);

    if (removed3)
    {
        // inserir projeto1 na sonda1
        // fazer busca
        bool alocExiste1 = false;
        int posicaoAloc1 = -1;
        Intervalo intervaloAloc1{};
        int prevMinus1 = 0;
        int currMinus1 = 0;
        int currPlus1 = 0;
        int nextPlus1 = 0;
        int caso1 = 0;
        std::tie(alocExiste1, posicaoAloc1, intervaloAloc1, prevMinus1, currMinus1, currPlus1, nextPlus1, caso1) = 
                                                    solucaoLocal.buscarJanelaViavel(sonda1, projeto1, modoRealoc);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda1
            solucaoLocal.inserirProjeto(sonda1, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                            currMinus1, currPlus1, nextPlus1, caso1);
            
            // inserir projeto2 na sonda1
            // fazer busca
            bool alocExiste2 = false;
            int posicaoAloc2 = -1;
            Intervalo intervaloAloc2{};
            int prevMinus2 = 0;
            int currMinus2 = 0;
            int currPlus2 = 0;
            int nextPlus2 = 0;
            int caso2 = 0;
            std::tie(alocExiste2, posicaoAloc2, intervaloAloc2, prevMinus2, currMinus2, currPlus2, nextPlus2, caso2) = 
                                                        solucaoLocal.buscarJanelaViavel(sonda1, projeto2, modoRealoc);
            if (alocExiste2)
            {
                // inserir projeto1 na sonda1
                solucaoLocal.inserirProjeto(sonda1, projeto2, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                                currMinus2, currPlus2, nextPlus2, caso2);
            }
        }
    }
    std::map<Sonda, std::vector<Alocacao>> alocsReturn = solucaoLocal.getAlocacoes();
    return alocsReturn;
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::swap2x2FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                         DadosDeEntrada dataset, int estrutura, int modoRealoc,
                                                         Alocacao alocacao1, Alocacao alocacao2, 
                                                         Projeto projeto1, Projeto projeto2)
{
    Sonda sonda1 = alocacao1.getSonda();
    Projeto projeto3 = alocacao1.getProjeto();
    Projeto projeto4 = alocacao2.getProjeto();
    Intervalo intervalo3 = alocacao1.getIntervalo();
    Intervalo intervalo4 = alocacao2.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // check de gastos
    double custoProjetado = solucaoLocal.getGastos() 
                            - alocacao1.getProjeto().getCusto() - alocacao2.getProjeto().getCusto() 
                            + projeto1.getCusto() + projeto2.getCusto();
    if (custoProjetado > dataset.getCapitalTotal())
    {
        return alocsMap;
    }

    // remover projeto3 da sonda1
    bool removed3 = solucaoLocal.removerProjeto(sonda1, projeto3, intervalo3);

    // remover projeto4 da sonda1
    bool removed4 = solucaoLocal.removerProjeto(sonda1, projeto4, intervalo4);

    if (removed3 && removed4)
    {
        // inserir projeto1 na sonda1
        // fazer busca
        bool alocExiste1 = false;
        int posicaoAloc1 = -1;
        Intervalo intervaloAloc1{};
        int prevMinus1 = 0;
        int currMinus1 = 0;
        int currPlus1 = 0;
        int nextPlus1 = 0;
        int caso1 = 0;
        std::tie(alocExiste1, posicaoAloc1, intervaloAloc1, prevMinus1, currMinus1, currPlus1, nextPlus1, caso1) = 
                                                    solucaoLocal.buscarJanelaViavel(sonda1, projeto1, modoRealoc);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda1
            solucaoLocal.inserirProjeto(sonda1, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                            currMinus1, currPlus1, nextPlus1, caso1);
            
            // inserir projeto2 na sonda1
            // fazer busca
            bool alocExiste2 = false;
            int posicaoAloc2 = -1;
            Intervalo intervaloAloc2{};
            int prevMinus2 = 0;
            int currMinus2 = 0;
            int currPlus2 = 0;
            int nextPlus2 = 0;
            int caso2 = 0;
            std::tie(alocExiste2, posicaoAloc2, intervaloAloc2, prevMinus2, currMinus2, currPlus2, nextPlus2, caso2) = 
                                                        solucaoLocal.buscarJanelaViavel(sonda1, projeto2, modoRealoc);
            if (alocExiste2)
            {
                // inserir projeto1 na sonda1
                solucaoLocal.inserirProjeto(sonda1, projeto2, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                                currMinus2, currPlus2, nextPlus2, caso2);
            }
        }
    }
    std::map<Sonda, std::vector<Alocacao>> alocsReturn = solucaoLocal.getAlocacoes();
    return alocsReturn;
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaShift1x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, DadosDeEntrada dataset, 
                                                  int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações    
    for (std::set<Sonda>::iterator itS1 = sondas.begin(); itS1 != sondas.end(); ++itS1)
    {
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1 = alocsMap[sonda1].begin(); itA1 != alocsMap[sonda1].end(); ++itA1)
        {
            Alocacao alocacao1 = *itA1;
            Projeto projeto1 = (*itA1).getProjeto();
            Intervalo intervalo1 = (*itA1).getIntervalo();
            for (std::set<Sonda>::iterator itS2 = sondas.begin(); itS2 != sondas.end(); ++itS2)
            {
                Sonda sonda2 = *itS2;
                if (sonda1 == sonda2)
                {
                    continue;
                }

                // realiza movimento
                std::map<Sonda, std::vector<Alocacao>> alocsMapAlt = shift1x0InterRota(alocsMap, dataset, estrutura, 
                                                                                       modoRealoc, alocacao1, sonda2);

                // instancia solução local
                Solucao solucaoLocal{alocsMapAlt, estrutura, dataset};

                // se for melhor que best
                if (solucaoLocal.getFitness() >= bestFitness)
                {
                    if (solucaoLocal.getTotalFree() > bestTotalFree)
                    {
                        bestAlocsMap = solucaoLocal.getAlocacoes();
                        bestFitness = solucaoLocal.getFitness();
                        bestGastos = solucaoLocal.getGastos();
                        bestTotalFree = solucaoLocal.getTotalFree();
                    }
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaShift2x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            Alocacao alocacao1 = *itA1;
            Projeto projeto1 = (*itA1).getProjeto();
            Intervalo intervalo1 = (*itA1).getIntervalo();
            for (std::vector<Alocacao>::iterator itA2=alocsMap[sonda1].begin(); itA2!=alocsMap[sonda1].end(); ++itA2)
            {
                Alocacao alocacao2 = *itA2;
                Projeto projeto2 = (*itA2).getProjeto();
                Intervalo intervalo2 = (*itA2).getIntervalo();
                if (projeto1 == projeto2)
                {
                    continue;
                }
                for (std::set<Sonda>::iterator itS2=sondas.begin(); itS2!=sondas.end(); ++itS2)
                {
                    Sonda sonda2 = *itS2;
                    if (sonda1 == sonda2)
                    {
                        continue;
                    }
                    // realiza movimento
                    std::map<Sonda, std::vector<Alocacao>> alocsMapAlt = shift2x0InterRota(alocsMap, dataset, estrutura, 
                                                                                    modoRealoc, alocacao1, alocacao2, sonda2);

                    // instancia solução local
                    Solucao solucaoLocal{alocsMapAlt, estrutura, dataset};

                    // se for melhor que best
                    if (solucaoLocal.getFitness() >= bestFitness)
                    {
                        if (solucaoLocal.getTotalFree() > bestTotalFree)
                        {
                            bestAlocsMap = solucaoLocal.getAlocacoes();
                            bestFitness = solucaoLocal.getFitness();
                            bestGastos = solucaoLocal.getGastos();
                            bestTotalFree = solucaoLocal.getTotalFree();
                        }
                    }
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaSwap1x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            Alocacao alocacao1 = *itA1;
            for (std::set<Sonda>::iterator itS2=sondas.begin(); itS2!=sondas.end(); ++itS2)
            {
                Sonda sonda2 = *itS2;
                if (alocsMap[sonda2].empty())
                {
                    continue;
                }
                if (sonda1 == sonda2)
                {
                    continue;
                }
                for (std::vector<Alocacao>::iterator itA2=alocsMap[sonda2].begin(); itA2!=alocsMap[sonda2].end(); ++itA2)
                {
                    Alocacao alocacao2 = *itA2;

                    // realiza movimento
                    std::map<Sonda, std::vector<Alocacao>> alocsMapAlt = swap1x1InterRota(alocsMap, dataset, estrutura, 
                                                                                        modoRealoc, alocacao1, alocacao2);

                    // instancia solução local
                    Solucao solucaoLocal{alocsMapAlt, estrutura, dataset};

                    // se for melhor que best
                    if (solucaoLocal.getFitness() >= bestFitness)
                    {
                        if (solucaoLocal.getTotalFree() > bestTotalFree)
                        {
                            bestAlocsMap = solucaoLocal.getAlocacoes();
                            bestFitness = solucaoLocal.getFitness();
                            bestGastos = solucaoLocal.getGastos();
                            bestTotalFree = solucaoLocal.getTotalFree();
                        }
                    }
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaSwap2x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            Alocacao alocacao1 = *itA1;
            for (std::vector<Alocacao>::iterator itA2=alocsMap[sonda1].begin(); itA2!=alocsMap[sonda1].end(); ++itA2)
            {
                Alocacao alocacao2 = *itA2;
                if (alocacao1 == alocacao2)
                {
                    continue;
                }
                for (std::set<Sonda>::iterator itS2=sondas.begin(); itS2!=sondas.end(); ++itS2)
                {
                    Sonda sonda2 = *itS2;
                    if (alocsMap[sonda2].empty())
                    {
                        continue;
                    }
                    if (sonda1 == sonda2)
                    {
                        continue;
                    }
                    for (std::vector<Alocacao>::iterator itA3=alocsMap[sonda2].begin(); itA3!=alocsMap[sonda2].end(); ++itA3)
                    {
                        Alocacao alocacao3 = *itA3;

                        // realiza movimento
                        std::map<Sonda, std::vector<Alocacao>> alocsMapAlt = swap2x1InterRota(alocsMap, dataset, estrutura, 
                                                                                            modoRealoc, 
                                                                                            alocacao1, alocacao2, alocacao3);

                        // instancia solução local
                        Solucao solucaoLocal{alocsMapAlt, estrutura, dataset};

                        // se for melhor que best
                        if (solucaoLocal.getFitness() >= bestFitness)
                        {
                            if (solucaoLocal.getTotalFree() > bestTotalFree)
                            {
                                bestAlocsMap = solucaoLocal.getAlocacoes();
                                bestFitness = solucaoLocal.getFitness();
                                bestGastos = solucaoLocal.getGastos();
                                bestTotalFree = solucaoLocal.getTotalFree();
                            }
                        }
                    }
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaSwap2x2InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            Alocacao alocacao1 = *itA1;
            for (std::vector<Alocacao>::iterator itA2=alocsMap[sonda1].begin(); itA2!=alocsMap[sonda1].end(); ++itA2)
            {
                Alocacao alocacao2 = *itA2;
                if (alocacao1 == alocacao2)
                {
                    continue;
                }
                for (std::set<Sonda>::iterator itS2=sondas.begin(); itS2!=sondas.end(); ++itS2)
                {
                    Sonda sonda2 = *itS2;
                    if (alocsMap[sonda2].empty())
                    {
                        continue;
                    }
                    if (sonda1 == sonda2)
                    {
                        continue;
                    }
                    for (std::vector<Alocacao>::iterator itA3=alocsMap[sonda2].begin(); itA3!=alocsMap[sonda2].end(); ++itA3)
                    {
                        Alocacao alocacao3 = *itA3;
                        for (std::vector<Alocacao>::iterator itA4=alocsMap[sonda2].begin(); itA4!=alocsMap[sonda2].end(); ++itA4)
                        {
                            Alocacao alocacao4 = *itA4;
                            if (alocacao3 == alocacao4)
                            {
                                continue;
                            }

                            // realiza movimento
                            std::map<Sonda, std::vector<Alocacao>> alocsMapAlt = swap2x2InterRota(alocsMap, dataset, estrutura, 
                                                                                                modoRealoc, 
                                                                                                alocacao1, alocacao2, 
                                                                                                alocacao3, alocacao4);

                            // instancia solução local
                            Solucao solucaoLocal{alocsMapAlt, estrutura, dataset};

                            // se for melhor que best
                            if (solucaoLocal.getFitness() >= bestFitness)
                            {
                                if (solucaoLocal.getTotalFree() > bestTotalFree)
                                {
                                    bestAlocsMap = solucaoLocal.getAlocacoes();
                                    bestFitness = solucaoLocal.getFitness();
                                    bestGastos = solucaoLocal.getGastos();
                                    bestTotalFree = solucaoLocal.getTotalFree();
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaReinsercao1IntraRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            Alocacao alocacao1 = *itA1;

            // realiza movimento
            std::map<Sonda, std::vector<Alocacao>> alocsMapAlt = reinsercao1InterRota(alocsMap, dataset, estrutura, 
                                                                                      modoRealoc, alocacao1);

            // instancia solução local
            Solucao solucaoLocal{alocsMapAlt, estrutura, dataset};

            // se for melhor que best
            if (solucaoLocal.getFitness() >= bestFitness)
            {
                if (solucaoLocal.getTotalFree() > bestTotalFree)
                {
                    bestAlocsMap = solucaoLocal.getAlocacoes();
                    bestFitness = solucaoLocal.getFitness();
                    bestGastos = solucaoLocal.getGastos();
                    bestTotalFree = solucaoLocal.getTotalFree();
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaReinsercao2IntraRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            Alocacao alocacao1 = *itA1;
            for (std::vector<Alocacao>::iterator itA2=alocsMap[sonda1].begin(); itA2!=alocsMap[sonda1].end(); ++itA2)
            {
                Alocacao alocacao2 = *itA2;
                if (alocacao1 == alocacao2)
                {
                    continue;
                }
                // realiza movimento
                std::map<Sonda, std::vector<Alocacao>> alocsMapAlt = reinsercao2InterRota(alocsMap, dataset, estrutura, 
                                                                                        modoRealoc, alocacao1, alocacao2);

                // instancia solução local
                Solucao solucaoLocal{alocsMapAlt, estrutura, dataset};

                // se for melhor que best
                if (solucaoLocal.getFitness() >= bestFitness)
                {
                    if (solucaoLocal.getTotalFree() > bestTotalFree)
                    {
                        bestAlocsMap = solucaoLocal.getAlocacoes();
                        bestFitness = solucaoLocal.getFitness();
                        bestGastos = solucaoLocal.getGastos();
                        bestTotalFree = solucaoLocal.getTotalFree();
                    }
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaInserirNovoFO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // inicializa conjunto de projetos não alocados
    std::set<Projeto> projetosNaoAloc = bestSolucao.getProjetosNaoAlocados();

    // percorre combinações    
    for (std::set<Projeto>::iterator itP1=projetosNaoAloc.begin(); itP1!=projetosNaoAloc.end(); ++itP1)
    {
        Projeto projeto1 = *itP1;
        for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
        {
            Sonda sonda1 = *itS1;

            // realiza movimento
            std::map<Sonda, std::vector<Alocacao>> alocsMapAlt = inserirNovoFO(alocsMap, dataset, estrutura, 
                                                                                    modoRealoc, sonda1, projeto1);

            // instancia solução local
            Solucao solucaoLocal{alocsMapAlt, estrutura, dataset};

            // se for melhor que best
            if (solucaoLocal.getFitness() >= bestFitness)
            {
                if (solucaoLocal.getTotalFree() > bestTotalFree)
                {
                    bestAlocsMap = solucaoLocal.getAlocacoes();
                    bestFitness = solucaoLocal.getFitness();
                    bestGastos = solucaoLocal.getGastos();
                    bestTotalFree = solucaoLocal.getTotalFree();
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaSwap1x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // inicializa conjunto de projetos não alocados
    std::set<Projeto> projetosNaoAloc = bestSolucao.getProjetosNaoAlocados();

    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            Alocacao alocacao1 = *itA1;
            for (std::set<Projeto>::iterator itP1=projetosNaoAloc.begin(); itP1!=projetosNaoAloc.end(); ++itP1)
            {
                Projeto projeto1 = *itP1;

                // realiza movimento
                std::map<Sonda, std::vector<Alocacao>> alocsMapAlt = swap1x1FO(alocsMap, dataset, estrutura, 
                                                                                        modoRealoc, alocacao1, projeto1);

                // instancia solução local
                Solucao solucaoLocal{alocsMapAlt, estrutura, dataset};

                // se for melhor que best
                if (solucaoLocal.getFitness() >= bestFitness)
                {
                    if (solucaoLocal.getTotalFree() > bestTotalFree)
                    {
                        bestAlocsMap = solucaoLocal.getAlocacoes();
                        bestFitness = solucaoLocal.getFitness();
                        bestGastos = solucaoLocal.getGastos();
                        bestTotalFree = solucaoLocal.getTotalFree();
                    }
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaSwap2x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // inicializa conjunto de projetos não alocados
    std::set<Projeto> projetosNaoAloc = bestSolucao.getProjetosNaoAlocados();

    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            Alocacao alocacao1 = *itA1;
            for (std::vector<Alocacao>::iterator itA2=alocsMap[sonda1].begin(); itA2!=alocsMap[sonda1].end(); ++itA2)
            {
                Alocacao alocacao2 = *itA2;
                if (alocacao1 == alocacao2)
                {
                    continue;
                }
                for (std::set<Projeto>::iterator itP1=projetosNaoAloc.begin(); itP1!=projetosNaoAloc.end(); ++itP1)
                {
                    Projeto projeto1 = *itP1;

                    // realiza movimento
                    std::map<Sonda, std::vector<Alocacao>> alocsMapAlt = swap2x1FO(alocsMap, dataset, estrutura, 
                                                                                   modoRealoc, alocacao1, alocacao2, projeto1);

                    // instancia solução local
                    Solucao solucaoLocal{alocsMapAlt, estrutura, dataset};

                    // se for melhor que best
                    if (solucaoLocal.getFitness() >= bestFitness)
                    {
                        if (solucaoLocal.getTotalFree() > bestTotalFree)
                        {
                            bestAlocsMap = solucaoLocal.getAlocacoes();
                            bestFitness = solucaoLocal.getFitness();
                            bestGastos = solucaoLocal.getGastos();
                            bestTotalFree = solucaoLocal.getTotalFree();
                        }
                    }
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaSwap1x2FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // inicializa conjunto de projetos não alocados
    std::set<Projeto> projetosNaoAloc = bestSolucao.getProjetosNaoAlocados();

    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            Alocacao alocacao1 = *itA1;
            for (std::set<Projeto>::iterator itP1=projetosNaoAloc.begin(); itP1!=projetosNaoAloc.end(); ++itP1)
            {
                Projeto projeto1 = *itP1;
                for (std::set<Projeto>::iterator itP2=projetosNaoAloc.begin(); itP2!=projetosNaoAloc.end(); ++itP2)
                {
                    Projeto projeto2 = *itP2;
                    if (projeto1 == projeto2)
                    {
                        continue;
                    }
                    // realiza movimento
                    std::map<Sonda, std::vector<Alocacao>> alocsMapAlt = swap1x2FO(alocsMap, dataset, estrutura, 
                                                                                   modoRealoc, alocacao1, projeto1, projeto2);

                    // instancia solução local
                    Solucao solucaoLocal{alocsMapAlt, estrutura, dataset};

                    // se for melhor que best
                    if (solucaoLocal.getFitness() >= bestFitness)
                    {
                        if (solucaoLocal.getTotalFree() > bestTotalFree)
                        {
                            bestAlocsMap = solucaoLocal.getAlocacoes();
                            bestFitness = solucaoLocal.getFitness();
                            bestGastos = solucaoLocal.getGastos();
                            bestTotalFree = solucaoLocal.getTotalFree();
                        }
                    }
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaSwap2x2FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    auto start = std::chrono::high_resolution_clock::now();

    // inicializa bests
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();

    // inicializa conjunto de sondas
    std::set<Sonda> sondas = bestSolucao.getSondas();

    // inicializa conjunto de projetos não alocados
    std::set<Projeto> projetosNaoAloc = bestSolucao.getProjetosNaoAlocados();
   
    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            Alocacao alocacao1 = *itA1;
            for (std::vector<Alocacao>::iterator itA2=alocsMap[sonda1].begin(); itA2!=alocsMap[sonda1].end(); ++itA2)
            {
                Alocacao alocacao2 = *itA2;
                if (alocacao1 == alocacao2)
                {
                    continue;
                }
                for (std::set<Projeto>::iterator itP1=projetosNaoAloc.begin(); itP1!=projetosNaoAloc.end(); ++itP1)
                {
                    Projeto projeto1 = *itP1;
                    for (std::set<Projeto>::iterator itP2=projetosNaoAloc.begin(); itP2!=projetosNaoAloc.end(); ++itP2)
                    {
                        Projeto projeto2 = *itP2;
                        if (projeto1 == projeto2)
                        {
                            continue;
                        }

                        // realiza movimento
                        std::map<Sonda, std::vector<Alocacao>> alocsMapAlt = swap2x2FO(alocsMap, dataset, estrutura, 
                                                                                    modoRealoc, alocacao1, alocacao2, 
                                                                                    projeto1, projeto2);

                        // instancia solução local
                        Solucao solucaoLocal{alocsMapAlt, estrutura, dataset};

                        // se for melhor que best
                        if (solucaoLocal.getFitness() >= bestFitness)
                        {
                            if (solucaoLocal.getTotalFree() > bestTotalFree)
                            {
                                bestAlocsMap = solucaoLocal.getAlocacoes();
                                bestFitness = solucaoLocal.getFitness();
                                bestGastos = solucaoLocal.getGastos();
                                bestTotalFree = solucaoLocal.getTotalFree();
                            }
                        }
                    }
                }
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaVND(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    // inicializa conjunto de vizinhanças
    std::set<int> vizinhancas;
    vizinhancas.insert(1);
    vizinhancas.insert(2);
    vizinhancas.insert(3);
    vizinhancas.insert(4);
    vizinhancas.insert(5);
    vizinhancas.insert(6);
    vizinhancas.insert(7);
    vizinhancas.insert(8);
    vizinhancas.insert(9);
    vizinhancas.insert(10);
    vizinhancas.insert(11);
    vizinhancas.insert(12);

    // inicializa valores a serem retornados
    double newFitness = 0;
    double newGastos = 0;
    int newTotalFree = 0;
    long long newTempo = 0;

    // inicializa bests
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();
    long long bestTempo = 0;
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;

    // enquanto ainda tem vizinhaças
    while (vizinhancas.empty() == false)
    {
        // seleciona vizinhança
        int vizinhanca = *(vizinhancas.begin());

        // remove vizinhança do conjunto
        vizinhancas.erase(vizinhancas.begin());

        // faz busca pela vizinhança
        if (vizinhanca == 1)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaShift1x0InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 2)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaShift2x0InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 3)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x1InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 4)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x1InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 5)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x2InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 6)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaReinsercao1IntraRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 7)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaReinsercao2IntraRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 8)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaInserirNovoFO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 9)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x1FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 10)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x1FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 11)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x2FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 12)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x2FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }

        // se melhora FO
        if (newFitness > bestFitness)
        {
            // reinsere vizinhança
            vizinhancas.insert(vizinhanca);

            // substitui bests
            bestAlocsMap = alocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;
        }
    }
    return std::make_tuple(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaRVND(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT)
{
    // inicializa conjunto de vizinhanças
    std::set<int> vizinhancas;
    vizinhancas.insert(1);
    vizinhancas.insert(2);
    vizinhancas.insert(3);
    vizinhancas.insert(4);
    vizinhancas.insert(5);
    vizinhancas.insert(6);
    vizinhancas.insert(7);
    vizinhancas.insert(8);
    vizinhancas.insert(9);
    vizinhancas.insert(10);
    vizinhancas.insert(11);
    vizinhancas.insert(12);

    // inicializa valores a serem retornados
    double newFitness = 0;
    double newGastos = 0;
    int newTotalFree = 0;
    long long newTempo = 0;

    // inicializa bests
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();
    long long bestTempo = 0;
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;

    // enquanto ainda tem vizinhaças
    while (vizinhancas.empty() == false)
    {
        // seleciona vizinhança
        int idx = rand() % vizinhancas.size();
        std::set<int>::iterator itr = std::next(vizinhancas.begin(), idx);
        int vizinhanca = *(itr);

        // remove vizinhança do conjunto
        vizinhancas.erase(*itr);

        // faz busca pela vizinhança
        if (vizinhanca == 1)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaShift1x0InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 2)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaShift2x0InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 3)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x1InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 4)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x1InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 5)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x2InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 6)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaReinsercao1IntraRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 7)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaReinsercao2IntraRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 8)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaInserirNovoFO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 9)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x1FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 10)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x1FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 11)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x2FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }
        else if (vizinhanca == 12)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x2FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
        }

        // se melhora FO
        if (newFitness > bestFitness)
        {
            // reinsere vizinhança
            vizinhancas.insert(vizinhanca);

            // substitui bests
            bestAlocsMap = alocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;
        }
    }
    return std::make_tuple(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaLocal(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                          DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int vizinhanca)
{
    // inicializa valores a serem retornados
    double newFitness = 0;
    double newGastos = 0;
    int newTotalFree = 0;
    long long newTempo = 0;

    // faz busca pela vizinhança
    if (vizinhanca == 1)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaShift1x0InterRota(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
    }
    else if (vizinhanca == 2)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaShift2x0InterRota(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
    }
    else if (vizinhanca == 3)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x1InterRota(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
    }
    else if (vizinhanca == 4)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x1InterRota(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
    }
    else if (vizinhanca == 5)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x2InterRota(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
    }
    else if (vizinhanca == 6)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaReinsercao1IntraRota(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
    }
    else if (vizinhanca == 7)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaReinsercao2IntraRota(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
    }
    else if (vizinhanca == 8)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaInserirNovoFO(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
    }
    else if (vizinhanca == 9)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x1FO(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
    }
    else if (vizinhanca == 10)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x1FO(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
    }
    else if (vizinhanca == 11)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x2FO(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
    }
    else if (vizinhanca == 12)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x2FO(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
    }
    else if (vizinhanca == 13)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaVND(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
    }
    else if (vizinhanca == 14)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaRVND(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta());
    }
    return std::make_tuple(newTempo, alocsMap, newFitness, newGastos, newTotalFree);
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaShift1x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();
    
    // check se todas sondas estão vazias
    bool solucaoVazia = true;
    for (std::set<Sonda>::iterator itS=sondas.begin(); itS!=sondas.end(); ++itS)
    {
        Sonda sondaX = *itS;
        if (alocsMap[sondaX].empty() == false)
        {
            solucaoVazia = false;
            break;
        }
    }

    if (sondas.size() < 2)
    {
        return alocsMap;
    }
    else if (solucaoVazia)
    {
        return alocsMap;
    }
    else
    {
        int count = 0;
        while (count < k)
        {
            // escolhe sonda1 para remover uma alocação
            int sonda1idx = rand() % (sondas.size());
            Sonda sonda1 = *(std::next(sondas.begin(), sonda1idx));

            // escolhe alocacao1 para remover da sonda1
            if (alocsMap[sonda1].empty())
            {
                continue;
            }
            int aloc1idx = rand() % (alocsMap[sonda1].size());
            Alocacao alocacao1 = *(std::next(alocsMap[sonda1].begin(), aloc1idx));

            // escolhe sonda2 para colocar alocacao1
            int sonda2idx = rand() % (sondas.size());
            Sonda sonda2 = *(std::next(sondas.begin(), sonda2idx));
            if (sonda1 == sonda2)
            {
                continue;
            }

            // realiza movimento
            alocsMap = shift1x0InterRota(alocsMap, dataset, estrutura, modoRealoc, alocacao1, sonda2);

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaShift2x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();
    
    // check
    bool solucaoVazia = true;
    for (std::set<Sonda>::iterator itS=sondas.begin(); itS!=sondas.end(); ++itS)
    {
        Sonda sondaX = *itS;
        if (alocsMap[sondaX].empty() == false)
        {
            if (alocsMap[sondaX].size() >= 2)
            {
                solucaoVazia = false;
                break;
            }
        }
    }

    if (sondas.size() < 2)
    {
        return alocsMap;
    }
    else if (solucaoVazia)
    {
        return alocsMap;
    }
    else
    {
        int count = 0;
        while (count < k)
        {
            // escolhe sonda1 para remover duas alocação
            int sonda1idx = rand() % (sondas.size());
            Sonda sonda1 = *(std::next(sondas.begin(), sonda1idx));

            // escolhe alocacao1 para remover da sonda1
            if (alocsMap[sonda1].size() < 2)
            {
                continue;
            }
            int aloc1idx = rand() % (alocsMap[sonda1].size());
            Alocacao alocacao1 = *(std::next(alocsMap[sonda1].begin(), aloc1idx));

            // escolhe alocacao2 para remover da sonda1
            int aloc2idx = rand() % (alocsMap[sonda1].size());
            Alocacao alocacao2 = *(std::next(alocsMap[sonda1].begin(), aloc2idx));
            if (alocacao1 == alocacao2)
            {
                continue;
            }

            // escolhe sonda2 para colocar alocacao1
            int sonda2idx = rand() % (sondas.size());
            Sonda sonda2 = *(std::next(sondas.begin(), sonda2idx));
            if (sonda1 == sonda2)
            {
                continue;
            }

            // realiza movimento
            alocsMap = shift2x0InterRota(alocsMap, dataset, estrutura, modoRealoc, alocacao1, alocacao2, sonda2);

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaSwap1x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();
    
    // check
    int countSondas = 0;
    for (std::set<Sonda>::iterator itS=sondas.begin(); itS!=sondas.end(); ++itS)
    {
        Sonda sondaX = *itS;
        if (alocsMap[sondaX].empty() == false)
        {
            countSondas++;
        }
    }

    if (sondas.size() < 2)
    {
        return alocsMap;
    }
    else if (countSondas < 2)
    {
        return alocsMap;
    }
    else
    {
        int count = 0;
        while (count < k)
        {
            // escolhe sonda1
            int sonda1idx = rand() % (sondas.size());
            Sonda sonda1 = *(std::next(sondas.begin(), sonda1idx));

            // escolhe alocacao1
            if (alocsMap[sonda1].empty())
            {
                continue;
            }
            int aloc1idx = rand() % (alocsMap[sonda1].size());
            Alocacao alocacao1 = *(std::next(alocsMap[sonda1].begin(), aloc1idx));

            // escolhe sonda2
            int sonda2idx = rand() % (sondas.size());
            Sonda sonda2 = *(std::next(sondas.begin(), sonda2idx));
            if (alocsMap[sonda2].empty())
            {
                continue;
            }
            if (sonda1 == sonda2)
            {
                continue;
            }

            // escolhe alocacao2
            int aloc2idx = rand() % (alocsMap[sonda2].size());
            Alocacao alocacao2 = *(std::next(alocsMap[sonda2].begin(), aloc2idx));

            // realiza movimento
            alocsMap = swap1x1InterRota(alocsMap, dataset, estrutura, modoRealoc, alocacao1, alocacao2);

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaSwap2x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();
    
    // check
    int countSondas = 0;
    int countAlocs = 0;
    for (std::set<Sonda>::iterator itS=sondas.begin(); itS!=sondas.end(); ++itS)
    {
        Sonda sondaX = *itS;
        if (alocsMap[sondaX].empty() == false)
        {
            countSondas++;
            if (alocsMap[sondaX].size() >= 2)
            {
                countAlocs++;
            }
        }
    }

    if (sondas.size() < 2)
    {
        return alocsMap;
    }
    else if ((countSondas < 2) || (countAlocs == 0))
    {
        return alocsMap;
    }
    else
    {
        int count = 0;
        while (count < k)
        {
            // escolhe sonda1
            int sonda1idx = rand() % (sondas.size());
            Sonda sonda1 = *(std::next(sondas.begin(), sonda1idx));

            // escolhe alocacao1
            if (alocsMap[sonda1].size() < 2)
            {
                continue;
            }
            int aloc1idx = rand() % (alocsMap[sonda1].size());
            Alocacao alocacao1 = *(std::next(alocsMap[sonda1].begin(), aloc1idx));

            // escolhe alocacao2
            int aloc2idx = rand() % (alocsMap[sonda1].size());
            Alocacao alocacao2 = *(std::next(alocsMap[sonda1].begin(), aloc2idx));
            if (alocacao1 == alocacao2)
            {
                continue;
            }

            // escolhe sonda2
            int sonda2idx = rand() % (sondas.size());
            Sonda sonda2 = *(std::next(sondas.begin(), sonda2idx));
            if (alocsMap[sonda2].empty())
            {
                continue;
            }
            if (sonda1 == sonda2)
            {
                continue;
            }

            // escolhe alocacao3
            int aloc3idx = rand() % (alocsMap[sonda2].size());
            Alocacao alocacao3 = *(std::next(alocsMap[sonda2].begin(), aloc3idx));

            // realiza movimento
            alocsMap = swap2x1InterRota(alocsMap, dataset, estrutura, modoRealoc, alocacao1, alocacao2, alocacao3);

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaSwap2x2InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();
    
    // check
    int countSondas = 0;
    int countAlocs = 0;
    for (std::set<Sonda>::iterator itS=sondas.begin(); itS!=sondas.end(); ++itS)
    {
        Sonda sondaX = *itS;
        if (alocsMap[sondaX].empty() == false)
        {
            countSondas++;
            if (alocsMap[sondaX].size() >= 2)
            {
                countAlocs++;
            }
        }
    }

    if (sondas.size() < 2)
    {
        return alocsMap;
    }
    else if ((countSondas < 2) || (countAlocs < 2))
    {
        return alocsMap;
    }
    else
    {
        int count = 0;
        while (count < k)
        {
            // escolhe sonda1
            int sonda1idx = rand() % (sondas.size());
            Sonda sonda1 = *(std::next(sondas.begin(), sonda1idx));

            // escolhe alocacao1
            if (alocsMap[sonda1].size() < 2)
            {
                continue;
            }
            int aloc1idx = rand() % (alocsMap[sonda1].size());
            Alocacao alocacao1 = *(std::next(alocsMap[sonda1].begin(), aloc1idx));

            // escolhe alocacao2
            int aloc2idx = rand() % (alocsMap[sonda1].size());
            Alocacao alocacao2 = *(std::next(alocsMap[sonda1].begin(), aloc2idx));
            if (alocacao1 == alocacao2)
            {
                continue;
            }

            // escolhe sonda2
            int sonda2idx = rand() % (sondas.size());
            Sonda sonda2 = *(std::next(sondas.begin(), sonda2idx));
            if (alocsMap[sonda2].size() < 2)
            {
                continue;
            }
            if (sonda1 == sonda2)
            {
                continue;
            }

            // escolhe alocacao3
            int aloc3idx = rand() % (alocsMap[sonda2].size());
            Alocacao alocacao3 = *(std::next(alocsMap[sonda2].begin(), aloc3idx));

            // escolhe alocacao4
            int aloc4idx = rand() % (alocsMap[sonda2].size());
            Alocacao alocacao4 = *(std::next(alocsMap[sonda2].begin(), aloc4idx));
            if (alocacao3 == alocacao4)
            {
                continue;
            }

            // realiza movimento
            alocsMap = swap2x1InterRota(alocsMap, dataset, estrutura, modoRealoc, alocacao1, alocacao2, alocacao3);

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaReinsercao1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();
    
    // check se todas sondas estão vazias
    bool solucaoVazia = true;
    for (std::set<Sonda>::iterator itS=sondas.begin(); itS!=sondas.end(); ++itS)
    {
        Sonda sondaX = *itS;
        if (alocsMap[sondaX].empty() == false)
        {
            solucaoVazia = false;
            break;
        }
    }

    if (solucaoVazia)
    {
        return alocsMap;
    }
    else
    {
        int count = 0;
        while (count < k)
        {
            // escolhe sonda1
            int sonda1idx = rand() % (sondas.size());
            Sonda sonda1 = *(std::next(sondas.begin(), sonda1idx));

            // escolhe alocacao1
            if (alocsMap[sonda1].empty())
            {
                continue;
            }
            int aloc1idx = rand() % (alocsMap[sonda1].size());
            Alocacao alocacao1 = *(std::next(alocsMap[sonda1].begin(), aloc1idx));

            // realiza movimento
            alocsMap = reinsercao1InterRota(alocsMap, dataset, estrutura, modoRealoc, alocacao1);

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaReinsercao2InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();
    
    // check
    bool solucaoVazia = true;
    for (std::set<Sonda>::iterator itS=sondas.begin(); itS!=sondas.end(); ++itS)
    {
        Sonda sondaX = *itS;
        if (alocsMap[sondaX].size() >= 2)
        {
            solucaoVazia = false;
            break;
        }
    }

    if (solucaoVazia)
    {
        return alocsMap;
    }
    else
    {
        int count = 0;
        while (count < k)
        {
            // escolhe sonda1
            int sonda1idx = rand() % (sondas.size());
            Sonda sonda1 = *(std::next(sondas.begin(), sonda1idx));

            // escolhe alocacao1
            if (alocsMap[sonda1].size() < 2)
            {
                continue;
            }
            int aloc1idx = rand() % (alocsMap[sonda1].size());
            Alocacao alocacao1 = *(std::next(alocsMap[sonda1].begin(), aloc1idx));

            // escolhe alocacao2
            int aloc2idx = rand() % (alocsMap[sonda1].size());
            Alocacao alocacao2 = *(std::next(alocsMap[sonda1].begin(), aloc2idx));
            if (alocacao1 == alocacao2)
            {
                continue;
            }

            // realiza movimento
            alocsMap = reinsercao2InterRota(alocsMap, dataset, estrutura, modoRealoc, alocacao1, alocacao2);

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaInserirNovoFO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();

    // inicializa conjunto de projetos não alocados
    std::set<Projeto> projetosNaoAlocs = solucaoLocal.getProjetosNaoAlocados();
    
    if (projetosNaoAlocs.empty())
    {
        return alocsMap;
    }
    else
    {
        int count = 0;
        while (count < k)
        {
            // escolhe projeto não alocado
            if (projetosNaoAlocs.empty())
            {
                return alocsMap;
            }
            int proj1idx = rand() % (projetosNaoAlocs.size());
            Projeto projeto1 = *(std::next(projetosNaoAlocs.begin(), proj1idx));
            projetosNaoAlocs.erase(std::next(projetosNaoAlocs.begin(), proj1idx));

            // escolhe sonda1
            int sonda1idx = rand() % (sondas.size());
            Sonda sonda1 = *(std::next(sondas.begin(), sonda1idx));

            // realiza movimento
            alocsMap = inserirNovoFO(alocsMap, dataset, estrutura, modoRealoc, sonda1, projeto1);

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaSwap1x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();

    // inicializa conjunto de projetos não alocados
    std::set<Projeto> projetosNaoAlocs = solucaoLocal.getProjetosNaoAlocados();
    
    // check
    bool solucaoVazia = true;
    for (std::set<Sonda>::iterator itS=sondas.begin(); itS!=sondas.end(); ++itS)
    {
        Sonda sondaX = *itS;
        if (alocsMap[sondaX].empty() == false)
        {
            solucaoVazia = false;
            break;
        }
    }

    if (projetosNaoAlocs.empty())
    {
        return alocsMap;
    }
    else if (solucaoVazia)
    {
        return alocsMap;
    }
    else
    {
        int count = 0;
        while (count < k)
        {
            // escolhe projeto não alocado
            if (projetosNaoAlocs.empty())
            {
                return alocsMap;
            }
            int proj1idx = rand() % (projetosNaoAlocs.size());
            Projeto projeto1 = *(std::next(projetosNaoAlocs.begin(), proj1idx));
            projetosNaoAlocs.erase(std::next(projetosNaoAlocs.begin(), proj1idx));

            // escolhe sonda1
            int sonda1idx = rand() % (sondas.size());
            Sonda sonda1 = *(std::next(sondas.begin(), sonda1idx));

            // escolhe alocacao1
            if (alocsMap[sonda1].empty())
            {
                continue;
            }
            int aloc1idx = rand() % (alocsMap[sonda1].size());
            Alocacao alocacao1 = *(std::next(alocsMap[sonda1].begin(), aloc1idx));

            // realiza movimento
            alocsMap = swap1x1FO(alocsMap, dataset, estrutura, modoRealoc, alocacao1, projeto1);

            // atualiza projetos não alocados
            Solucao solucaoTemp{alocsMap, estrutura, dataset};
            projetosNaoAlocs = solucaoTemp.getProjetosNaoAlocados();

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaSwap2x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();

    // inicializa conjunto de projetos não alocados
    std::set<Projeto> projetosNaoAlocs = solucaoLocal.getProjetosNaoAlocados();
    
    // check
    bool solucaoVazia = true;
    for (std::set<Sonda>::iterator itS=sondas.begin(); itS!=sondas.end(); ++itS)
    {
        Sonda sondaX = *itS;
        if (alocsMap[sondaX].size() >= 2)
        {
            solucaoVazia = false;
            break;
        }
    }

    if (projetosNaoAlocs.empty())
    {
        return alocsMap;
    }
    else if (solucaoVazia)
    {
        return alocsMap;
    }
    else
    {
        int count = 0;
        while (count < k)
        {
            // escolhe projeto não alocado
            if (projetosNaoAlocs.empty())
            {
                return alocsMap;
            }
            int proj1idx = rand() % (projetosNaoAlocs.size());
            Projeto projeto1 = *(std::next(projetosNaoAlocs.begin(), proj1idx));
            projetosNaoAlocs.erase(std::next(projetosNaoAlocs.begin(), proj1idx));

            // escolhe sonda1
            int sonda1idx = rand() % (sondas.size());
            Sonda sonda1 = *(std::next(sondas.begin(), sonda1idx));

            // escolhe alocacao1
            if (alocsMap[sonda1].size() < 2)
            {
                continue;
            }
            int aloc1idx = rand() % (alocsMap[sonda1].size());
            Alocacao alocacao1 = *(std::next(alocsMap[sonda1].begin(), aloc1idx));

            // escolhe alocação2
            int aloc2idx = rand() % (alocsMap[sonda1].size());
            Alocacao alocacao2 = *(std::next(alocsMap[sonda1].begin(), aloc2idx));
            if (alocacao1 == alocacao2)
            {
                continue;
            }

            // realiza movimento
            alocsMap = swap2x1FO(alocsMap, dataset, estrutura, modoRealoc, alocacao1, alocacao2, projeto1);

            // atualiza projetos não alocados
            Solucao solucaoTemp{alocsMap, estrutura, dataset};
            projetosNaoAlocs = solucaoTemp.getProjetosNaoAlocados();

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaSwap1x2FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();

    // inicializa conjunto de projetos não alocados
    std::set<Projeto> projetosNaoAlocs = solucaoLocal.getProjetosNaoAlocados();
    
    // check
    bool solucaoVazia = true;
    for (std::set<Sonda>::iterator itS=sondas.begin(); itS!=sondas.end(); ++itS)
    {
        Sonda sondaX = *itS;
        if (alocsMap[sondaX].empty() == false)
        {
            solucaoVazia = false;
            break;
        }
    }

    if (projetosNaoAlocs.size() < 2)
    {
        return alocsMap;
    }
    else if (solucaoVazia)
    {
        return alocsMap;
    }
    else
    {
        int count = 0;
        while (count < k)
        {
            // escolhe projeto não alocado
            if (projetosNaoAlocs.size() < 2)
            {
                return alocsMap;
            }
            int proj1idx = rand() % (projetosNaoAlocs.size());
            Projeto projeto1 = *(std::next(projetosNaoAlocs.begin(), proj1idx));
            projetosNaoAlocs.erase(std::next(projetosNaoAlocs.begin(), proj1idx));

            int proj2idx = rand() % (projetosNaoAlocs.size());
            Projeto projeto2 = *(std::next(projetosNaoAlocs.begin(), proj2idx));
            projetosNaoAlocs.erase(std::next(projetosNaoAlocs.begin(), proj2idx));

            // escolhe sonda1
            int sonda1idx = rand() % (sondas.size());
            Sonda sonda1 = *(std::next(sondas.begin(), sonda1idx));

            // escolhe alocacao1
            if (alocsMap[sonda1].empty())
            {
                continue;
            }
            int aloc1idx = rand() % (alocsMap[sonda1].size());
            Alocacao alocacao1 = *(std::next(alocsMap[sonda1].begin(), aloc1idx));

            // realiza movimento
            alocsMap = swap1x2FO(alocsMap, dataset, estrutura, modoRealoc, alocacao1, projeto1, projeto2);

            // atualiza projetos não alocados
            Solucao solucaoTemp{alocsMap, estrutura, dataset};
            projetosNaoAlocs = solucaoTemp.getProjetosNaoAlocados();

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaSwap2x2FO(std::map<Sonda, std::vector<Alocacao>> alocsMap,
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();

    // inicializa conjunto de projetos não alocados
    std::set<Projeto> projetosNaoAlocs = solucaoLocal.getProjetosNaoAlocados();
    
    // check
    bool solucaoVazia = true;
    for (std::set<Sonda>::iterator itS=sondas.begin(); itS!=sondas.end(); ++itS)
    {
        Sonda sondaX = *itS;
        if (alocsMap[sondaX].size() >= 2)
        {
            solucaoVazia = false;
            break;
        }
    }

    if (projetosNaoAlocs.size() < 2)
    {
        return alocsMap;
    }
    else if (solucaoVazia)
    {
        return alocsMap;
    }
    else
    {
        int count = 0;
        while (count < k)
        {
            // escolhe projeto não alocado
            if (projetosNaoAlocs.size() < 2)
            {
                return alocsMap;
            }
            int proj1idx = rand() % (projetosNaoAlocs.size());
            Projeto projeto1 = *(std::next(projetosNaoAlocs.begin(), proj1idx));
            projetosNaoAlocs.erase(std::next(projetosNaoAlocs.begin(), proj1idx));

            int proj2idx = rand() % (projetosNaoAlocs.size());
            Projeto projeto2 = *(std::next(projetosNaoAlocs.begin(), proj2idx));
            projetosNaoAlocs.erase(std::next(projetosNaoAlocs.begin(), proj2idx));

            // escolhe sonda1
            int sonda1idx = rand() % (sondas.size());
            Sonda sonda1 = *(std::next(sondas.begin(), sonda1idx));

            // escolhe alocacao1
            if (alocsMap[sonda1].size() < 2)
            {
                continue;
            }
            int aloc1idx = rand() % (alocsMap[sonda1].size());
            Alocacao alocacao1 = *(std::next(alocsMap[sonda1].begin(), aloc1idx));

            // escolhe alocação2
            int aloc2idx = rand() % (alocsMap[sonda1].size());
            Alocacao alocacao2 = *(std::next(alocsMap[sonda1].begin(), aloc2idx));
            if (alocacao1 == alocacao2)
            {
                continue;
            }

            // realiza movimento
            alocsMap = swap2x2FO(alocsMap, dataset, estrutura, modoRealoc, alocacao1, alocacao2, projeto1, projeto2);

            // atualiza projetos não alocados
            Solucao solucaoTemp{alocsMap, estrutura, dataset};
            projetosNaoAlocs = solucaoTemp.getProjetosNaoAlocados();

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaAleatorio(std::map<Sonda, std::vector<Alocacao>> alocsMap,
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k)
{
    // inicializa conjunto de vizinhanças
    std::set<int> vizinhancas;
    vizinhancas.insert(1);
    vizinhancas.insert(2);
    vizinhancas.insert(3);
    vizinhancas.insert(4);
    vizinhancas.insert(5);
    vizinhancas.insert(6);
    vizinhancas.insert(7);
    vizinhancas.insert(8);
    vizinhancas.insert(9);
    vizinhancas.insert(10);
    vizinhancas.insert(11);
    vizinhancas.insert(12);

    int count = 0;
    while (count < k)
    {
        // seleciona vizinhança
        int idx = rand() % vizinhancas.size();
        std::set<int>::iterator itr = std::next(vizinhancas.begin(), idx);
        int vizinhanca = *(itr);

        // faz busca pela vizinhança
        if (vizinhanca == 1)
        {
            alocsMap = perturbaShift1x0InterRota(alocsMap, dataset, estrutura, modoRealoc, 1);
        }
        else if (vizinhanca == 2)
        {
            alocsMap = perturbaShift2x0InterRota(alocsMap, dataset, estrutura, modoRealoc, 1);
        }
        else if (vizinhanca == 3)
        {
            alocsMap = perturbaSwap1x1InterRota(alocsMap, dataset, estrutura, modoRealoc, 1);
        }
        else if (vizinhanca == 4)
        {
            alocsMap = perturbaSwap2x1InterRota(alocsMap, dataset, estrutura, modoRealoc, 1);
        }
        else if (vizinhanca == 5)
        {
            alocsMap = perturbaSwap2x2InterRota(alocsMap, dataset, estrutura, modoRealoc, 1);
        }
        else if (vizinhanca == 6)
        {
            alocsMap = perturbaReinsercao1InterRota(alocsMap, dataset, estrutura, modoRealoc, 1);
        }
        else if (vizinhanca == 7)
        {
            alocsMap = perturbaReinsercao2InterRota(alocsMap, dataset, estrutura, modoRealoc, 1);
        }
        else if (vizinhanca == 8)
        {
            alocsMap = perturbaInserirNovoFO(alocsMap, dataset, estrutura, modoRealoc, 1);
        }
        else if (vizinhanca == 9)
        {
            alocsMap = perturbaSwap1x1FO(alocsMap, dataset, estrutura, modoRealoc, 1);
        }
        else if (vizinhanca == 10)
        {
            alocsMap = perturbaSwap2x1FO(alocsMap, dataset, estrutura, modoRealoc, 1);
        }
        else if (vizinhanca == 11)
        {
            alocsMap = perturbaSwap1x2FO(alocsMap, dataset, estrutura, modoRealoc, 1);
        }
        else if (vizinhanca == 12)
        {
            alocsMap = perturbaSwap2x2FO(alocsMap, dataset, estrutura, modoRealoc, 1);
        }

        // contabiliza movimento feito
        count++;
    }
    return alocsMap;
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaSolucao(std::map<Sonda, std::vector<Alocacao>> alocsMap,
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, 
                                                                int k, int vizinhanca)
{
    if (vizinhanca == 1)
    {
        alocsMap = perturbaShift1x0InterRota(alocsMap, dataset, estrutura, modoRealoc, k);
    }
    else if (vizinhanca == 2)
    {
        alocsMap = perturbaShift2x0InterRota(alocsMap, dataset, estrutura, modoRealoc, k);
    }
    else if (vizinhanca == 3)
    {
        alocsMap = perturbaSwap1x1InterRota(alocsMap, dataset, estrutura, modoRealoc, k);
    }
    else if (vizinhanca == 4)
    {
        alocsMap = perturbaSwap2x1InterRota(alocsMap, dataset, estrutura, modoRealoc, k);
    }
    else if (vizinhanca == 5)
    {
        alocsMap = perturbaSwap2x2InterRota(alocsMap, dataset, estrutura, modoRealoc, k);
    }
    else if (vizinhanca == 6)
    {
        alocsMap = perturbaReinsercao1InterRota(alocsMap, dataset, estrutura, modoRealoc, k);
    }
    else if (vizinhanca == 7)
    {
        alocsMap = perturbaReinsercao2InterRota(alocsMap, dataset, estrutura, modoRealoc, k);
    }
    else if (vizinhanca == 8)
    {
        alocsMap = perturbaInserirNovoFO(alocsMap, dataset, estrutura, modoRealoc, k);
    }
    else if (vizinhanca == 9)
    {
        alocsMap = perturbaSwap1x1FO(alocsMap, dataset, estrutura, modoRealoc, k);
    }
    else if (vizinhanca == 10)
    {
        alocsMap = perturbaSwap2x1FO(alocsMap, dataset, estrutura, modoRealoc, k);
    }
    else if (vizinhanca == 11)
    {
        alocsMap = perturbaSwap1x2FO(alocsMap, dataset, estrutura, modoRealoc, k);
    }
    else if (vizinhanca == 12)
    {
        alocsMap = perturbaSwap2x2FO(alocsMap, dataset, estrutura, modoRealoc, k);
    }
    else if (vizinhanca == 13)
    {
        alocsMap = perturbaAleatorio(alocsMap, dataset, estrutura, modoRealoc, k);
    }
    return alocsMap;
}

