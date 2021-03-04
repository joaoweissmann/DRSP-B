#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ilcplex/ilocplex.h>

ILOSTLBEGIN

typedef IloArray<IloNumVarArray> NumVarMatrix2D;
typedef IloArray<NumVarMatrix2D> NumVarMatrix3D;

typedef IloArray<IloBoolVarArray> BoolVarMatrix2D;
typedef IloArray<BoolVarMatrix2D> BoolVarMatrix3D;

typedef IloArray<IloNumArray> NumMatrix2D;
typedef IloArray<NumMatrix2D> NumMatrix3D;

int main()
{
    cout << "Criando ambiente CPLEX..." << endl;
    IloEnv env;
    cout << "Ambiente CPLEX criado." << endl;

    try
    {
        string filename;
        cin >> filename;
        //filename="./instancias/instancia_100projetos_2sondas_delta_t28.dat";
        
        // reading data from file
        cout << "Lendo dados de entrada..." << endl;
        
        IloInt n_projetos, n_sondas;
        IloInt n_periodos, t_init, t_final, delta;
        IloNum capital_total;

        ifstream file (filename);
        
        if (file.is_open())
        {    
            cout << "Arquivo aberto corretamente." << endl;
            cout << "Lendo dados gerais..." << endl;
            file >> n_projetos >> capital_total >> t_init >> t_final >> delta >> n_periodos;
            cout << "Dados gerais lidos." << endl;
        }
        else
        {
            cout << "Não foi possível abrir o arquivo." << endl;
            return 0;
        }

        cout << "Instanciando arrays..." << endl;
        IloNumArray coords_x(env), coords_y(env);
        IloNumArray bacias(env), nome_projetos(env);
        IloNumArray maturidades(env), qualidades_dado(env), plays(env); 
        IloNumArray soterramentos(env), pcgnas(env);
        IloNumArray geracao(env), migracao(env), reservatorio(env); 
        IloNumArray geometria(env), retencao(env), pshc(env);
        IloNumArray medias_volume_condicional(env), medias_volume_incondicional(env);
        IloNumArray medias_vpl_condicional(env), medias_vpl_incondicional(env);
        IloNumArray custos(env);
        IloIntArray tempos_exec(env), inicio_janela(env), final_janela(env);
        cout << "Arrays instanciados." << endl;

        IloInt n_vertices;
        n_vertices = n_projetos + n_sondas;
        
        cout << "Definindo s[i][j]" << endl;
        // definindo s[i][j]
        NumMatrix2D s(env);
        cout << "s[i][j] definido." << endl;

        cout << "Lendo arrays..." << endl;
        file >> coords_x;
        file >> coords_y;
        file >> bacias;
        file >> nome_projetos;
        file >> maturidades;
        file >> qualidades_dado;
        file >> plays;
        file >> soterramentos;
        file >> pcgnas;
        file >> geracao;
        file >> migracao;
        file >> reservatorio;
        file >> geometria;
        file >> retencao;
        file >> pshc;
        file >> medias_volume_condicional;
        file >> medias_volume_incondicional;
        file >> medias_vpl_condicional;
        file >> medias_vpl_incondicional;
        file >> custos;
        file >> tempos_exec;
        file >> inicio_janela;
        file >> final_janela;
        file >> n_sondas;
        IloNumArray sondas_x(env, n_sondas), sondas_y(env, n_sondas);
        file >> sondas_x;
        file >> sondas_y;
        file >> s;
        cout << "Arrays lidos." << endl;

        // end reading data
        
        // closing file
        file.close();
        cout << "Dados de entrada lidos." << endl;
        
        // diplay data
        cout << "A instância tem:" << endl;
        cout << n_projetos << " projetos, e capital total de " << capital_total << endl;
        cout << "Coordenadas x dos projetos iguais a " << coords_x << endl;
        cout << "Coordenadas y dos projetos iguais a " << coords_y << endl;
        cout << "Bacias dos projetos iguais a " << bacias << endl;
        cout << "Nomes dos projetos iguais a " << nome_projetos << endl;
        cout << "Maturidades dos projetos iguais a " << maturidades << endl;
        cout << "Qualidades dos dados dos projetos iguais a " << qualidades_dado << endl;
        cout << "Plays dos projetos iguais a " << plays << endl;
        cout << "Soterramentos dos projetos iguais a " << soterramentos << endl;
        cout << "PCGNAs dos projetos iguais a " << pcgnas << endl;
        cout << "Chance de geração dos projetos iguais a " << geracao << endl;
        cout << "Chance de migração dos projetos iguais a " << migracao << endl;
        cout << "Chance de reservatório dos projetos iguais a " << reservatorio << endl;
        cout << "Chance de geometria dos projetos iguais a " << geometria << endl;
        cout << "Chance de retenção dos projetos iguais a " << retencao << endl;
        cout << "PSHCs dos projetos iguais a " << pshc << endl;
        cout << "Média condicional de volume dos projetos iguais a " << medias_volume_condicional << endl;
        cout << "Média incondicional de volume dos projetos iguais a " << medias_volume_incondicional << endl;
        cout << "Média condicional de VPL dos projetos iguais a " << medias_vpl_condicional << endl;
        cout << "Média incondicional de VPL dos projetos iguais a " << medias_vpl_incondicional << endl;
        cout << "Custo dos projetos iguais a " << custos << endl;
        cout << "Tempo de execução dos projetos iguais a " << tempos_exec << endl;
        cout << "Inĩcio do contrato dos projetos iguais a " << inicio_janela << endl;
        cout << "Final do contrato dos projetos iguais a " << final_janela << endl;
        cout << "Número de sondas igual a " << n_sondas << endl;
        cout << "Coordenaxas x das sondas iguais a " << sondas_x << endl;
        cout << "Coordenadas y das sondas iguais a " << sondas_y << endl;
        cout << "tempo inicial: " << t_init << " tempo final: " << t_final << " e quantidade de periodos: " << n_periodos << endl;
        cout << "s[i][j] tem tamanho: " << s.getSize() << " por " << s[1].getSize() << endl;
        cout << "s[i][j]: " << s << endl;
        // end display data
        
        // deletando dados não utilizados no modelo
        coords_x.end();
        coords_y.end();
        bacias.end();
        nome_projetos.end();
        maturidades.end();
        qualidades_dado.end();
        plays.end();
        soterramentos.end();
        pcgnas.end();
        geracao.end();
        migracao.end();
        reservatorio.end();
        geometria.end();
        retencao.end();
        pshc.end();
        medias_volume_condicional.end();
        medias_volume_incondicional.end();
        medias_vpl_condicional.end();
        sondas_x.end();
        sondas_y.end();

        IloInt lag;
        lag = n_sondas;

        // instanciando o modelo
        cout << "Instanciando modelo CPLEX..." << endl;
        IloModel model(env);
        cout << "Modelo CPLEX instanciado." << endl;

        // declarando o otimizador
        cout << "Declarando o solver CPLEX..." << endl;
        IloCplex cplex(env);
        cout << "Solver CPLEX declarado." << endl;
        
        // definindo parametros
        cout << "Definindo parametros do CPLEX..." << endl;
        cplex.setParam(IloCplex::Param::WorkMem, 2048); // 1024 megabytes
        cplex.setParam(IloCplex::Param::MIP::Limits::TreeMemory, 262144); // 131072 megabytes
        cplex.setParam(IloCplex::Param::Emphasis::Memory, 1); // 1: conservar memoria
        cplex.setParam(IloCplex::Param::MIP::Strategy::File, 3); // 1: em memória, 2: em disco, 3: em disco otimizado 
        cplex.setParam(IloCplex::Param::WorkDir, ".");

        cplex.setParam(IloCplex::Param::RootAlgorithm, 0); // 1: primal, 2: dual, 4: barrier, 6: concurrent
        cplex.setParam(IloCplex::Param::NodeAlgorithm, 0); // 1: primal, 2: dual, 4: barrier, 6: concurrent
        cplex.setParam(IloCplex::Param::MIP::SubMIP::SubAlg, 4); // 1: primal, 2: dual, 4: barrier
        cplex.setParam(IloCplex::Param::MIP::SubMIP::StartAlg, 4); // 1: primal, 2: dual, 4: barrier
        
        cplex.setParam(IloCplex::Param::MIP::Strategy::Probe, 3); // 1: moderado, 2: agressivo, 3: muito agressivo
        //cplex.setParam(IloCplex::Param::MIP::Cuts::Cliques, 3); // 1: moderado, 2: agressivo, 3: muito agressivo
        //cplex.setParam(IloCplex::Param::MIP::Cuts::Covers, 3); // 1: moderado, 2: agressivo, 3: muito agressivo
        //cplex.setParam(IloCplex::Param::MIP::Cuts::LiftProj, 3); // 1: moderado, 2: agressivo, 3: muito agressivo
        cout << "Parametros do CPLEX definidos." << endl;

        // criando variáveis de decisão ---------------------------------------------
        // criando a variável de decisão x_{imt}
        cout << "Criando variaveis de decisão..." << endl;
        NumVarMatrix3D x_var(env, n_projetos+n_sondas);
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            x_var[i] = NumVarMatrix2D(env, n_sondas);
            for (int m=0; m<n_sondas; m++)
            {
                x_var[i][m] = IloNumVarArray(env, n_periodos+1, 0, 1, ILOINT);
                //for (int t=0; t<n_periodos; t++)
                //{
                //    if (i<n_sondas)
                //    {
                //        x_var[i][m][t] = IloNumVar(env, 0, 1, ILOINT, "x_var");
                //        model.add(x_var[i][m][t]);
                //    }
                //    else
                //    {
                //        if ( (t < inicio_janela[i-lag]) || (t > final_janela[i-lag]-tempos_exec[i-lag]) )
                //        {
                //            x_var[i][m][t] = IloNumVar(env, 0, 0, ILOINT, "x_var");
                //            model.add(x_var[i][m][t]);
                //        }
                //        else
                //        {
                //            x_var[i][m][t] = IloNumVar(env, 0, 1, ILOINT, "x_var");
                //            model.add(x_var[i][m][t]);
                //        }
                //    }
                //}
            }
        }

        // criando a variável de decisão y_{j}
        IloNumVarArray y_var(env, n_projetos, 0, 1, ILOINT);
        //for (int j=0; j<n_projetos; j++)
        //{
        //    y_var[j] = IloNumVar(env, 0, 1, ILOINT, "y_var");
        //    model.add(y_var[j]);
        //}
        cout << "Variaveis de decisão criadas." << endl;

        // verificando uso de memória
        cout << "Memory usage after creating constraints: " << env.getMemoryUsage() / (1024. * 1024.) << " MB" << endl;
        
        // criando restrições ---------------------------------------------------------
        // 1. restrição de orçamento total
        cout << "Criando restrição de orçamento total..." << endl;
        IloExpr expr1(env);
        for (int j=0; j<n_projetos; j++)
        {
            expr1 += y_var[j] * custos[j];
        }
        IloConstraint c1(expr1 <= capital_total);
        c1.setName("investimento total");
        model.add(c1);
        expr1.end();
        cout << "Restrição de orçamento total criada." << endl;
        
        // verificando uso de memória
        cout << "Memory usage after creating constraints: " << env.getMemoryUsage() / (1024. * 1024.) << " MB" << endl;

        // 2. restrição de orçamento por tipo de projeto ------------- TODO: incluir
        
        // 3. restrição de unicidade dos projetos + relação das variáveis de decisão
        cout << "Criando restrição de unicidade dos projetos..." << endl;
        for (int j=0; j<n_projetos; j++)
        {
            IloExpr expr2(env);
            expr2 += y_var[j];
            for (int m=0; m<n_sondas; m++)
            {
                for (int t=0; t<n_periodos+1; t++)
                {
                    expr2 += - x_var[j+lag][m][t];
                }
            }
            IloConstraint c2(expr2 == 0);
            c2.setName("relação entre variáveis e unicidade dos projetos");
            model.add(c2);
            expr2.end();
        }
        cout << "Restrição de unicidade dos projetos criada." << endl;
        
        // verificando uso de memória
        cout << "Memory usage after creating constraints: " << env.getMemoryUsage() / (1024. * 1024.) << " MB" << endl;

        // 4. restrição de que toda sonda começa na origem
        cout << "Criando restrição de unicidade da origem das sondas..." << endl;
        for (int m=0; m<n_sondas; m++)
        {
            IloExpr expr3(env);
            expr3 += x_var[m][m][0];
            IloConstraint c3(expr3 == 1);
            c3.setName("sondas partindo da origem");
            model.add(c3);
            expr3.end();
        }
        cout << "Restrição da origem das sondas criada." << endl;
        
        // verificando uso de memória
        cout << "Memory usage after creating constraints: " << env.getMemoryUsage() / (1024. * 1024.) << " MB" << endl;
        
        // 5. restrição de preempção
        cout << "Criando restrição de preempção..." << endl;
        IloInt inicio_t=0, final_t=0;
        IloInt inicio_s=0, final_s=0;
        IloInt inicio_j=0;
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            if (i < n_sondas)
            {
                inicio_j = 0;
            }
            else
            {
                inicio_j = (i - lag) + 1;
            }
            for (int j=inicio_j; j<n_projetos; j++)
            {
                if (i-lag == j)
                {
                    continue;
                }
                for (int m=0; m<n_sondas; m++)
                {
                    inicio_t = inicio_janela[j];
                    final_t = final_janela[j] - tempos_exec[j] + 1;
                    for (int t=inicio_t; t<final_t+1; t++)
                    {
                        IloExpr expr4(env);
                        expr4 += x_var[j+lag][m][t];
                        if (i<n_sondas)
                        {
                            inicio_s = t - s[i][j+lag] + 1;
                            final_s = t + tempos_exec[j] + s[i][j+lag] - 1;
                        }
                        else
                        {
                            if (inicio_janela[i-lag] >= t - tempos_exec[i-lag] - s[i][j+lag] + 1)
                            {
                                inicio_s = inicio_janela[i-lag];
                            }
                            else
                            {
                                inicio_s = t - tempos_exec[i-lag] - s[i][j+lag] + 1;
                            }
                            if (final_janela[i-lag]-tempos_exec[i-lag] + 1 <= t + tempos_exec[j] + s[i][j+lag] - 1)
                            {
                                final_s = final_janela[i-lag]-tempos_exec[i-lag] + 1;
                            }
                            else
                            {
                                final_s = t + tempos_exec[j] + s[i][j+lag] - 1;
                            }
                        }
                        if (inicio_s < 0)
                        {
                            inicio_s = 0;
                        }
                        if (final_s > n_periodos)
                        {
                            final_s = n_periodos;
                        }
                        for (int s_temp=inicio_s; s_temp<final_s+1; s_temp++)
                        {
                            expr4 += x_var[i][m][s_temp];
                        }
                        IloConstraint c4(expr4 <= 1);
                        c4.setName("preempção");
                        model.add(c4);
                        expr4.end();
                    }
                }
            }
        }
        cout << "Restrição de preempção criada." << endl;
        
        // verificando uso de memória
        cout << "Memory usage after creating constraints: " << env.getMemoryUsage() / (1024. * 1024.) << " MB" << endl;

        // 6. restrição de janela de tempo
        cout << "Criando restrição de janela de tempo..." << endl;
        for (int j=0; j<n_projetos; j++)
        {
            IloExpr expr5(env);
            expr5 += - inicio_janela[j] * y_var[j];
            for (int m=0; m<n_sondas; m++)
            {
                inicio_t = inicio_janela[j];
                final_t = final_janela[j] - tempos_exec[j] + 1;
                for (int t=inicio_t; t<final_t+1; t++)
                {
                    expr5 += x_var[j+lag][m][t] * t;
                }
            }
            IloConstraint c5(expr5 >= 0);
            c5.setName("janela de tempo: inicio");
            model.add(c5);
            expr5.end();
        }
        for (int j=0; j<n_projetos; j++)
        {
            IloExpr expr6(env);
            expr6 += (final_janela[j] - tempos_exec[j] + 1) * y_var[j];
            for (int m=0; m<n_sondas; m++)
            {
                inicio_t = inicio_janela[j];
                final_t = final_janela[j] - tempos_exec[j] + 1;
                for (int t=inicio_t; t<final_t+1; t++)
                {
                    expr6 += - x_var[j+lag][m][t] * t;
                }
            }
            IloConstraint c6(expr6 >= 0);
            c6.setName("janela de tempo: final");
            model.add(c6);
            expr6.end();
        }
        cout << "Restrição de janela de tempo criada." << endl;
        
        // verificando uso de memória
        cout << "Memory usage after creating constraints: " << env.getMemoryUsage() / (1024. * 1024.) << " MB" << endl;

        // criando a função objetivo
        cout << "Criando a função objetivo..." << endl;
        IloExpr expro(env);
        for (int j=0; j<n_projetos; j++)
        {
            expro += y_var[j] * medias_vpl_incondicional[j];
        }
        model.add(IloMaximize(env, expro));
        expro.end();
        cout << "Função objetivo criada." << endl;

        // verificando uso de memória
        cout << "Memory usage after creating constraints: " << env.getMemoryUsage() / (1024. * 1024.) << " MB" << endl;

        // resolvendo o modelo
        cout << "Extracting model..." << endl;
        cplex.extract(model);
        cout << "Model extracted!" << endl;
        cplex.solve();
        
        // printando status da otimização
        env.out() << "Solution status = " << cplex.getStatus() << endl;
        
        // printando valor obtido para a função objetivo
        env.out() << "Solution value  = " << cplex.getObjValue() << endl;
        
        /*
        // pegando valor das variáveis de decisão
        NumMatrix3D x_vals(env, n_projetos+n_sondas);
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            x_vals[i] = NumMatrix2D(env, n_sondas);
            for (int m=0; m<n_sondas; m++)
            {
                x_vals[i][m] = IloNumArray(env, n_periodos);
                for (int t=0; t<n_periodos; t++)
                {
                    if (cplex.getValue(x_var[i][m][t]))
                    {
                        cout << "x[" << i << "][" << m << "][" << t << "]: "  << cplex.getValue(x_var[i][m][t]) << endl;
                    }
                    x_vals[i][m][t] = cplex.getValue(x_var[i][m][t]);
                }
            }
        }
        IloNumArray y_vals(env, n_projetos);
        for (int j=0; j<n_projetos; j++)
        {
            //cout << "y[" << j << "]: " << cplex.getValue(y_var[j]) << endl;
            y_vals[j] = cplex.getValue(y_var[j]);
        }

        //env.out() << "x[i][j][m] = " << x_vals << endl;
        //env.out() << "y[j] = " << y_vals << endl;
        */

        // exportando modelo
        //cplex.exportModel("modelo_TI_mestrado_joao.lp");


        env.end();
    }
    catch (IloException& e) 
    {
        cerr << "Erro na chamada da API: " << e << endl;
        env.end();
    }
    catch (...) 
    {
        cerr << "Erro desconhecido" << endl;
        env.end();
    }
    return 0;
}
