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
#include <cmath>
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

    Projeto projeto3;
    projeto3.print();
    projeto3.copyFrom(projeto2);
    projeto3.print();
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

    Sonda sonda3;
    sonda3.print();
    sonda3.copyFrom(sonda2);
    sonda3.print();
}

void Testador::testarCalculadorDeDesloc()
{
    double x1, x2, x3, x4, y1, y2, y3, y4;
    x1 = 0; y1 = 0;
    x2 = 1; y2 = 1;
    x3 = 2; y3 = 2;
    x4 = 3; y4 = 3;
    Sonda sonda1{1, x1, y1};
    Sonda sonda2{2, x2, y2};
    Projeto projeto1{x3, y3, 3, 7, 1, 2, 3, 4500, 0.5, 0.9, 0.8, 0.7, 0.8, 0.7, 0.3, 500, 150, 1000, 200, 50, 5, 0, 100};
    Projeto projeto2{x4, y4, 3, 7, 1, 2, 3, 4500, 0.5, 0.9, 0.8, 0.7, 0.8, 0.7, 0.3, 500, 150, 1000, 200, 50, 5, 0, 100};
    
    CalculadorDeDesloc calc;
    int deltaT = 28;

    std::cout << std::endl;
    std::cout << "A distância entre a sonda1 e a sonda2 é: " << calc.getDesloc(sonda1, sonda2, deltaT) << std::endl;
    std::cout << "A distância entre a sonda1 e a projeto1 é: " << calc.getDesloc(sonda1, projeto1, deltaT) << std::endl;
    std::cout << "A distância entre a sonda1 e a projeto2 é: " << calc.getDesloc(sonda1, projeto2, deltaT) << std::endl;
    std::cout << "A distância entre a sonda2 e a sonda1 é: " << calc.getDesloc(sonda2, sonda1, deltaT) << std::endl;
    std::cout << "A distância entre a sonda2 e a projeto1 é: " << calc.getDesloc(sonda2, projeto1, deltaT) << std::endl;
    std::cout << "A distância entre a sonda2 e a projeto2 é: " << calc.getDesloc(sonda2, projeto2, deltaT) << std::endl;
    std::cout << "A distância entre a projeto1 e a sonda1 é: " << calc.getDesloc(projeto1, sonda1, deltaT) << std::endl;
    std::cout << "A distância entre a projeto1 e a sonda2 é: " << calc.getDesloc(projeto1, sonda2, deltaT) << std::endl;
    std::cout << "A distância entre a projeto1 e a projeto2 é: " << calc.getDesloc(projeto1, projeto2, deltaT) << std::endl;
    std::cout << "A distância entre a projeto2 e a sonda1 é: " << calc.getDesloc(projeto2, sonda1, deltaT) << std::endl;
    std::cout << "A distância entre a projeto2 e a sonda2 é: " << calc.getDesloc(projeto2, sonda2, deltaT) << std::endl;
    std::cout << "A distância entre a projeto2 e a projeto1 é: " << calc.getDesloc(projeto2, projeto1, deltaT) << std::endl;
    std::cout << std::endl;
}

void Testador::testarDadosDeEntrada()
{
    int nProjetos, nSondas, nPeriodos, propriedadesProj, propriedadesSondas, tInit, tFinal, delta;
    double capitalTotal;
    std::vector<Projeto> projetos;
    std::vector<Sonda> sondas;
    std::vector<std::vector<double>> desloc;
    
    nProjetos = 1;
    nSondas = 1;
    propriedadesProj = 0;
    propriedadesSondas = 0;
    tInit = 0;
    tFinal = 100;
    delta = 1;
    nPeriodos = 100;
    capitalTotal = 100;

    projetos.resize(nProjetos);
    for (int i=0; i<nProjetos; i++)
    {
        projetos[i] = Projeto{};

        projetos[i].setBacia(10);
        projetos[i].setCoordX(100);
        projetos[i].setCoordY(100);
        projetos[i].setCusto(30);
        projetos[i].setInicioJanela(7);
        projetos[i].setFinalJanela(700);
        projetos[i].setGeometria(0.5);
        projetos[i].setGeracao(0.9);
        projetos[i].setMaturidade(7);
        projetos[i].setMcVol(700);
        projetos[i].setMcVpl(7000);
        projetos[i].setMigracao(0.7);
        projetos[i].setMiVol(70);
        projetos[i].setMiVpl(700);
        projetos[i].setNome(i);
        projetos[i].setPcgna(0.5);
        projetos[i].setPlay(3);
        projetos[i].setPshc(0.1);
        projetos[i].setQualidade(3);
        projetos[i].setReservatorio(0.7);
        projetos[i].setRetencao(0.8);
        projetos[i].setSoterramento(5000);
        projetos[i].setTempExec(20);
    }

    sondas.resize(nSondas);
    for (int i=0; i<nSondas; i++)
    {
        sondas[i] = Sonda{};

        sondas[i].setCoordX(0);
        sondas[i].setCoordY(0);
        sondas[i].setNome(i);
    }

    desloc.resize((nProjetos+nSondas));
    for (int i=0; i<(nProjetos+nSondas); i++)
    {
        desloc[i].resize((nProjetos+nSondas));
    }
    for (int i=0; i<(nProjetos+nSondas); i++)
    {
        for (int j=0; j<(nProjetos+nSondas); j++)
        {
            desloc[i][j] = i * j;
        }
    }

    DadosDeEntrada dataset2{nProjetos, nSondas, nPeriodos, propriedadesProj, propriedadesSondas, tInit, tFinal, delta, 
                            capitalTotal, projetos, sondas, desloc};
    dataset2.print();

    DadosDeEntrada dataset1;
    dataset1.setNProjetos(2);
    dataset1.setNSondas(2);
    dataset1.setPropriedadesProj(23);
    dataset1.setPropriedadesSondas(2);
    dataset1.setTInit(0);
    dataset1.setTFinal(200);
    dataset1.setDelta(1);
    dataset1.setNPeriodos(200);
    dataset1.setCapitalTotal(100);

    nProjetos = 2;
    projetos.resize(nProjetos);
    for (int i=0; i<nProjetos; i++)
    {
        projetos[i] = Projeto{};

        projetos[i].setBacia(10*(i+1));
        projetos[i].setCoordX(100*(i+1));
        projetos[i].setCoordY(100*(i+1));
        projetos[i].setCusto(30*(i+1));
        projetos[i].setInicioJanela(7*(i+1));
        projetos[i].setFinalJanela(700*(i+1));
        projetos[i].setGeometria(0.5);
        projetos[i].setGeracao(0.9);
        projetos[i].setMaturidade(7*(i+1));
        projetos[i].setMcVol(700*(i+1));
        projetos[i].setMcVpl(7000*(i+1));
        projetos[i].setMigracao(0.7);
        projetos[i].setMiVol(70*(i+1));
        projetos[i].setMiVpl(700*(i+1));
        projetos[i].setNome(i);
        projetos[i].setPcgna(0.5);
        projetos[i].setPlay(3*(i+1));
        projetos[i].setPshc(0.1);
        projetos[i].setQualidade(3*(i+1));
        projetos[i].setReservatorio(0.7);
        projetos[i].setRetencao(0.8);
        projetos[i].setSoterramento(5000);
        projetos[i].setTempExec(20*(i+1));
    }
    
    dataset1.setProjetos(projetos);

    // dataset1.setProjeto(projetos[1], 0);

    nSondas = 2;
    sondas.resize(nSondas);
    for (int i=0; i<nSondas; i++)
    {
        sondas[i] = Sonda{};

        sondas[i].setCoordX(10*(i+1));
        sondas[i].setCoordY(10*(i+1));
        sondas[i].setNome(i);
    }

    dataset1.setSondas(sondas);

    // dataset1.setSonda(sondas[1], 0);

    desloc.resize((nProjetos+nSondas));
    for (int i=0; i<(nProjetos+nSondas); i++)
    {
        desloc[i].resize((nProjetos+nSondas));
    }
    for (int i=0; i<(nProjetos+nSondas); i++)
    {
        for (int j=0; j<(nProjetos+nSondas); j++)
        {
            desloc[i][j] = i * j;
        }
    }

    dataset1.setDesloc(desloc);

    CalculadorDeDesloc calc{};
    double dist;

    dist = calc.getDesloc(sondas[0], projetos[0], delta);
    dataset1.setDesloc(sondas[0], projetos[0], dist);

    dist = calc.getDesloc(projetos[0], projetos[1], delta);
    dataset1.setDesloc(projetos[0], projetos[1], dist);

    dist = calc.getDesloc(sondas[1], projetos[1], delta);
    dataset1.setDeslocIdx2Idx(1, 3, dist);
    
    dist = calc.getDesloc(sondas[0], projetos[0], delta);
    dataset1.setDeslocSonda2Proj(0, 0, dist);

    dist = calc.getDesloc(projetos[1], projetos[1], delta);
    dataset1.setDeslocProj2Proj(1, 1, dist);

    dataset1.print();
}

