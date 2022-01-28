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

    std::cout << std::endl;
    std::cout << "A distância entre a sonda1 e a sonda2 é: " << calc.getDesloc(sonda1, sonda2) << std::endl;
    std::cout << "A distância entre a sonda1 e a projeto1 é: " << calc.getDesloc(sonda1, projeto1) << std::endl;
    std::cout << "A distância entre a sonda1 e a projeto2 é: " << calc.getDesloc(sonda1, projeto2) << std::endl;
    std::cout << "A distância entre a sonda2 e a sonda1 é: " << calc.getDesloc(sonda2, sonda1) << std::endl;
    std::cout << "A distância entre a sonda2 e a projeto1 é: " << calc.getDesloc(sonda2, projeto1) << std::endl;
    std::cout << "A distância entre a sonda2 e a projeto2 é: " << calc.getDesloc(sonda2, projeto2) << std::endl;
    std::cout << "A distância entre a projeto1 e a sonda1 é: " << calc.getDesloc(projeto1, sonda1) << std::endl;
    std::cout << "A distância entre a projeto1 e a sonda2 é: " << calc.getDesloc(projeto1, sonda2) << std::endl;
    std::cout << "A distância entre a projeto1 e a projeto2 é: " << calc.getDesloc(projeto1, projeto2) << std::endl;
    std::cout << "A distância entre a projeto2 e a sonda1 é: " << calc.getDesloc(projeto2, sonda1) << std::endl;
    std::cout << "A distância entre a projeto2 e a sonda2 é: " << calc.getDesloc(projeto2, sonda2) << std::endl;
    std::cout << "A distância entre a projeto2 e a projeto1 é: " << calc.getDesloc(projeto2, projeto1) << std::endl;
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

    dist = calc.getDesloc(sondas[0], projetos[0]);
    dataset1.setDesloc(sondas[0], projetos[0], dist);

    dist = calc.getDesloc(projetos[0], projetos[1]);
    dataset1.setDesloc(projetos[0], projetos[1], dist);

    dist = calc.getDesloc(sondas[1], projetos[1]);
    dataset1.setDeslocIdx2Idx(1, 3, dist);
    
    dist = calc.getDesloc(sondas[0], projetos[0]);
    dataset1.setDeslocSonda2Proj(0, 0, dist);

    dist = calc.getDesloc(projetos[1], projetos[1]);
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

    std::set<Sonda> sondas1;
    Sonda sonda1{1, 0, 0};
    Sonda sonda2{2, 10, 10};
    sondas1.insert(sonda1);
    sondas1.insert(sonda2);

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

    std::map<Sonda, std::vector<Alocacao>> alocacoesVector0;
    std::map<Sonda, std::list<Alocacao>> alocacoesList0;
    int nSondasVector = 2;
    int nSondasList = 2;
    int nProjetosVector = 3;
    int nProjetosList = 3;
    Projeto projPrev{};
    Projeto projeto{};
    Sonda sonda{};
    int nomeSonda;
    std::vector<Alocacao> vetorAloc;
    std::list<Alocacao> listaAloc;
    double coordXSonda, coordYSonda;
    double coordXProj, coordYProj;
    int baciaProj, nomeProj;
    int maturidadeProj, qualidadeProj, playProj, tempExecProj, releaseDateProj, dueDateProj;
    double soterramentoProj, pcgnaProj, geracaoProj, migracaoProj, reservatorioProj, geometriaProj;
    double retencaoProj, pshcProj, mcVolProj, miVolProj, mcVplProj, miVplProj, custoProj;
    int inicioIntervalo, finalIntervalo, desloc, maximo, minimo;
    int countProj = 0;
    Intervalo intervalo{};
    Alocacao alocacao{};
    std::vector<Alocacao> vetorTestViabilidade;
    bool feasible;
    Alocacao x;
    std::vector<Alocacao>::iterator itrRefVector;
    std::list<Alocacao>::iterator itrRefList;
    int diferenca, diferencaBest;
    for (int s=0; s<nSondasVector; s++)
    {
        nomeSonda = s;
        coordXSonda = rand()%100+1;
        coordYSonda = rand()%100+1;
        sonda.setNome(nomeSonda);
        sonda.setCoordX(coordXSonda);
        sonda.setCoordY(coordYSonda);
        alocacoesVector0.insert(std::pair<Sonda, std::vector<Alocacao>>(sonda, vetorAloc));
        alocacoesList0.insert(std::pair<Sonda,std::list<Alocacao>>(sonda, listaAloc));

        vetorTestViabilidade.clear();
        for (int p=0; p<nProjetosVector; p++)
        {
            coordXProj=rand()%100+1; 
            coordYProj=rand()%100+1;
            baciaProj=rand()%10+1;
            nomeProj=countProj;
            maturidadeProj=rand()%10+1;
            qualidadeProj=rand()%10+1;
            playProj=rand()%10+1;
            soterramentoProj=rand()%3000+1500;
            pcgnaProj=rand()/RAND_MAX;
            geracaoProj=rand()/RAND_MAX;
            migracaoProj=rand()/RAND_MAX;
            reservatorioProj=rand()/RAND_MAX;
            geometriaProj=rand()/RAND_MAX;
            retencaoProj=rand()/RAND_MAX;
            pshcProj=rand()/RAND_MAX;
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
            projeto.setTempExec(tempExecProj);
            projeto.setInicioJanela(releaseDateProj);
            projeto.setFinalJanela(dueDateProj);

            if (p==0)
            {
                desloc = sqrt(pow(coordXSonda-coordXProj, 2) + pow(coordYSonda-coordYProj, 2));
            }
            else
            {
                desloc = sqrt(pow(projPrev.getCoordX()-coordXProj, 2) + pow(projPrev.getCoordY()-coordYProj, 2));
            }
            
            for (int tests=0; tests<100; tests++)
            {
                feasible = true;
                tempExecProj=rand()%70+1;
                releaseDateProj=rand()%300+1;
                dueDateProj = releaseDateProj + rand()%(1000- (releaseDateProj+tempExecProj+desloc) ) + tempExecProj + desloc; 

                minimo = releaseDateProj;
                maximo = dueDateProj - tempExecProj - desloc;
                inicioIntervalo = rand()%(maximo-minimo) + minimo;
                finalIntervalo = inicioIntervalo + tempExecProj + desloc;

                intervalo.setIntervalo(inicioIntervalo, finalIntervalo);
                alocacao.setAlocacao(projeto, sonda, intervalo);
                
                std::cout << "Início da janela do projeto: " << releaseDateProj << std::endl;
                std::cout << "Final da janela do projeto: " << dueDateProj << std::endl;
                std::cout << "Deslocamento em relação à alocação anterior: " << desloc << std::endl;
                std::cout << "Tempo de execução do projeto: " << tempExecProj << std::endl;
                std::cout << "Início do intervalo alocado: " << inicioIntervalo << std::endl;
                std::cout << "Final do intervalo alocado: " << finalIntervalo << std::endl;
                std::cout << std::endl;

                // testar viabilidade
                if (!vetorTestViabilidade.empty())
                {
                    for (std::vector<Alocacao>::iterator itr=vetorTestViabilidade.begin(); itr!=vetorTestViabilidade.end(); ++itr)
                    {
                        x = *itr;
                        // testar interceção
                        if ( ! (((inicioIntervalo<x.getIntervalo().getInicio())&&(finalIntervalo<x.getIntervalo().getInicio())) 
                               || 
                               ((inicioIntervalo>x.getIntervalo().getFinal())&&(finalIntervalo>x.getIntervalo().getFinal())))
                           )
                        {
                            feasible = false;
                            break;
                        }
                    } 
                }
                // testar tamanho da alocação
                if (feasible)
                {
                    if (!(finalIntervalo == inicioIntervalo + desloc + tempExecProj))
                    {
                        feasible = false;
                    }
                }

                if (feasible)
                {
                    break;
                }
            }
            if (!feasible)
            {
                std::cout << "Nenhuma alocação gerada é viável" << std::endl;
                assert (feasible);
            }

            // colocar na fucking ordem
            diferencaBest = RAND_MAX;
            for (std::vector<Alocacao>::iterator itr=vetorTestViabilidade.begin(); itr!=vetorTestViabilidade.end(); ++itr)
            {
                if ( finalIntervalo < (*itr).getIntervalo().getInicio() )
                {
                    diferenca = (*itr).getIntervalo().getInicio() - finalIntervalo;
                    if (diferenca < diferencaBest)
                    {
                        x = *itr;
                        itrRefVector = itr;
                        diferencaBest = diferenca;
                    }
                }
            }
            alocacoesVector0[sonda].insert(itrRefVector, x);

            itrRefList = std::find(alocacoesList0[sonda].begin(), alocacoesList0[sonda].end(), x);
            
            alocacoesList0[sonda].insert(itrRefList, x);

            vetorTestViabilidade.push_back(alocacao);

            projPrev.copyFrom(projeto);
            countProj ++;
        }
        vetorAloc.clear();
        listaAloc.clear();
    } 
    
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

    // TODO: testar novo construtor

    /*
    Alocacoes * ptrAlocacoesVector1 = & alocacoesVector1;
    Alocacoes * ptrAlocacoesList1 = & alocacoesList1;

    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << "NSondas das alocações (vector): " << ptrAlocacoesVector1->getNSondas() << std::endl;
    std::cout << std::endl;
    std::cout << "NSondas das alocações (list): " << ptrAlocacoesList1->getNSondas() << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;

    std::cout << "-------------------------------------------------------------------------";
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
    
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    std::map<Sonda, std::vector<Alocacao>> mapaVector = ptrAlocacoesVector1->getAlocacoes();
    AlocacoesVector alocsVector{mapaVector};
    std::cout << "As alocações (vector) são:";
    alocsVector.print();
    std::cout << std::endl;
    std::map<Sonda, std::vector<Alocacao>> mapaVector = ptrAlocacoesList1->getAlocacoes();
    AlocacoesList alocsList{mapaVector};
    std::cout << "As alocações (vector) são:";
    alocsList.print();
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    */

    // TODO: testar getAlocacoes(Sonda)

    /*
    std::cout << std::endl;
    std::cout << "-------------------------------------------------------------------------";
    
    std::cout << "-------------------------------------------------------------------------";
    std::cout << std::endl;
    */

    std::cout << "################### Teste concluído ###################" << std::endl;
}

