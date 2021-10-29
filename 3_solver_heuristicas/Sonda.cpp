// TODO: debug mode
// TODO: asserts


#include <bits/stdc++.h>
#include "Sonda.h"

Sonda::Sonda()
{
    _nome = 0;
    _coordX = 0;
    _coordY = 0;
    _mapPropIdx.insert(std::pair<std::string, int>("coordX", 0));
    _mapPropIdx.insert(std::pair<std::string, int>("coordY", 1));
}

Sonda::Sonda(int nome, double coordX, double coordY)
{
    _nome = nome;
    _coordX = coordX;
    _coordY = coordY;
    _mapPropIdx.insert(std::pair<std::string, int>("coordX", 0));
    _mapPropIdx.insert(std::pair<std::string, int>("coordY", 1));
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

std::map<std::string, int> Sonda::getMapPropIdx()
{
    return _mapPropIdx;
}

int Sonda::getPropIdx(std::string s)
{
    auto itr = _mapPropIdx.find(s);
    return itr->second;
}

void Sonda::setNome(int value)
{
    _nome = value;
}

void Sonda::setCoordX(double value)
{
    _coordX = value;
}

void Sonda::setCoordY(double value)
{
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

