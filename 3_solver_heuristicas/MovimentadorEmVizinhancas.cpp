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

std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::shift1x0InterRota(const std::map<Sonda, std::vector<Alocacao>> & alocsMap, const DadosDeEntrada & dataset, 
                                                  int estrutura, int modoRealoc, Alocacao alocacao1, Sonda sonda2, int modoDebug, double fitness, double gastos, int totalFree)
{
    Sonda sonda1 = alocacao1.getSonda();
    Projeto projeto1 = alocacao1.getProjeto();
    Intervalo intervalo1 = alocacao1.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // remove projeto
    bool removed = false;
    removed = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1, modoDebug);
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
                                                    solucaoLocal.buscarJanelaViavel(sonda2, projeto1, modoRealoc, modoDebug);
        // se viável, insere     
        if (alocExiste)
        {
            solucaoLocal.inserirProjeto(sonda2, projeto1, posicaoAloc, intervaloAloc, prevMinus, 
                                            currMinus, currPlus, nextPlus, caso, modoDebug);
        }
    }
    return std::make_tuple(solucaoLocal.getAlocacoes(), solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
}

std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::shift2x0InterRota(const std::map<Sonda, std::vector<Alocacao>> & alocsMap, 
                                                         const DadosDeEntrada & dataset, int estrutura, int modoRealoc,
                                                         Alocacao alocacao1, Alocacao alocacao2, Sonda sonda2, int modoDebug, double fitness, double gastos, int totalFree)
{
    Sonda sonda1 = alocacao1.getSonda();
    Projeto projeto1 = alocacao1.getProjeto();
    Intervalo intervalo1 = alocacao1.getIntervalo();
    Projeto projeto2 = alocacao2.getProjeto();
    Intervalo intervalo2 = alocacao2.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // remover projeto1 da sonda1
    bool removed1 = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1, modoDebug);
    
    // remover projeto2 da sonda1
    bool removed2 = solucaoLocal.removerProjeto(sonda1, projeto2, intervalo2, modoDebug);
    
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
                                                    solucaoLocal.buscarJanelaViavel(sonda2, projeto1, modoRealoc, modoDebug);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda2
            solucaoLocal.inserirProjeto(sonda2, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1, modoDebug);
            
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
                                                        solucaoLocal.buscarJanelaViavel(sonda2, projeto2, modoRealoc, modoDebug);
            if (alocExiste2)
            {
                // inserir projeto2 na sonda2
                solucaoLocal.inserirProjeto(sonda2, projeto2, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                            currMinus2, currPlus2, nextPlus2, caso2, modoDebug);
            }
        }
    }
    return std::make_tuple(solucaoLocal.getAlocacoes(), solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
}

std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::swap1x1InterRota(const std::map<Sonda, std::vector<Alocacao>> & alocsMap, 
                                                                 const DadosDeEntrada & dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2, int modoDebug, double fitness, double gastos, int totalFree)
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
    bool removed1 = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1, modoDebug);

    // remover projeto2 da sonda2
    bool removed2 = solucaoLocal.removerProjeto(sonda2, projeto2, intervalo2, modoDebug);

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
                                                    solucaoLocal.buscarJanelaViavel(sonda2, projeto1, modoRealoc, modoDebug);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda2
            solucaoLocal.inserirProjeto(sonda2, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1, modoDebug);
            
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
                                                        solucaoLocal.buscarJanelaViavel(sonda1, projeto2, modoRealoc, modoDebug);
            if (alocExiste2)
            {
                // inserir projeto2 na sonda1
                solucaoLocal.inserirProjeto(sonda1, projeto2, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                            currMinus2, currPlus2, nextPlus2, caso2, modoDebug);
            }
        }
    }
    return std::make_tuple(solucaoLocal.getAlocacoes(), solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
}

std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::swap2x1InterRota(const std::map<Sonda, std::vector<Alocacao>> & alocsMap, 
                                                                 const DadosDeEntrada & dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2, Alocacao alocacao3, int modoDebug, double fitness, double gastos, int totalFree)
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
    bool removed1 = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1, modoDebug);

    // remover projeto2 da sonda1
    bool removed2 = solucaoLocal.removerProjeto(sonda1, projeto2, intervalo2, modoDebug);

    // remover projeto3 da sonda2
    bool removed3 = solucaoLocal.removerProjeto(sonda2, projeto3, intervalo3, modoDebug);

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
                                                    solucaoLocal.buscarJanelaViavel(sonda2, projeto1, modoRealoc, modoDebug);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda2
            solucaoLocal.inserirProjeto(sonda2, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1, modoDebug);

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
                                                        solucaoLocal.buscarJanelaViavel(sonda2, projeto2, modoRealoc, modoDebug);
            if (alocExiste2)
            {
                // inserir projeto2 na sonda2
                solucaoLocal.inserirProjeto(sonda2, projeto2, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                        currMinus2, currPlus2, nextPlus2, caso2, modoDebug);

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
                                                            solucaoLocal.buscarJanelaViavel(sonda1, projeto3, modoRealoc, modoDebug);
                if (alocExiste3)
                {
                    // inserir projeto3 na sonda1
                    solucaoLocal.inserirProjeto(sonda1, projeto3, posicaoAloc3, intervaloAloc3, prevMinus3, 
                                        currMinus3, currPlus3, nextPlus3, caso3, modoDebug);
                }
            }
        }
    }
    return std::make_tuple(solucaoLocal.getAlocacoes(), solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
}

std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::swap2x2InterRota(const std::map<Sonda, std::vector<Alocacao>> & alocsMap, 
                                                                 const DadosDeEntrada & dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2, 
                                                                 Alocacao alocacao3, Alocacao alocacao4, int modoDebug, double fitness, double gastos, int totalFree)
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
    bool removed1 = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1, modoDebug);

    // remover projeto2 da sonda1
    bool removed2 = solucaoLocal.removerProjeto(sonda1, projeto2, intervalo2, modoDebug);

    // remover projeto3 da sonda2
    bool removed3 = solucaoLocal.removerProjeto(sonda2, projeto3, intervalo3, modoDebug);

    // remover projeto4 da sonda2
    bool removed4 = solucaoLocal.removerProjeto(sonda2, projeto4, intervalo3, modoDebug);

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
                                                    solucaoLocal.buscarJanelaViavel(sonda2, projeto1, modoRealoc, modoDebug);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda2
            solucaoLocal.inserirProjeto(sonda2, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1, modoDebug);

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
                                                        solucaoLocal.buscarJanelaViavel(sonda2, projeto2, modoRealoc, modoDebug);
            if (alocExiste2)
            {
                // inserir projeto2 na sonda2
                solucaoLocal.inserirProjeto(sonda2, projeto2, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                        currMinus2, currPlus2, nextPlus2, caso2, modoDebug);

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
                                                            solucaoLocal.buscarJanelaViavel(sonda1, projeto3, modoRealoc, modoDebug);
                if (alocExiste3)
                {
                    // inserir projeto3 na sonda1
                    solucaoLocal.inserirProjeto(sonda1, projeto3, posicaoAloc3, intervaloAloc3, prevMinus3, 
                                        currMinus3, currPlus3, nextPlus3, caso3, modoDebug);
                    
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
                                                                solucaoLocal.buscarJanelaViavel(sonda1, projeto4, modoRealoc, modoDebug);
                    if (alocExiste4)
                    {
                        // inserir projeto4 na sonda1
                        solucaoLocal.inserirProjeto(sonda1, projeto4, posicaoAloc4, intervaloAloc4, prevMinus4, 
                                        currMinus4, currPlus4, nextPlus4, caso4, modoDebug);
                    }
                }
            }
        }
    }
    return std::make_tuple(solucaoLocal.getAlocacoes(), solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
}

std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::reinsercao1InterRota(const std::map<Sonda, std::vector<Alocacao>> & alocsMap, 
                                                                 const DadosDeEntrada & dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, int modoDebug, double fitness, double gastos, int totalFree)
{
    Sonda sonda1 = alocacao1.getSonda();
    Projeto projeto1 = alocacao1.getProjeto();
    Intervalo intervalo1 = alocacao1.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // remover projeto1 da sonda1
    bool removed1 = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1, modoDebug);

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
                                                    solucaoLocal.buscarJanelaViavel(sonda1, projeto1, modoRealoc, modoDebug);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda1
            solucaoLocal.inserirProjeto(sonda1, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1, modoDebug);
        }
    }
    return std::make_tuple(solucaoLocal.getAlocacoes(), solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
}

