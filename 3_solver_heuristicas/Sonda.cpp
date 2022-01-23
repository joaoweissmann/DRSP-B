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
#include "Sonda.h"

Sonda::Sonda()
{
    _nome = 0;
    _coordX = 0;
    _coordY = 0;
}

Sonda::Sonda(int nome, double coordX, double coordY)
{
    if (nome < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "nome fornecido é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << nome << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(nome >= 0);
    _nome = nome;
    if (coordX < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "coordX fornecida é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << coordX << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(coordX >= 0);
    _coordX = coordX;
    if (coordY < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "coordY fornecida é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << coordY << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(coordY >= 0);
    _coordY = coordY;
}

bool Sonda::operator<(const Sonda & s) const
{
    return this->_nome < s._nome;
}

void Sonda::copyFrom(Sonda s)
{
    _nome = s.getNome();
    _coordX = s.getCoordX();
    _coordY = s.getCoordY();
}

int Sonda::getNome()
{
    return _nome;
}

double Sonda::getCoordX()
{
    return _coordX;
}

double Sonda::getCoordY()
{
    return _coordY;
}

void Sonda::setNome(int value)
{
    if (value < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "nome fornecido é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(value >= 0);
    _nome = value;
}

void Sonda::setCoordX(double value)
{
    if (value < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "coordX fornecida é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(value >= 0);
    _coordX = value;
}

void Sonda::setCoordY(double value)
{
    if (value < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "coordY fornecida é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(value >= 0);
    _coordY = value;
}

void Sonda::print()
{
    std::cout << std::endl;
    std::cout << "A sonda de nome " << _nome << ", tem:" << std::endl;
    std::cout << "CoordX: " << _coordX << std::endl;
    std::cout << "CoordY: " << _coordY << std::endl;
    std::cout << std::endl;
}

