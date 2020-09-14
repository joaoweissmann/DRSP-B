#include <iostream>
#include <fstream>
#include <string>
#include <ilcplex/ilocplex.h>

ILOSTLBEGIN

using namespace std;

int main()
{
    IloEnv env;
    try
    {
        string filename="instancia_mestrado.dat";
        ifstream file;
        
        // reading data from file
        file.open(filename);
        if (!file)
        {
            cerr << "ERRO ao abrir o arquivo " << filename << endl;
        }
        IloInt n_projetos, capital_total, n_sondas;
        IloNumArray coords_x(env), coords_y(env), bacias(env), nome_projetos(env);
        IloNumArray maturidades(env), qualidades_dado(env), plays(env), soterramentos(env), pcgnas(env);
        IloNumArray geracao(env), migracao(env), reservatorio(env), geometria(env), retencao(env), pshc(env);
        IloNumArray medias_volume_condicional(env), medias_volume_incondicional(env);
        IloNumArray medias_vpl_condicional(env), medias_vpl_incondicional(env);
        IloNumArray custos(env), tempos_exec(env), inicio_janela(env), final_janela(env);
        IloNumArray sondas_x(env), sondas_y(env);
        file >> n >> cap_total;
        file >> coords_x, coords_y, bacias, nome_projetos;
        file >> maturidades, qualidades_dado, plays, soterramentos, pcgnas;
        file >> geracao, migracao, reservatorio, geometria, retencao, pshc;
        file >> medias_volume_condicional, medias_volume_incondicional;
        file >> medias_vpl_condicional, medias_vpl_incondicional;
        file >> custos, tempos_exec, inicio_janela, final_janela;
        file >> n_sondas >> sondas_x, sondas_y;
        // end reading data
        
        // criando a variável de decisão
        IloNumVarArray x(env, n, 0, 1, ILOINT);
        
        // criando expressão para a restrição
        IloExpr expr1(env); 
        for (int i = 0; i < n; ++i) 
        {
            expr1 += caps[i] * x[i];
        }
        // criando a restrição 1
        IloRange r1(env, 0, expr1, cap_total);
        // deletando expressão
        expr1.end();

        // criando expressão para a função objetivo
        IloExpr expr2(env); 
        for (int i = 0; i < n; ++i) 
        {
            expr2 += values[i] * x[i];
        }
        // criando a função objetivo
        IloObjective obj(env, expr2, IloObjective::Maximize);
        // deletando expressão
        expr2.end();

        // criando o modelo e adicionando restrições e FO
        IloModel model(env);
        model.add(r1);
        model.add(obj);

        // declarando o otimizador
        IloCplex cplex(model);
        // resolvendo o modelo
        cplex.solve();
        
        // printando status da otimização
        env.out() << "Solution status = " << cplex.getStatus() << endl;

        // printando valor obtido para a função objetivo
        env.out() << "Solution value  = " << cplex.getObjValue() << endl;

        // delcarando objeto que vai conter valor das variáveis de decisão
        IloNumArray vals(env);
        
        // pegando valores atribuídos às variáveis de decisão
        cplex.getValues(vals, x);
        env.out() << "Values        = " << vals << endl;
        
        // exportando modelo
        cplex.exportModel("knapsack_model_CPLEX.lp");

        // closing file
        file.close();
    }
    catch (IloException& e) 
    {
        cerr << "Erro na chamada da API: " << e << endl;
    }
    catch (...) 
    {
        cerr << "Erro desconhecido" << endl;
    }
    env.end();
    return 0;
}