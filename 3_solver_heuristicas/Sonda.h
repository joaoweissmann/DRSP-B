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