// TODO: debug mode
// TODO: asserts


#include <bits/stdc++.h>
#include "Vertice.h"

Vertice::Vertice()
{
    _nSondas = 0;
    _nProjetos = 0;
}

Vertice::Vertice(int nSondas, int nProjetos)
{
    _nSondas = nSondas;
    _nProjetos = nProjetos;
}

int Vertice::getNSondas()
{
    return _nSondas;
}

int Vertice::getNProjetos()
{
    return _nProjetos;
}

void Vertice::setNSondas(int value)
{
    _nSondas = value;
}

void Vertice::setNProjetos(int value)
{
    _nProjetos = value;
}

int Vertice::getVerticeIndex(Sonda sonda)
{
    return sonda.getNome();
}

int Vertice::getVerticeIndex(Projeto projeto)
{
    return _nSondas + projeto.getNome();
}

int Vertice::getVerticeIndexBySonda(int sondaIdx)
{
    return sondaIdx;
}

int Vertice::getVerticeIndexByProjeto(int projIdx)
{
    return _nSondas + projIdx;
}

