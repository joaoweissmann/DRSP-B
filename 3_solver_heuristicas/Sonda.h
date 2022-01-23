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

#ifndef SONDA_H
#define SONDA_H

#include <bits/stdc++.h>

class Sonda
{
    private:
        int _nome;
        double _coordX;
        double _coordY;
    public:
        // construtores
        Sonda();
        Sonda(int, double, double);

        bool operator<(const Sonda & s) const;

        void copyFrom(Sonda);

        // gets
        int getNome();
        double getCoordX();
        double getCoordY();

        // sets
        void setNome(int);
        void setCoordX(double);
        void setCoordY(double);

        // outros
        void print();
};

#endif