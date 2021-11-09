

#include <bits/stdc++.h>
#include "LeitorDeDados.h"

LeitorDeDados::LeitorDeDados()
{
    _mapProjPropIdx.insert(std::pair<int, std::string>(0, "coordX"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(1, "coordY"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(2, "bacia"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(3, "nome"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(4, "maturidade"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(5, "qualidade"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(6, "play"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(7, "soterramento"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(8, "pcgna"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(9, "geracao"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(10, "migracao"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(11, "reservatorio"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(12, "geometria"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(13, "retencao"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(14, "pshc"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(15, "mcVol"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(16, "miVol"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(17, "mcVpl"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(18, "miVpl"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(19, "custos"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(20, "tempExec"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(21, "inicioJanela"));
    _mapProjPropIdx.insert(std::pair<int, std::string>(22, "finalJanela"));

    _mapSondasPropIdx.insert(std::pair<int, std::string>(0, "coordX"));
    _mapSondasPropIdx.insert(std::pair<int, std::string>(1, "coordY"));
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
        for (int i=0; i<propriedadesProj; i++)
        {
            for (int j=0; j<nProjetos; j++)
            {
                if (_mapProjPropIdx[i] == "coordX")
                {
                    double temp;
                    infile >> temp;
                    projetos[j].setCoordX(temp);
                }
                if (_mapProjPropIdx[i] == "coordY")
                {
                    double temp;
                    infile >> temp;
                    projetos[j].setCoordY(temp);
                }
                if (_mapProjPropIdx[i] == "bacia")
                {
                    int temp;
                    infile >> temp;
                    projetos[j].setBacia(temp);
                }
                if (_mapProjPropIdx[i] == "nome")
                {
                    int temp;
                    infile >> temp;
                    projetos[j].setNome(temp);
                }
                if (_mapProjPropIdx[i] == "maturidade")
                {
                    int temp;
                    infile >> temp;
                    projetos[j].setMaturidade(temp);
                }
                if (_mapProjPropIdx[i] == "qualidade")
                {
                    int temp;
                    infile >> temp;
                    projetos[j].setQualidade(temp);
                }
                if (_mapProjPropIdx[i] == "play")
                {
                    int temp;
                    infile >> temp;
                    projetos[j].setPlay(temp);
                }
                if (_mapProjPropIdx[i] == "soterramento")
                {
                    double temp;
                    infile >> temp;
                    projetos[j].setSoterramento(temp);
                }
                if (_mapProjPropIdx[i] == "pcgna")
                {
                    double temp;
                    infile >> temp;
                    projetos[j].setPcgna(temp);
                }
                if (_mapProjPropIdx[i] == "geracao")
                {
                    double temp;
                    infile >> temp;
                    projetos[j].setGeracao(temp);
                }
                if (_mapProjPropIdx[i] == "migracao")
                {
                    double temp;
                    infile >> temp;
                    projetos[j].setMigracao(temp);
                }
                if (_mapProjPropIdx[i] == "reservatorio")
                {
                    double temp;
                    infile >> temp;
                    projetos[j].setReservatorio(temp);
                }
                if (_mapProjPropIdx[i] == "geometria")
                {
                    double temp;
                    infile >> temp;
                    projetos[j].setGeometria(temp);
                }
                if (_mapProjPropIdx[i] == "retencao")
                {
                    double temp;
                    infile >> temp;
                    projetos[j].setRetencao(temp);
                }
                if (_mapProjPropIdx[i] == "pshc")
                {
                    double temp;
                    infile >> temp;
                    projetos[j].setPshc(temp);
                }
                if (_mapProjPropIdx[i] == "mcVol")
                {
                    double temp;
                    infile >> temp;
                    projetos[j].setMcVol(temp);
                }
                if (_mapProjPropIdx[i] == "miVol")
                {
                    double temp;
                    infile >> temp;
                    projetos[j].setMiVol(temp);
                }
                if (_mapProjPropIdx[i] == "mcVpl")
                {
                    double temp;
                    infile >> temp;
                    projetos[j].setMcVpl(temp);
                }
                if (_mapProjPropIdx[i] == "miVpl")
                {
                    double temp;
                    infile >> temp;
                    projetos[j].setMiVpl(temp);
                }
                if (_mapProjPropIdx[i] == "custos")
                {
                    double temp;
                    infile >> temp;
                    projetos[j].setCusto(temp);
                }
                if (_mapProjPropIdx[i] == "tempExec")
                {
                    int temp;
                    infile >> temp;
                    projetos[j].setTempExec(temp);
                }
                if (_mapProjPropIdx[i] == "inicioJanela")
                {
                    int temp;
                    infile >> temp;
                    projetos[j].setInicioJanela(temp);
                }
                if (_mapProjPropIdx[i] == "finalJanela")
                {
                    int temp;
                    infile >> temp;
                    projetos[j].setFinalJanela(temp);
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

                if (_mapSondasPropIdx[i] == "coordX")
                {
                    double temp;
                    infile >> temp;
                    sondas[j].setCoordX(temp);
                }
                if (_mapSondasPropIdx[i] == "coordY")
                {
                    double temp;
                    infile >> temp;
                    sondas[j].setCoordY(temp);
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

