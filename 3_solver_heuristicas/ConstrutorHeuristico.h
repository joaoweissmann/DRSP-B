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

#ifndef CONSTRUTOR_HEURISTICO
#define CONSTRUTOR_HEURISTICO

#include <bits/stdc++.h>
#include "Solucao.h"

class ConstrutorHeuristico
{
    private:
        double _alpha;
        int _criterio;
            // criterio = 1 -> lucro/custo : maior melhor
            // criterio = 2 -> lucro : maior melhor
            // criterio = 3 -> lucro/duração : maior melhor
            // criterio = 4 -> duração : menor melhor
        int _estrutura;
            // estrutura = 1 -> vector
            // estrutura = 2 -> list
        int _modoRealoc;
            // modoRealoc = 0 -> sem realocações
            // modoRealoc = 1 -> com realocações

    public:
        ConstrutorHeuristico();
        ConstrutorHeuristico(double alpha, int criterio, int estrutura, int modoRealoc);

        double getAlpha();
        int getCriterio();
        int getEstrutura();
        int getModoRealoc();

        void setAlpha(double alpha);
        void setCriterio(int criterio);
        void setEstrutura(int estrutura);
        void setModoRealoc(int modoRealoc);

        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> ConstruirSolucao(DadosDeEntrada dataset, int modoDebug);
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> ConstruirSolucao(DadosDeEntrada dataset, std::map<Sonda, std::vector<Alocacao>> alocacoes, int modoDebug);
};

#endif

