
#include <bits/stdc++.h>

using namespace std;

// struct para dados de entrada
struct DadosEntrada
{
    int n_projetos, n_sondas, n_periodos;
    int propriedades_proj, propriedades_sondas;
    int t_init, t_final, delta;
    double capital_total;
    // double * projetos;
    vector<vector<double>> projetos;
    // double * sondas;
    vector<vector<double>> sondas;
    // double * desloc;
    vector<vector<double>> desloc;
    map<string, int> mapProjetos, mapSondas;
};

class Solucao
{
    // TODO: separar métodos da classe dos que usam a classe
    // TODO: conferir tipos dos membros
    // TODO: conferir tipos de return dos métodos
    // TODO: conferir inputs dos métodos
    private:
        vector<list<int>> s;
        vector<vector<int>> sondas;
        vector<vector<int>> candidatos;
        double fitness;
        double custo;
        int total_free;
        int total_setup;
        int max_free;
    public:
        Solucao();

        // TODO: gets e sets
        
        void print_solucao();
        void verifica_solucao();
        
        void add_projeto_posicao();

        void verifica_setup_removendo_projeto();
        void remove_projeto_posicao();
        
        void construir_RCL();
         
        void tenta_chegar_proj_para_tras();
        void tenta_chegar_proj_para_frente();
        void tenta_inserir_node_de_projeto();
        
        void tenta_colocar_diff_para_frente();
        void tenta_colocar_diff_para_tras();
        void atualiza_lista_de_atividades();
        void tenta_realocar_projetos_vizinhos();
        void tenta_inserir_node_de_janela();
        
        void construir_solucao();

        void rodar_heuristica();
        void multstart_heuristic();
        void iterated_greedy();
        
        void pre_processamento();
        
        void shift_1x0_interrota();
        void shift_2x0_interrota();
        void swap_1x1_interrota();
        void swap_2x1_interrota();
        void swap_2x2_interrota();
        void reinsercao_1_intrarota();
        void reinsercao_2_intrarota();
        void inserir_novo_fo();
        void swap_1x1_fo();
        void swap_1x2_fo();
        void swap_2x1_fo();
        void swap_2x2_fo();

        void perturbacao();

        void busca_local();
        void busca_VND();
        void busca_RVND();

        void GRASP_VND();
        void GRASP_RVND();
        void ILS_VND();
        void ILS_RVND();

        void rodar_heuristica_com_busca_local();
        void rodar_heuristicas_varios_arquivos();

};

void printDadosEntrada(DadosEntrada dados)
{
    cout << endl;
    cout << "A instância tem: " << endl;
    cout << dados.n_projetos << " projetos" << endl;
    cout << dados.capital_total << " como orçamento total" << endl;
    cout << dados.t_init << " como o tempo inicial" << endl;
    cout << dados.t_final << " como o tempo final" << endl;
    cout << dados.delta << " como delta tempo" << endl;
    cout << dados.n_periodos << " períodos de tempo" << endl;
    cout << dados.n_sondas << " sondas disponíveis" << endl;
    cout << endl;
    
    cout << "Dados lidos de projetos:" << endl;
    for (int j=0; j<dados.propriedades_proj; j++)
    {
        for (int i=0; i<dados.n_projetos; i++)
        {
            // cout << *(dados.projetos + j + i*dados.propriedades_proj) << " ";
            cout << dados.projetos[i][j] << " ";
        } cout << endl;
    } cout << endl;

    cout << "Dados lidos dos projetos: " << endl;
    for (auto itr=dados.mapProjetos.begin(); itr!=dados.mapProjetos.end(); ++itr)
    {
        cout << "Propriedade " << itr->first << " : ";
        for (int i=0; i<dados.n_projetos; i++)
        {
            // cout << *(dados.projetos + itr->second + i*dados.propriedades_proj) << " ";
            cout << dados.projetos[i][itr->second] << " ";
        }
        cout << endl;
    } cout << endl;

    cout << "dados lidos de sondas: " << endl;
    for (int j=0; j<dados.propriedades_sondas; j++)
    {
        for (int i=0; i<dados.n_sondas; i++)
        {
            // cout << *(dados.sondas + j + i*dados.propriedades_sondas) << " ";
            cout << dados.sondas[i][j] << " ";
        } cout << endl;
    } cout << endl;

    cout << "dados lidos de sondas: " << endl;
    for (auto itr=dados.mapSondas.begin(); itr!=dados.mapSondas.end(); ++itr)
    {
        cout << "Propriedade " << itr->first << ": ";
        for (int i=0; i<dados.n_sondas; i++)
        {
            // cout << *(dados.sondas + itr->second + i*dados.propriedades_sondas) << " ";
            cout << dados.sondas[i][itr->second] << " " ;
        } cout << endl;
    } cout << endl;
    
    cout << "deslocamentos lidos: " << endl;
    for (int i=0; i<dados.n_projetos+dados.n_sondas; i++)
    {
        for (int j=0; j<dados.n_projetos+dados.n_sondas; j++)
        {
            // cout << *(dados.desloc + j + i*(dados.n_projetos+dados.n_sondas)) << " ";
            cout << dados.desloc[i][j] << " ";
        } cout << endl;
    } cout << endl;

}

// função para ler os dados de entrada das instâncias
DadosEntrada read_data(string filename)
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

        // array projetos (n_projetos, propriedades_proj)
        int propriedades_proj=23;

        // double projetos[n_projetos][propriedades_proj];
        // double * projetos = new double[n_projetos * propriedades_proj];
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
                // infile >> *(projetos + j + i*propriedades_proj);
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
        
        // double sondas[n_sondas][2];
        // double * sondas = new double [n_sondas*propriedades_sondas];
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
                // infile >> *(sondas + j + i*propriedades_sondas);
                infile >> sondas[i][j];
            }
        }
        
        // criar mapa de propriedade para índice de sondas
        map<string, int> mapSondas;
        mapSondas.insert(pair<string, int>("coord_x", 0));
        mapSondas.insert(pair<string, int>("coord_y", 1)); 

        // array desloc ((n_projetos+n_sondas), (n_projetos+n_sondas))
        // double desloc[n_projetos+n_sondas][n_projetos+n_sondas];
        // double * desloc = new double [(n_projetos+n_sondas)*(n_projetos+n_sondas)];
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
                // infile >> *(desloc + j + i*(n_projetos+n_sondas));
                infile >> desloc[i][j];
            }
        }

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
        result.projetos = projetos;
        result.sondas = sondas;
        result.desloc = desloc;
        result.mapProjetos = mapProp2Indice;
        result.mapSondas = mapSondas;

        cout << "Dados lidos." << endl;

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

    printDadosEntrada(dados);

    return 0;
}

