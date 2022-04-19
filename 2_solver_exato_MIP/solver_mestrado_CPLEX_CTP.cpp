#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
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
        
        //IloTimer timer(env);
        //timer.start();
        auto start = std::chrono::high_resolution_clock::now();

        // reading data from file
        cout << "Lendo dados de entrada..." << endl;
        
        int n_projetos, n_sondas;
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
        IloNumArray coords_x(env, n_projetos), coords_y(env, n_projetos);
        IloNumArray bacias(env, n_projetos), nome_projetos(env, n_projetos);
        IloNumArray maturidades(env, n_projetos), qualidades_dado(env, n_projetos), plays(env, n_projetos); 
        IloNumArray soterramentos(env, n_projetos), pcgnas(env, n_projetos);
        IloNumArray geracao(env, n_projetos), migracao(env, n_projetos), reservatorio(env, n_projetos); 
        IloNumArray geometria(env, n_projetos), retencao(env, n_projetos), pshc(env, n_projetos);
        IloNumArray medias_volume_condicional(env, n_projetos), medias_volume_incondicional(env, n_projetos);
        IloNumArray medias_vpl_condicional(env, n_projetos), medias_vpl_incondicional(env, n_projetos);
        IloNumArray custos(env, n_projetos);
        IloIntArray tempos_exec(env, n_projetos), inicio_janela(env, n_projetos), final_janela(env, n_projetos);
        cout << "Arrays instanciados." << endl;

        cout << "Lendo arrays..." << endl;

        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            coords_x[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            coords_y[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            bacias[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            nome_projetos[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            maturidades[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            qualidades_dado[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            plays[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            soterramentos[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            pcgnas[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            geracao[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            migracao[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            reservatorio[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            geometria[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            retencao[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            pshc[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            medias_volume_condicional[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            medias_volume_incondicional[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            medias_vpl_condicional[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            medias_vpl_incondicional[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            custos[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            tempos_exec[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            inicio_janela[i] = temp;
        }
        for (int i=0; i<n_projetos; i++)
        {
            double temp;
            file >> temp;
            final_janela[i] = temp;
        }

        file >> n_sondas;

        int n_vertices;
        n_vertices = n_projetos + n_sondas;
        
        cout << "Definindo s[i][j]" << endl;
        
        // definindo s[i][j]
        // NumMatrix2D s(env, n_vertices);
        // for (int i=0; i<n_vertices; i++)
        // {
        //     s[i] = IloNumArray(env, n_vertices);
        // }
        
        double s[n_vertices][n_vertices];
        
        cout << "s[i][j] definido." << endl;

        IloNumArray sondas_x(env, n_sondas), sondas_y(env, n_sondas);

        for (int i=0; i<n_sondas; i++)
        {
            double temp;
            file >> temp;
            sondas_x[i] = temp;
        }
        for (int i=0; i<n_sondas; i++)
        {
            double temp;
            file >> temp;
            sondas_y[i] = temp;
        }

        for (int i=0; i<n_vertices; i++)
        {
            for (int j=0; j<n_vertices; j++)
            {
                double temp;
                file >> temp;
                s[i][j] = temp;
            }
        }

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
        //cout << "s[i][j] tem tamanho: " << s.size() << " por " << s[1].size() << endl;
        //cout << "s[i][j]: " << s << endl;
        cout << "s[i][j]: " << endl;
        for (int i=0; i<n_vertices; i++)
        {
            for (int j=0; j<n_vertices; j++)
            {
                cout << s[i][j] << " ";
            } cout << endl;
        } cout << endl;
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

        // definindo BigM[i][j]
        cout << "Criando BigM..." << endl;
        NumMatrix2D BigM(env, n_projetos+n_sondas);
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            BigM[i] = IloNumArray(env, n_projetos);
        }
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            for (int j=0; j<n_projetos; j++)
            {
                if (i < n_sondas)
                {
                    BigM[i][j] = s[i][j+lag] + tempos_exec[j] + 1; // - inicio_janela[j];
                }
                else
                {
                    BigM[i][j] = final_janela[i-lag] + s[i][j+lag] + tempos_exec[j] + 1; // - inicio_janela[j];
                }
            }
        }
        cout << "BigM criado." << endl;
        
        //cout << "BigM[i][j] tem tamanho: " << BigM.getSize() << " por " << BigM[1].getSize() << endl;
        //cout << "BigM[i][j]: " << BigM << endl;

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

        cplex.setParam(IloCplex::Param::TimeLimit, 1800); // in seconds: 3600, 7200, 14400, 21600, 43200, 86400

        cplex.setParam(IloCplex::Param::WorkMem, 4096); // 1024 megabytes
        cplex.setParam(IloCplex::Param::MIP::Limits::TreeMemory, 20000); // 131072 megabytes
        cplex.setParam(IloCplex::Param::Emphasis::Memory, 1); // 1: conservar memoria
        cplex.setParam(IloCplex::Param::MIP::Strategy::File, 3); // 1: em memória, 2: em disco, 3: em disco otimizado 
        cplex.setParam(IloCplex::Param::WorkDir, ".");

        //cplex.setParam(IloCplex::Param::RootAlgorithm, 0); // 1: primal, 2: dual, 4: barrier, 6: concurrent
        //cplex.setParam(IloCplex::Param::NodeAlgorithm, 0); // 1: primal, 2: dual, 4: barrier, 6: concurrent
        //cplex.setParam(IloCplex::Param::MIP::SubMIP::SubAlg, 4); // 1: primal, 2: dual, 4: barrier
        //cplex.setParam(IloCplex::Param::MIP::SubMIP::StartAlg, 4); // 1: primal, 2: dual, 4: barrier
        
        //cplex.setParam(IloCplex::Param::MIP::Strategy::Probe, 2); // 1: moderado, 2: agressivo, 3: muito agressivo
        //cplex.setParam(IloCplex::Param::MIP::Cuts::Cliques, 1); // 1: moderado, 2: agressivo, 3: muito agressivo
        //cplex.setParam(IloCplex::Param::MIP::Cuts::Covers, 1); // 1: moderado, 2: agressivo, 3: muito agressivo
        //cplex.setParam(IloCplex::Param::MIP::Cuts::LiftProj, 2); // 1: moderado, 2: agressivo, 3: muito agressivo
        cout << "Parametros do CPLEX definidos." << endl;

        // criando variáveis de decisão ---------------------------------------------
        cout << "Criando variáveis de decisão..." << endl;
        // criando a variável de decisão x_{ijm} 
        NumVarMatrix3D x_var(env, n_projetos+n_sondas);
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            x_var[i] = NumVarMatrix2D(env, n_projetos);
            for (int j=0; j<n_projetos; j++)
            {
                x_var[i][j] = IloNumVarArray(env, n_sondas, 0, 1, ILOINT);
            }
        }
        
        IloInt inicio_t=0, final_t=0;

        // criando a variável de decisão c_{jm}
        NumVarMatrix2D c_var(env, n_projetos+n_sondas);
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            c_var[i] = IloNumVarArray(env, n_sondas, 0, n_periodos, ILOINT);
            //for (int m=0; m<n_sondas; m++)
            //{
            //    if (i < n_sondas)
            //    {
            //        c_var[i][m] = IloNumVar(env, 0, 0, ILOINT, "c_var");
            //        model.add(c_var[i][m]);
            //    }
            //    else
            //    {
            //        inicio_t = inicio_janela[i-lag];
            //        final_t = final_janela[i-lag] - tempos_exec[i-lag] + 1;
            //        c_var[i][m] = IloNumVar(env, inicio_t, final_t, ILOINT, "c_var");
            //        model.add(c_var[i][m]);
            //    }
            //}
        }
        cout << "Variáveis de deicisão criadas." << endl;
        
        // verificando uso de memória
        cout << "Memory usage after creating constraints: " << env.getMemoryUsage() / (1024. * 1024.) << " MB" << endl;

        // criando restrições ---------------------------------------------------------
        // 1. restrição de orçamento total
        cout << "Criando restrição de orçamento total..." << endl;
        IloExpr expr1(env);
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            for (int j=0; j<n_projetos; j++)
            {
                for (int m=0; m<n_sondas; m++)
                {
                    if (i-lag != j)
                    {
                        expr1 += x_var[i][j][m] * custos[j];
                    }
                }
            }
        }
        IloConstraint c1(expr1 <= capital_total);
        c1.setName("investimento total");
        model.add(c1);
        expr1.end();
        cout << "Restrição de orçamento total criada." << endl;
        
        // verificando uso de memória
        cout << "Memory usage after creating constraints: " << env.getMemoryUsage() / (1024. * 1024.) << " MB" << endl;

        // 2. restrição de orçamento por tipo de projeto ------------- TODO: incluir

        // 3. restrição de unicidade de saída da origem (forall m)
        cout << "Criando restrição de unicidade das origens..." << endl;
        for (int m=0; m<n_sondas; m++)
        {
            IloExpr expr2(env);
            for (int j=0; j<n_projetos; j++)
            {
                for (int i=0; i<n_sondas; i++)
                {
                    if (i == m && i-lag != j)
                    {
                        expr2 += x_var[i][j][m];
                    }
                }
            }
            IloConstraint c2(expr2 <= 1);
            c2.setName("unicidade de saida da origem");
            model.add(c2);
            expr2.end();
        }
        cout << "Restrição de unicidade das origens criada." << endl;
        
        // verificando uso de memória
        cout << "Memory usage after creating constraints: " << env.getMemoryUsage() / (1024. * 1024.) << " MB" << endl;

        // 4. restrição de cada sonda não poder sair de uma origem que não seja a sua 
        cout << "Criando restrição para limitar origens de sondas diferentes..." << endl;
        IloExpr expr3(env);
        for (int m=0; m<n_sondas; m++)
        {
            for (int j=0; j<n_projetos; j++)
            {
                for (int i=0; i<n_sondas; i++)
                {
                    if (m != i && i-lag != j)
                    {
                        expr3 += x_var[i][j][m];
                    }
                }
            }
        }
        IloConstraint c3(expr3 == 0);
        c3.setName("sonda nao pode sair de outra origem");
        model.add(c3);
        expr3.end();
        cout << "Restrição de origens de sondas diferentes criada." << endl;

        // verificando uso de memória
        cout << "Memory usage after creating constraints: " << env.getMemoryUsage() / (1024. * 1024.) << " MB" << endl;

        // 5. restrição de unicidade na execução dos projetos (forall j)
        cout << "Criando restrição de unicidade de projetos..." << endl;
        for (int j=0; j<n_projetos; j++)
        {
            IloExpr expr4(env);
            for (int i=0; i<n_projetos+n_sondas; i++)
            {
                for (int m=0; m<n_sondas; m++)
                {
                    if (i-lag != j)
                    {
                        expr4 += x_var[i][j][m];
                    }
                }
            }
            IloConstraint c4(expr4 <= 1);
            c4.setName("unicidade na execucao de projetos: ida");
            model.add(c4);
            expr4.end();
        }
        // 6. restrição de unicidade na execução dos projetos (forall i)
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            IloExpr expr5(env);
            for (int j=0; j<n_projetos; j++)
            {
                for (int m=0; m<n_sondas; m++)
                {
                    if (i-lag != j)
                    {
                        expr5 += x_var[i][j][m];
                    }
                }
            }
            IloConstraint c5(expr5 <= 1);
            c5.setName("unicidade na execucao de projetos: volta");
            model.add(c5);
            expr5.end();
        }
        cout << "Restrição de unicidade de projetos criada." << endl;
        
        // verificando uso de memória
        cout << "Memory usage after creating constraints: " << env.getMemoryUsage() / (1024. * 1024.) << " MB" << endl;

        // 7. restrição de conservação de fluxo
        cout << "Criando restrição de conservação de fluxo..." << endl;
        for (int m=0; m<n_sondas; m++)
        {
            for (int j=0; j<n_projetos; j++)
            {
                IloExpr expr6(env);
                for (int i=0; i<n_projetos+n_sondas; i++)
                {
                    if (i-lag != j)
                    {
                        expr6 += x_var[i][j][m];
                    }
                }
                for (int k=0; k<n_projetos; k++)
                {
                    if (j != k)
                    {
                        expr6 += - x_var[j+lag][k][m];
                    }
                }
                IloConstraint c6(expr6 >= 0);
                c6.setName("conservacao de fluxo");
                model.add(c6);
                expr6.end();
            }
        }
        cout << "Restrição de conservação de fluxo criada." << endl;

        // verificando uso de memória
        cout << "Memory usage after creating constraints: " << env.getMemoryUsage() / (1024. * 1024.) << " MB" << endl;

        // 8. restrição de completion time zero para origens
        cout << "Criando restrição de completion time zero para origens..." << endl;
        IloExpr expr7(env);
        for (int m=0; m<n_sondas; m++)
        {
            for (int j=0; j<n_sondas; j++)
            {
                expr7 += c_var[j][m];
            }
        }
        IloConstraint c7(expr7 == 0);
        c7.setName("origens com completion time zero");
        model.add(c7);
        expr7.end();
        cout << "Restrição de completion time zero para origens criada." << endl;

        // verificando uso de memória
        cout << "Memory usage after creating constraints: " << env.getMemoryUsage() / (1024. * 1024.) << " MB" << endl;

        // 9. restrição de escalonamento mtz ----- TODO: refinar limite superior da restricao: due date?
        cout << "Criando restrição de escalonamento TMZ..." << endl;
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            for (int j=0; j<n_projetos; j++)
            {
                for (int m=0; m<n_sondas; m++)
                {
                    if (i-lag != j)
                    {
                        IloExpr expr8(env);
                        expr8 += c_var[j+lag][m] - (c_var[i][m] + s[i][j+lag] + tempos_exec[j] - BigM[i][j]*(1-x_var[i][j][m])) ;
                        IloConstraint c8(expr8 >= 0);
                        c8.setName("tmz escalonamento temporal lowerbound");
                        model.add(c8);
                        //IloConstraint c91(expr8 <= final_janela[j]);
                        //c91.setName("tmz escalonamento temporal upperbound");
                        //model.add(c91);
                        expr8.end();
                    }
                }
            }
        }
        cout << "Restrição de escalonamento TMZ criada." << endl;

        // verificando uso de memória
        cout << "Memory usage after creating constraints: " << env.getMemoryUsage() / (1024. * 1024.) << " MB" << endl;

        // 10. restrição de janela de tempo -------- TODO: refinar limite superior das restrições: due date?
        cout << "Criando restrição de janela de tempo..." << endl;
        for (int m=0; m<n_sondas; m++)
        {
            for (int j=0; j<n_projetos; j++)
            {
                IloExpr expr9(env);
                expr9 += c_var[j+lag][m];
                for (int i=0; i<n_projetos+n_sondas; i++)
                {
                    if (i-lag != j)
                    {
                        expr9 += - ((inicio_janela[j]+tempos_exec[j]-1)*x_var[i][j][m]);
                    }
                }
                IloConstraint c9(expr9 >= 0);
                c9.setName("janela de tempo lowerbound");
                model.add(c9);
                //IloConstraint c92(expr9 <= final_janela[j]);
                //c92.setName("janela de tempo upperbound");
                //model.add(c92);
                expr9.end();
            }
        }
        for (int m=0; m<n_sondas; m++)
        {
            for (int j=0; j<n_projetos; j++)
            {
                IloExpr expr10(env);
                expr10 += - c_var[j+lag][m];
                for (int i=0; i<n_projetos+n_sondas; i++)
                {
                    if (i-lag != j)
                    {
                        expr10 += final_janela[j]*x_var[i][j][m];
                    }
                }
                IloConstraint c10(expr10 >= 0);
                c10.setName("janela de tempo lowerbound");
                model.add(c10);
                //IloConstraint c93(expr10 <= final_janela[j]);
                //c93.setName("janela de tempo upperbound");
                //model.add(c93);
                expr10.end();
            }
        }
        cout << "Restrição de janela de tempo criada." << endl;

        // criando a função objetivo
        cout << "Criando função objetivo..." << endl;
        IloExpr expro(env);
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            for (int j=0; j<n_projetos; j++)
            {
                for (int m=0; m<n_sondas; m++)
                {
                    if (i-lag != j)
                    {
                        expro += x_var[i][j][m] * medias_vpl_incondicional[j];
                    }
                }
            }
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

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        long long tempoTotal = duration.count();
        
        ofstream outfile;
        outfile.open("resultados_automatico.txt", ios_base::app);
        outfile << "CTP " << filename << " " << cplex.getObjValue() << " " << cplex.getStatus() << " " << cplex.getBestObjValue() << " " << cplex.getMIPRelativeGap() << " " << tempoTotal << endl;

        // printando tempo de execução
        env.out() << "Tempo de execução = " << tempoTotal << endl;
        
        // printando status da otimização
        env.out() << "Solution status = " << cplex.getStatus() << endl;
        
        // printando valor obtido para a função objetivo
        env.out() << "Solution value = " << cplex.getObjValue() << endl;

        // printando valor do GAP
        env.out() << "GAP = " << cplex.getMIPRelativeGap() << endl;
        
        /*
        // pegando valor das variáveis de decisão
        //NumMatrix3D x_vals(env, n_projetos+n_sondas);
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            //x_vals[i] = NumMatrix2D(env, n_projetos);
            for (int j=0; j<n_projetos; j++)
            {
                //x_vals[i][j] = IloNumArray(env, n_sondas);
                for (int m=0; m<n_sondas; m++)
                {
                    cout << "x[" << i << "][" << j << "][" << m << "]: "  << cplex.getValue(x_var[i][j][m]) << endl;
                    //x_vals[i][j][m] = cplex.getValue(x_var[i][j][m]);
                }
            }
        }
        //NumMatrix2D c_vals(env, n_projetos+n_sondas);
        //for (int i=0; i<n_projetos+n_sondas; i++)
        //{
        //    c_vals[i] = IloNumArray(env, n_sondas);
        //    for (int m=0; m<n_sondas; m++)
        //    {
        //        //cout << "c[" << i << "][" << m << "]: " << cplex.getValue(c_var[i][m]) << endl;
        //        //c_vals[i][m] = cplex.getValue(c_var[i][m]);
        //    }
        //}

        //env.out() << "x[i][j][m] = " << x_vals << endl;
        //env.out() << "c[j][m]    = " << c_vals << endl;
        
        */

        // exportando modelo
        //cplex.exportModel("modeloCTP_mestrado_joao.lp");
        
        outfile.close();
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
