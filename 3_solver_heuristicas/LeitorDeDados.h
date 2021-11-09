

#include <bits/stdc++.h>
#include "DadosDeEntrada.h"

#pragma once

class LeitorDeDados
{
    private:
        std::map <int, std::string> _mapProjPropIdx;
        std::map <int, std::string> _mapSondasPropIdx;
    public:
        LeitorDeDados();
        DadosDeEntrada lerDadosDeEntrada(std::string);
};

