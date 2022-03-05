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

#ifndef PROJETO_H
#define PROJETO_H

#include <bits/stdc++.h>

class Projeto
{
    private:
        double _coordX;
        double _coordY;
        int _bacia;
        int _nome;
        int _maturidade;
        int _qualidade;
        int _play;
        double _soterramento;
        double _pcgna;
        double _geracao;
        double _migracao;
        double _reservatorio;
        double _geometria;
        double _retencao;
        double _pshc;
        double _mcVol;
        double _miVol;
        double _mcVpl;
        double _miVpl;
        double _custo;
        int _tempExec;
        int _inicioJanela;
        int _finalJanela;
    public:
        // construtores
        Projeto();
        Projeto(double, double, int, int, int, int, int, double,
                double, double, double, double, double, double,
                double, double, double, double, double, double,
                int, int, int);

        bool operator==(const Projeto & p) const;

        bool operator<(const Projeto & p) const;
        
        void copyFrom(Projeto);

        // gets
        double getCoordX();
        double getCoordY();
        int getBacia();
        int getNome();
        int getMaturidade();
        int getQualidade();
        int getPlay();
        double getSoterramento();
        double getPcgna();
        double getGeracao();
        double getMigracao();
        double getReservatorio();
        double getGeometria();
        double getRetencao();
        double getPshc();
        double getMcVol();
        double getMiVol();
        double getMcVpl();
        double getMiVpl();
        double getCusto();
        int getTempExec();
        int getInicioJanela();
        int getFinalJanela();

        // sets
        void setCoordX(double);
        void setCoordY(double);
        void setBacia(int);
        void setNome(int);
        void setMaturidade(int);
        void setQualidade(int);
        void setPlay(int);
        void setSoterramento(double);
        void setPcgna(double);
        void setGeracao(double);
        void setMigracao(double);
        void setReservatorio(double);
        void setGeometria(double);
        void setRetencao(double);
        void setPshc(double);
        void setMcVol(double);
        void setMiVol(double);
        void setMcVpl(double);
        void setMiVpl(double);
        void setCusto(double);
        void setTempExec(int);
        void setInicioJanela(int);
        void setFinalJanela(int);

        // outros
        void print();
};

#endif