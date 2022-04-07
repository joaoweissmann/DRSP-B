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

#ifndef EXECUTADOR_DE_METAHEURISTICAS
#define EXECUTADOR_DE_METAHEURISTICAS

#include <bits/stdc++.h>
#include "ConstrutorHeuristico.h"
#include "MovimentadorEmVizinhancas.h"
#include <dirent.h>
#include "LeitorDeDados.h"

class ExecutadorDeMetaheuristicas
{
    private:
        int _estrutura;
        int _modoRealoc;
        int _criterio;
        double _alpha;
        int _modoBusca;
        int _modoPerturba;
        int _nivelPerturba;
    
    public:
        ExecutadorDeMetaheuristicas();
        ExecutadorDeMetaheuristicas(int estrutura, int modoRealoc, int criterio, double alpha, int modoBusca, 
                                    int modoPerturba, int nivelPerturba);
        
        void setAlpha(double alpha);
        void setNivelPerturba(int nivelPerturba);
        
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> multStartHeuristic(DadosDeEntrada dataset,
                                                                                                        int nIter, int modoDebug);

        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> GRASP(DadosDeEntrada dataset,
                                                                                                        int nIter, int modoDebug, 
                                                                                                        std::set<int> vizinhancasinit, std::set<int> vizinhancasFinal,
                                                                                                        int nivelIntensifica);
        
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> GRASPadaptativo(DadosDeEntrada dataset,
                                                                                                        int nIter, int modoDebug, 
                                                                                                        std::set<int> vizinhancasinit, std::set<int> vizinhancasFinal,
                                                                                                        int nivelIntensifica, int nIterMelhora, double taxaAlpha, int nIterAlpha);

        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> ILS(DadosDeEntrada dataset,
                                                                                                        int nIter, int modoDebug,
                                                                                                        std::set<int> vizinhancasinit, std::set<int> vizinhancasFinal,
                                                                                                        double aceitacaoLimite, int nivelIntensifica);
        
        std::tuple<long long, std::map<Sonda, std::vector<Alocacao>>, double, double, int> ILSadaptativo(DadosDeEntrada dataset,
                                                                                                        int nIter, int modoDebug,
                                                                                                        std::set<int> vizinhancasinit, std::set<int> vizinhancasFinal,
                                                                                                        double aceitacaoLimite, int nivelIntensifica, int nIterMelhora, int taxaPerturba, double taxaAceitacao);

        void rodarVariosArquivos(const char * caminho, int nIter, int modoDebug,
                                                        std::set<int> vizinhancasinit, std::set<int> vizinhancasFinal,
                                                        double aceitacaoLimite, int nivelIntensifica,
                                                        int nIterMelhora, double taxaAlpha, int nIterAlpha,
                                                        int taxaPerturba, double taxaAceitacao);
        
        void rodarVariosArquivosSensibilidade(const char * caminho, int modoDebug,
                                                        std::set<int> vizinhancasinit, std::set<int> vizinhancasFinal);
};

#endif