void Testador::testarLeitorDeDados()
{
    std::string filename;
    filename = "/home/joaoweissmann/Documents/repos/synthetic_instance_generator/synthetic_instance_generator/1_gerador_instancias_sinteticas/instancias/instancia_10projetos_2sondas_delta_t28.dat";

    LeitorDeDados leitor;
    DadosDeEntrada dataset = leitor.lerDadosDeEntrada(filename);
    dataset.print();
}

void Testador::testarIntervalo()
{
    Intervalo x1{};
    x1.print();

    Intervalo x2{1, 3};
    x2.print();

    x1.setIntervalo(2, 5);
    x1.print();

    x1.copyFrom(x2);
    x1.print();

}

void Testador::testarAlocacao()
{
    Alocacao alocacao1{};
    alocacao1.print();

    Projeto projeto1{};
    Sonda sonda1{};
    Intervalo intervalo1{};
    Alocacao alocacao2{projeto1, sonda1, intervalo1};
    alocacao2.print();

    Projeto projeto2{25, 40, 3, 7, 1, 2, 3, 4500, 0.5, 0.9, 0.8, 0.7, 0.8, 0.7, 0.3, 500, 150, 1000, 200, 50, 5, 0, 100};
    Sonda sonda2{3, 30, 33};
    Intervalo intervalo2{7, 22};
    Alocacao alocacao3{projeto2, sonda2, intervalo2};
    alocacao3.print();

    alocacao1.setAlocacao(projeto2, sonda2, intervalo2);
    alocacao1.print();

    projeto2.setInicioJanela(7);
    projeto2.setFinalJanela(23);
    intervalo2.setIntervalo(11, 20);
    Alocacao alocacao4{projeto2, sonda2, intervalo2};
    alocacao4.print();

}

