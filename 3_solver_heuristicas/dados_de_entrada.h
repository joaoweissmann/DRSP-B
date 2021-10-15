
#include <bits/stdc++.h>

using namespace std;

#pragma once

// classe para dados de entrada
class DadosEntrada
{
    public:

        // membros
        int n_projetos, n_sondas, n_periodos;
        int propriedades_proj, propriedades_sondas;
        int t_init, t_final, delta;
        double capital_total;
        vector<vector<double>> projetos;
        vector<vector<double>> sondas;
        vector<vector<double>> desloc;
        map<string, int> mapProjetos, mapSondas;

        // metodos
        DadosEntrada(string);
        void printDadosEntrada();
};

