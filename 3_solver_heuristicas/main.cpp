

#include <bits/stdc++.h>
#include "Testador.h"
#include "LeitorDeDados.h"

int main()
{
    Testador test;
    test.testarProjeto();
    test.testarSonda();
    test.testarVertice();

    std::string filename;
    filename = "/home/joaoweissmann/Documents/repos/synthetic_instance_generator/synthetic_instance_generator/1_gerador_instancias_sinteticas/instancias/instancia_10projetos_2sondas_delta_t28.dat";

    LeitorDeDados leitor;
    DadosDeEntrada dataset = leitor.lerDadosDeEntrada(filename);

    return 0;
};

