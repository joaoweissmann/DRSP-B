

#include <bits/stdc++.h>
#include "Testador.h"

void Testador::testarProjeto()
{
    Projeto projeto1;
    projeto1.print();

    projeto1.setBacia(10);
    projeto1.setCoordX(100);
    projeto1.setCoordY(100);
    projeto1.setCusto(30);
    projeto1.setInicioJanela(7);
    projeto1.setFinalJanela(700);
    projeto1.setGeometria(0.5);
    projeto1.setGeracao(0.9);
    projeto1.setMaturidade(7);
    projeto1.setMcVol(700);
    projeto1.setMcVpl(7000);
    projeto1.setMigracao(0.7);
    projeto1.setMiVol(70);
    projeto1.setMiVpl(700);
    projeto1.setNome(1);
    projeto1.setPcgna(0.5);
    projeto1.setPlay(3);
    projeto1.setPshc(0.1);
    projeto1.setQualidade(3);
    projeto1.setReservatorio(0.7);
    projeto1.setRetencao(0.8);
    projeto1.setSoterramento(5000);
    projeto1.setTempExec(20);

    projeto1.print();

    Projeto projeto2{25, 40, 3, 7, 1, 2, 3, 4500, 0.5, 0.9, 0.8, 0.7, 0.8, 0.7, 0.3, 500, 150, 1000, 200, 50, 5, 0, 100};
    projeto2.print();
}

void Testador::testarSonda()
{
    // TODO
}

void Testador::testarVertice()
{
    // TODO
}