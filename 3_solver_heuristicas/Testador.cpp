// TODO: testar projetos map
// TODO: testar sondas map
// TODO: testar dados de entrada
// TODO: testar leitos de dados


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
    Sonda sonda1;
    sonda1.print();

    sonda1.setNome(7);
    sonda1.setCoordX(70);
    sonda1.setCoordY(77);

    sonda1.print();

    Sonda sonda2{3, 30, 33};
    sonda2.print();
}

void Testador::testarVertice()
{
    Sonda sonda1(3, 30, 33);
    Projeto projeto1{25, 40, 3, 7, 1, 2, 3, 4500, 0.5, 0.9, 0.8, 0.7, 0.8, 0.7, 0.3, 500, 150, 1000, 200, 50, 5, 0, 100};
    int nSondas, nProjetos;
    nSondas = 5;
    nProjetos = 10;
    Vertice vertice1{nSondas, nProjetos};

    std::cout << std::endl;
    std::cout << "Minha instância tem " << nSondas << " sondas e " << nProjetos << " projetos." << std::endl;
    std::cout << "O índice do vértice representado pela sonda " << sonda1.getNome() << " é: " 
                                                        << vertice1.getVerticeIndexBySonda(sonda1.getNome()) << std::endl;
    std::cout << "O índice do vértice representado pelo projeto " << projeto1.getNome() << " é: "
                                                        << vertice1.getVerticeIndexByProjeto(projeto1.getNome()) << std::endl;
    
    std::cout << "O índice do vértice representado pela sonda " << sonda1.getNome() << " é: " 
                                                        << vertice1.getVerticeIndex(sonda1) << std::endl;
    std::cout << "O índice do vértice representado pelo projeto " << projeto1.getNome() << " é: "
                                                        << vertice1.getVerticeIndex(projeto1) << std::endl;
    std::cout << std::endl;
}

void Testador::testarDadosDeEntrada()
{
    // TODO
}

void Testador::testarLeitorDeDados()
{
    // TODO
}

