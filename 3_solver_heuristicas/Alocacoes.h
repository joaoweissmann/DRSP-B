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

#ifndef ALOCACOES
#define ALOCACOES

#include <bits/stdc++.h>
#include "Alocacao.h"

class Alocacoes
{
    public:
        
        virtual int getNSondas() = 0;
        virtual std::set<Sonda> getSondas() = 0;
        
        virtual std::map<Sonda, std::vector<Alocacao>> getAlocacoes() = 0;
        virtual std::vector<Alocacao> getAlocacoes(Sonda) = 0;
        
        virtual int getNAlocacoes(Sonda) = 0;
        virtual Alocacao getAlocacao(Sonda, int) = 0;
        virtual Alocacao getAlocacao(Sonda, Projeto) = 0;
        virtual int getAlocacaoIndex(Sonda, Projeto) = 0;
        
        virtual void setAlocacoes(std::map<Sonda, std::vector<Alocacao>>) = 0;
        virtual void setAlocacoes(Sonda, std::vector<Alocacao>) = 0;

        virtual std::tuple<bool, int, Intervalo, int, int, int, int, int> buscarJanelaViavel(Sonda, Projeto, int) = 0;

        virtual void inserirProjeto(Sonda, Projeto, int, Intervalo, int, int, int, int, int) = 0;

        /*

        virtual std::tuple<> removerProjeto(Sonda, int) = 0;

        */
};

#endif

