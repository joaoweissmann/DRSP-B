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