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
#include "Intervalo.h"

Intervalo::Intervalo()
{
    _inicio = 0;
    _final = 0;
}

Intervalo::Intervalo(int inicio, int final)
{
    if (inicio < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "inicio < 0" << std::endl;
        std::cout << "Valor fornecido: " << inicio << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert (inicio >= 0);

    if (final < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "final < 0" << std::endl;
        std::cout << "Valor fornecido: " << final << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert (final >= 0);

    if (inicio > final)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "inicio > final" << std::endl;
        std::cout << "Valores fornecido (inicio, final): " << inicio << "," << final << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert (inicio <= final);

    _inicio = inicio;
    _final = final;
}

bool Intervalo::operator==(const Intervalo & i) const
{
    bool x1 = this->_inicio == i._inicio;
    bool x2 = this->_final == i._final;
    return x1 && x2;
}

int Intervalo::getInicio()
{
    return _inicio;
}

int Intervalo::getFinal()
{
    return _final;
}

void Intervalo::setIntervalo(int inicio, int final)
{
    if (inicio < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "inicio < 0" << std::endl;
        std::cout << "Valor fornecido: " << inicio << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert (inicio >= 0);

    if (final < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "final < 0" << std::endl;
        std::cout << "Valor fornecido: " << final << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert (final >= 0);

    if (inicio > final)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "inicio > final" << std::endl;
        std::cout << "Valores fornecido (inicio, final): " << inicio << "," << final << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert (inicio <= final);

    _inicio = inicio;
    _final = final;
}

int Intervalo::getTamanho()
{
    return _final - _inicio + 1;
}

void Intervalo::copyFrom(Intervalo value)
{
    _inicio = value.getInicio();
    _final = value.getFinal();
}

void Intervalo::print()
{
    std::cout << std::endl;
    std::cout << "O intervalo tem :" << std::endl;
    std::cout << "Início: " << _inicio << std::endl;
    std::cout << "Final: " << _final << std::endl;
    std::cout << "Tamanho: " << this->getTamanho() << std::endl;;
    std::cout << std::endl;
}