std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::reinsercao2InterRota(const std::map<Sonda, std::vector<Alocacao>> & alocsMap, 
                                                                 const DadosDeEntrada & dataset, int estrutura, int modoRealoc,
                                                                 Alocacao alocacao1, Alocacao alocacao2, int modoDebug, double fitness, double gastos, int totalFree)
{
    Sonda sonda1 = alocacao1.getSonda();
    Projeto projeto1 = alocacao1.getProjeto();
    Projeto projeto2 = alocacao2.getProjeto();
    Intervalo intervalo1 = alocacao1.getIntervalo();
    Intervalo intervalo2 = alocacao2.getIntervalo();

    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // remover projeto1 da sonda1
    bool removed1 = solucaoLocal.removerProjeto(sonda1, projeto1, intervalo1, modoDebug);

    // remover projeto2 da sonda1
    bool removed2 = solucaoLocal.removerProjeto(sonda1, projeto2, intervalo2, modoDebug);

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
                                                    solucaoLocal.buscarJanelaViavel(sonda1, projeto2, modoRealoc, modoDebug);
        if (alocExiste1)
        {
            solucaoLocal.inserirProjeto(sonda1, projeto2, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1, modoDebug);
            
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
                                                        solucaoLocal.buscarJanelaViavel(sonda1, projeto1, modoRealoc, modoDebug);
            if (alocExiste2)
            {
                // inserir projeto1 na sonda1
                solucaoLocal.inserirProjeto(sonda1, projeto1, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                        currMinus2, currPlus2, nextPlus2, caso2, modoDebug);
            }
        }
    }
    return std::make_tuple(solucaoLocal.getAlocacoes(), solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
}