void Testador::testarAlocacoes()
{
    std::cout << "################### Testando classe alocações ###################" << std::endl;

    /*
    std::set<Sonda> sondas1;
    Sonda sonda1{1, 0, 0};
    Sonda sonda2{2, 10, 10};
    sondas1.insert(sonda1);
    sondas1.insert(sonda2);
    */

    /*
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    AlocacoesVector alocacoesVector1{sondas1};
    std::cout << "As alocações (vector) são:" << std::endl;
    alocacoesVector1.print();
    std::cout << std::endl;
    AlocacoesList alocacoesList1{sondas1};
    std::cout << "As alocações (list) são:" << std::endl;
    alocacoesList1.print();
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    */

    ///*
    std::map<Sonda, std::vector<Alocacao>> alocacoesVector0;
    std::map<Sonda, std::list<Alocacao>> alocacoesList0;
    int nSondasVector = 2;
    int nSondasList = 2;
    int nProjetosVector = 0;
    int nProjetosList = 0;
    Projeto projeto{};
    Sonda sonda{};
    int nomeSonda;
    std::vector<Alocacao> vetorAloc;
    std::list<Alocacao> listaAloc;
    double coordXSonda=0.0, coordYSonda=0.0;
    double coordXProj=0.0, coordYProj=0.0;
    int baciaProj=0, nomeProj=0;
    int maturidadeProj=0, qualidadeProj=0, playProj=0, tempExecProj=0, releaseDateProj=0, dueDateProj=0;
    double soterramentoProj=0.0, pcgnaProj=0.0, geracaoProj=0.0, migracaoProj=0.0, reservatorioProj=0.0, geometriaProj=0.0;
    double retencaoProj=0.0, pshcProj=0.0, mcVolProj=0.0, miVolProj=0.0, mcVplProj=0.0, miVplProj=0.0, custoProj=0.0;
    int inicioIntervalo=0, finalIntervalo=0, desloc=0, maximo=0, minimo=0;
    int countProj = 0;
    Intervalo intervalo{};
    Alocacao alocacao{};
    bool feasible;
    Alocacao x;
    std::vector<Alocacao>::iterator itrRefVector;
    std::list<Alocacao>::iterator itrRefList;
    int diferenca=0, diferencaBest=0;
    CalculadorDeDesloc calc{};
    int deltaT = 1;
    for (int s=0; s<nSondasVector; s++)
    {
        nomeSonda = s;
        coordXSonda = rand()%50+1;
        coordYSonda = rand()%50+1;
        sonda.setNome(nomeSonda);
        sonda.setCoordX(coordXSonda);
        sonda.setCoordY(coordYSonda);
        alocacoesVector0.insert(std::pair<Sonda, std::vector<Alocacao>>(sonda, vetorAloc));
        alocacoesList0.insert(std::pair<Sonda,std::list<Alocacao>>(sonda, listaAloc));

        for (int p=0; p<nProjetosVector; p++)
        {
            std::cout << std::endl;
            std::cout << "Sonda " << s << " Projeto " << p << std::endl;

            coordXProj=rand()%50+1; 
            coordYProj=rand()%50+1;
            baciaProj=rand()%10+1;
            nomeProj=countProj;
            maturidadeProj=rand()%10+1;
            qualidadeProj=rand()%10+1;
            playProj=rand()%10+1;
            soterramentoProj=rand()%3000+1500;
            pcgnaProj=(double)rand()/(double)RAND_MAX;
            geracaoProj=(double)rand()/(double)RAND_MAX;
            migracaoProj=(double)rand()/(double)RAND_MAX;
            reservatorioProj=(double)rand()/(double)RAND_MAX;
            geometriaProj=(double)rand()/(double)RAND_MAX;
            retencaoProj=(double)rand()/(double)RAND_MAX;
            pshcProj=(double)rand()/(double)RAND_MAX;
            mcVolProj=rand()%1000+1;
            miVolProj=rand()%1000+1;
            mcVplProj=rand()%1000+1;
            miVplProj=rand()%1000+1;
            custoProj=rand()%100+1;
            projeto.setCoordX(coordXProj);
            projeto.setCoordY(coordYProj);
            projeto.setBacia(baciaProj);
            projeto.setNome(nomeProj);
            projeto.setMaturidade(maturidadeProj);
            projeto.setQualidade(qualidadeProj);
            projeto.setPlay(playProj);
            projeto.setSoterramento(soterramentoProj);
            projeto.setPcgna(pcgnaProj);
            projeto.setGeracao(geracaoProj);
            projeto.setMigracao(migracaoProj);
            projeto.setReservatorio(reservatorioProj);
            projeto.setGeometria(geometriaProj);
            projeto.setRetencao(retencaoProj);
            projeto.setPshc(pshcProj);
            projeto.setMcVol(mcVolProj);
            projeto.setMiVol(miVolProj);
            projeto.setMcVpl(mcVplProj);
            projeto.setMiVpl(miVplProj);
            projeto.setCusto(custoProj);
            
            for (int tests=0; tests<100; tests++)
            {
                std::cout << std::endl;
                std::cout << "Teste número: " << tests;
                std::cout << std::endl;

                feasible = true;
                
                tempExecProj=rand()%70+1;

                minimo = 0;
                maximo = 300;
                releaseDateProj = rand()%(maximo-minimo+1) + minimo;

                // calcula due do projeto
                minimo = releaseDateProj + 71 + tempExecProj;
                maximo = 1000;
                dueDateProj = rand()%(maximo-minimo+1) + minimo;
                
                projeto.setTempExec(tempExecProj);
                projeto.setInicioJanela(releaseDateProj);
                projeto.setFinalJanela(dueDateProj);

                // define inicio do intervalo
                minimo = releaseDateProj;
                maximo = dueDateProj - tempExecProj - 71;
                inicioIntervalo = rand()%(maximo-minimo+1) + minimo;

                if (alocacoesVector0[sonda].empty())
                {
                    std::cout << std::endl;
                    std::cout << "Tentando inserir em container vazio";
                    std::cout << std::endl;

                    // acha posição que projeto novo será inserido, se viável
                    itrRefVector = alocacoesVector0[sonda].begin();
                    itrRefList = alocacoesList0[sonda].begin();

                    // calcula desloc
                    desloc = calc.getDesloc(sonda, projeto, deltaT);

                    // define final do intervalo
                    finalIntervalo = inicioIntervalo + tempExecProj + desloc - 1;
                    intervalo.setIntervalo(inicioIntervalo, finalIntervalo);
                    alocacao.setAlocacao(projeto, sonda, intervalo);

                    std::cout << std::endl;
                    std::cout << "Inserindo em container vazio: " << std::endl;
                    std::cout << "Sonda: " << sonda.getNome() << std::endl;
                    std::cout << "Projeto: " << projeto.getNome() << std::endl;
                    std::cout << "Início: " << inicioIntervalo << std::endl;
                    std::cout << "Desloc: " << desloc << std::endl;
                    std::cout << "tempExec: " << tempExecProj << std::endl;
                    std::cout << "Final: " << finalIntervalo << std::endl;
                    std::cout << std::endl;
                    
                    // insere, se viável
                    alocacoesVector0[sonda].insert(itrRefVector, alocacao);
                    alocacoesList0[sonda].insert(itrRefList, alocacao);

                    std::cout << std::endl;
                    std::cout << "Inserção feita.";
                    std::cout << std::endl;

                    // AlocacoesVector alocsTemp{alocacoesVector0};
                    // alocsTemp.print();

                    break;
                }
                else
                {
                    std::cout << std::endl;
                    std::cout << "Tentando inserir em container NÃO vazio";
                    std::cout << std::endl;

                    // acha posição que projeto novo será inserido, se viável
                    diferencaBest = RAND_MAX;
                    for (std::vector<Alocacao>::iterator itr=alocacoesVector0[sonda].begin(); itr!=alocacoesVector0[sonda].end(); ++itr)
                    {
                        if ( inicioIntervalo < (*itr).getIntervalo().getInicio() )
                        {
                            diferenca = (*itr).getIntervalo().getInicio() - inicioIntervalo;
                            if (diferenca < diferencaBest)
                            {
                                x = *itr;
                                itrRefVector = itr;
                                itrRefList = std::find(alocacoesList0[sonda].begin(), alocacoesList0[sonda].end(), x);
                                diferencaBest = diferenca;
                            }
                        }
                        else
                        {
                            if (diferencaBest == RAND_MAX)
                            {
                                itrRefVector = alocacoesVector0[sonda].end();
                                itrRefList = alocacoesList0[sonda].end();
                            }
                        }
                    }

                    // calcula desloc
                    if (itrRefVector == alocacoesVector0[sonda].begin())
                    {
                        desloc = calc.getDesloc(sonda, projeto, deltaT);
                    }
                    else
                    {
                        Alocacao alocPrev = *(itrRefVector-1);
                        Projeto projPrev = alocPrev.getProjeto();
                        desloc = calc.getDesloc(projPrev, projeto, deltaT);
                    }

                    // define final intervalo
                    finalIntervalo = inicioIntervalo + tempExecProj + desloc - 1;
                    intervalo.setIntervalo(inicioIntervalo, finalIntervalo);
                    alocacao.setAlocacao(projeto, sonda, intervalo);

                    // verifica se tem interceção com outros projetos
                    for (std::vector<Alocacao>::iterator itr=alocacoesVector0[sonda].begin(); itr!=alocacoesVector0[sonda].end(); ++itr)
                    {
                        x = *itr;
                        // testar interceção
                        if ( ! (((inicioIntervalo<x.getIntervalo().getInicio())&&(finalIntervalo<x.getIntervalo().getInicio())) 
                               || 
                               ((inicioIntervalo>x.getIntervalo().getFinal())&&(finalIntervalo>x.getIntervalo().getFinal())))
                           )
                        {
                            std::cout << std::endl;
                            std::cout << "Não viável pois tem interceção.";
                            std::cout << std::endl;
                            feasible = false;
                            break;
                        }
                    }
                    if (!feasible)
                    {
                        continue;
                    }

                    // verifica se projeto posterior continua viável (muda desloc do projeto posterior)
                    Alocacao alocNext = *(itrRefVector);
                    int oldSetup;

                    if ((itrRefVector) == alocacoesVector0[sonda].begin())
                    {
                        oldSetup = calc.getDesloc(sonda, alocNext.getProjeto(), deltaT);
                    }
                    else
                    {
                        Alocacao alocPrev = *(itrRefVector-1);
                        oldSetup = calc.getDesloc(alocPrev.getProjeto(), alocNext.getProjeto(), deltaT);
                    }

                    int newSetup = calc.getDesloc(projeto, alocNext.getProjeto(), deltaT);
                    
                    int deltaSetup = newSetup - oldSetup;
                    int releaseNext = alocNext.getProjeto().getInicioJanela();
                    if (deltaSetup > (alocNext.getIntervalo().getInicio() - std::max(finalIntervalo, releaseNext) - 1))
                    {
                        std::cout << std::endl;
                        std::cout << "Não viável por conta da mudança de desloc.";
                        std::cout << std::endl;
                        feasible = false;
                    }
                    if (!feasible)
                    {
                        continue;
                    }
                    else
                    {
                        std::cout << std::endl;
                        std::cout << "Modificando início do intervalo em: " << deltaSetup << std::endl;
                        std::cout << "oldSetup = " << oldSetup << std::endl;
                        std::cout << "newSetup = " << newSetup << std::endl;
                        std::cout << std::endl;

                        // modifica o projeto posterior
                        Projeto projTemp = itrRefVector->getProjeto();
                        Sonda sondaTemp = itrRefVector->getSonda();
                        Intervalo intervaloTemp = itrRefVector->getIntervalo();
                        int tempInit = intervaloTemp.getInicio() - deltaSetup;
                        int tempFinal = intervaloTemp.getFinal();
                        intervaloTemp.setIntervalo(tempInit, tempFinal);
                        itrRefVector->setAlocacao(projTemp, sondaTemp, intervaloTemp);
                        itrRefList->setAlocacao(projTemp, sondaTemp, intervaloTemp);

                        std::cout << std::endl;
                        std::cout << "Inserindo em container NÃO vazio: " << std::endl;
                        std::cout << "Sonda: " << sonda.getNome() << std::endl;
                        std::cout << "Projeto: " << projeto.getNome() << std::endl;
                        std::cout << "Início: " << inicioIntervalo << std::endl;
                        std::cout << "Desloc: " << desloc << std::endl;
                        std::cout << "tempExec: " << tempExecProj << std::endl;
                        std::cout << "Final: " << finalIntervalo << std::endl;
                        std::cout << std::endl;

                        // insere
                        alocacoesVector0[sonda].insert(itrRefVector, alocacao);
                        alocacoesList0[sonda].insert(itrRefList, alocacao);

                        std::cout << std::endl;
                        std::cout << "Inserção concluída.";
                        std::cout << std::endl;

                        // AlocacoesVector alocsTemp{alocacoesVector0};
                        // alocsTemp.print();

                        break;
                    }
                }
            }
            if (!feasible)
            {
                std::cout << std::endl;
                std::cout << "Nenhuma alocação gerada é viável" << std::endl;
                assert (feasible);
            }
            countProj ++;
        }
        vetorAloc.clear();
        listaAloc.clear();
    }
    //*/
    
    /*
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    AlocacoesVector alocsVector0{alocacoesVector0};
    std::cout << "As alocações (vector) são:" << std::endl; 
    alocsVector0.print();
    std::cout << std::endl;
    AlocacoesList alocsList0{alocacoesList0};
    std::cout << "As alocações (list) são:" << std::endl;
    alocsList0.print();
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    */

    // std::cout << std::endl;
    // std::cout << "-------------------------------------------------------------------------" << std::endl;
    // AlocacoesVector alocsVector0{alocacoesList0};
    // std::cout << "As alocações (vector) são:" << std::endl; 
    // alocsVector0.print();
    // std::cout << std::endl;
    // AlocacoesList alocsList0{alocacoesVector0};
    // std::cout << "As alocações (list) são:" << std::endl;
    // alocsList0.print();
    // std::cout << "-------------------------------------------------------------------------";
    // std::cout << std::endl;

    // Alocacoes * ptrAlocacoesVector1 = & alocsVector0;
    // Alocacoes * ptrAlocacoesList1 = & alocsList0;

    /*
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    std::cout << "NSondas das alocações (vector): " << ptrAlocacoesVector1->getNSondas();
    std::cout << std::endl;
    std::cout << "NSondas das alocações (list): " << ptrAlocacoesList1->getNSondas();
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    */

    /*
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    std::cout << "As sondas que estão nas alocações (vector) são:" << std::endl;
    std::set<Sonda> sondas999;
    sondas999 = ptrAlocacoesVector1->getSondas();
    for (std::set<Sonda>::iterator itr=sondas999.begin(); itr!=sondas999.end(); ++itr)
    {
        Sonda s = *itr;
        s.print();
    }
    std::cout << std::endl;
    std::cout << "As sondas que estão nas alocações (list) são:" << std::endl;
    sondas999 = ptrAlocacoesList1->getSondas();
    for (std::set<Sonda>::iterator itr=sondas999.begin(); itr!=sondas999.end(); ++itr)
    {
        Sonda s = *itr;
        s.print();
    }
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    */
    
    /*
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    std::map<Sonda, std::vector<Alocacao>> mapaVector;
    mapaVector = ptrAlocacoesVector1->getAlocacoes();
    AlocacoesVector alocsVector{mapaVector};
    std::cout << "As alocações (vector) são:";
    alocsVector.print();
    std::cout << std::endl;
    mapaVector = ptrAlocacoesList1->getAlocacoes();
    AlocacoesList alocsList{mapaVector};
    std::cout << "As alocações (list) são:";
    alocsList.print();
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    */

    // testar getAlocacoes(Sonda)
    /*
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    sonda = *( ptrAlocacoesVector1->getSondas().begin() );
    std::cout << "Sonda selecionada: " << sonda.getNome() << std::endl;

    std::vector<Alocacao> vetorAlocs = ptrAlocacoesVector1->getAlocacoes(sonda);
    std::cout << "Alocações da sonda selecionada (vector):" << std::endl;
    for (std::vector<Alocacao>::iterator it=vetorAlocs.begin(); it!=vetorAlocs.end(); ++it)
    {
        it->print();
    }

    vetorAlocs = ptrAlocacoesList1->getAlocacoes(sonda);
    std::cout << "Alocações da sonda selecionada (list):" << std::endl;
    for (std::vector<Alocacao>::iterator it=vetorAlocs.begin(); it!=vetorAlocs.end(); ++it)
    {
        it->print();
    }

    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    */

   /*
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    std::cout << "Mostrando alocações (vector)" << std::endl;
    for (std::map<Sonda, std::vector<Alocacao>>::iterator it=alocacoesVector0.begin(); it!=alocacoesVector0.end(); ++it)
    {
        Sonda sonda = it->first;
        std::cout << "A sonda " << sonda.getNome() << " tem " << ptrAlocacoesVector1->getNAlocacoes(sonda) << " alocações";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    std::cout << "Mostrando alocações (list)" << std::endl;
    for (std::map<Sonda, std::list<Alocacao>>::iterator it=alocacoesList0.begin(); it!=alocacoesList0.end(); ++it)
    {
        Sonda sonda = it->first;
        std::cout << "A sonda " << sonda.getNome() << " tem " << ptrAlocacoesList1->getNAlocacoes(sonda) << " alocações";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    */

    /*
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    std::set<Sonda> sondas = ptrAlocacoesVector1->getSondas();
    Sonda sondaX = *sondas.begin();
    Alocacao alocX = ptrAlocacoesVector1->getAlocacao(sondaX, 0);
    std::cout << "Mostrando alocação (vector)" << std::endl;
    alocX.print();
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    //std::set<Sonda> sondas = ptrAlocacoesVector1->getSondas();
    //Sonda sondaX = *sondas.begin();
    Alocacao alocY = ptrAlocacoesList1->getAlocacao(sondaX, 0);
    std::cout << "Mostrando alocação (list)" << std::endl;
    alocY.print();
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    */

    /*
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    std::set<Sonda> sondas = ptrAlocacoesVector1->getSondas();
    Sonda sondaX = *sondas.begin();
    Projeto projX = alocacoesVector0[sondaX].begin()->getProjeto();
    Alocacao alocX = ptrAlocacoesVector1->getAlocacao(sondaX, projX);
    std::cout << "Mostrando alocação (vector)" << std::endl;
    alocX.print();
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    //std::set<Sonda> sondas = ptrAlocacoesVector1->getSondas();
    //Sonda sondaX = *sondas.begin();
    //Projeto projX = alocacoesVector0[sondaX].begin()->getProjeto();
    Alocacao alocY = ptrAlocacoesList1->getAlocacao(sondaX, projX);
    std::cout << "Mostrando alocação (list)" << std::endl;
    alocY.print();
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    */

    /*
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    std::set<Sonda> sondas = ptrAlocacoesVector1->getSondas();
    Sonda sondaX = *sondas.begin();
    Projeto projX = alocacoesVector0[sondaX].begin()->getProjeto();
    int idxX = ptrAlocacoesVector1->getAlocacaoIndex(sondaX, projX);
    std::cout << "O índice da alocação (vector) do projeto " << projX.getNome() << " na sonda " << sondaX.getNome() << 
                " é " << idxX << std::endl;
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    //std::set<Sonda> sondas = ptrAlocacoesVector1->getSondas();
    //Sonda sondaX = *sondas.begin();
    //Projeto projX = alocacoesVector0[sondaX].begin()->getProjeto();
    int idxY = ptrAlocacoesList1->getAlocacaoIndex(sondaX, projX);
    std::cout << "O índice da alocação (list) do projeto " << projX.getNome() << " na sonda " << sondaX.getNome() << 
                " é " << idxY << std::endl;
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    */

    /*
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    std::set<Sonda> sondas = ptrAlocacoesList1->getSondas();
    AlocacoesVector alocsVector1{sondas};
    std::cout << "Alocações (vector) antes de modificar: " << std::endl;
    alocsVector1.print();
    std::cout << "Alocações (vector) depois de modificar uma sonda: " << std::endl;
    Sonda sondaX = *sondas.begin();
    std::vector<Alocacao> vetorAlocX = ptrAlocacoesVector1->getAlocacoes(sondaX);
    alocsVector1.setAlocacoes(sondaX, vetorAlocX);
    alocsVector1.print();
    std::cout << "Alocações (vector) depois de modificar tudo: " << std::endl;
    alocsVector1.setAlocacoes(alocacoesVector0);
    alocsVector1.print();
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    */

    /*
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    std::set<Sonda> sondas = ptrAlocacoesList1->getSondas();
    AlocacoesList alocsList1{sondas};
    std::cout << "Alocações (list) antes de modificar: " << std::endl;
    alocsList1.print();
    std::cout << "Alocações (list) depois de modificar uma sonda: " << std::endl;
    Sonda sondaX = *sondas.begin();
    std::vector<Alocacao> vetorAlocX = ptrAlocacoesVector1->getAlocacoes(sondaX);
    alocsList1.setAlocacoes(sondaX, vetorAlocX);
    alocsList1.print();
    std::cout << "Alocações (list) depois de modificar tudo: " << std::endl;
    alocsList1.setAlocacoes(alocacoesVector0);
    alocsList1.print();
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    */

    /*
    AlocacoesVector alocsVector1{sondas1};
    Alocacoes * ptrAlocsVector1 = & alocsVector1;

    std::cout << "Mostrando alocações iniciais: " << std::endl;
    alocsVector1.print();

    Sonda sondaX = *sondas1.begin();

    Projeto projetoX{};
    projetoX.setCoordX(10);
    projetoX.setCoordY(20);
    projetoX.setNome(0);
    projetoX.setMiVpl(10);
    projetoX.setCusto(5);
    projetoX.setTempExec(11);
    projetoX.setInicioJanela(20);
    projetoX.setFinalJanela(420);

    bool alocExiste = false;
    int posicaoAloc = -1;
    Intervalo intervaloAloc{};
    int deltaNext = 0;
    int numNexts = 0;
    std::cout << "Buscando janela viável..." << std::endl;
    std::tie(alocExiste, posicaoAloc, intervaloAloc, deltaNext, numNexts) = ptrAlocsVector1->buscarJanelaViavel(sondaX, projetoX);

    std::cout << "Janela viável encontrada? " << alocExiste << std::endl;
    std::cout << "Posição para alocação: " << posicaoAloc << std::endl;
    std::cout << "deltaNext: " << deltaNext << std::endl;
    std::cout << "numNexts: " << numNexts << std::endl;
    std::cout << "Intervalo para alocação: " << std::endl;
    intervaloAloc.print();

    if (alocExiste)
    {
        ptrAlocsVector1->inserirProjeto(sondaX, projetoX, posicaoAloc, intervaloAloc, deltaNext, numNexts);
        std::cout << "Mostrando alocações após inserção do projeto " << projetoX.getNome() << std::endl;
        alocsVector1.print();
    }
    */

    /*
    // testes com inserções aleatórias ---------------------------------------
    // instanciar alocações por set
    AlocacoesVector alocsVector2{alocacoesVector0};
    Alocacoes * ptrAlocsVector2 = & alocsVector2;

    // mostra alocações iniciais
    std::cout << std::endl;
    std::cout << "Mostrando alocações iniciais =================================================" << std::endl;
    alocsVector2.print();

    // get sondas
    std::set<Sonda> sondas2 = ptrAlocsVector2->getSondas();
    Sonda sonda1 = *(sondas2.begin());
    Sonda sonda2 = *(std::next(sondas2.begin(), 1));

    // loop para buscas e inserções
    int nTests = 6;
    Sonda sondaX{};
    Projeto projetoX{};
    for (int tests=0; tests<nTests; tests++)
    {
        // std::cout << "Sonda 1 empty: " << ptrAlocsVector2->getAlocacoes()[sonda1].empty() << std::endl;
        // std::cout << "Sonda 1 size: " << ptrAlocsVector2->getAlocacoes()[sonda1].size() << std::endl;
        // std::cout << "Sonda 2 empty: " << ptrAlocsVector2->getAlocacoes()[sonda2].empty() << std::endl;
        // std::cout << "Sonda 2 size: " << ptrAlocsVector2->getAlocacoes()[sonda2].size() << std::endl;

        // escolhe sonda
        sondaX = *(std::next(sondas2.begin(), rand()%2));

        // escolhe projeto
        projetoX.setCoordX(rand()%20);
        projetoX.setCoordY(rand()%20);
        projetoX.setNome(tests);
        projetoX.setMiVpl(rand()%20);
        projetoX.setCusto(rand()%20);
        projetoX.setTempExec(rand()%20);
        projetoX.setInicioJanela(rand()%100);
        projetoX.setFinalJanela(rand()%200 + projetoX.getInicioJanela());

        // faz busca
        int modo = 1; // sem realocações: 0; com realocações 1;
        bool alocExiste = false;
        int posicaoAloc = -1;
        Intervalo intervaloAloc{};
        int prevMinus = 0;
        int currMinus = 0;
        int currPlus = 0;
        int nextPlus = 0;
        int caso = 0;
        std::tie(alocExiste, posicaoAloc, intervaloAloc, prevMinus, currMinus, currPlus, nextPlus, caso) = 
                                                               ptrAlocsVector2->buscarJanelaViavel(sondaX, projetoX, modo);
        
        // mostra resultados da busca
        std::cout << "Janela viável encontrada? " << alocExiste << std::endl;
        std::cout << "Posição para alocação: " << posicaoAloc << std::endl;
        std::cout << "prevMinus: " << prevMinus << std::endl;
        std::cout << "currMinus: " << currMinus << std::endl;
        std::cout << "currPlus: " << currPlus << std::endl;
        std::cout << "nextPlus: " << nextPlus << std::endl;
        std::cout << "Intervalo para alocação: " << std::endl;
        intervaloAloc.print();

        // se viável, insere       
        if (alocExiste)
        {
            ptrAlocsVector2->inserirProjeto(sondaX, projetoX, posicaoAloc, intervaloAloc, prevMinus, 
                                            currMinus, currPlus, nextPlus, caso);
            std::cout << "Mostrando alocações após inserção do projeto " << projetoX.getNome() << std::endl;
            alocsVector2.print();
        }
    }
    */

    ///*
    // Testes direcionados ===============================================
    
    // instanciar alocações
    // AlocacoesVector alocsVector2{alocacoesVector0};
    AlocacoesList alocsVector2{alocacoesList0, deltaT};
    Alocacoes * ptrAlocsVector2 = & alocsVector2;

    // mostra alocações iniciais
    std::cout << std::endl;
    std::cout << "Mostrando alocações iniciais =================================================" << std::endl;
    alocsVector2.print();

    // get sondas
    std::set<Sonda> sondas2 = ptrAlocsVector2->getSondas();
    Sonda sonda1 = *(sondas2.begin());
    Sonda sonda2 = *(std::next(sondas2.begin(), 1));

    // cria projeto
    Projeto p1{};
    p1.setCoordX(30);
    p1.setCoordY(20);
    p1.setNome(1);
    p1.setMiVpl(10);
    p1.setCusto(10);
    p1.setTempExec(4);
    p1.setInicioJanela(130);
    p1.setFinalJanela(150);
    
    int modoDebug = 1;

    // faz busca
    int modo = 1; // sem realocações: 0; com realocações 1;
    bool alocExiste = false;
    int posicaoAloc = -1;
    Intervalo intervaloAloc{};
    int prevMinus = 0;
    int currMinus = 0;
    int currPlus = 0;
    int nextPlus = 0;
    int caso = 0;
    std::tie(alocExiste, posicaoAloc, intervaloAloc, prevMinus, currMinus, currPlus, nextPlus, caso) = 
                                                            ptrAlocsVector2->buscarJanelaViavel(sonda1, p1, modo, deltaT, modoDebug);

    // mostra resultados da busca
    std::cout << "Janela viável encontrada? " << alocExiste << std::endl;
    std::cout << "Posição para alocação: " << posicaoAloc << std::endl;
    std::cout << "prevMinus: " << prevMinus << std::endl;
    std::cout << "currMinus: " << currMinus << std::endl;
    std::cout << "currPlus: " << currPlus << std::endl;
    std::cout << "nextPlus: " << nextPlus << std::endl;
    std::cout << "Intervalo para alocação: " << std::endl;
    intervaloAloc.print();

    // se viável, insere       
    if (alocExiste)
    {
        ptrAlocsVector2->inserirProjeto(sonda1, p1, posicaoAloc, intervaloAloc, prevMinus, 
                                        currMinus, currPlus, nextPlus, caso, modoDebug);
        std::cout << "Mostrando alocações após inserção do projeto " << p1.getNome() << std::endl;
        alocsVector2.print();
    }

    // removendo projeto
    //bool removido;
    //removido = ptrAlocsVector2->removerProjeto(sonda1, p1);
    //std::cout << "Mostrando alocações após remoção do projeto " << p1.getNome() << std::endl;
    //alocsVector2.print();
    
    // cria projeto
    Projeto p2{};
    p2.setCoordX(25);
    p2.setCoordY(25);
    p2.setNome(2);
    p2.setMiVpl(10);
    p2.setCusto(10);
    p2.setTempExec(4);
    p2.setInicioJanela(130);
    p2.setFinalJanela(195);

    // faz busca
    std::tie(alocExiste, posicaoAloc, intervaloAloc, prevMinus, currMinus, currPlus, nextPlus, caso) = 
                                                            ptrAlocsVector2->buscarJanelaViavel(sonda1, p2, modo, deltaT, modoDebug);

    // mostra resultados da busca
    std::cout << "Janela viável encontrada? " << alocExiste << std::endl;
    std::cout << "Posição para alocação: " << posicaoAloc << std::endl;
    std::cout << "prevMinus: " << prevMinus << std::endl;
    std::cout << "currMinus: " << currMinus << std::endl;
    std::cout << "currPlus: " << currPlus << std::endl;
    std::cout << "nextPlus: " << nextPlus << std::endl;
    std::cout << "Intervalo para alocação: " << std::endl;
    intervaloAloc.print();

    // se viável, insere       
    if (alocExiste)
    {
        ptrAlocsVector2->inserirProjeto(sonda1, p2, posicaoAloc, intervaloAloc, prevMinus, 
                                        currMinus, currPlus, nextPlus, caso, modoDebug);
        std::cout << "Mostrando alocações após inserção do projeto " << p2.getNome() << std::endl;
        alocsVector2.print();
    }

    // removendo projeto
    bool removido;
    removido = ptrAlocsVector2->removerProjeto(sonda1, p1, deltaT, modoDebug);
    std::cout << "Mostrando alocações após remoção do projeto " << p1.getNome() << std::endl;
    alocsVector2.print();

    // cria projeto
    Projeto p3{};
    p3.setCoordX(25);
    p3.setCoordY(25);
    p3.setNome(3);
    p3.setMiVpl(10);
    p3.setCusto(10);
    p3.setTempExec(19);
    p3.setInicioJanela(150);
    p3.setFinalJanela(198);

    // faz busca
    std::tie(alocExiste, posicaoAloc, intervaloAloc, prevMinus, currMinus, currPlus, nextPlus, caso) = 
                                                            ptrAlocsVector2->buscarJanelaViavel(sonda1, p3, modo, deltaT, modoDebug);

    // mostra resultados da busca
    std::cout << "Janela viável encontrada? " << alocExiste << std::endl;
    std::cout << "Posição para alocação: " << posicaoAloc << std::endl;
    std::cout << "prevMinus: " << prevMinus << std::endl;
    std::cout << "currMinus: " << currMinus << std::endl;
    std::cout << "currPlus: " << currPlus << std::endl;
    std::cout << "nextPlus: " << nextPlus << std::endl;
    std::cout << "Intervalo para alocação: " << std::endl;
    intervaloAloc.print();

    // se viável, insere       
    if (alocExiste)
    {
        ptrAlocsVector2->inserirProjeto(sonda1, p3, posicaoAloc, intervaloAloc, prevMinus, 
                                        currMinus, currPlus, nextPlus, caso, modoDebug);
        std::cout << "Mostrando alocações após inserção do projeto " << p3.getNome() << std::endl;
        alocsVector2.print();
    }

    // cria projeto
    Projeto p4{};
    p4.setCoordX(45);
    p4.setCoordY(32);
    p4.setNome(4);
    p4.setMiVpl(10);
    p4.setCusto(10);
    p4.setTempExec(1);
    p4.setInicioJanela(120);
    p4.setFinalJanela(190);

    // faz busca
    std::tie(alocExiste, posicaoAloc, intervaloAloc, prevMinus, currMinus, currPlus, nextPlus, caso) = 
                                                            ptrAlocsVector2->buscarJanelaViavel(sonda1, p4, modo, deltaT, modoDebug);

    // mostra resultados da busca
    std::cout << "Janela viável encontrada? " << alocExiste << std::endl;
    std::cout << "Posição para alocação: " << posicaoAloc << std::endl;
    std::cout << "prevMinus: " << prevMinus << std::endl;
    std::cout << "currMinus: " << currMinus << std::endl;
    std::cout << "currPlus: " << currPlus << std::endl;
    std::cout << "nextPlus: " << nextPlus << std::endl;
    std::cout << "Intervalo para alocação: " << std::endl;
    intervaloAloc.print();

    // se viável, insere       
    if (alocExiste)
    {
        ptrAlocsVector2->inserirProjeto(sonda1, p4, posicaoAloc, intervaloAloc, prevMinus, 
                                        currMinus, currPlus, nextPlus, caso, modoDebug);
        std::cout << "Mostrando alocações após inserção do projeto " << p4.getNome() << std::endl;
        alocsVector2.print();
    }

    //*/

    /*
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    */

    std::cout << std::endl;
    std::cout << "################### Teste concluído ###################" << std::endl;
}

