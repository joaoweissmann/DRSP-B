// TODO: debug mode
// TODO: asserts


#include <bits/stdc++.h>
#include "LeitorDeDados.h"

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
        
        std::cout << std::endl << std::endl;
        std::cout << "Lendo dados gerais" << std::endl;
        std::cout << std::endl;

        int nProjetos, tInit, tFinal, delta, nPeriodos;
        double capitalTotal;
        infile >> nProjetos >> capitalTotal >> tInit >> tFinal >> delta >> nPeriodos;

        std::cout << std::endl << std::endl;
        std::cout << "Dados gerais lidos" << std::endl;
        std::cout << std::endl;

        std::cout << std::endl << std::endl;
        std::cout << "Inserindo dados gerais dentro do dataset" << std::endl;
        std::cout << std::endl;

        dataset.setNProjetos(nProjetos);
        dataset.setCapitalTotal(capitalTotal);
        dataset.setTInit(tInit);
        dataset.setTFinal(tFinal);
        dataset.setDelta(delta);
        dataset.setNPeriodos(nPeriodos);

        std::cout << std::endl << std::endl;
        std::cout << "Dados gerais inseridos no dataset" << std::endl;
        std::cout << std::endl;

        std::cout << std::endl << std::endl;
        std::cout << "Inserindo no dataset propriedadesProj" << std::endl;
        std::cout << std::endl;

        int propriedadesProj=23;
        dataset.setPropriedadesProj(propriedadesProj);

        std::cout << std::endl << std::endl;
        std::cout << "propriedadesProj inserido no dataset" << std::endl;
        std::cout << std::endl;

        std::cout << std::endl << std::endl;
        std::cout << "Criando vetor de double para ler matriz de projetos" << std::endl;
        std::cout << std::endl;

        std::vector<std::vector<double>> projetos;
        projetos.resize(nProjetos);
        for (int i=0; i<nProjetos; i++)
        {
            projetos[i].resize(propriedadesProj);
        }
        for (int j=0; j<propriedadesProj; j++)
        {
            for (int i=0; i<nProjetos; i++)
            {
                infile >> projetos[i][j];
            }
        }

        std::cout << std::endl << std::endl;
        std::cout << "Matriz de projetos lida" << std::endl;
        std::cout << std::endl;

        std::cout << std::endl << std::endl;
        std::cout << "Inserindo matriz de projetos no dataset" << std::endl;
        std::cout << std::endl;

        dataset.setProjetos(projetos);

        std::cout << std::endl << std::endl;
        std::cout << "Matriz de projetos inserida no dataset" << std::endl;
        std::cout << std::endl;

        int nSondas;
        infile >> nSondas;
        dataset.setNSondas(nSondas);
        int propriedadesSondas=2;
        dataset.setPropriedadesSondas(propriedadesSondas);
        
        std::vector<std::vector<double>> sondas;
        sondas.resize(nSondas);
        for (int i=0; i<nSondas; i++)
        {
            sondas[i].resize(propriedadesSondas);
        }
        for (int j=0; j<propriedadesSondas; j++)
        {
            for (int i=0; i<nSondas; i++)
            {
                infile >> sondas[i][j];
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

