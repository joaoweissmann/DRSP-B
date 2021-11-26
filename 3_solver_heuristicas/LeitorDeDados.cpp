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

// File comments:
// 
// TODO: descrever conteúdo do arquivo, em alto nível

#include <bits/stdc++.h>
#include "LeitorDeDados.h"

enum projProp {coordXProj, coordYProj, bacia, nome, maturidade, qualidade, play, soterramento,
              pcgna, geracao, migracao, reservatorio, geometria, retencao, pshc, mcVol, 
              miVol, mcVpl, miVpl, custos, inicioJanela, finalJanela, tempExec
              };

enum sondaProp {coordXSonda, coordYSonda};

LeitorDeDados::LeitorDeDados()
{
    _mapProjPropIdx.insert(std::pair<int, int>(0, projProp::coordXProj));
    _mapProjPropIdx.insert(std::pair<int, int>(1, projProp::coordYProj));
    _mapProjPropIdx.insert(std::pair<int, int>(2, projProp::bacia));
    _mapProjPropIdx.insert(std::pair<int, int>(3, projProp::nome));
    _mapProjPropIdx.insert(std::pair<int, int>(4, projProp::maturidade));
    _mapProjPropIdx.insert(std::pair<int, int>(5, projProp::qualidade));
    _mapProjPropIdx.insert(std::pair<int, int>(6, projProp::play));
    _mapProjPropIdx.insert(std::pair<int, int>(7, projProp::soterramento));
    _mapProjPropIdx.insert(std::pair<int, int>(8, projProp::pcgna));
    _mapProjPropIdx.insert(std::pair<int, int>(9, projProp::geracao));
    _mapProjPropIdx.insert(std::pair<int, int>(10, projProp::migracao));
    _mapProjPropIdx.insert(std::pair<int, int>(11, projProp::reservatorio));
    _mapProjPropIdx.insert(std::pair<int, int>(12, projProp::geometria));
    _mapProjPropIdx.insert(std::pair<int, int>(13, projProp::retencao));
    _mapProjPropIdx.insert(std::pair<int, int>(14, projProp::pshc));
    _mapProjPropIdx.insert(std::pair<int, int>(15, projProp::mcVol));
    _mapProjPropIdx.insert(std::pair<int, int>(16, projProp::miVol));
    _mapProjPropIdx.insert(std::pair<int, int>(17, projProp::mcVpl));
    _mapProjPropIdx.insert(std::pair<int, int>(18, projProp::miVpl));
    _mapProjPropIdx.insert(std::pair<int, int>(19, projProp::custos));
    _mapProjPropIdx.insert(std::pair<int, int>(20, projProp::tempExec));
    _mapProjPropIdx.insert(std::pair<int, int>(21, projProp::inicioJanela));
    _mapProjPropIdx.insert(std::pair<int, int>(22, projProp::finalJanela));

    _mapSondasPropIdx.insert(std::pair<int, int>(0, sondaProp::coordXSonda));
    _mapSondasPropIdx.insert(std::pair<int, int>(1, sondaProp::coordYSonda));
}

