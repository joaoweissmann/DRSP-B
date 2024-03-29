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

    if (intervalo.getInicio() < projeto.getInicioJanela())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "inicio < release" << std::endl;
        std::cout << "Valores fornecidos: " << intervalo.getInicio() << " < " << projeto.getInicioJanela() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert (intervalo.getInicio() >= projeto.getInicioJanela());

    if (intervalo.getFinal() > projeto.getFinalJanela())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "final > due" << std::endl;
        std::cout << "Valores fornecidos: " << intervalo.getFinal() << " > " << projeto.getFinalJanela() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert (intervalo.getFinal() <= projeto.getFinalJanela());

    _intervalo.copyFrom(intervalo);
}

bool Alocacao::operator==(const Alocacao & a) const
{
    bool x = (this->_projeto == a._projeto) && (this->_sonda == a._sonda) && (this->_intervalo == a._intervalo);
    return x;
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

void Alocacao::setAlocacao(Projeto projeto, Sonda sonda, Intervalo intervalo)
{
    if (intervalo.getInicio() < projeto.getInicioJanela())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "inicio < release" << std::endl;
        std::cout << "Valores fornecidos: " << intervalo.getInicio() << " < " << projeto.getInicioJanela() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert (intervalo.getInicio() >= projeto.getInicioJanela());

    if (intervalo.getFinal() > projeto.getFinalJanela())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "final > due" << std::endl;
        std::cout << "Valores fornecidos: " << intervalo.getFinal() << " > " << projeto.getFinalJanela() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert (intervalo.getFinal() <= projeto.getFinalJanela());

    if (intervalo.getInicio() < projeto.getInicioJanela())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "inicio < release" << std::endl;
        std::cout << "Valores fornecidos: " << intervalo.getInicio() << " < " << projeto.getInicioJanela() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert (intervalo.getInicio() >= projeto.getInicioJanela());

    if (intervalo.getFinal() > projeto.getFinalJanela())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "final > due" << std::endl;
        std::cout << "Valores fornecidos: " << intervalo.getFinal() << " > " << projeto.getFinalJanela() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert (intervalo.getFinal() <= projeto.getFinalJanela());

    _sonda.copyFrom(sonda);
    _intervalo.copyFrom(intervalo);
    _projeto.copyFrom(projeto);
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

