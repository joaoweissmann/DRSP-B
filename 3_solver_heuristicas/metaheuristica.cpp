
#include <bits/stdc++.h>

using namespace std;

// função para ler os dados de entrada das instâncias
void read_data(string filename)
{
    ifstream infile (filename);

    if (infile.is_open())
    {
        cout << "Arquivo aberto corretamente." << endl;
        cout << "Lendo dados..." << endl;
        cout << endl;
        
        int n_projetos, t_init, t_final, delta, n_periodos;
        double capital_total;
        
        // ler primeira linha com dados gerais
        infile >> n_projetos >> capital_total >> t_init >> t_final >> delta >> n_periodos;

        cout << "A instância tem: " << endl;
        cout << n_projetos << " projetos" << endl;
        cout << capital_total << " como orçamento total" << endl;
        cout << t_init << " como o tempo inicial" << endl;
        cout << t_final << " como o tempo final" << endl;
        cout << delta << " como delta tempo" << endl;
        cout << n_periodos << " períodos de tempo" << endl;
        cout << endl;

        // array projetos (n_projetos, propriedades_proj)
        int propriedades_proj=23;
        double projetos[n_projetos][propriedades_proj];

        for (int j=0; j<propriedades_proj; j++)
        {
            for (int i=0; i<n_projetos; i++)
            {
                infile >> projetos[i][j];
            }
        }
        /*
        cout << "dados lidos: " << endl;
        for (int j=0; j<propriedades_proj; j++)
        {
            for (int i=0; i<n_projetos; i++)
            {
                cout << projetos[i][j] << " " ;
            }
            cout << endl;
        }
        */

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

        cout << "Dados lidos dos projetos: " << endl;
        for (auto itr=mapProp2Indice.begin(); itr!=mapProp2Indice.end(); ++itr)
        {
            cout << "Propriedade " << itr->first << " : ";
            for (int i=0; i<n_projetos; i++)
            {
                cout << projetos[i][itr->second] << " " ;
            }
            cout << endl;
        }

        // array sondas (n_sondas, 2)

        // criar mapa de propriedade para índice de sondas

        // array desloc ((n_projetos+n_sondas), (n_projetos+n_sondas))

        // fechar aquivo

        // retornar tudo numa struct
    }
    else
    {
        cout << "Não foi possível abrir o arquivo." << endl;
    }

}

int main()
{
    string filename;
    filename = "/home/joaoweissmann/Documents/repos/synthetic_instance_generator/synthetic_instance_generator/1_gerador_instancias_sinteticas/instancias/instancia_10projetos_2sondas_delta_t28.dat";
    read_data(filename);
    return 0;
}