std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::inserirNovoFO(const std::map<Sonda, std::vector<Alocacao>> & alocsMap, 
                                                             DadosDeEntrada & dataset, int estrutura, int modoRealoc,
                                                             Sonda sonda1, Projeto projeto1, int modoDebug, double fitness, double gastos, int totalFree)
{
    // instancia solução local
    Solucao solucaoLocal{alocsMap, estrutura, dataset};

    // check de gastos
    double custoProjetado = solucaoLocal.getGastos() + projeto1.getCusto();
    if (custoProjetado > dataset.getCapitalTotal())
    {
        return std::make_tuple(alocsMap, solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
    }

    if (fitness != -1)
    {
        // projeta fitness
        double fitnessProjetado = solucaoLocal.getFitness() + projeto1.getMiVpl();
        if (fitnessProjetado <= solucaoLocal.getFitness())
        {
            return std::make_tuple(alocsMap, solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
        }
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
                                                solucaoLocal.buscarJanelaViavel(sonda1, projeto1, modoRealoc, modoDebug);
    if (alocExiste1)
    {
        // inserir projeto1 na sonda1
        solucaoLocal.inserirProjeto(sonda1, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                        currMinus1, currPlus1, nextPlus1, caso1, modoDebug);
    }
    return std::make_tuple(solucaoLocal.getAlocacoes(), solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
}

std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::swap1x1FO(const std::map<Sonda, std::vector<Alocacao>> & alocsMap, 
                                                         DadosDeEntrada & dataset, int estrutura, int modoRealoc,
                                                         Alocacao alocacao1, Projeto projeto1, int modoDebug, double fitness, double gastos, int totalFree)
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
        return std::make_tuple(alocsMap, solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
    }

    if (fitness != -1)
    {
        // projeta fitness
        double fitnessProjetado = solucaoLocal.getFitness() - alocacao1.getProjeto().getMiVpl() + projeto1.getMiVpl();
        if (fitnessProjetado <= solucaoLocal.getFitness())
        {
            return std::make_tuple(alocsMap, solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
        }
    }

    // remover projeto2 da sonda1
    bool removed2 = solucaoLocal.removerProjeto(sonda1, projeto2, intervalo2, modoDebug);

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
                                                    solucaoLocal.buscarJanelaViavel(sonda1, projeto1, modoRealoc, modoDebug);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda1
            solucaoLocal.inserirProjeto(sonda1, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                            currMinus1, currPlus1, nextPlus1, caso1, modoDebug);
        }
    }
    return std::make_tuple(solucaoLocal.getAlocacoes(), solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
}

std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::swap2x1FO(const std::map<Sonda, std::vector<Alocacao>> & alocsMap, 
                                                         DadosDeEntrada & dataset, int estrutura, int modoRealoc,
                                                         Alocacao alocacao1, Alocacao alocacao2, Projeto projeto1, int modoDebug, double fitness, double gastos, int totalFree)
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
        return std::make_tuple(alocsMap, solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
    }

    if (fitness != -1)
    {
        // projeta fitness
        double fitnessProjetado = solucaoLocal.getFitness() 
                                - alocacao1.getProjeto().getMiVpl() - alocacao2.getProjeto().getMiVpl() 
                                + projeto1.getMiVpl();
        if (fitnessProjetado <= solucaoLocal.getFitness())
        {
            return std::make_tuple(alocsMap, solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
        }
    }

    // remover projeto2 da sonda1
    bool removed2 = solucaoLocal.removerProjeto(sonda1, projeto2, intervalo2, modoDebug);

    // remover projeto3 da sonda1
    bool removed3 = solucaoLocal.removerProjeto(sonda1, projeto3, intervalo3, modoDebug);

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
                                                    solucaoLocal.buscarJanelaViavel(sonda1, projeto1, modoRealoc, modoDebug);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda1
            solucaoLocal.inserirProjeto(sonda1, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                            currMinus1, currPlus1, nextPlus1, caso1, modoDebug);
        }
    }
    return std::make_tuple(solucaoLocal.getAlocacoes(), solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
}

std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::swap1x2FO(const std::map<Sonda, std::vector<Alocacao>> & alocsMap, 
                                                         DadosDeEntrada & dataset, int estrutura, int modoRealoc,
                                                         Alocacao alocacao1, Projeto projeto1, Projeto projeto2, int modoDebug, double fitness, double gastos, int totalFree)
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
        return std::make_tuple(alocsMap, solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
    }

    if (fitness != -1)
    {
        // projeta fitness
        double fitnessProjetado = solucaoLocal.getFitness()
                                - alocacao1.getProjeto().getMiVpl() 
                                + projeto1.getMiVpl() + projeto2.getMiVpl();
        if (fitnessProjetado <= solucaoLocal.getFitness())
        {
            return std::make_tuple(alocsMap, solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
        }
    }

    // remover projeto3 da sonda1
    bool removed3 = solucaoLocal.removerProjeto(sonda1, projeto3, intervalo3, modoDebug);

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
                                                    solucaoLocal.buscarJanelaViavel(sonda1, projeto1, modoRealoc, modoDebug);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda1
            solucaoLocal.inserirProjeto(sonda1, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                            currMinus1, currPlus1, nextPlus1, caso1, modoDebug);
            
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
                                                        solucaoLocal.buscarJanelaViavel(sonda1, projeto2, modoRealoc, modoDebug);
            if (alocExiste2)
            {
                // inserir projeto1 na sonda1
                solucaoLocal.inserirProjeto(sonda1, projeto2, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                                currMinus2, currPlus2, nextPlus2, caso2, modoDebug);
            }
        }
    }
    return std::make_tuple(solucaoLocal.getAlocacoes(), solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
}

std::tuple<std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::swap2x2FO(const std::map<Sonda, std::vector<Alocacao>> & alocsMap, 
                                                         DadosDeEntrada & dataset, int estrutura, int modoRealoc,
                                                         Alocacao alocacao1, Alocacao alocacao2, 
                                                         Projeto projeto1, Projeto projeto2, int modoDebug, double fitness, double gastos, int totalFree)
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
        return std::make_tuple(alocsMap, solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
    }

    if (fitness != -1)
    {
        // projeta fitness
        double fitnessProjetado = solucaoLocal.getFitness()
                                - alocacao1.getProjeto().getMiVpl() - alocacao2.getProjeto().getMiVpl() 
                                + projeto1.getMiVpl() + projeto2.getMiVpl();
        if (fitnessProjetado <= solucaoLocal.getFitness())
        {
            return std::make_tuple(alocsMap, solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
        }
    }

    // remover projeto3 da sonda1
    bool removed3 = solucaoLocal.removerProjeto(sonda1, projeto3, intervalo3, modoDebug);

    // remover projeto4 da sonda1
    bool removed4 = solucaoLocal.removerProjeto(sonda1, projeto4, intervalo4, modoDebug);

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
                                                    solucaoLocal.buscarJanelaViavel(sonda1, projeto1, modoRealoc, modoDebug);
        if (alocExiste1)
        {
            // inserir projeto1 na sonda1
            solucaoLocal.inserirProjeto(sonda1, projeto1, posicaoAloc1, intervaloAloc1, prevMinus1, 
                                            currMinus1, currPlus1, nextPlus1, caso1, modoDebug);
            
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
                                                        solucaoLocal.buscarJanelaViavel(sonda1, projeto2, modoRealoc, modoDebug);
            if (alocExiste2)
            {
                // inserir projeto1 na sonda1
                solucaoLocal.inserirProjeto(sonda1, projeto2, posicaoAloc2, intervaloAloc2, prevMinus2, 
                                                currMinus2, currPlus2, nextPlus2, caso2, modoDebug);
            }
        }
    }
    return std::make_tuple(solucaoLocal.getAlocacoes(), solucaoLocal.getFitness(), solucaoLocal.getGastos(), solucaoLocal.getTotalFree());
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaShift1x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, DadosDeEntrada dataset, 
                                                  int estrutura, int modoRealoc, int deltaT, int modoDebug)
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

    int parar = 0;
    // percorre combinações    
    for (std::set<Sonda>::iterator itS1 = sondas.begin(); itS1 != sondas.end(); ++itS1)
    {
        if (parar == 1) 
        {
            break;
        }
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1 = alocsMap[sonda1].begin(); itA1 != alocsMap[sonda1].end(); ++itA1)
        {
            if (parar == 1) 
            {
                break;
            }
            Alocacao alocacao1 = *itA1;
            Projeto projeto1 = (*itA1).getProjeto();
            Intervalo intervalo1 = (*itA1).getIntervalo();
            for (std::set<Sonda>::iterator itS2 = sondas.begin(); itS2 != sondas.end(); ++itS2)
            {
                if (parar == 1) 
                {
                    break;
                }
                Sonda sonda2 = *itS2;
                if (sonda1 == sonda2)
                {
                    continue;
                }

                // realiza movimento
                std::map<Sonda, std::vector<Alocacao>> alocsMapAlt;
                double fitnessAlt;
                double gastosAlt;
                int totalFreeAlt;
                std::tie(alocsMapAlt, fitnessAlt, gastosAlt, totalFreeAlt) = shift1x0InterRota(alocsMap, dataset, estrutura, modoRealoc, alocacao1, sonda2, modoDebug, bestFitness, bestGastos, bestTotalFree);

                // se for melhor que best
                if (fitnessAlt >= bestFitness)
                {
                    if (totalFreeAlt > bestTotalFree)
                    {
                        bestAlocsMap = alocsMapAlt;
                        bestFitness = fitnessAlt;
                        bestGastos = gastosAlt;
                        bestTotalFree = totalFreeAlt;
                        parar = 1;
                        break;
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
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug)
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

    int parar = 0;
    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        if (parar == 1) 
        {
            break;
        }
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            if (parar == 1) 
            {
                break;
            }
            Alocacao alocacao1 = *itA1;
            Projeto projeto1 = (*itA1).getProjeto();
            Intervalo intervalo1 = (*itA1).getIntervalo();
            for (std::vector<Alocacao>::iterator itA2=alocsMap[sonda1].begin(); itA2!=alocsMap[sonda1].end(); ++itA2)
            {
                if (parar == 1) 
                {
                    break;
                }
                Alocacao alocacao2 = *itA2;
                Projeto projeto2 = (*itA2).getProjeto();
                Intervalo intervalo2 = (*itA2).getIntervalo();
                if (projeto1 == projeto2)
                {
                    continue;
                }
                for (std::set<Sonda>::iterator itS2=sondas.begin(); itS2!=sondas.end(); ++itS2)
                {
                    if (parar == 1) 
                    {
                        break;
                    }
                    Sonda sonda2 = *itS2;
                    if (sonda1 == sonda2)
                    {
                        continue;
                    }
                    // realiza movimento
                    std::map<Sonda, std::vector<Alocacao>> alocsMapAlt;
                    double fitnessAlt;
                    double gastosAlt;
                    int totalFreeAlt;
                    std::tie(alocsMapAlt, fitnessAlt, gastosAlt, totalFreeAlt) = shift2x0InterRota(alocsMap, dataset, estrutura, 
                                                                                    modoRealoc, alocacao1, alocacao2, sonda2, modoDebug, bestFitness, bestGastos, bestTotalFree);

                    // se for melhor que best
                    if (fitnessAlt >= bestFitness)
                    {
                        if (totalFreeAlt > bestTotalFree)
                        {
                            bestAlocsMap = alocsMapAlt;
                            bestFitness = fitnessAlt;
                            bestGastos = gastosAlt;
                            bestTotalFree = totalFreeAlt;
                            parar = 1;
                            break;
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
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug)
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

    int parar = 0;
    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        if (parar == 1) 
        {
            break;
        }
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            if (parar == 1) 
            {
                break;
            }
            Alocacao alocacao1 = *itA1;
            for (std::set<Sonda>::iterator itS2=sondas.begin(); itS2!=sondas.end(); ++itS2)
            {
                if (parar == 1) 
                {
                    break;
                }
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
                    if (parar == 1) 
                    {
                        break;
                    }
                    Alocacao alocacao2 = *itA2;

                    // realiza movimento
                    std::map<Sonda, std::vector<Alocacao>> alocsMapAlt;
                    double fitnessAlt;
                    double gastosAlt;
                    int totalFreeAlt;
                    std::tie(alocsMapAlt, fitnessAlt, gastosAlt, totalFreeAlt) = swap1x1InterRota(alocsMap, dataset, estrutura, 
                                                                                        modoRealoc, alocacao1, alocacao2, modoDebug, bestFitness, bestGastos, bestTotalFree);

                    // se for melhor que best
                    if (fitnessAlt >= bestFitness)
                    {
                        if (totalFreeAlt > bestTotalFree)
                        {
                            bestAlocsMap = alocsMapAlt;
                            bestFitness = fitnessAlt;
                            bestGastos = gastosAlt;
                            bestTotalFree = totalFreeAlt;
                            parar = 1;
                            break;
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
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug)
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

    int parar = 0;
    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        if (parar == 1) 
        {
            break;
        }
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            if (parar == 1) 
            {
                break;
            }
            Alocacao alocacao1 = *itA1;
            for (std::vector<Alocacao>::iterator itA2=alocsMap[sonda1].begin(); itA2!=alocsMap[sonda1].end(); ++itA2)
            {
                if (parar == 1) 
                {
                    break;
                }
                Alocacao alocacao2 = *itA2;
                if (alocacao1 == alocacao2)
                {
                    continue;
                }
                for (std::set<Sonda>::iterator itS2=sondas.begin(); itS2!=sondas.end(); ++itS2)
                {
                    if (parar == 1) 
                    {
                        break;
                    }
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
                        if (parar == 1) 
                        {
                            break;
                        }
                        Alocacao alocacao3 = *itA3;

                        // realiza movimento
                        std::map<Sonda, std::vector<Alocacao>> alocsMapAlt;
                        double fitnessAlt;
                        double gastosAlt;
                        int totalFreeAlt;
                        std::tie(alocsMapAlt, fitnessAlt, gastosAlt, totalFreeAlt) = swap2x1InterRota(alocsMap, dataset, estrutura, 
                                                                                            modoRealoc, 
                                                                                            alocacao1, alocacao2, alocacao3, modoDebug, bestFitness, bestGastos, bestTotalFree);

                        // se for melhor que best
                        if (fitnessAlt >= bestFitness)
                        {
                            if (totalFreeAlt > bestTotalFree)
                            {
                                bestAlocsMap = alocsMapAlt;
                                bestFitness = fitnessAlt;
                                bestGastos = gastosAlt;
                                bestTotalFree = totalFreeAlt;
                                parar = 1;
                                break;
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
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug)
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

    int parar = 0;
    // percorre combinações
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        if (parar == 1) 
        {
            break;
        }
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            if (parar == 1) 
            {
                break;
            }
            Alocacao alocacao1 = *itA1;
            for (std::vector<Alocacao>::iterator itA2=alocsMap[sonda1].begin(); itA2!=alocsMap[sonda1].end(); ++itA2)
            {
                if (parar == 1) 
                {
                    break;
                }
                Alocacao alocacao2 = *itA2;
                if (alocacao1 == alocacao2)
                {
                    continue;
                }
                for (std::set<Sonda>::iterator itS2=sondas.begin(); itS2!=sondas.end(); ++itS2)
                {
                    if (parar == 1) 
                    {
                        break;
                    }
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
                        if (parar == 1) 
                        {
                            break;
                        }
                        Alocacao alocacao3 = *itA3;
                        for (std::vector<Alocacao>::iterator itA4=alocsMap[sonda2].begin(); itA4!=alocsMap[sonda2].end(); ++itA4)
                        {
                            if (parar == 1) 
                            {
                                break;
                            }
                            Alocacao alocacao4 = *itA4;
                            if (alocacao3 == alocacao4)
                            {
                                continue;
                            }

                            // realiza movimento
                            std::map<Sonda, std::vector<Alocacao>> alocsMapAlt;
                            double fitnessAlt;
                            double gastosAlt;
                            int totalFreeAlt;
                            std::tie(alocsMapAlt, fitnessAlt, gastosAlt, totalFreeAlt) = swap2x2InterRota(alocsMap, dataset, estrutura, 
                                                                                                modoRealoc, 
                                                                                                alocacao1, alocacao2, 
                                                                                                alocacao3, alocacao4, modoDebug, bestFitness, bestGastos, bestTotalFree);

                            // se for melhor que best
                            if (fitnessAlt >= bestFitness)
                            {
                                if (totalFreeAlt > bestTotalFree)
                                {
                                    bestAlocsMap = alocsMapAlt;
                                    bestFitness = fitnessAlt;
                                    bestGastos = gastosAlt;
                                    bestTotalFree = totalFreeAlt;
                                    parar = 1;
                                    break;
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
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug)
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

    int parar = 0;
    // percorre combinações
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        if (parar == 1) 
        {
            break;
        }
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            if (parar == 1) 
            {
                break;
            }
            Alocacao alocacao1 = *itA1;

            // realiza movimento
            std::map<Sonda, std::vector<Alocacao>> alocsMapAlt;
            double fitnessAlt;
            double gastosAlt;
            int totalFreeAlt;
            std::tie(alocsMapAlt, fitnessAlt, gastosAlt, totalFreeAlt) = reinsercao1InterRota(alocsMap, dataset, estrutura, 
                                                                                      modoRealoc, alocacao1, modoDebug, bestFitness, bestGastos, bestTotalFree);

            // se for melhor que best
            if (fitnessAlt >= bestFitness)
            {
                if (totalFreeAlt > bestTotalFree)
                {
                    bestAlocsMap = alocsMapAlt;
                    bestFitness = fitnessAlt;
                    bestGastos = gastosAlt;
                    bestTotalFree = totalFreeAlt;
                    parar = 1;
                    break;
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
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug)
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

    int parar = 0;
    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        if (parar == 1) 
        {
            break;
        }
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            if (parar == 1) 
            {
                break;
            }
            Alocacao alocacao1 = *itA1;
            for (std::vector<Alocacao>::iterator itA2=alocsMap[sonda1].begin(); itA2!=alocsMap[sonda1].end(); ++itA2)
            {
                if (parar == 1) 
                {
                    break;
                }
                Alocacao alocacao2 = *itA2;
                if (alocacao1 == alocacao2)
                {
                    continue;
                }
                // realiza movimento
                std::map<Sonda, std::vector<Alocacao>> alocsMapAlt;
                double fitnessAlt;
                double gastosAlt;
                int totalFreeAlt;
                std::tie(alocsMapAlt, fitnessAlt, gastosAlt, totalFreeAlt) = reinsercao2InterRota(alocsMap, dataset, estrutura, 
                                                                                        modoRealoc, alocacao1, alocacao2, modoDebug, bestFitness, bestGastos, bestTotalFree);

                // se for melhor que best
                if (fitnessAlt >= bestFitness)
                {
                    if (totalFreeAlt > bestTotalFree)
                    {
                        bestAlocsMap = alocsMapAlt;
                        bestFitness = fitnessAlt;
                        bestGastos = gastosAlt;
                        bestTotalFree = totalFreeAlt;
                        parar = 1;
                        break;
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
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug)
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

    int parar = 0;
    // percorre combinações    
    for (std::set<Projeto>::iterator itP1=projetosNaoAloc.begin(); itP1!=projetosNaoAloc.end(); ++itP1)
    {
        if (parar == 1) 
        {
            break;
        }
        Projeto projeto1 = *itP1;
        for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
        {
            if (parar == 1) 
            {
                break;
            }
            Sonda sonda1 = *itS1;

            // realiza movimento
            std::map<Sonda, std::vector<Alocacao>> alocsMapAlt;
            double fitnessAlt;
            double gastosAlt;
            int totalFreeAlt;
            std::tie(alocsMapAlt, fitnessAlt, gastosAlt, totalFreeAlt) = inserirNovoFO(alocsMap, dataset, estrutura, 
                                                                                    modoRealoc, sonda1, projeto1, modoDebug, bestFitness, bestGastos, bestTotalFree);

            // se for melhor que best
            if (fitnessAlt > bestFitness)
            {
                bestAlocsMap = alocsMapAlt;
                bestFitness = fitnessAlt;
                bestGastos = gastosAlt;
                bestTotalFree = totalFreeAlt;
                parar = 1;
                break;
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    long long tempo = duration.count();
    return std::make_tuple(tempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaSwap1x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug)
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

    int parar = 0;
    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        if (parar == 1) 
        {
            break;
        }
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            if (parar == 1) 
            {
                break;
            }
            Alocacao alocacao1 = *itA1;
            for (std::set<Projeto>::iterator itP1=projetosNaoAloc.begin(); itP1!=projetosNaoAloc.end(); ++itP1)
            {
                if (parar == 1) 
                {
                    break;
                }
                Projeto projeto1 = *itP1;

                // realiza movimento
                std::map<Sonda, std::vector<Alocacao>> alocsMapAlt;
                double fitnessAlt;
                double gastosAlt;
                int totalFreeAlt;
                std::tie(alocsMapAlt, fitnessAlt, gastosAlt, totalFreeAlt) = swap1x1FO(alocsMap, dataset, estrutura, 
                                                                                        modoRealoc, alocacao1, projeto1, modoDebug, bestFitness, bestGastos, bestTotalFree);

                // se melhora FO
                if (fitnessAlt > bestFitness)
                {
                    // substitui bests
                    bestAlocsMap = alocsMapAlt;
                    bestFitness = fitnessAlt;
                    bestGastos = gastosAlt;
                    bestTotalFree = totalFreeAlt;
                    parar = 1;
                    break;
                }
                else if (fitnessAlt >= bestFitness)
                {
                    if (gastosAlt < bestGastos)
                    {
                        // substitui bests
                        bestAlocsMap = alocsMapAlt;
                        bestFitness = fitnessAlt;
                        bestGastos = gastosAlt;
                        bestTotalFree = totalFreeAlt;
                    }
                    else if (totalFreeAlt > bestTotalFree)
                    {
                        // substitui bests
                        bestAlocsMap = alocsMapAlt;
                        bestFitness = fitnessAlt;
                        bestGastos = gastosAlt;
                        bestTotalFree = totalFreeAlt;
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
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug)
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

    int parar = 0;
    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        if (parar == 1) 
        {
            break;
        }
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            if (parar == 1) 
            {
                break;
            }
            Alocacao alocacao1 = *itA1;
            for (std::vector<Alocacao>::iterator itA2=alocsMap[sonda1].begin(); itA2!=alocsMap[sonda1].end(); ++itA2)
            {
                if (parar == 1) 
                {
                    break;
                }
                Alocacao alocacao2 = *itA2;
                if (alocacao1 == alocacao2)
                {
                    continue;
                }
                for (std::set<Projeto>::iterator itP1=projetosNaoAloc.begin(); itP1!=projetosNaoAloc.end(); ++itP1)
                {
                    if (parar == 1) 
                    {
                        break;
                    }
                    Projeto projeto1 = *itP1;

                    // realiza movimento
                    std::map<Sonda, std::vector<Alocacao>> alocsMapAlt;
                    double fitnessAlt;
                    double gastosAlt;
                    int totalFreeAlt;
                    std::tie(alocsMapAlt, fitnessAlt, gastosAlt, totalFreeAlt) = swap2x1FO(alocsMap, dataset, estrutura, 
                                                                                   modoRealoc, alocacao1, alocacao2, projeto1, modoDebug, bestFitness, bestGastos, bestTotalFree);

                    // se melhora FO
                    if (fitnessAlt > bestFitness)
                    {
                        // substitui bests
                        bestAlocsMap = alocsMapAlt;
                        bestFitness = fitnessAlt;
                        bestGastos = gastosAlt;
                        bestTotalFree = totalFreeAlt;
                        parar = 1;
                        break;
                    }
                    else if (fitnessAlt >= bestFitness)
                    {
                        if (gastosAlt < bestGastos)
                        {
                            // substitui bests
                            bestAlocsMap = alocsMapAlt;
                            bestFitness = fitnessAlt;
                            bestGastos = gastosAlt;
                            bestTotalFree = totalFreeAlt;
                        }
                        else if (totalFreeAlt > bestTotalFree)
                        {
                            // substitui bests
                            bestAlocsMap = alocsMapAlt;
                            bestFitness = fitnessAlt;
                            bestGastos = gastosAlt;
                            bestTotalFree = totalFreeAlt;
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
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug)
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

    int parar = 0;
    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        if (parar == 1) 
        {
            break;
        }
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            if (parar == 1) 
            {
                break;
            }
            Alocacao alocacao1 = *itA1;
            for (std::set<Projeto>::iterator itP1=projetosNaoAloc.begin(); itP1!=projetosNaoAloc.end(); ++itP1)
            {
                if (parar == 1) 
                {
                    break;
                }
                Projeto projeto1 = *itP1;
                for (std::set<Projeto>::iterator itP2=projetosNaoAloc.begin(); itP2!=projetosNaoAloc.end(); ++itP2)
                {
                    if (parar == 1) 
                    {
                        break;
                    }
                    Projeto projeto2 = *itP2;
                    if (projeto1 == projeto2)
                    {
                        continue;
                    }
                    // realiza movimento
                    std::map<Sonda, std::vector<Alocacao>> alocsMapAlt;
                    double fitnessAlt;
                    double gastosAlt;
                    int totalFreeAlt;
                    std::tie(alocsMapAlt, fitnessAlt, gastosAlt, totalFreeAlt) = swap1x2FO(alocsMap, dataset, estrutura, 
                                                                                   modoRealoc, alocacao1, projeto1, projeto2, modoDebug, bestFitness, bestGastos, bestTotalFree);

                    // se melhora FO
                    if (fitnessAlt > bestFitness)
                    {
                        // substitui bests
                        bestAlocsMap = alocsMapAlt;
                        bestFitness = fitnessAlt;
                        bestGastos = gastosAlt;
                        bestTotalFree = totalFreeAlt;
                        parar = 1;
                        break;
                    }
                    else if (fitnessAlt >= bestFitness)
                    {
                        if (gastosAlt < bestGastos)
                        {
                            // substitui bests
                            bestAlocsMap = alocsMapAlt;
                            bestFitness = fitnessAlt;
                            bestGastos = gastosAlt;
                            bestTotalFree = totalFreeAlt;
                        }
                        else if (totalFreeAlt > bestTotalFree)
                        {
                            // substitui bests
                            bestAlocsMap = alocsMapAlt;
                            bestFitness = fitnessAlt;
                            bestGastos = gastosAlt;
                            bestTotalFree = totalFreeAlt;
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
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug)
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

    int parar = 0;
    // percorre combinações    
    for (std::set<Sonda>::iterator itS1=sondas.begin(); itS1!=sondas.end(); ++itS1)
    {
        if (parar == 1) 
        {
            break;
        }
        Sonda sonda1 = *itS1;
        if (alocsMap[sonda1].empty())
        {
            continue;
        }
        for (std::vector<Alocacao>::iterator itA1=alocsMap[sonda1].begin(); itA1!=alocsMap[sonda1].end(); ++itA1)
        {
            if (parar == 1) 
            {
                break;
            }
            Alocacao alocacao1 = *itA1;
            for (std::vector<Alocacao>::iterator itA2=alocsMap[sonda1].begin(); itA2!=alocsMap[sonda1].end(); ++itA2)
            {
                if (parar == 1) 
                {
                    break;
                }
                Alocacao alocacao2 = *itA2;
                if (alocacao1 == alocacao2)
                {
                    continue;
                }
                for (std::set<Projeto>::iterator itP1=projetosNaoAloc.begin(); itP1!=projetosNaoAloc.end(); ++itP1)
                {
                    if (parar == 1) 
                    {
                        break;
                    }
                    Projeto projeto1 = *itP1;
                    for (std::set<Projeto>::iterator itP2=projetosNaoAloc.begin(); itP2!=projetosNaoAloc.end(); ++itP2)
                    {
                        if (parar == 1) 
                        {
                            break;
                        }
                        Projeto projeto2 = *itP2;
                        if (projeto1 == projeto2)
                        {
                            continue;
                        }

                        // realiza movimento
                        std::map<Sonda, std::vector<Alocacao>> alocsMapAlt;
                        double fitnessAlt;
                        double gastosAlt;
                        int totalFreeAlt;
                        std::tie(alocsMapAlt, fitnessAlt, gastosAlt, totalFreeAlt) = swap2x2FO(alocsMap, dataset, estrutura, 
                                                                                    modoRealoc, alocacao1, alocacao2, 
                                                                                    projeto1, projeto2, modoDebug, bestFitness, bestGastos, bestTotalFree);

                        // se melhora FO
                        if (fitnessAlt > bestFitness)
                        {
                            // substitui bests
                            bestAlocsMap = alocsMapAlt;
                            bestFitness = fitnessAlt;
                            bestGastos = gastosAlt;
                            bestTotalFree = totalFreeAlt;
                            parar = 1;
                            break;
                        }
                        else if (fitnessAlt >= bestFitness)
                        {
                            if (gastosAlt < bestGastos)
                            {
                                // substitui bests
                                bestAlocsMap = alocsMapAlt;
                                bestFitness = fitnessAlt;
                                bestGastos = gastosAlt;
                                bestTotalFree = totalFreeAlt;
                            }
                            else if (totalFreeAlt > bestTotalFree)
                            {
                                // substitui bests
                                bestAlocsMap = alocsMapAlt;
                                bestFitness = fitnessAlt;
                                bestGastos = gastosAlt;
                                bestTotalFree = totalFreeAlt;
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
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug, std::set<int> vizinhancas, int maxIterFO)
{
    int modoDebugAltoNivel = 0;

    if (modoDebugAltoNivel)
    {
        std::cout << std::endl;
        std::cout << "Realizando busca VND";
        std::cout << std::endl;
    }
    
    // inicializa valores a serem retornados
    double newFitness = 0;
    double newGastos = 0;
    int newTotalFree = 0;
    long long newTempo = 0;

    int countIterFO = 0;

    // inicializa bests
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();
    long long bestTempo = 0;
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;

    // guarda conjunto de vizinhanças inicial
    std::set<int> vizinhancasInit = vizinhancas;

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
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 2)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaShift2x0InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 3)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x1InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 4)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x1InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 5)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x2InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 6)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaReinsercao1IntraRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 7)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaReinsercao2IntraRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 8)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaInserirNovoFO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 9)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x1FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 10)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x1FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 11)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x2FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 12)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x2FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }

        if (modoDebugAltoNivel)
        {
            std::cout << std::endl;
            std::cout << "Movimento realizado" << std::endl;
            std::cout << "best fitness: " << bestFitness << std::endl;
            std::cout << "new fitness: " << newFitness << std::endl;
            std::cout << "best gastos: " << bestGastos << std::endl;
            std::cout << "new gastos: " << newGastos << std::endl;
            std::cout << "best totalFree: " << bestTotalFree << std::endl;
            std::cout << "new totalFree: " << newTotalFree << std::endl;
            std::cout << "contagem sem melhorar FO: " << countIterFO << std::endl;
        }
        
        // se melhora FO
        if ((int)newFitness > (int)bestFitness)
        {
            if (modoDebugAltoNivel)
            {
                std::cout << std::endl << "Melhora fitness" << std::endl;
            }

            if ((newFitness >= 0) && (bestFitness >= 0))
            {
                if ((int)newFitness > (int)(1.01 * bestFitness))
                {
                    if (modoDebugAltoNivel)
                    {
                        std::cout << std::endl << "Reinicializa vizinhanças" << std::endl;
                    }
                    
                    // reinicializa conjunto de vizinhanças
                    vizinhancas = vizinhancasInit;
                }
            }
            else if ((newFitness >= 0) && (bestFitness < 0))
            {
                if ((int)newFitness > (int)(bestFitness))
                {
                    if (modoDebugAltoNivel)
                    {
                        std::cout << std::endl << "Reinicializa vizinhanças" << std::endl;
                    }

                    // reinicializa conjunto de vizinhanças
                    vizinhancas = vizinhancasInit;
                }
            }
            else if ((newFitness < 0) && (bestFitness >= 0))
            {
                if ((int)newFitness > (int)(bestFitness))
                {
                    if (modoDebugAltoNivel)
                    {
                        std::cout << std::endl << "Reinicializa vizinhanças" << std::endl;
                    }

                    // reinicializa conjunto de vizinhanças
                    vizinhancas = vizinhancasInit;
                }
            }
            else if ((newFitness < 0) && (bestFitness < 0))
            {
                if ((int)newFitness > (int)(bestFitness))
                {
                    if (modoDebugAltoNivel)
                    {
                        std::cout << std::endl << "Reinicializa vizinhanças" << std::endl;
                    }

                    // reinicializa conjunto de vizinhanças
                    vizinhancas = vizinhancasInit;
                }
            }

            // substitui bests
            bestAlocsMap = alocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;

            countIterFO = 0;
        }
        else if ((int)newFitness >= (int)bestFitness)
        {
            if (modoDebugAltoNivel)
            {
                std::cout << std::endl << "Não melhora fitness, mas não piora." << std::endl;
            }
            
            countIterFO++;
            if ((int)newGastos < (int)bestGastos)
            {
                if (modoDebugAltoNivel)
                {
                   std::cout << std::endl << "Melhora gastos" << std::endl; 
                }
                
                // reinicializa conjunto de vizinhanças
                if (countIterFO <= maxIterFO)
                {
                    if ((int)newGastos < (int)(0.99 * bestGastos))
                    {
                        if (modoDebugAltoNivel)
                        {
                            std::cout << std::endl << "reinicializa vizinhanças" << std::endl;
                        }
                        
                        vizinhancas = vizinhancasInit;
                    }
                }
        
                // substitui bests
                bestAlocsMap = alocsMap;
                bestFitness = newFitness;
                bestGastos = newGastos;
                bestTempo = newTempo;
                bestTotalFree = newTotalFree;
            }
            else if ((int)newTotalFree > (int)bestTotalFree)
            {
                if (modoDebugAltoNivel)
                {
                    std::cout << std::endl << "Melhora totalFree" << std::endl;
                }
                
                // reinicializa conjunto de vizinhanças
                if (countIterFO <= maxIterFO)
                {
                    if (modoDebugAltoNivel)
                    {
                       std::cout << std::endl << "reinicializa vizinhanças" << std::endl; 
                    }
                    
                    vizinhancas = vizinhancasInit;
                }
        
                // substitui bests
                bestAlocsMap = alocsMap;
                bestFitness = newFitness;
                bestGastos = newGastos;
                bestTempo = newTempo;
                bestTotalFree = newTotalFree;
            }
        }
        else
        {
            if (modoDebugAltoNivel)
            {
                std::cout << std::endl << "Piora fitness" << std::endl;
            }
            
            countIterFO++;
        }
    }
    return std::make_tuple(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaVNDTosco(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                   DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug, std::set<int> vizinhancas, int maxIterFO)
{
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

    // guarda conjunto de vizinhanças inicial
    std::set<int> vizinhancasInit = vizinhancas;

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
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 2)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaShift2x0InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 3)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x1InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 4)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x1InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 5)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x2InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 6)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaReinsercao1IntraRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 7)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaReinsercao2IntraRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 8)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaInserirNovoFO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 9)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x1FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 10)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x1FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 11)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x2FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 12)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x2FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }

        // se melhora FO
        if (newFitness > bestFitness)
        {
            // substitui bests
            bestAlocsMap = alocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;
        }
        else if (newFitness >= bestFitness)
        {
            if (newGastos < bestGastos)
            {
                // substitui bests
                bestAlocsMap = alocsMap;
                bestFitness = newFitness;
                bestGastos = newGastos;
                bestTempo = newTempo;
                bestTotalFree = newTotalFree;
            }
            else if (newTotalFree > bestTotalFree)
            {
                // substitui bests
                bestAlocsMap = alocsMap;
                bestFitness = newFitness;
                bestGastos = newGastos;
                bestTempo = newTempo;
                bestTotalFree = newTotalFree;
            }
        }
    }
    return std::make_tuple(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaRVND(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug, std::set<int> vizinhancas, int maxIterFO)
{
    int modoDebugAltoNivel = 0;

    if (modoDebugAltoNivel)
    {
        std::cout << std::endl;
        std::cout << "Realizando busca RVND";
        std::cout << std::endl;
    }
    
    // inicializa valores a serem retornados
    double newFitness = 0;
    double newGastos = 0;
    int newTotalFree = 0;
    long long newTempo = 0;

    int countIterFO = 0;

    // inicializa bests
    Solucao bestSolucao{alocsMap, estrutura, dataset};
    double bestFitness = bestSolucao.getFitness();
    double bestGastos = bestSolucao.getGastos();
    int bestTotalFree = bestSolucao.getTotalFree();
    long long bestTempo = 0;
    std::map<Sonda, std::vector<Alocacao>> bestAlocsMap = alocsMap;

    // guarda conjunto de vizinhanças inicial
    std::set<int> vizinhancasInit = vizinhancas;

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
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 2)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaShift2x0InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 3)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x1InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 4)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x1InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 5)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x2InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 6)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaReinsercao1IntraRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 7)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaReinsercao2IntraRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 8)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaInserirNovoFO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 9)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x1FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 10)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x1FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 11)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x2FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 12)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x2FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }

        if (modoDebugAltoNivel)
        {
            std::cout << std::endl;
            std::cout << "Movimento realizado" << std::endl;
            std::cout << "best fitness: " << bestFitness << std::endl;
            std::cout << "new fitness: " << newFitness << std::endl;
            std::cout << "best gastos: " << bestGastos << std::endl;
            std::cout << "new gastos: " << newGastos << std::endl;
            std::cout << "best totalFree: " << bestTotalFree << std::endl;
            std::cout << "new totalFree: " << newTotalFree << std::endl;
            std::cout << "contagem sem melhorar FO: " << countIterFO << std::endl;
        }
        
        // se melhora FO
        if ((int)newFitness > (int)bestFitness)
        {
            if (modoDebugAltoNivel)
            {
                std::cout << std::endl << "Melhora fitness" << std::endl;
            }

            if ((newFitness >= 0) && (bestFitness >= 0))
            {
                if ((int)newFitness > (int)(1.01 * bestFitness))
                {
                    if (modoDebugAltoNivel)
                    {
                        std::cout << std::endl << "Reinicializa vizinhanças" << std::endl;
                    }
                    
                    // reinicializa conjunto de vizinhanças
                    vizinhancas = vizinhancasInit;
                }
            }
            else if ((newFitness >= 0) && (bestFitness < 0))
            {
                if ((int)newFitness > (int)(bestFitness))
                {
                    if (modoDebugAltoNivel)
                    {
                        std::cout << std::endl << "Reinicializa vizinhanças" << std::endl;
                    }

                    // reinicializa conjunto de vizinhanças
                    vizinhancas = vizinhancasInit;
                }
            }
            else if ((newFitness < 0) && (bestFitness >= 0))
            {
                if ((int)newFitness > (int)(bestFitness))
                {
                    if (modoDebugAltoNivel)
                    {
                        std::cout << std::endl << "Reinicializa vizinhanças" << std::endl;
                    }

                    // reinicializa conjunto de vizinhanças
                    vizinhancas = vizinhancasInit;
                }
            }
            else if ((newFitness < 0) && (bestFitness < 0))
            {
                if ((int)newFitness > (int)(bestFitness))
                {
                    if (modoDebugAltoNivel)
                    {
                        std::cout << std::endl << "Reinicializa vizinhanças" << std::endl;
                    }
                    
                    // reinicializa conjunto de vizinhanças
                    vizinhancas = vizinhancasInit;
                }
            }

            // substitui bests
            bestAlocsMap = alocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;

            countIterFO = 0;
        }
        else if ((int)newFitness >= (int)bestFitness)
        {
            if (modoDebugAltoNivel)
            {
                std::cout << std::endl << "Não melhora fitness, mas não piora." << std::endl;
            }
            
            countIterFO++;
            if ((int)newGastos < (int)bestGastos)
            {
                if (modoDebugAltoNivel)
                {
                   std::cout << std::endl << "Melhora gastos" << std::endl; 
                }
                
                // reinicializa conjunto de vizinhanças
                if (countIterFO <= maxIterFO)
                {
                    if ((int)newGastos < (int)(0.99 * bestGastos))
                    {
                        if (modoDebugAltoNivel)
                        {
                            std::cout << std::endl << "reinicializa vizinhanças" << std::endl;
                        }
                        
                        vizinhancas = vizinhancasInit;
                    }
                }
        
                // substitui bests
                bestAlocsMap = alocsMap;
                bestFitness = newFitness;
                bestGastos = newGastos;
                bestTempo = newTempo;
                bestTotalFree = newTotalFree;
            }
            else if ((int)newTotalFree > (int)bestTotalFree)
            {
                if (modoDebugAltoNivel)
                {
                    std::cout << std::endl << "Melhora totalFree" << std::endl;
                }
                
                // reinicializa conjunto de vizinhanças
                if (countIterFO <= maxIterFO)
                {
                    if (modoDebugAltoNivel)
                    {
                       std::cout << std::endl << "reinicializa vizinhanças" << std::endl; 
                    }
                    
                    vizinhancas = vizinhancasInit;
                }
        
                // substitui bests
                bestAlocsMap = alocsMap;
                bestFitness = newFitness;
                bestGastos = newGastos;
                bestTempo = newTempo;
                bestTotalFree = newTotalFree;
            }
        }
        else
        {
            if (modoDebugAltoNivel)
            {
                std::cout << std::endl << "Piora fitness" << std::endl;
            }
            
            countIterFO++;
        }
    }
    return std::make_tuple(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaRVNDTosco(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                            DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int modoDebug, std::set<int> vizinhancas, int maxIterFO)
{
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

    // guarda conjunto de vizinhanças inicial
    std::set<int> vizinhancasInit = vizinhancas;

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
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 2)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaShift2x0InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 3)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x1InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 4)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x1InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 5)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x2InterRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 6)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaReinsercao1IntraRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 7)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaReinsercao2IntraRota(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 8)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaInserirNovoFO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 9)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x1FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 10)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x1FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 11)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x2FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }
        else if (vizinhanca == 12)
        {
            std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x2FO(
                                                alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
        }

        // se melhora FO
        if (newFitness > bestFitness)
        {
            // substitui bests
            bestAlocsMap = alocsMap;
            bestFitness = newFitness;
            bestGastos = newGastos;
            bestTempo = newTempo;
            bestTotalFree = newTotalFree;
        }
        else if (newFitness >= bestFitness)
        {
            if (newGastos < bestGastos)
            {
                // substitui bests
                bestAlocsMap = alocsMap;
                bestFitness = newFitness;
                bestGastos = newGastos;
                bestTempo = newTempo;
                bestTotalFree = newTotalFree;
            }
            else if (newTotalFree > bestTotalFree)
            {
                // substitui bests
                bestAlocsMap = alocsMap;
                bestFitness = newFitness;
                bestGastos = newGastos;
                bestTempo = newTempo;
                bestTotalFree = newTotalFree;
            }
        }
    }
    return std::make_tuple(bestTempo, bestAlocsMap, bestFitness, bestGastos, bestTotalFree);
}

