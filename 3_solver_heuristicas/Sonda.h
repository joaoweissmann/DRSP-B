// TODO: debug mode


#include <bits/stdc++.h>

#pragma once

class Sonda
{
    private:
        int _nome;
        double _coordX;
        double _coordY;
        std::map<std::string, int> _mapPropIdx;
    public:
        // construtores
        Sonda();
        Sonda(int, double, double);

        // gets
        int getNome();
        double getCoordX();
        double getCoordY();
        std::map<std::string, int> getMapPropIdx();
        int getPropIdx(std::string);

        // sets
        void setNome(int);
        void setCoordX(double);
        void setCoordY(double);

        // outros
        void print();
};