DadosDeEntrada LeitorDeDados::lerDadosDeEntrada(std::string filename)
{
    DadosDeEntrada dataset;

    std::ifstream infile (filename);

    if (infile.is_open())
    {
        std::cout << std::endl << std::endl;
        std::cout << "Arquivo aberto corretamente." << std::endl;
        std::cout << "Lendo dados..." << std::endl;
        std::cout << std::endl;
        
        int nProjetos, tInit, tFinal, delta, nPeriodos;
        double capitalTotal;
        infile >> nProjetos >> capitalTotal >> tInit >> tFinal >> delta >> nPeriodos;

        dataset.setNProjetos(nProjetos);
        dataset.setCapitalTotal(capitalTotal);
        dataset.setTInit(tInit);
        dataset.setTFinal(tFinal);
        dataset.setDelta(delta);
        dataset.setNPeriodos(nPeriodos);

        int propriedadesProj=23;
        dataset.setPropriedadesProj(propriedadesProj);

        std::vector<Projeto> projetos;
        projetos.resize(nProjetos);
        for (int i=0; i<nProjetos; i++)
        {
            projetos[i] = Projeto{};
        }
        double temp;
        for (int i=0; i<propriedadesProj; i++)
        {
            for (int j=0; j<nProjetos; j++)
            {
                switch (_mapProjPropIdx[i])
                {
                    case projProp::coordXProj:
                        // double temp;
                        infile >> temp;
                        projetos[j].setCoordX(temp);
                        break;
                    case projProp::coordYProj:
                        // double temp;
                        infile >> temp;
                        projetos[j].setCoordY(temp);
                        break;
                    case projProp::bacia:
                        // int temp;
                        infile >> temp;
                        projetos[j].setBacia(int(temp));
                        break;
                    case projProp::nome:
                        // int temp;
                        infile >> temp;
                        projetos[j].setNome(int(temp));
                        break;
                    case projProp::maturidade:
                        // int temp;
                        infile >> temp;
                        projetos[j].setMaturidade(int(temp));
                        break;
                    case projProp::qualidade:
                        // int temp;
                        infile >> temp;
                        projetos[j].setQualidade(int(temp));
                        break;
                    case projProp::play:
                        // int temp;
                        infile >> temp;
                        projetos[j].setPlay(int(temp));
                        break;
                    case projProp::soterramento:
                        // double temp;
                        infile >> temp;
                        projetos[j].setSoterramento(temp);
                        break;
                    case projProp::pcgna:
                        // double temp;
                        infile >> temp;
                        projetos[j].setPcgna(temp);
                        break;
                    case projProp::geracao:
                        // double temp;
                        infile >> temp;
                        projetos[j].setGeracao(temp);
                        break;
                    case projProp::migracao:
                        // double temp;
                        infile >> temp;
                        projetos[j].setMigracao(temp);
                        break;
                    case projProp::reservatorio:
                        // double temp;
                        infile >> temp;
                        projetos[j].setReservatorio(temp);
                        break;
                    case projProp::geometria:
                        // double temp;
                        infile >> temp;
                        projetos[j].setGeometria(temp);
                        break;
                    case projProp::retencao:
                        // double temp;
                        infile >> temp;
                        projetos[j].setRetencao(temp);
                        break;
                    case projProp::pshc:
                        // double temp;
                        infile >> temp;
                        projetos[j].setPshc(temp);
                        break;
                    case projProp::mcVol:
                        // double temp;
                        infile >> temp;
                        projetos[j].setMcVol(temp);
                        break;
                    case projProp::miVol:
                        // double temp;
                        infile >> temp;
                        projetos[j].setMiVol(temp);
                        break;
                    case projProp::mcVpl:
                        // double temp;
                        infile >> temp;
                        projetos[j].setMcVpl(temp);
                        break;
                    case projProp::miVpl:
                        // double temp;
                        infile >> temp;
                        projetos[j].setMiVpl(temp);
                        break;
                    case projProp::custos:
                        // double temp;
                        infile >> temp;
                        projetos[j].setCusto(temp);
                        break;
                    case projProp::tempExec:
                        // int temp;
                        infile >> temp;
                        projetos[j].setTempExec(int(temp));
                        break;
                    case projProp::inicioJanela:
                        // int temp;
                        infile >> temp;
                        projetos[j].setInicioJanela(int(temp));
                        break;
                    case projProp::finalJanela:
                        // int temp;
                        infile >> temp;
                        projetos[j].setFinalJanela(int(temp));
                        break;
                }
            }
        }
        
        dataset.setProjetos(projetos);

        int nSondas;
        infile >> nSondas;
        dataset.setNSondas(nSondas);
        int propriedadesSondas=2;
        dataset.setPropriedadesSondas(propriedadesSondas);
        
        std::vector<Sonda> sondas;
        sondas.resize(nSondas);
        for (int i=0; i<nSondas; i++)
        {
            sondas[i] = Sonda{};
        }
        for (int i=0; i<propriedadesSondas; i++)
        {
            for (int j=0; j<nSondas; j++)
            {
                sondas[j].setNome(j);

                switch (_mapSondasPropIdx[i])
                {
                    case sondaProp::coordXSonda:
                        // double temp;
                        infile >> temp;
                        sondas[j].setCoordX(temp);
                        break;
                    case sondaProp::coordYSonda:
                        // double temp;
                        infile >> temp;
                        sondas[j].setCoordY(temp);
                        break;
                }
            }
        }
        dataset.setSondas(sondas);

        std::vector<std::vector<double>> desloc;
        desloc.resize(nProjetos+nSondas);
        for (int i=0; i<(nProjetos+nSondas); i++)
        {
            desloc[i].resize(nProjetos+nSondas);
        }
        for (int i=0; i<nProjetos+nSondas; i++)
        {
            for (int j=0; j<nProjetos+nSondas; j++)
            {
                infile >> desloc[i][j];
            }
        }
        dataset.setDesloc(desloc);

        // fechar aquivo
        infile.close();

        std::cout << "Dados lidos." << std::endl;

        return dataset;
    }
    else
    {
        std::cout << "Não foi possível abrir o arquivo." << std::endl;
        return dataset;
    }
}

