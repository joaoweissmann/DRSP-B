// Copyright 2021 João Ricardo Weissmann Santos
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <bits/stdc++.h>
#include "Testador.h"

///*
// main original
int main()
{
    Testador test;
    //test.testarProjeto();
    //test.testarSonda();
    //test.testarCalculadorDeDesloc();
    //test.testarDadosDeEntrada();
    //test.testarLeitorDeDados();
    //test.testarIntervalo();
    //test.testarAlocacao();
    //test.testarAlocacoes();
    //test.testarSolucao();
    //test.testarConstrutorHeuristico();
    test.testarExecutadorDeMetaheuristicas();

    return 0;
};
//*/

/*
// main para IRACE GRASP adaptativo
// argumentos:
//     1: std::string filename
//     2: double alpha
//     3: double taxaAlpha
//     4: int nIterMelhora
//     5: int nIterAlpha
int main(int argc, char* argv[])
{
    if (argc != 6) 
    {
        std::cerr << "Uso: " << argv[0] << " <filename> <alpha> <taxaAlpha> <nIterMelhora> <nIterAlpha>" << std::endl;
        return 1;
    }

    // converte parâmetros de linha de comando
    std::string filename = argv[1];

    double alpha;
    std::istringstream(argv[2]) >> alpha;

    double taxaAlpha;
    std::istringstream(argv[3]) >> taxaAlpha;

    int nIterMelhora;
    std::istringstream(argv[4]) >> nIterMelhora;

    int nIterAlpha;
    std::istringstream(argv[5]) >> nIterAlpha;

    // Imprimi variáveis
    //std::cout << "Filename: " << filename << std::endl;
    //std::cout << "Alpha: " << alpha << std::endl;
    //std::cout << "Taxa Alpha: " << taxaAlpha << std::endl;
    //std::cout << "nIterMelhora: " << nIterMelhora << std::endl;
    //std::cout << "nIterAlpha: " << nIterAlpha << std::endl;

    // inicializa conjunto de vizinhanças para busca local principal
    std::set<int> vizinhancasInit;
    vizinhancasInit.insert(1); // shift_1x0_interRota
    vizinhancasInit.insert(2); // shift_2x0_interRota
    vizinhancasInit.insert(3); // swap_1x1_interRota
    //vizinhancasInit.insert(4); // swap_2x1_interRota //
    //vizinhancasInit.insert(5); // swap_2x2_interRota //
    vizinhancasInit.insert(6); // reinsercao1
    vizinhancasInit.insert(7); // reinsercao2
    vizinhancasInit.insert(8); // inserirNovoFO
    vizinhancasInit.insert(9); // swap_1x1_FO
    //vizinhancasInit.insert(10); // swap_2x1_FO //
    //vizinhancasInit.insert(11); // swap_1x2_FO //
    //vizinhancasInit.insert(12); // swap_2x2_FO //

    // inicializa conjunto de vizinhanças para busca local final
    std::set<int> vizinhancasFinal;
    vizinhancasFinal.insert(1); // shift_1x0_interRota
    vizinhancasFinal.insert(2); // shift_2x0_interRota
    vizinhancasFinal.insert(3); // swap_1x1_interRota
    vizinhancasFinal.insert(4); // swap_2x1_interRota
    //vizinhancasFinal.insert(5); // swap_2x2_interRota
    vizinhancasFinal.insert(6); // reinsercao1
    vizinhancasFinal.insert(7); // reinsercao2
    vizinhancasFinal.insert(8); // inserirNovoFO
    vizinhancasFinal.insert(9); // swap_1x1_FO
    vizinhancasFinal.insert(10); // swap_2x1_FO
    vizinhancasFinal.insert(11); // swap_1x2_FO
    //vizinhancasFinal.insert(12); // swap_2x2_FO

    // le os dados da instância
    LeitorDeDados leitor;
    DadosDeEntrada dataset = leitor.lerDadosDeEntrada(filename);

    // define parâmetros que não vão ser otimizados
    int nIter = 1000 / (std::sqrt(dataset.getNProjetos() / 3)); // 100
    int nIterConverge = nIter / 5; // 20
    int maxIterFO = 10;
    int modoDebug = 0;
    int estrutura = 1;
    int modoRealoc = 1;
    int criterio = 1;
    int modoBusca = 14;
    int modoPerturba = 13;
    int nivelIntensifica = 0;
    int nivelPerturba = 2;

    // chama metaheurística usando parâmetros de linha de comando
    long long tempo;
    std::map<Sonda, std::vector<Alocacao>> alocsMap;
    double fitness;
    double gastos;
    int totalFree;
    ExecutadorDeMetaheuristicas executador{estrutura, modoRealoc, criterio, alpha, modoBusca, modoPerturba, nivelPerturba};
    std::tie(tempo, alocsMap, fitness, gastos, totalFree) = executador.GRASPadaptativo(dataset, nIter, modoDebug, vizinhancasInit, vizinhancasFinal, nivelIntensifica, nIterMelhora, taxaAlpha, nIterAlpha, maxIterFO, nIterConverge);
    
    // imprimi função objetivo
    std::cout << -fitness << std::endl;

    return 0;
}
*/