void Testador::testarSolucao()
{
    std::cout << "################### Testando classe solução ###################" << std::endl;

    // ler dataset
    std::string filename;
    filename = "/home/joaoweissmann/Documents/repos/synthetic_instance_generator/synthetic_instance_generator/1_gerador_instancias_sinteticas/instancia_10projetos_2sondas_delta_t28.dat";
    LeitorDeDados leitor;
    DadosDeEntrada dataset = leitor.lerDadosDeEntrada(filename);

    // inicializar solução vazia
    std::vector<Sonda> sondasVector = dataset.getSondas();
    std::set<Sonda> sondas;
    for (std::vector<Sonda>::iterator itr = sondasVector.begin(); itr!=sondasVector.end(); ++itr)
    {
        Sonda x = *itr;
        sondas.insert(x);
    }
    int dataStruct = 1; // 1 -> vector
    Solucao solucao1{dataStruct, dataset};

    // mostra alocações iniciais
    std::cout << std::endl;
    std::cout << "Mostrando alocações iniciais =================================================" << std::endl;
    solucao1.print();

    // inicializa conjunto de projetos não alocados
    std::set<Projeto> projetosNaoAlocs = solucao1.getProjetosNaoAlocados();
    std::cout << "Mostrando projetos não alocados" << std::endl;
    for (std::set<Projeto>::iterator itS=projetosNaoAlocs.begin(); itS!=projetosNaoAlocs.end(); ++itS)
    {
        Projeto x = *itS;
        std::cout << "Projeto: " << x.getNome() << std::endl;
    }

    // inicializa conjunto de projetos alocados
    std::set<Projeto> projetosAlocs = solucao1.getProjetosAlocados();
    std::cout << "Mostrando projetos alocados" << std::endl;
    for (std::set<Projeto>::iterator itS=projetosAlocs.begin(); itS!=projetosAlocs.end(); ++itS)
    {
        Projeto x = *itS;
        std::cout << "Projeto: " << x.getNome() << std::endl;
    }

    // inserir projetos na solução
    std::vector<Projeto> projetos = dataset.getProjetos();
    Projeto projeto1 = projetos[0];
    Sonda sonda1 = *sondas.begin();

    int modoDebug = 1;

    // faz busca
    int modo = 1; // sem realocações: 0; com realocações 1;
    bool alocExiste = false;
    int posicaoAloc = -1;
    Intervalo intervaloAloc{};
    int prevMinus = 0;
    int currMinus = 0;
    int currPlus = 0;
    int nextPlus = 0;
    int caso = 0;
    std::tie(alocExiste, posicaoAloc, intervaloAloc, prevMinus, currMinus, currPlus, nextPlus, caso) = 
                                                            solucao1.buscarJanelaViavel(sonda1, projeto1, modo, modoDebug);

    // mostra resultados da busca
    std::cout << "Janela viável encontrada? " << alocExiste << std::endl;
    std::cout << "Posição para alocação: " << posicaoAloc << std::endl;
    std::cout << "prevMinus: " << prevMinus << std::endl;
    std::cout << "currMinus: " << currMinus << std::endl;
    std::cout << "currPlus: " << currPlus << std::endl;
    std::cout << "nextPlus: " << nextPlus << std::endl;
    std::cout << "Intervalo para alocação: " << std::endl;
    intervaloAloc.print();

    // se viável, insere       
    if (alocExiste)
    {
        solucao1.inserirProjeto(sonda1, projeto1, posicaoAloc, intervaloAloc, prevMinus, 
                                        currMinus, currPlus, nextPlus, caso, modoDebug);
        std::cout << "Mostrando alocações após inserção do projeto " << projeto1.getNome() << std::endl;
        solucao1.print();
    }

    // inicializa conjunto de projetos não alocados
    projetosNaoAlocs = solucao1.getProjetosNaoAlocados();
    std::cout << "Mostrando projetos não alocados" << std::endl;
    for (std::set<Projeto>::iterator itS=projetosNaoAlocs.begin(); itS!=projetosNaoAlocs.end(); ++itS)
    {
        Projeto x = *itS;
        std::cout << "Projeto: " << x.getNome() << std::endl;
    }

    // inicializa conjunto de projetos alocados
    projetosAlocs = solucao1.getProjetosAlocados();
    std::cout << "Mostrando projetos alocados" << std::endl;
    for (std::set<Projeto>::iterator itS=projetosAlocs.begin(); itS!=projetosAlocs.end(); ++itS)
    {
        Projeto x = *itS;
        std::cout << "Projeto: " << x.getNome() << std::endl;
    }

    // mais um projeto
    Projeto projeto2 = projetos[1];

    std::tie(alocExiste, posicaoAloc, intervaloAloc, prevMinus, currMinus, currPlus, nextPlus, caso) = 
                                                            solucao1.buscarJanelaViavel(sonda1, projeto2, modo, modoDebug);

    // mostra resultados da busca
    std::cout << "Janela viável encontrada? " << alocExiste << std::endl;
    std::cout << "Posição para alocação: " << posicaoAloc << std::endl;
    std::cout << "prevMinus: " << prevMinus << std::endl;
    std::cout << "currMinus: " << currMinus << std::endl;
    std::cout << "currPlus: " << currPlus << std::endl;
    std::cout << "nextPlus: " << nextPlus << std::endl;
    std::cout << "Intervalo para alocação: " << std::endl;
    intervaloAloc.print();

    // se viável, insere       
    if (alocExiste)
    {
        solucao1.inserirProjeto(sonda1, projeto2, posicaoAloc, intervaloAloc, prevMinus, 
                                        currMinus, currPlus, nextPlus, caso, modoDebug);
        std::cout << "Mostrando alocações após inserção do projeto " << projeto2.getNome() << std::endl;
        solucao1.print();
    }

    // inicializa conjunto de projetos não alocados
    projetosNaoAlocs = solucao1.getProjetosNaoAlocados();
    std::cout << "Mostrando projetos não alocados" << std::endl;
    for (std::set<Projeto>::iterator itS=projetosNaoAlocs.begin(); itS!=projetosNaoAlocs.end(); ++itS)
    {
        Projeto x = *itS;
        std::cout << "Projeto: " << x.getNome() << std::endl;
    }

    // inicializa conjunto de projetos alocados
    projetosAlocs = solucao1.getProjetosAlocados();
    std::cout << "Mostrando projetos alocados" << std::endl;
    for (std::set<Projeto>::iterator itS=projetosAlocs.begin(); itS!=projetosAlocs.end(); ++itS)
    {
        Projeto x = *itS;
        std::cout << "Projeto: " << x.getNome() << std::endl;
    }

    std::map<Sonda, std::vector<Alocacao>> mapAlocs = solucao1.getAlocacoes();
    Solucao solucao2{mapAlocs, dataStruct, dataset};
    std::cout << std::endl;
    std::cout << "Mostrando solução criada a partir da solução anterior: " << std::endl;
    solucao2.print();

    std::cout << std::endl;
    std::cout << "################### Teste concluído ###################" << std::endl;
}

