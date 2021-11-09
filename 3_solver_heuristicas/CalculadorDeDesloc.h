#ifndef CALCULADOR_DE_DESLOC_H
#define CALCULADOR_DE_DESLOC_H

#include <bits/stdc++.h>
#include "Sonda.h"
#include "Projeto.h"

class CalculadorDeDesloc
{
    public:
        double getDesloc(Sonda, Sonda);
        double getDesloc(Sonda, Projeto);
        double getDesloc(Projeto, Sonda);
        double getDesloc(Projeto, Projeto);
};

#endif