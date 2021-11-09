

#include <bits/stdc++.h>
#include "DadosDeEntrada.h"

#pragma once

class LeitorDeDados
{
    private:
        std::map <std::string, int> _mapPropIdx;
        std::map<std::string, int> _mapPropIdx;
    public:
        LeitorDeDados();
        DadosDeEntrada lerDadosDeEntrada(std::string);
};

