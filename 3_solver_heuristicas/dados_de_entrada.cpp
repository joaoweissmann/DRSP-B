
#include <bits/stdc++.h>
#include "dados_de_entrada.h"

using namespace std;

// função para ler os dados de entrada das instâncias
DadosEntrada::DadosEntrada(string filename)
{
    ifstream infile (filename);

    if (infile.is_open())
    {
        cout << endl << endl;
        cout << "Arquivo aberto corretamente." << endl;
        cout << "Lendo dados..." << endl;
        cout << endl;
        
        int n_projetos, t_init, t_final, delta, n_periodos;
        double capital_total;
        
        // ler primeira linha com dados gerais
        infile >> n_projetos >> capital_total >> t_init >> t_final >> delta >> n_periodos;

        int propriedades_proj=23;

        vector<vector<double>> projetos;

        // resize
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
        map <string, int> mapProp2Indice;
        mapProp2Indice.insert(pair<string,int>("coord_x", 0));
        mapProp2Indice.insert(pair<string,int>("coord_y", 1));
        mapProp2Indice.insert(pair<string,int>("bacia", 2));
        mapProp2Indice.insert(pair<string,int>("nome", 3));
        mapProp2Indice.insert(pair<string,int>("maturidade", 4));
        mapProp2Indice.insert(pair<string,int>("qualidade", 5));
        mapProp2Indice.insert(pair<string,int>("play", 6));
        mapProp2Indice.insert(pair<string,int>("soterramento", 7));
        mapProp2Indice.insert(pair<string,int>("pcgna", 8));
        mapProp2Indice.insert(pair<string,int>("geracao", 9));
        mapProp2Indice.insert(pair<string,int>("migracao", 10));
        mapProp2Indice.insert(pair<string,int>("reservatorio", 11));
        mapProp2Indice.insert(pair<string,int>("geometria", 12));
        mapProp2Indice.insert(pair<string,int>("retencao", 13));
        mapProp2Indice.insert(pair<string,int>("pshc", 14));
        mapProp2Indice.insert(pair<string,int>("mc_vol", 15));
        mapProp2Indice.insert(pair<string,int>("mi_vol", 16));
        mapProp2Indice.insert(pair<string,int>("mc_vpl", 17));
        mapProp2Indice.insert(pair<string,int>("mi_vpl", 18));
        mapProp2Indice.insert(pair<string,int>("custo", 19));
        mapProp2Indice.insert(pair<string,int>("temp_exec", 20));
        mapProp2Indice.insert(pair<string,int>("inicio_janela", 21));
        mapProp2Indice.insert(pair<string,int>("final_janela", 22));

        // array sondas (n_sondas, 2)
        int n_sondas;
        infile >> n_sondas;
        int propriedades_sondas=2;
        
        vector<vector<double>> sondas;
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
        map<string, int> mapSondas;
        mapSondas.insert(pair<string, int>("coord_x", 0));
        mapSondas.insert(pair<string, int>("coord_y", 1)); 

        // array desloc ((n_projetos+n_sondas), (n_projetos+n_sondas))
        vector<vector<double>> desloc;
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

