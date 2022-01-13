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

#include <bits/stdc++.h>
#include "DadosDeEntrada.h"

#ifndef LEITOR_DE_DADOS
#define LEITOR_DE_DADOS

class LeitorDeDados
{
    private:
        std::map <int, int> _mapProjPropIdx;
        std::map <int, int> _mapSondasPropIdx;
    public:
        LeitorDeDados();
        DadosDeEntrada lerDadosDeEntrada(std::string);
};

#endif

