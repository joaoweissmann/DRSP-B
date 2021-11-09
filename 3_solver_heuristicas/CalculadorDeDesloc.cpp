

#include <bits/stdc++.h>
#include "CalculadorDeDesloc.h"

double CalculadorDeDesloc::getDesloc(Sonda s1, Sonda s2)
{
    double x1, x2, y1, y2, desloc;
    x1 = s1.getCoordX();
    y1 = s1.getCoordX();
    x2 = s2.getCoordX();
    y2 = s2.getCoordY();
    desloc = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
    return desloc;
}

double CalculadorDeDesloc::getDesloc(Sonda s, Projeto p)
{
    double x1, x2, y1, y2, desloc;
    x1 = p.getCoordX();
    y1 = p.getCoordX();
    x2 = s.getCoordX();
    y2 = s.getCoordY();
    desloc = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
    return desloc;
}

double CalculadorDeDesloc::getDesloc(Projeto p, Sonda s)
{
    double x1, x2, y1, y2, desloc;
    x1 = p.getCoordX();
    y1 = p.getCoordX();
    x2 = s.getCoordX();
    y2 = s.getCoordY();
    desloc = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
    return desloc;
}

double CalculadorDeDesloc::getDesloc(Projeto p1, Projeto p2)
{
    double x1, x2, y1, y2, desloc;
    x1 = p1.getCoordX();
    y1 = p1.getCoordX();
    x2 = p2.getCoordX();
    y2 = p2.getCoordY();
    desloc = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
    return desloc;
}