void Testador::testarConstrutorHeuristico()
{
    std::cout << std::endl;
    std::cout << "################### Testando classe construtor heuristico ###################" << std::endl;

    // ler dataset
    std::string filename;
    filename = "/home/joaoweissmann/Documents/repos/synthetic_instance_generator/synthetic_instance_generator/1_gerador_instancias_sinteticas/instancia_10projetos_2sondas_delta_t28.dat";
    LeitorDeDados leitor;
    DadosDeEntrada dataset = leitor.lerDadosDeEntrada(filename);

    ConstrutorHeuristico construtor{};
    construtor.setAlpha(0.99);
    construtor.setCriterio(1);
    construtor.setEstrutura(1);
    construtor.setModoRealoc(1);

    int modoDebug = 1;

    long long tempo;
    std::map<Sonda, std::vector<Alocacao>> alocsMap;
    double fitness;
    double gastos;
    int totalFree;
    std::tie(tempo, alocsMap, fitness, gastos, totalFree) = construtor.ConstruirSolucao(dataset, modoDebug);

    std::cout << std::endl;
    Solucao solucao1{alocsMap, construtor.getEstrutura(), dataset};
    solucao1.print();

    // testando verificador de solução ------------------------------
    VerificadorDeSolucao verificador{};
    Solucao solut{alocsMap, construtor.getEstrutura(), dataset};
    bool viavel = verificador.verificarSolucao(solut, dataset);
    if (viavel)
    {
        std::cout << std::endl;
        std::cout << "Solução viável: " << viavel;
        std::cout << std::endl;
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Solução INviável: " << viavel;
        std::cout << std::endl;
    }
    // --------------------------------------------------------------

    // testando movimentador em vizinhanças -------------------------
    std::cout << "Testando vizinhanças XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
    MovimentadorEmVizinhancas movimentador{};

    std::map<Sonda, std::vector<Alocacao>> newAlocsMap;
    double newFitness = 0;
    double newGastos = 0;
    int newTotalFree = 0;
    long long newTempo = 0;
    
    //std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaShift1x0InterRota(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), dataset.getDelta());
    //std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaShift2x0InterRota(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), dataset.getDelta());
    //std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaSwap1x1InterRota(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), dataset.getDelta());
    //std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaSwap2x1InterRota(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), dataset.getDelta());
    //std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaSwap2x2InterRota(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), dataset.getDelta());
    //std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaReinsercao1IntraRota(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), dataset.getDelta());
    //std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaReinsercao2IntraRota(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), dataset.getDelta());
    //std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaInserirNovoFO(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), dataset.getDelta());
    //std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaSwap1x1FO(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), dataset.getDelta());
    //std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaSwap2x1FO(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), dataset.getDelta());
    //std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaSwap1x2FO(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), dataset.getDelta());
    //std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaSwap2x2FO(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), dataset.getDelta());
    //std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaVND(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), dataset.getDelta());
    //std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaRVND(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), dataset.getDelta());
    
    int k = 20;
    //newAlocsMap = movimentador.perturbaShift1x0InterRota(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), k);
    //newAlocsMap = movimentador.perturbaShift2x0InterRota(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), k);
    //newAlocsMap = movimentador.perturbaSwap1x1InterRota(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), k);
    //newAlocsMap = movimentador.perturbaSwap2x1InterRota(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), k);
    //newAlocsMap = movimentador.perturbaSwap2x2InterRota(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), k);
    //newAlocsMap = movimentador.perturbaReinsercao1InterRota(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), k);
    //newAlocsMap = movimentador.perturbaReinsercao2InterRota(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), k);
    //newAlocsMap = movimentador.perturbaInserirNovoFO(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), k);
    //newAlocsMap = movimentador.perturbaSwap1x1FO(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), k);
    //newAlocsMap = movimentador.perturbaSwap2x1FO(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), k);
    //newAlocsMap = movimentador.perturbaSwap1x2FO(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), k);
    //newAlocsMap = movimentador.perturbaSwap2x2FO(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), k);
    //newAlocsMap = movimentador.perturbaAleatorio(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), k);
    
    // inicializa conjunto de vizinhanças
    std::set<int> vizinhancas;
    vizinhancas.insert(1);
    vizinhancas.insert(2);
    vizinhancas.insert(3);
    //vizinhancas.insert(4); //
    //vizinhancas.insert(5); //
    vizinhancas.insert(6);
    vizinhancas.insert(7);
    vizinhancas.insert(8);
    vizinhancas.insert(9);
    //vizinhancas.insert(10); //
    //vizinhancas.insert(11); //
    //vizinhancas.insert(12);

    int modoVizinhanca = 13;
    //newAlocsMap = movimentador.perturbaSolucao(alocsMap, dataset, construtor.getEstrutura(), construtor.getModoRealoc(), 
    //                                            k, modoVizinhanca);

    int modoBusca = 14;
    std::tie(newTempo, newAlocsMap, newFitness, newGastos, newTotalFree) = movimentador.buscaLocal(alocsMap, dataset, 
                                        construtor.getEstrutura(), construtor.getModoRealoc(), dataset.getDelta(), modoBusca, modoDebug, vizinhancas, 20);

    std::cout << std::endl;
    Solucao solucao2{newAlocsMap, construtor.getEstrutura(), dataset};
    solucao2.print();

    // --------------------------------------------------------------

    std::cout << std::endl;
    std::cout << "################### Teste concluído ###################" << std::endl;
}

