
#include <bits/stdc++.h>
#include "dados_de_entrada.h"

using namespace std;

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

int main()
{
    string filename;
    filename = "/home/joaoweissmann/Documents/repos/synthetic_instance_generator/synthetic_instance_generator/1_gerador_instancias_sinteticas/instancias/instancia_10projetos_2sondas_delta_t28.dat";
    
    DadosEntrada dados(filename);

    dados.printDadosEntrada();

    return 0;
};