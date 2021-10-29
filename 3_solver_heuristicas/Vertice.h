// TODO: debug mode


#include <bits/stdc++.h>
#include "Sonda.h"
#include "Projeto.h"

#pragma once

class Vertice
{
    private:
        int _nSondas;
        int _nProjetos;
    public:
        Vertice();
        Vertice(int, int);
        int getNSondas();
        int getNProjetos();
        void setNSondas(int);
        void setNProjetos(int);
        int getVerticeIndex(Sonda);
        int getVerticeIndex(Projeto);
        int getVerticeIndexBySonda(int);
        int getVerticeIndexByProjeto(int);
};

