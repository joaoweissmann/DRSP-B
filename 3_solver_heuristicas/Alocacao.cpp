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
#include "Alocacao.h"

Alocacao::Alocacao()
{
    _projeto = Projeto{};
    _sonda = Sonda{};
    _intervalo = Intervalo{};
}

Alocacao::Alocacao(Projeto projeto, Sonda sonda, Intervalo intervalo)
{
    _projeto = Projeto{};
    _sonda = Sonda{};
    _intervalo = Intervalo{};

    _projeto.copyFrom(projeto);
    _sonda.copyFrom(sonda);
    _intervalo.copyFrom(intervalo);
}

Projeto Alocacao::getProjeto()
{
    return _projeto;
}

Sonda Alocacao::getSonda()
{
    return _sonda;
}

Intervalo Alocacao::getIntervalo()
{
    return _intervalo;
}

void Alocacao::setProjeto(Projeto projeto)
{
    _projeto.copyFrom(projeto);
}

void Alocacao::setSonda(Sonda sonda)
{
    _sonda.copyFrom(sonda);
}

void Alocacao::setIntervalo(Intervalo intervalo)
{
    _intervalo.copyFrom(intervalo);
}

void Alocacao::print()
{
    std::cout << std::endl;
    std::cout << "A alocação tem:" << std::endl;
    _projeto.print();
    _sonda.print();
    _intervalo.print();
    std::cout << std::endl;
}

