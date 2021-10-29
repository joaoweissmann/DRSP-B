// TODO: debug mode


#include <bits/stdc++.h>

#pragma once

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
        std::map <std::string, int> _mapPropIdx;
    public:
        // construtores
        Projeto();
        Projeto(double, double, int, int, int, int, int, double,
                double, double, double, double, double, double,
                double, double, double, double, double, double,
                int, int, int);

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
        std::map<std::string, int> getMapPropIdx();
        int getPropIdx(std::string);

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