std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> MovimentadorEmVizinhancas::buscaLocal(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                          DadosDeEntrada dataset, int estrutura, int modoRealoc, int deltaT, int vizinhanca, int modoDebug, std::set<int> vizinhancas, int maxIterFO)
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
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
    }
    else if (vizinhanca == 2)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaShift2x0InterRota(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
    }
    else if (vizinhanca == 3)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x1InterRota(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
    }
    else if (vizinhanca == 4)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x1InterRota(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
    }
    else if (vizinhanca == 5)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x2InterRota(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
    }
    else if (vizinhanca == 6)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaReinsercao1IntraRota(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
    }
    else if (vizinhanca == 7)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaReinsercao2IntraRota(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
    }
    else if (vizinhanca == 8)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaInserirNovoFO(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
    }
    else if (vizinhanca == 9)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x1FO(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
    }
    else if (vizinhanca == 10)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x1FO(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
    }
    else if (vizinhanca == 11)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap1x2FO(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
    }
    else if (vizinhanca == 12)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaSwap2x2FO(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug);
    }
    else if (vizinhanca == 13)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaVND(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug, vizinhancas, maxIterFO);
    }
    else if (vizinhanca == 14)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaRVND(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug, vizinhancas, maxIterFO);
    }
    else if (vizinhanca == 15)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaVNDTosco(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug, vizinhancas, maxIterFO);
    }
    else if (vizinhanca == 16)
    {
        std::tie(newTempo, alocsMap, newFitness, newGastos, newTotalFree) = buscaRVNDTosco(
                                            alocsMap, dataset, estrutura, modoRealoc, dataset.getDelta(), modoDebug, vizinhancas, maxIterFO);
    }
    return std::make_tuple(newTempo, alocsMap, newFitness, newGastos, newTotalFree);
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaShift1x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();

    double fitness = solucaoLocal.getFitness();
    double gastos = solucaoLocal.getGastos();
    int totalFree = solucaoLocal.getTotalFree();
    
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
            std::tie(alocsMap, fitness, gastos, totalFree) = shift1x0InterRota(alocsMap, dataset, estrutura, modoRealoc, alocacao1, sonda2, modoDebug, fitness, gastos, totalFree);

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaShift2x0InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();

    double fitness = solucaoLocal.getFitness();
    double gastos = solucaoLocal.getGastos();
    int totalFree = solucaoLocal.getTotalFree();
    
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
            std::tie(alocsMap, fitness, gastos, totalFree) = shift2x0InterRota(alocsMap, dataset, estrutura, modoRealoc, alocacao1, alocacao2, sonda2, modoDebug, fitness, gastos, totalFree);

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaSwap1x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();

    double fitness = solucaoLocal.getFitness();
    double gastos = solucaoLocal.getGastos();
    int totalFree = solucaoLocal.getTotalFree();
    
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
            std::tie(alocsMap, fitness, gastos, totalFree) = swap1x1InterRota(alocsMap, dataset, estrutura, modoRealoc, alocacao1, alocacao2, modoDebug, fitness, gastos, totalFree);

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaSwap2x1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();

    double fitness = solucaoLocal.getFitness();
    double gastos = solucaoLocal.getGastos();
    int totalFree = solucaoLocal.getTotalFree();
    
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
            std::tie(alocsMap, fitness, gastos, totalFree) = swap2x1InterRota(alocsMap, dataset, estrutura, modoRealoc, alocacao1, alocacao2, alocacao3, modoDebug, fitness, gastos, totalFree);

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaSwap2x2InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();

    double fitness = solucaoLocal.getFitness();
    double gastos = solucaoLocal.getGastos();
    int totalFree = solucaoLocal.getTotalFree();
    
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
            std::tie(alocsMap, fitness, gastos, totalFree) = swap2x1InterRota(alocsMap, dataset, estrutura, modoRealoc, alocacao1, alocacao2, alocacao3, modoDebug, fitness, gastos, totalFree);

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaReinsercao1InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();

    double fitness = solucaoLocal.getFitness();
    double gastos = solucaoLocal.getGastos();
    int totalFree = solucaoLocal.getTotalFree();
    
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
            std::tie(alocsMap, fitness, gastos, totalFree) = reinsercao1InterRota(alocsMap, dataset, estrutura, modoRealoc, alocacao1, modoDebug, fitness, gastos, totalFree);

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaReinsercao2InterRota(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();

    double fitness = solucaoLocal.getFitness();
    double gastos = solucaoLocal.getGastos();
    int totalFree = solucaoLocal.getTotalFree();
    
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
            std::tie(alocsMap, fitness, gastos, totalFree) = reinsercao2InterRota(alocsMap, dataset, estrutura, modoRealoc, alocacao1, alocacao2, modoDebug, fitness, gastos, totalFree);

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaInserirNovoFO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();

    double fitness = -1;
    double gastos = solucaoLocal.getGastos();
    int totalFree = solucaoLocal.getTotalFree();

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
            std::tie(alocsMap, fitness, gastos, totalFree) = inserirNovoFO(alocsMap, dataset, estrutura, modoRealoc, sonda1, projeto1, modoDebug, fitness, gastos, totalFree);

            // incrementa count
            count++;
        }
        return alocsMap;
    }
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaSwap1x1FO(std::map<Sonda, std::vector<Alocacao>> alocsMap, 
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();

    double fitness = -1;
    double gastos = solucaoLocal.getGastos();
    int totalFree = solucaoLocal.getTotalFree();

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
            std::tie(alocsMap, fitness, gastos, totalFree) = swap1x1FO(alocsMap, dataset, estrutura, modoRealoc, alocacao1, projeto1, modoDebug, fitness, gastos, totalFree);

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
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();

    double fitness = -1;
    double gastos = solucaoLocal.getGastos();
    int totalFree = solucaoLocal.getTotalFree();

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
            std::tie(alocsMap, fitness, gastos, totalFree) = swap2x1FO(alocsMap, dataset, estrutura, modoRealoc, alocacao1, alocacao2, projeto1, modoDebug, fitness, gastos, totalFree);

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
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();

    double fitness = -1;
    double gastos = solucaoLocal.getGastos();
    int totalFree = solucaoLocal.getTotalFree();

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
            std::tie(alocsMap, fitness, gastos, totalFree) = swap1x2FO(alocsMap, dataset, estrutura, modoRealoc, alocacao1, projeto1, projeto2, modoDebug, fitness, gastos, totalFree);

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
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug)
{
    // inicializa conjunto de sondas
    Solucao solucaoLocal{alocsMap, estrutura, dataset};
    std::set<Sonda> sondas = solucaoLocal.getSondas();

    double fitness = -1;
    double gastos = solucaoLocal.getGastos();
    int totalFree = solucaoLocal.getTotalFree();

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
            std::tie(alocsMap, fitness, gastos, totalFree) = swap2x2FO(alocsMap, dataset, estrutura, modoRealoc, alocacao1, alocacao2, projeto1, projeto2, modoDebug, fitness, gastos, totalFree);

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
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, int k, int modoDebug, std::set<int> vizinhancas)
{
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
            alocsMap = perturbaShift1x0InterRota(alocsMap, dataset, estrutura, modoRealoc, 1, modoDebug);
        }
        else if (vizinhanca == 2)
        {
            alocsMap = perturbaShift2x0InterRota(alocsMap, dataset, estrutura, modoRealoc, 1, modoDebug);
        }
        else if (vizinhanca == 3)
        {
            alocsMap = perturbaSwap1x1InterRota(alocsMap, dataset, estrutura, modoRealoc, 1, modoDebug);
        }
        else if (vizinhanca == 4)
        {
            alocsMap = perturbaSwap2x1InterRota(alocsMap, dataset, estrutura, modoRealoc, 1, modoDebug);
        }
        else if (vizinhanca == 5)
        {
            alocsMap = perturbaSwap2x2InterRota(alocsMap, dataset, estrutura, modoRealoc, 1, modoDebug);
        }
        else if (vizinhanca == 6)
        {
            alocsMap = perturbaReinsercao1InterRota(alocsMap, dataset, estrutura, modoRealoc, 1, modoDebug);
        }
        else if (vizinhanca == 7)
        {
            alocsMap = perturbaReinsercao2InterRota(alocsMap, dataset, estrutura, modoRealoc, 1, modoDebug);
        }
        else if (vizinhanca == 8)
        {
            alocsMap = perturbaInserirNovoFO(alocsMap, dataset, estrutura, modoRealoc, 1, modoDebug);
        }
        else if (vizinhanca == 9)
        {
            alocsMap = perturbaSwap1x1FO(alocsMap, dataset, estrutura, modoRealoc, 1, modoDebug);
        }
        else if (vizinhanca == 10)
        {
            alocsMap = perturbaSwap2x1FO(alocsMap, dataset, estrutura, modoRealoc, 1, modoDebug);
        }
        else if (vizinhanca == 11)
        {
            alocsMap = perturbaSwap1x2FO(alocsMap, dataset, estrutura, modoRealoc, 1, modoDebug);
        }
        else if (vizinhanca == 12)
        {
            alocsMap = perturbaSwap2x2FO(alocsMap, dataset, estrutura, modoRealoc, 1, modoDebug);
        }

        // contabiliza movimento feito
        count++;
    }
    return alocsMap;
}

