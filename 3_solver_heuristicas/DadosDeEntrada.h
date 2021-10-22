

#include <bits/stdc++.h>

#pragma once

class DadosDeEntrada
{
    private:
        // TODO: colocar membros como privados
    public:

        int n_projetos, n_sondas, n_periodos;
        int propriedades_proj, propriedades_sondas;
        int t_init, t_final, delta;
        double capital_total;
        std::vector<std::vector<double>> projetos;
        std::vector<std::vector<double>> sondas;
        std::vector<std::vector<double>> desloc;
        std::map<std::string, int> mapProjetos, mapSondas;

        // TODO: construtor default
        // TODO: gets e sets
        
        // TODO: jogar esses métodos para outra classe
        DadosDeEntrada(std::string);
        void printDadosEntrada();
};

