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
        string filename="instancia_300projetos_2sondas.dat";
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
        IloNumArray custos(env);
        IloIntArray tempos_exec(env), inicio_janela(env), final_janela(env);
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
        cout << "tempo inicial: " << t_init << " tempo final: " << t_final << " e quantidade de periodos: " << n_periodos << endl;
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
        
        // instanciando o modelo
        IloModel model(env);

        // criando variáveis de decisão ---------------------------------------------
        
        // criando a variável de decisão x_{imt}
        NumVarMatrix3D x_var(env, n_projetos+n_sondas);
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            x_var[i] = NumVarMatrix2D(env, n_sondas);
            for (int m=0; m<n_sondas; m++)
            {
                x_var[i][m] = IloNumVarArray(env, n_periodos, 0, 1, ILOINT);
                for (int t=0; t<n_periodos; t++)
                {
                    if (i<n_sondas)
                    {
                        x_var[i][m][t] = IloNumVar(env, 0, 1, ILOINT, "x_var");
                        model.add(x_var[i][m][t]);
                    }
                    else
                    {
                        if ( (t < inicio_janela[i-lag]) || (t > final_janela[i-lag]-tempos_exec[i-lag]) )
                        {
                            x_var[i][m][t] = IloNumVar(env, 0, 0, ILOINT, "x_var");
                            model.add(x_var[i][m][t]);
                        }
                        else
                        {
                            x_var[i][m][t] = IloNumVar(env, 0, 1, ILOINT, "x_var");
                            model.add(x_var[i][m][t]);
                        }
                    }
                }
            }
        }
        
        // criando a variável de decisão y_{j}
        IloNumVarArray y_var(env, n_projetos, 0, 1);
        for (int j=0; j<n_projetos; j++)
        {
            y_var[j] = IloNumVar(env, 0, 1, ILOINT, "y_var");
            model.add(y_var[j]);
        }

        // criando restrições ---------------------------------------------------------
        // 1. restrição de orçamento total
        IloExpr expr1(env);
        for (int j=0; j<n_projetos; j++)
        {
            expr1 += y_var[j] * custos[j];
        }
        IloConstraint c1(expr1 <= capital_total);
        c1.setName("investimento total");
        model.add(c1);
        expr1.end();
        
        // 2. restrição de orçamento por tipo de projeto ------------- TODO: incluir
        
        // 3. restrição de unicidade dos projetos + relação das variáveis de decisão
        for (int j=0; j<n_projetos; j++)
        {
            IloExpr expr2(env);
            expr2 += y_var[j];
            for (int m=0; m<n_sondas; m++)
            {
                for (int t=0; t<n_periodos; t++)
                {
                    expr2 += - x_var[j+lag][m][t];
                }
            }
            IloConstraint c2(expr2 == 0);
            c2.setName("relação entre variáveis e unicidade dos projetos");
            model.add(c2);
            expr2.end();
        }
        
        // 4. restrição de que toda sonda começa na origem
        for (int m=0; m<n_sondas; m++)
        {
            IloExpr expr3(env);
            expr3 += x_var[m][m][0];
            IloConstraint c3(expr3 == 1);
            c3.setName("sondas partindo da origem");
            model.add(c3);
            expr3.end();
        }
        
        // 5. restrição de preempção
        for (int i=0; i<n_projetos+n_sondas; i++)
        {
            for (int j=0; j<n_projetos; j++)
            {
                if (i-lag == j)
                {
                    continue;
                }
                for (int m=0; m<n_sondas; m++)
                {
                    for (int t=0; t<n_periodos; t++)
                    {
                        IloExpr expr4(env);
                        expr4 += x_var[j+lag][m][t];
                        IloInt inicio_s=0, final_s=0;
                        if (i<n_sondas)
                        {
                            inicio_s = t - s[i][j] + 1;
                            final_s = t + tempos_exec[j] + s[i][j] - 1;
                        }
                        else
                        {
                            if (inicio_janela[i-lag] >= t - tempos_exec[i-lag] - s[i][j] + 1)
                            {
                                inicio_s = inicio_janela[i-lag];
                            }
                            else
                            {
                                inicio_s = t - tempos_exec[i-lag] - s[i][j] + 1;
                            }
                            if (final_janela[i-lag]-tempos_exec[i-lag] <= t + tempos_exec[j] + s[i][j] - 1)
                            {
                                final_s = final_janela[i-lag]-tempos_exec[i-lag];
                            }
                            else
                            {
                                final_s = t + tempos_exec[j] + s[i][j] - 1;
                            }
                        }
                        if (inicio_s < 0)
                        {
                            inicio_s = 0;
                        }
                        if (final_s > n_periodos - 1)
                        {
                            final_s = n_periodos - 1;
                        }
                        for (int s=inicio_s; s<final_s+1; s++)
                        {
                            expr4 += x_var[i][m][s];
                        }
                        IloConstraint c4(expr4 <= 1);
                        c4.setName("preempção");
                        model.add(c4);
                        expr4.end();
                    }
                }
            }
        }
            
        // 6. restrição de janela de tempo
        for (int j=0; j<n_projetos; j++)
        {
            IloExpr expr5(env);
            expr5 += - inicio_janela[j] * y_var[j];
            for (int m=0; m<n_sondas; m++)
            {
                IloInt inicio_t, final_t;
                inicio_t = inicio_janela[j];
                final_t = final_janela[j] - tempos_exec[j] + 1;
                for (int t=inicio_t; t<final_t; t++)
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
            expr6 +=  (final_janela[j] - tempos_exec[j]) * y_var[j];
            for (int m=0; m<n_sondas; m++)
            {
                IloInt inicio_t, final_t;
                inicio_t = inicio_janela[j];
                final_t = final_janela[j] - tempos_exec[j] + 1;
                for (int t=inicio_t; t<final_t; t++)
                {
                    expr6 += - x_var[j+lag][m][t] * t;
                }
            }
            IloConstraint c6(expr6 >= 0);
            c6.setName("janela de tempo: final");
            model.add(c6);
            expr6.end();
        }
        
        // criando a função objetivo
        IloExpr expro(env);
        for (int j=0; j<n_projetos; j++)
        {
            expro += y_var[j] * medias_vpl_incondicional[j];
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
        
        // exportando modelo
        cplex.exportModel("modelo_TI_mestrado_joao.lp");

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