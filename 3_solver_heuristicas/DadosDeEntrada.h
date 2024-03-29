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

#ifndef DADOS_DE_ENTRADA_H
#define DADOS_DE_ENTRADA_H

#include <bits/stdc++.h>
#include "Sonda.h"
#include "Projeto.h"

class DadosDeEntrada
{
    private:
        int _nProjetos, _nSondas, _nPeriodos;
        int _propriedadesProj, _propriedadesSondas;
        int _tInit, _tFinal, _delta;
        double _capitalTotal;
        std::vector<Projeto> _projetos;
        std::vector<Sonda> _sondas;
        std::vector<std::vector<double>> _desloc;
    public:
        DadosDeEntrada();
        DadosDeEntrada(int, int, int, int, int, int, int, int, double, 
                        std::vector<Projeto>, std::vector<Sonda>, std::vector<std::vector<double>>);
        
        int getNProjetos();
        int getNSondas();
        int getNPeriodos();
        int getPropriedadesProj();
        int getPropriedadesSondas();
        int getTInit();
        int getTFinal();
        int getDelta();
        double getCapitalTotal();
        std::vector<Projeto> getProjetos();
        Projeto getProjeto(int);
        std::vector<Sonda> getSondas();
        Sonda getSonda(int);
        std::vector<std::vector<double>> getDesloc();
        double getDesloc(Sonda, Projeto);
        double getDesloc(Projeto, Projeto);
        double getDeslocIdx2Idx(int, int);
        double getDeslocSonda2Proj(int, int);
        double getDeslocProj2Proj(int, int);
        
        void setNProjetos(int);
        void setNSondas(int);
        void setNPeriodos(int);
        void setPropriedadesProj(int);
        void setPropriedadesSondas(int);
        void setTInit(int);
        void setTFinal(int);
        void setDelta(int);
        void setCapitalTotal(double);
        void setProjetos(std::vector<Projeto>);
        void setProjeto(Projeto, int);
        void setSondas(std::vector<Sonda>);
        void setSonda(Sonda, int);
        void setDesloc(std::vector<std::vector<double>>);
        void setDesloc(Sonda, Projeto, double);
        void setDesloc(Projeto, Projeto, double);
        void setDeslocIdx2Idx(int, int, double);
        void setDeslocSonda2Proj(int, int, double);
        void setDeslocProj2Proj(int, int, double);

        void print();
};

#endif