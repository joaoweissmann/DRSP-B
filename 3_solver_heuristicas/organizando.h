

#include <bits/stdc++.h>

class Organizando
{
    public:
        
        // verificador de solucao
        void verificarSondas();
        void verificarMaxFree();
        void verificarTotalFree();
        void verificarTotalSetup();
        void verificarFuncaoObjetivo();
        void verificarRestricaoOrcamento();
        void verificarRestricaoUnicidadeProjetos();
        void verificarRestricaoTimeWindows();
        void verificarRestricaoSchedulling();
        void verificarRestricaoContinuidade();
        void verificarSolucao();
        
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

