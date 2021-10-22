

#include <bits/stdc++.h>

class Solucao
{
    private:
        std::vector<std::list<int>> s;
        std::vector<std::vector<int>> sondas;
        std::vector<std::vector<int>> candidatos;
        double fitness;
        double custo;
        int total_free;
        int total_setup;
        int max_free;
    public:
        Solucao();
        
        // processador de solução
        void print_solucao();
        void verifica_solucao();
        
        // modificador de solução
        void add_projeto_posicao();
        void tenta_chegar_proj_para_tras();
        void tenta_chegar_proj_para_frente();
        void tenta_inserir_node_de_projeto();
        void tenta_colocar_diff_para_frente();
        void tenta_colocar_diff_para_tras();
        void atualiza_lista_de_atividades();
        void tenta_realocar_projetos_vizinhos();
        void tenta_inserir_node_de_janela();
        void verifica_setup_removendo_projeto();
        void remove_projeto_posicao();
        
        // util global
        void construir_RCL();
        void pre_processamento();
        
        // movimentador em vizinhanças
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

        // construtor heuristico
        void construir_solucao();
        void rodar_heuristica();

        // executador de busca local
        void busca_local();
        void busca_VND();
        void busca_RVND();

        // executador de metaheuristicas
        void multstart_heuristic();
        void iterated_greedy();
        void rodar_heuristica_com_busca_local();
        void GRASP_VND();
        void GRASP_RVND();
        void ILS_VND();
        void ILS_RVND();
        void rodar_heuristicas_varios_arquivos();
};

