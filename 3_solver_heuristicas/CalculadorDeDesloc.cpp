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
#include "CalculadorDeDesloc.h"

double CalculadorDeDesloc::getDesloc(Sonda s1, Sonda s2)
{
    double x1, x2, y1, y2, desloc;
    x1 = s1.getCoordX();
    y1 = s1.getCoordY();
    x2 = s2.getCoordX();
    y2 = s2.getCoordY();
    desloc = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
    return desloc;
}

double CalculadorDeDesloc::getDesloc(Sonda s, Projeto p)
{
    double x1, x2, y1, y2, desloc;
    x1 = p.getCoordX();
    y1 = p.getCoordY();
    x2 = s.getCoordX();
    y2 = s.getCoordY();
    desloc = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
    return desloc;
}

double CalculadorDeDesloc::getDesloc(Projeto p, Sonda s)
{
    double x1, x2, y1, y2, desloc;
    x1 = p.getCoordX();
    y1 = p.getCoordY();
    x2 = s.getCoordX();
    y2 = s.getCoordY();
    desloc = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
    return desloc;
}

double CalculadorDeDesloc::getDesloc(Projeto p1, Projeto p2)
{
    double x1, x2, y1, y2, desloc;
    x1 = p1.getCoordX();
    y1 = p1.getCoordY();
    x2 = p2.getCoordX();
    y2 = p2.getCoordY();
    desloc = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
    return desloc;
}

