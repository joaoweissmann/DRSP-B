#ifndef TESTADOR_H
#define TESTADOR_H

#include <bits/stdc++.h>
#include "Projeto.h"
#include "Sonda.h"
#include "CalculadorDeDesloc.h"
#include "DadosDeEntrada.h"
#include "LeitorDeDados.h"

class Testador
{
    public:
        void testarProjeto();
        void testarSonda();
        void testarCalculadorDeDesloc();
        void testarDadosDeEntrada();
        void testarLeitorDeDados();
};

#endif