void Testador::testarExecutadorDeMetaheuristicas()
{
    std::cout << std::endl;
    std::cout << "################### Testando classe executador de metaheuristicas ###################" << std::endl;

    // inicializa conjunto de vizinhanças
    std::set<int> vizinhancasInit;
    vizinhancasInit.insert(1); // shift_1x0_interRota
    vizinhancasInit.insert(2); // shift_2x0_interRota
    vizinhancasInit.insert(3); // swap_1x1_interRota
    //vizinhancasInit.insert(4); // swap_2x1_interRota //
    //vizinhancasInit.insert(5); // swap_2x2_interRota //
    vizinhancasInit.insert(6); // reinsercao1
    vizinhancasInit.insert(7); // reinsercao2
    vizinhancasInit.insert(8); // inserirNovoFO
    vizinhancasInit.insert(9); // swap_1x1_FO
    //vizinhancasInit.insert(10); // swap_2x1_FO //
    //vizinhancasInit.insert(11); // swap_1x2_FO //
    //vizinhancasInit.insert(12); // swap_2x2_FO //

    // inicializa conjunto de vizinhanças
    std::set<int> vizinhancasFinal;
    vizinhancasFinal.insert(1); // shift_1x0_interRota
    vizinhancasFinal.insert(2); // shift_2x0_interRota
    vizinhancasFinal.insert(3); // swap_1x1_interRota
    vizinhancasFinal.insert(4); // swap_2x1_interRota
    //vizinhancasFinal.insert(5); // swap_2x2_interRota
    vizinhancasFinal.insert(6); // reinsercao1
    vizinhancasFinal.insert(7); // reinsercao2
    vizinhancasFinal.insert(8); // inserirNovoFO
    vizinhancasFinal.insert(9); // swap_1x1_FO
    vizinhancasFinal.insert(10); // swap_2x1_FO
    vizinhancasFinal.insert(11); // swap_1x2_FO
    //vizinhancasFinal.insert(12); // swap_2x2_FO

    // ler dataset
    std::string filename;
    
    filename = "/home/joaoweissmann/Documents/repos/DRSP-B/1_gerador_instancias_sinteticas/instance_set_2/instancias/10p_2s_14dt.dat";
    //filename = "/home/joaoweissmann/Documents/repos/DRSP-B/1_gerador_instancias_sinteticas/instance_set_2/instancias/10p_10s_14dt.dat";
    //filename = "/home/joaoweissmann/Documents/repos/DRSP-B/1_gerador_instancias_sinteticas/instance_set_2/instancias/100p_10s_1dt.dat";
    //filename = "/home/joaoweissmann/Documents/repos/DRSP-B/1_gerador_instancias_sinteticas/instance_set_2/instancias/200p_5s_14dt.dat";

    LeitorDeDados leitor;
    DadosDeEntrada dataset = leitor.lerDadosDeEntrada(filename);

    // parâmetros
    int nIter = 1000 / (std::sqrt(dataset.getNProjetos() / 3)); // 100
    int nIterConverge = nIter / 5; // 20
    int maxIterFO = 10; // 10
    int nIterMelhoraGRASPada = 20; // manual=10; IRACE1=26; IRACE2=29; IRACE3=24;
    int nIterMelhoraILSada = 16; // manual = 10; IRACE1=16; IRACE2=15; IRACE3=10;
    int nIterAlpha = 20; // manual=10; IRACE1=18; IRACE2=23; IRACE3=11;
    int nIterRestart = 15; // manual=10; IRACE1=16; IRACE2=14; IRACE3=10;
    int modoDebug = 0; // 0
    int estrutura = 1; // 1
    int modoRealoc = 1; // 1
    int criterio = 1; // 1
    double alphaGRASP = 0.9; // 0.99
    double alphaGRASPada = 0.7; // manual=0.99; IRACE1=0.6; IRACE2=0.6; IRACE3=0.6;
    double alphaILS = 0.9; // 0.99
    double alphaILSada = 0.9; // manual=0.99; IRACE1=0.9; IRACE2=0.9; IRACE3=0.9;
    int modoBusca = 14; // 14
    int modoPerturba = 13; // 13
    int nivelPerturbaILS = 2; // 2
    int nivelPerturbaILSada = 2; // manual=2; IRACE1=2; IRACE2=2; IRACE3=2;
    double aceitacaoLimiteILS = 1.0 ; // 1.0
    double aceitacaoLimiteILSada = 1.0 ; // manual=1.0; IRACE1=1.0; IRACE2=1.0; IRACE3=1.0;
    int nivelIntensifica = 0; // 0
    double taxaAlpha = 0.7; // manual=0.95; IRACE1=0.6; IRACE2=0.7; IRACE3=0.6;
    int taxaPerturba = 4; // manual=2; IRACE1=4; IRACE2=2; IRACE3=2;
    double taxaAceitacao = 0.8 ; // manual=0.95; IRACE1=0.8; IRACE2=0.7; IRACE3=0.99;
    double alphaRestart = 0.9; // manual=0.9; IRACE1=0.9; IRACE2=0.8; IRACE3=0.9;

    long long tempo;
    std::map<Sonda, std::vector<Alocacao>> alocsMap;
    double fitness;
    double gastos;
    int totalFree;
    
    //ExecutadorDeMetaheuristicas executador{estrutura, modoRealoc, criterio, alphaGRASP, modoBusca, modoPerturba, nivelPerturbaILS};
    //std::tie(tempo, alocsMap, fitness, gastos, totalFree) = executador.multStartHeuristic(dataset, nIter, modoDebug, nIterConverge);
    
    //ExecutadorDeMetaheuristicas executador{estrutura, modoRealoc, criterio, alphaGRASP, modoBusca, modoPerturba, nivelPerturbaILS};
    //std::tie(tempo, alocsMap, fitness, gastos, totalFree) = executador.GRASP(dataset, nIter, modoDebug, vizinhancasInit, vizinhancasFinal, nivelIntensifica, maxIterFO, nIterConverge);
    
    ExecutadorDeMetaheuristicas executador{estrutura, modoRealoc, criterio, alphaGRASPada, modoBusca, modoPerturba, nivelPerturbaILS};
    //std::tie(tempo, alocsMap, fitness, gastos, totalFree) = executador.GRASPadaptativo(dataset, nIter, modoDebug, vizinhancasInit, vizinhancasFinal, nivelIntensifica, nIterMelhoraGRASPada, taxaAlpha, nIterAlpha, maxIterFO, nIterConverge);
    
    //ExecutadorDeMetaheuristicas executador{estrutura, modoRealoc, criterio, alphaILS, modoBusca, modoPerturba, nivelPerturbaILS};
    //std::tie(tempo, alocsMap, fitness, gastos, totalFree) = executador.ILS(dataset, nIter, modoDebug, vizinhancasInit, vizinhancasFinal, aceitacaoLimiteILS, nivelIntensifica, maxIterFO, nIterConverge);
    
    //ExecutadorDeMetaheuristicas executador{estrutura, modoRealoc, criterio, alphaILSada, modoBusca, modoPerturba, nivelPerturbaILSada};
    //std::tie(tempo, alocsMap, fitness, gastos, totalFree) = executador.ILSadaptativo(dataset, nIter, modoDebug, vizinhancasInit, vizinhancasFinal, aceitacaoLimiteILSada, nivelIntensifica, nIterMelhoraILSada, taxaPerturba, taxaAceitacao, nIterRestart, alphaRestart, maxIterFO, nIterConverge);

    /*
    std::cout << std::endl;
    std::cout << "nIter: " << nIter << std::endl;
    std::cout << "nIterConverge: " << nIterConverge << std::endl;
    std::cout << "A solução tem: " << std::endl;
    //std::cout << "Alocações:" << std::endl;
    //AlocacoesVector alocs{alocsMap, dataset.getDelta()};
    //alocs.print();
    std::cout << "fitness: " << fitness << std::endl;
    std::cout << "gastos: " << gastos << std::endl;
    std::cout << "limite gastos: " << dataset.getCapitalTotal() << std::endl;
    std::cout << "total free: " << totalFree << std::endl;

    VerificadorDeSolucao verificador{};
    Solucao solut{alocsMap, estrutura, dataset};
    //std::cout << "fitness solução: " << solut.getFitness() << std::endl;
    //std::cout << "gastos solução: " << solut.getGastos() << std::endl;
    bool viavel = verificador.verificarSolucao(solut, dataset);
    if (viavel)
    {
        std::cout << std::endl;
        std::cout << "Solução viável: " << viavel;
        std::cout << std::endl;
    }
    else
    {
        std::cout << std::endl;
        std::cout << "Solução Inviável: " << viavel;
        std::cout << std::endl;
    }
    */

    const char * caminho = "/home/joaoweissmann/Documents/repos/DRSP-B/1_gerador_instancias_sinteticas/instance_set_1/instancias/";
    
    ///*
    executador.rodarVariosArquivos(caminho, nIter, modoDebug, vizinhancasInit, vizinhancasFinal, 
                                   aceitacaoLimiteILSada, nivelIntensifica, nIterMelhoraGRASPada, taxaAlpha, nIterAlpha,
                                   taxaPerturba, taxaAceitacao, nIterRestart, alphaRestart, maxIterFO, nIterConverge);
    //*/

    std::cout << std::endl;
    std::cout << "################### Teste concluído ###################" << std::endl;
}