/*
// main para IRACE ILS adaptativo
// argumentos:
//     1: std::string filename
//     2: double alpha
//     3: int nivelPerturba
//     4: double aceitacaoLimite
//     5: int taxaPerturba
//     6: double taxaAceitacao
//     7: double alphaRestart
//     8: int nIterMelhora
//     9: int nIterRestart
int main(int argc, char* argv[])
{
    if (argc != 10) 
    {
        std::cerr << "Uso: " << argv[0] << " <filename> <alpha> <nivelPerturba> <aceitacaoLimite> <taxaPerturba> <taxaAceitacao> <alphaRestart> <nIterMelhora> <nIterRestart>" << std::endl;
        return 1;
    }

    // converte parâmetros de linha de comando
    std::string filename = argv[1];

    double alpha;
    std::istringstream(argv[2]) >> alpha;

    int nivelPerturba;
    std::istringstream(argv[3]) >> nivelPerturba;

    double aceitacaoLimite;
    std::istringstream(argv[4]) >> aceitacaoLimite;

    int taxaPerturba;
    std::istringstream(argv[5]) >> taxaPerturba;

    double taxaAceitacao;
    std::istringstream(argv[6]) >> taxaAceitacao;

    double alphaRestart;
    std::istringstream(argv[7]) >> alphaRestart;

    int nIterMelhora;
    std::istringstream(argv[8]) >> nIterMelhora;

    int nIterRestart;
    std::istringstream(argv[9]) >> nIterRestart;

    // Imprimi variáveis
    //std::cout << "Filename: " << filename << std::endl;
    //std::cout << "Alpha: " << alpha << std::endl;
    //std::cout << "nivelPerturba: " << nivelPerturba << std::endl;
    //std::cout << "aceitacaoLimite: " << aceitacaoLimite << std::endl;
    //std::cout << "taxaPerturba: " << taxaPerturba << std::endl;
    //std::cout << "taxaAceitacao: " << taxaAceitacao << std::endl;
    //std::cout << "alphaRestart: " << alphaRestart << std::endl;
    //std::cout << "nIterMelhora: " << nIterMelhora << std::endl;
    //std::cout << "nIterRestart: " << nIterRestart << std::endl;

    // inicializa conjunto de vizinhanças para busca local principal
    std::set<int> vizinhancasInit;
    vizinhancasInit.insert(1); // shift_1x0_interRota
    vizinhancasInit.insert(2); // shift_2x0_interRota
    vizinhancasInit.insert(3); // swap_1x1_interRota
    //vizinhancasInit.insert(4); // swap_2x1_interRota //
    //vizinhancasInit.insert(5); // swap_2x2_interRota //
    vizinhancasInit.insert(6); // reinsercao1
    vizinhancasInit.insert(7); // reinsercao2
    vizinhancasInit.insert(8); // inserirNovoFO
    vizinhancasInit.insert(9); // swap_1x1_FO
    //vizinhancasInit.insert(10); // swap_2x1_FO //
    //vizinhancasInit.insert(11); // swap_1x2_FO //
    //vizinhancasInit.insert(12); // swap_2x2_FO //

    // inicializa conjunto de vizinhanças para busca local final
    std::set<int> vizinhancasFinal;
    vizinhancasFinal.insert(1); // shift_1x0_interRota
    vizinhancasFinal.insert(2); // shift_2x0_interRota
    vizinhancasFinal.insert(3); // swap_1x1_interRota
    vizinhancasFinal.insert(4); // swap_2x1_interRota
    //vizinhancasFinal.insert(5); // swap_2x2_interRota
    vizinhancasFinal.insert(6); // reinsercao1
    vizinhancasFinal.insert(7); // reinsercao2
    vizinhancasFinal.insert(8); // inserirNovoFO
    vizinhancasFinal.insert(9); // swap_1x1_FO
    vizinhancasFinal.insert(10); // swap_2x1_FO
    vizinhancasFinal.insert(11); // swap_1x2_FO
    //vizinhancasFinal.insert(12); // swap_2x2_FO

    // le os dados da instância
    LeitorDeDados leitor;
    DadosDeEntrada dataset = leitor.lerDadosDeEntrada(filename);

    // define parâmetros que não vão ser otimizados
    int nIter = 1000 / (std::sqrt(dataset.getNProjetos() / 3)); // 100
    int nIterConverge = nIter / 5; // 20
    int maxIterFO = 10;
    int modoDebug = 0;
    int estrutura = 1;
    int modoRealoc = 1;
    int criterio = 1;
    int modoBusca = 14;
    int modoPerturba = 13;
    int nivelIntensifica = 0;

    // chama metaheurística usando parâmetros de linha de comando
    long long tempo;
    std::map<Sonda, std::vector<Alocacao>> alocsMap;
    double fitness;
    double gastos;
    int totalFree;
    ExecutadorDeMetaheuristicas executador{estrutura, modoRealoc, criterio, alpha, modoBusca, modoPerturba, nivelPerturba};
    std::tie(tempo, alocsMap, fitness, gastos, totalFree) = executador.ILSadaptativo(dataset, nIter, modoDebug, vizinhancasInit, vizinhancasFinal, aceitacaoLimite, nivelIntensifica, nIterMelhora, taxaPerturba, taxaAceitacao, nIterRestart, alphaRestart, maxIterFO, nIterConverge);
    
    // imprimi função objetivo
    std::cout << -fitness << std::endl;

    return 0;
}
*/
