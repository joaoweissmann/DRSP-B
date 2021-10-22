

#include <bits/stdc++.h>

#include "DadosDeEntrada.h"

DadosDeEntrada::DadosDeEntrada(std::string filename)
{
    std::ifstream infile (filename);

    if (infile.is_open())
    {
        cout << std::endl << std::endl;
        cout << "Arquivo aberto corretamente." << std::endl;
        cout << "Lendo dados..." << std::endl;
        cout << std::endl;
        
        infile >> n_projetos >> capital_total >> t_init >> t_final >> delta >> n_periodos;

        propriedades_proj=23;

        projetos.resize(n_projetos);
        for (int i=0; i<n_projetos; i++)
        {
            projetos[i].resize(propriedades_proj);
        }

        for (int j=0; j<propriedades_proj; j++)
        {
            for (int i=0; i<n_projetos; i++)
            {
                infile >> projetos[i][j];
            }
        }
        
        // criar mapa de propriedade para índice de projetos
        // map <string, int> mapProp2Indice;
        "coord_x", 0));
        "coord_y", 1));
        "bacia", 2));
        "nome", 3));
        "maturidade", 4));
        "qualidade", 5));
        "play", 6));
        "soterramento", 7));
        "pcgna", 8));
        "geracao", 9));
        "migracao", 10));
        "reservatorio", 11));
        "geometria", 12));
        "retencao", 13));
        "pshc", 14));
        "mc_vol", 15));
        "mi_vol", 16));
        "mc_vpl", 17));
        "mi_vpl", 18));
        "custo", 19));
        "temp_exec", 20));
        "inicio_janela", 21));
        "final_janela", 22));

        // array sondas (n_sondas, 2)
        // int n_sondas;
        infile >> n_sondas;
        // int propriedades_sondas=2;
        propriedades_sondas=2;
        
        // vector<vector<double>> sondas;
        sondas.resize(n_sondas);
        for (int i=0; i<n_sondas; i++)
        {
            sondas[i].resize(propriedades_sondas);
        }
        
        for (int j=0; j<propriedades_sondas; j++)
        {
            for (int i=0; i<n_sondas; i++)
            {
                infile >> sondas[i][j];
            }
        }
        
        // criar mapa de propriedade para índice de sondas
        // map<string, int> mapSondas;
        mapSondas.insert(pair<string, int>("coord_x", 0));
        mapSondas.insert(pair<string, int>("coord_y", 1)); 

        // array desloc ((n_projetos+n_sondas), (n_projetos+n_sondas))
        // vector<vector<double>> desloc;
        desloc.resize(n_projetos+n_sondas);
        for (int i=0; i<(n_projetos+n_sondas); i++)
        {
            desloc[i].resize(n_projetos+n_sondas);
        }
        
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            for (int j=0; j<n_projetos+n_sondas; j++)
            {
                infile >> desloc[i][j];
            }
        }

        // fechar aquivo
        infile.close();

        cout << "Dados lidos." << endl;
    }
    else
    {
        cout << "Não foi possível abrir o arquivo." << endl;
    }

}

void DadosEntrada::printDadosEntrada()
{
    cout << endl;
    cout << "A instância tem: " << endl;
    cout << n_projetos << " projetos" << endl;
    cout << capital_total << " como orçamento total" << endl;
    cout << t_init << " como o tempo inicial" << endl;
    cout << t_final << " como o tempo final" << endl;
    cout << delta << " como delta tempo" << endl;
    cout << n_periodos << " períodos de tempo" << endl;
    cout << n_sondas << " sondas disponíveis" << endl;
    cout << endl;
    
    cout << "Dados lidos de projetos:" << endl;
    for (int j=0; j<propriedades_proj; j++)
    {
        for (int i=0; i<n_projetos; i++)
        {
            cout << projetos[i][j] << " ";
        } cout << endl;
    } cout << endl;

    cout << "Dados lidos dos projetos: " << endl;
    for (auto itr=mapProjetos.begin(); itr!=mapProjetos.end(); ++itr)
    {
        cout << "Propriedade " << itr->first << " : ";
        for (int i=0; i<n_projetos; i++)
        {
            cout << projetos[i][itr->second] << " ";
        }
        cout << endl;
    } cout << endl;

    cout << "dados lidos de sondas: " << endl;
    for (int j=0; j<propriedades_sondas; j++)
    {
        for (int i=0; i<n_sondas; i++)
        {
            cout << sondas[i][j] << " ";
        } cout << endl;
    } cout << endl;

    cout << "dados lidos de sondas: " << endl;
    for (auto itr=mapSondas.begin(); itr!=mapSondas.end(); ++itr)
    {
        cout << "Propriedade " << itr->first << ": ";
        for (int i=0; i<n_sondas; i++)
        {
            cout << sondas[i][itr->second] << " " ;
        } cout << endl;
    } cout << endl;
    
    cout << "deslocamentos lidos: " << endl;
    for (int i=0; i<n_projetos+n_sondas; i++)
    {
        for (int j=0; j<n_projetos+n_sondas; j++)
        {
            cout << desloc[i][j] << " ";
        } cout << endl;
    } cout << endl;
}

