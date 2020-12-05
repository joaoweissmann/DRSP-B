#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ilcplex/ilocplex.h>

ILOSTLBEGIN

using namespace std;

typedef IloArray<IloNumVarArray> NumVarMatrix2D;
typedef IloArray<NumVarMatrix2D> NumVarMatrix3D;

typedef IloArray<IloBoolVarArray> BoolVarMatrix2D;
typedef IloArray<BoolVarMatrix2D> BoolVarMatrix3D;

typedef IloArray<IloNumArray> NumMatrix2D;
typedef IloArray<NumMatrix2D> NumMatrix3D;

int main()
{
    IloEnv env;
    try
    {
        string filename="instancia_50projetos_2sondas.dat";
        ifstream file;
        
        // reading data from file
        file.open(filename);
        if (!file)
        {
            cerr << "ERRO ao abrir o arquivo " << filename << endl;
        }
        IloInt n_projetos, n_sondas;
        IloInt n_periodos, t_init, t_final;
        IloNum capital_total;
        IloNumArray coords_x(env), coords_y(env);
        IloArray<string> bacias(env), nome_projetos(env);
        IloArray<string> maturidades(env), qualidades_dado(env), plays(env); 
        IloNumArray soterramentos(env), pcgnas(env);
        IloNumArray geracao(env), migracao(env), reservatorio(env), geometria(env), retencao(env), pshc(env);
        IloNumArray medias_volume_condicional(env), medias_volume_incondicional(env);
        IloNumArray medias_vpl_condicional(env), medias_vpl_incondicional(env);
        IloNumArray custos(env), tempos_exec(env), inicio_janela(env), final_janela(env);
        IloNumArray sondas_x(env), sondas_y(env);
        file >> n_projetos >> capital_total;
        file >> coords_x >> coords_y; 
        //file >> bacias >> nome_projetos;
        //file >> maturidades >> qualidades_dado >> plays;
        file >> soterramentos >> pcgnas;
        file >> geracao >> migracao >> reservatorio >> geometria >> retencao >> pshc;
        file >> medias_volume_condicional >> medias_volume_incondicional;
        file >> medias_vpl_condicional >> medias_vpl_incondicional;
        file >> custos >> tempos_exec >> inicio_janela >> final_janela;
        file >> n_sondas >> sondas_x >> sondas_y;
        t_init = 0;
        t_final = 5 * 12 * 4 * 7;
        IloInt delta = 7 * 4 * 3;
        n_periodos = ((t_final - t_init)/delta) + 1;
        // end reading data

        // convertendo de dias para periodos
        if (delta != 1)
        {
            for (int j=0; j<n_projetos; j++)
            {
                tempos_exec[j] = (tempos_exec[j] / delta) + 1;
                inicio_janela[j] = inicio_janela[j] / delta;
                final_janela[j] = final_janela[j] / delta;
            }
            t_final = t_final / delta;
        }

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
        // end display data
        
        IloInt lag;
        lag = n_sondas;

        // definindo s[i][j]
        NumMatrix2D s(env, n_projetos+n_sondas);
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            s[i] = IloNumArray(env, n_projetos);
        }
        IloInt dist=0;
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            for (int j=0; j<n_projetos; j++)
            {
                if (i<n_sondas)
                {
                    dist = sqrt(pow(sondas_x[i] - coords_x[j], 2)+pow(sondas_y[i] - coords_y[j], 2));
                }
                else
                {
                    dist = sqrt(pow(coords_x[i-lag] - coords_x[j], 2)+pow(coords_y[i-lag] - coords_y[j], 2));
                }
                if (delta != 1)
                {
                    s[i][j] = (dist / delta) + 1;
                }
                else
                {
                    s[i][j] = dist;
                }            
            }
        }
        cout << "s[i][j] tem tamanho: " << s.getSize() << " por " << s[1].getSize() << endl;
        cout << "s[i][j]: " << s << endl;

        // definindo BigM[i][j]
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
                    BigM[i][j] = s[i][j] + tempos_exec[j]; // - inicio_janela[j];
                }
                else
                {
                    BigM[i][j] = final_janela[i-lag] + s[i][j] + tempos_exec[j]; // - inicio_janela[j];
                }
            }
        }
        cout << "BigM[i][j] tem tamanho: " << BigM.getSize() << " por " << BigM[1].getSize() << endl;
        cout << "BigM[i][j]: " << BigM << endl;

        // instanciando o modelo
        IloModel model(env);
        
        // criando variáveis de decisão ---------------------------------------------
        // criando a variável de decisão x_{ijm} 
        NumVarMatrix3D x_var(env, n_projetos+n_sondas);
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            x_var[i] = NumVarMatrix2D(env, n_projetos);
            for (int j=0; j<n_projetos; j++)
            {
                x_var[i][j] = IloNumVarArray(env, n_sondas, 0, 1, ILOINT);
                for (int m=0; m<n_sondas; m++)
                {
                    if (i-lag != j)
                    {
                        x_var[i][j][m] = IloNumVar(env, 0, 1, ILOINT, "x_var");
                        model.add(x_var[i][j][m]);
                    }
                    else
                    {
                        x_var[i][j][m] = IloNumVar(env, 0, 0, ILOINT, "x_var");
                        model.add(x_var[i][j][m]);
                    }
                }
            }
        }
        cout << "x[i][j][m] tem tamanho: " << x_var.getSize() << " por " << x_var[0].getSize() << " por " << x_var[0][0].getSize() << endl;
        cout << "x[i][j][m]: " << x_var << endl;
        // criando a variável de decisão c_{jm}
        NumVarMatrix2D c_var(env, n_projetos+n_sondas);
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            c_var[i] = IloNumVarArray(env, n_sondas, t_init, t_final, ILOINT);
            for (int m=0; m<n_sondas; m++)
            {
                c_var[i][m] = IloNumVar(env, t_init, t_final, ILOINT, "c_var");
                model.add(c_var[i][m]);
            }
            // ----------------------------------------------- TODO: pre processar origens = 0 ?
        }
        cout << "C[j][m] tem tamanho: " << c_var.getSize() << " por " << c_var[0].getSize() << endl;
        cout << "C[j][m]: " << c_var << endl;
    
        // criando restrições ---------------------------------------------------------
        // 1. restrição de orçamento total
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
        
        // 2. restrição de orçamento por tipo de projeto ------------- TODO: incluir
        // 3. restrição de unicidade de saída da origem (forall m)
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
        
        // 4. restrição de cada sonda não poder sair de uma origem que não seja a sua 
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
        
        // 5. restrição de unicidade na execução dos projetos (forall j)
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
        // 7. restrição de conservação de fluxo
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
        // 8. restrição de completion time zero para origens
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
        
        // 9. restrição de escalonamento mtz ----- TODO: refinar limite superior da restricao: due date?
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            for (int j=0; j<n_projetos; j++)
            {
                for (int m=0; m<n_sondas; m++)
                {
                    if (i-lag != j)
                    {
                        IloExpr expr8(env);
                        expr8 += c_var[j+lag][m] - (c_var[i][m] + s[i][j] + tempos_exec[j] - BigM[i][j]*(1-x_var[i][j][m])) ;
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
        // 10. restrição de janela de tempo -------- TODO: refinar limite superior das restrições: due date?
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
                        expr9 += - ((inicio_janela[j]+tempos_exec[j])*x_var[i][j][m]);
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

        // criando a função objetivo
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
        
        // declarando o otimizador
        IloCplex cplex(model);
        // resolvendo o modelo
        cplex.solve();
        
        // printando status da otimização
        env.out() << "Solution status = " << cplex.getStatus() << endl;
        
        // printando valor obtido para a função objetivo
        env.out() << "Solution value  = " << cplex.getObjValue() << endl;
        
        // pegando valor das variáveis de decisão
        NumMatrix3D x_vals(env, n_projetos+n_sondas);
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            x_vals[i] = NumMatrix2D(env, n_projetos);
            for (int j=0; j<n_projetos; j++)
            {
                x_vals[i][j] = IloNumArray(env, n_sondas);
                for (int m=0; m<n_sondas; m++)
                {
                    //cout << "x[" << i << "][" << j << "][" << m << "]: "  << cplex.getValue(x_var[i][j][m]) << endl;
                    x_vals[i][j][m] = cplex.getValue(x_var[i][j][m]);
                }
            }
        }
        NumMatrix2D c_vals(env, n_projetos+n_sondas);
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            c_vals[i] = IloNumArray(env, n_sondas);
            for (int m=0; m<n_sondas; m++)
            {
                //cout << "c[" << i << "][" << m << "]: " << cplex.getValue(c_var[i][m]) << endl;
                c_vals[i][m] = cplex.getValue(c_var[i][m]);
            }
        }

        //env.out() << "x[i][j][m] = " << x_vals << endl;
        //env.out() << "c[j][m]    = " << c_vals << endl;
        
        // exportando modelo
        cplex.exportModel("modeloCTP_mestrado_joao.lp");
        

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