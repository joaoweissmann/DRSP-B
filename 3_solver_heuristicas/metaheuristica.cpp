
#include <bits/stdc++.h>

using namespace std;

// struct para dados de entrada
struct DadosEntrada
{
    int n_projetos, n_sondas, n_periodos;
    int propriedades_proj, propriedades_sondas;
    int t_init, t_final, delta;
    double capital_total;
    double * projetos;
    double * sondas;
    double * desloc;
    map<string, int> mapProjetos, mapSondas;
};

void printDadosEntrada(DadosEntrada dados)
{
    cout << "A instância tem: " << endl;
    cout << dados.n_projetos << " projetos" << endl;
    cout << dados.capital_total << " como orçamento total" << endl;
    cout << dados.t_init << " como o tempo inicial" << endl;
    cout << dados.t_final << " como o tempo final" << endl;
    cout << dados.delta << " como delta tempo" << endl;
    cout << dados.n_periodos << " períodos de tempo" << endl;
    cout << dados.n_sondas << " sondas disponíveis" << endl;
    cout << endl;
    

}

// função para ler os dados de entrada das instâncias
DadosEntrada read_data(string filename)
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
        
        cout << "dados lidos de projetos: " << endl;
        for (int j=0; j<propriedades_proj; j++)
        {
            for (int i=0; i<n_projetos; i++)
            {
                cout << projetos[i][j] << " " ;
            }
            cout << endl;
        } cout << endl;
        
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
        } cout << endl;

        // array sondas (n_sondas, 2)
        int n_sondas;
        infile >> n_sondas;
        int propriedades_sondas=2;
        
        double sondas[n_sondas][2];
        for (int j=0; j<propriedades_sondas; j++)
        {
            for (int i=0; i<n_sondas; i++)
            {
                infile >> sondas[i][j];
            }
        }

        cout << "dados lidos de sondas: " << endl;
        for (int j=0; j<propriedades_sondas; j++)
        {
            for (int i=0; i<n_sondas; i++)
            {
                cout << sondas[i][j] << " ";
            } cout << endl;
        } cout << endl;


        // criar mapa de propriedade para índice de sondas
        map<string, int> mapSondas;
        mapSondas.insert(pair<string, int>("coord_x", 0));
        mapSondas.insert(pair<string, int>("coord_y", 1)); 

        cout << "dados lidos de sondas: " << endl;
        for (auto itr=mapSondas.begin(); itr!=mapSondas.end(); ++itr)
        {
            cout << "Propriedade " << itr->first << ": ";
            for (int i=0; i<n_sondas; i++)
            {
                cout << sondas[i][itr->second] << " " ;
            } cout << endl;
        } cout << endl;

        // array desloc ((n_projetos+n_sondas), (n_projetos+n_sondas))
        double desloc[n_projetos+n_sondas][n_projetos+n_sondas];
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            for (int j=0; j<n_projetos+n_sondas; j++)
            {
                infile >> desloc[i][j];
            }
        }

        cout << "deslocamentos lidos: " << endl;
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            for (int j=0; j<n_projetos+n_sondas; j++)
            {
                cout << desloc[i][j] << " ";
            } cout << endl;
        } cout << endl;

        // fechar aquivo
        infile.close();

        // retornar tudo numa struct
        DadosEntrada result;
        result.n_projetos = n_projetos;
        result.n_sondas = n_sondas;
        result.n_periodos = n_periodos;
        result.propriedades_proj = propriedades_proj;
        result.propriedades_sondas = propriedades_sondas;
        result.t_init = t_init;
        result.t_final = t_final;
        result.delta = delta;
        result.capital_total = capital_total;
        result.projetos = &projetos[0][0];
        result.sondas = &sondas[0][0];
        result.desloc = &desloc[0][0];
        result.mapProjetos = mapProp2Indice;
        result.mapSondas = mapSondas;

        cout << "testando com ponteiros (dentro da função):" << endl;
        for (int j=0; j<result.propriedades_proj; j++)
        {
            for (int i=0; i<n_projetos; i++)
            {
                cout << *(result.projetos + j + i*result.propriedades_proj) << " ";
            } cout << endl;
        } cout << endl;

        return (result);
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
    
    DadosEntrada dados;
    dados = read_data(filename);

    // verificando dados lidos
    cout << "testando com ponteiros (dentro da função):" << endl;
    for (int j=0; j<dados.propriedades_proj; j++)
    {
        for (int i=0; i<dados.n_projetos; i++)
        {
            cout << *(dados.projetos + j + i*dados.propriedades_proj) << " ";
        } cout << endl;
    } cout << endl;
    //printDadosEntrada(dados);

    return 0;
}