std::map<Sonda, std::vector<Alocacao>> MovimentadorEmVizinhancas::perturbaSolucao(std::map<Sonda, std::vector<Alocacao>> alocsMap,
                                                                DadosDeEntrada dataset, int estrutura, int modoRealoc, 
                                                                int k, int vizinhanca, int modoDebug, std::set<int> vizinhancas)
{
    if (vizinhanca == 1)
    {
        alocsMap = perturbaShift1x0InterRota(alocsMap, dataset, estrutura, modoRealoc, k, modoDebug);
    }
    else if (vizinhanca == 2)
    {
        alocsMap = perturbaShift2x0InterRota(alocsMap, dataset, estrutura, modoRealoc, k, modoDebug);
    }
    else if (vizinhanca == 3)
    {
        alocsMap = perturbaSwap1x1InterRota(alocsMap, dataset, estrutura, modoRealoc, k, modoDebug);
    }
    else if (vizinhanca == 4)
    {
        alocsMap = perturbaSwap2x1InterRota(alocsMap, dataset, estrutura, modoRealoc, k, modoDebug);
    }
    else if (vizinhanca == 5)
    {
        alocsMap = perturbaSwap2x2InterRota(alocsMap, dataset, estrutura, modoRealoc, k, modoDebug);
    }
    else if (vizinhanca == 6)
    {
        alocsMap = perturbaReinsercao1InterRota(alocsMap, dataset, estrutura, modoRealoc, k, modoDebug);
    }
    else if (vizinhanca == 7)
    {
        alocsMap = perturbaReinsercao2InterRota(alocsMap, dataset, estrutura, modoRealoc, k, modoDebug);
    }
    else if (vizinhanca == 8)
    {
        alocsMap = perturbaInserirNovoFO(alocsMap, dataset, estrutura, modoRealoc, k, modoDebug);
    }
    else if (vizinhanca == 9)
    {
        alocsMap = perturbaSwap1x1FO(alocsMap, dataset, estrutura, modoRealoc, k, modoDebug);
    }
    else if (vizinhanca == 10)
    {
        alocsMap = perturbaSwap2x1FO(alocsMap, dataset, estrutura, modoRealoc, k, modoDebug);
    }
    else if (vizinhanca == 11)
    {
        alocsMap = perturbaSwap1x2FO(alocsMap, dataset, estrutura, modoRealoc, k, modoDebug);
    }
    else if (vizinhanca == 12)
    {
        alocsMap = perturbaSwap2x2FO(alocsMap, dataset, estrutura, modoRealoc, k, modoDebug);
    }
    else if (vizinhanca == 13)
    {
        alocsMap = perturbaAleatorio(alocsMap, dataset, estrutura, modoRealoc, k, modoDebug, vizinhancas);
    }
    return alocsMap;
}

