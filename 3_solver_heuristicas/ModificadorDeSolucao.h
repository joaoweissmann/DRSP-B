#ifndef MODIFICADOR_DE_SOLUCAO
#define MODIFICADOR_DE_SOLUCAO

#include <bits/stdc++.h>
#include "Solucao.h"

// TODO: avaliar modificar só para nodes de projeto

class ModificadorDeSolucao
{
    public:
        ModificadorDeSolucao();

        Solucao inserirProjeto(Solucao);

        Solucao tentaInserirNodeDeProjeto(Solucao);
        Solucao tentaChegarProjParaTras(Solucao);
        Solucao tentaChegarProjParaFrente(Solucao);

        Solucao tentaInserirNodeDeJanela(Solucao);
        Solucao tentaColocarDiffParaFrente(Solucao);
        Solucao tentaColocarDiffParaTras(Solucao);
        Solucao atualizaListaDeAtividades(Solucao);
        Solucao tentaRealocarProjetosVizinhos(Solucao);

        Solucao removerProjeto(Solucao);

        Solucao verificaSetupRemovendoProjeto(Solucao);
};

#endif
