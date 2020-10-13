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
        string filename="instancia_mestrado.dat";
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
        t_final = 365*5;
        n_periodos = t_final - t_init + 1;
        // end reading data

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
        
        // definindo s[i][j] -------- TODO: preciso acrescentar a dimensão das sondas, certo?
        NumMatrix3D s(env, n_projetos+1);
        for (int i=0; i<n_projetos+1; i++)
        {
            s[i] = NumMatrix2D(env, n_projetos);
            for (int j=0; j<n_projetos; j++)
            {
                s[i][j] = IloNumArray(env, n_sondas);
            }
        }
        IloInt dist=0;
        for (int i=0; i<n_projetos+1; i++)
        {
            for (int j=0; j<n_projetos; j++)
            {
                for (int m=0; m<n_sondas; m++)
                {
                    if (i==0)
                    {
                        // se i==0, usar origem m como um dos extremos
                        dist = sqrt(pow(sondas_x[m] - coords_x[j], 2)+pow(sondas_y[m] - coords_y[j], 2));
                        s[i][j][m] = dist;
                    }
                    else
                    {
                        // senão, calcular distância entre i e j normalmente
                        dist = sqrt(pow(coords_x[i] - coords_x[j], 2)+pow(coords_y[i] - coords_y[j], 2));
                        s[i][j][m] = dist;
                    }
                }
            }
        }

        // definindo BigM[i][j] ------------- TODO: olhar no artigo
        NumMatrix2D BigM(env, n_projetos+1);
        for (int i=0; i<n_projetos+1; i++)
        {
            BigM[i] = IloNumArray(env, n_projetos);
        }

        // instanciando o modelo
        IloModel model(env);

        // criando variáveis de decisão ---------------------------------------------
        // criando a variável de decisão x_{ijm}
        NumVarMatrix3D x_var(env, n_projetos+1);
        for (int i=0; i<n_projetos+1; i++)
        {
            x_var[i] = NumVarMatrix2D(env, n_projetos);
            for (int j=0; j<n_projetos; j++)
            {
                x_var[i][j] = IloNumVarArray(env, n_sondas, 0, 1, ILOINT);
            }
        }
        // criando a variável de decisão c_{jm} -------- TODO: conferir se add origem ou nao
        // --------------------------------------------- TODO: se sim, garantir c[0][m] = 0
        NumVarMatrix2D c_var(env, n_projetos+1);
        for (int i=0; i<n_projetos+1; i++)
        {
            c_var[i] = IloNumVarArray(env, n_sondas, t_init, t_final, ILOINT);
        }

        // criando restrições ---------------------------------------------------------
        // 1. restrição de orçamento total
        IloExpr expr(env);
        for (int i=0; i<n_projetos+1; i++)
        {
            for (int j=0; j<n_projetos; j++)
            {
                for (int m=0; m<n_sondas; m++)
                {
                    expr += x_var[i][j][m] * custos[j];
                }
            }
        }
        model.add(IloRange(env, 0, expr, capital_total));
        expr.end();
        // 2. restrição de orçamento por tipo de projeto ------- TODO: incluir
        // 3. restrição de unicidade de saída da origem (forall m)
        for (int m=0; m<n_sondas; m++)
        {
            IloExpr expr(env);
            for (int j=0; j<n_projetos; j++)
            {
                expr += x_var[0][j][m]; 
            }
            model.add(IloRange(env, 0, expr, 1));
            expr.end();
        }
        // 4. restrição de unicidade na execução dos projetos (forall j)
        for (int j=0; j<n_projetos; j++)
        {
            IloExpr expr(env);
            for (int i=0; i<n_projetos+1; i++)
            {
                for (int m=0; m<n_sondas; m++)
                {
                    expr += x_var[i][j][m];
                }
            }
            model.add(IloRange(env, 0, expr, 1));
            expr.end();
        }
        // 5. restrição de unicidade na execução dos projetos (forall i)
        for (int i=0; i<n_projetos+1; i++)
        {
            IloExpr expr(env);
            for (int j=0; j<n_projetos; j++)
            {
                for (int m=0; m<n_sondas; m++)
                {
                    expr += x_var[i][j][m];
                }
            }
            model.add(IloRange(env, 0, expr, 1));
            expr.end();
        }
        // 6. restrição de conservação de fluxo ---------------- TODO: conferir se precisa do k
        for (int m=0; m<n_sondas; m++)
        {
            for (int j=0; j<n_projetos; j++)
            {
                IloExpr expr(env);
                for (int i=0; i<n_projetos+1; i++)
                {
                    for (int k=0; k<n_projetos; k++)
                    {
                        expr += x_var[i][j][m] - x_var[j+1][k][m];
                    }
                }
                model.add(IloRange(env, 0, expr, 1));
                expr.end();
            }
        }
        // 7. restrição de escalonamento mtz ----- TODO: conferir limite superior da restricao
        //  -------------------------------------- TODO: definir BigM[i][j]
        //  -------------------------------------- TODO: i != j neh ??? se sim, add na formulacao e codigo
        for (int i=0; i<n_projetos+1; i++)
        {
            for (int j=0; j<n_projetos; j++)
            {
                for (int m=0; m<n_sondas; m++)
                {
                    IloExpr expr(env);
                    expr += c_var[j+1][m] - (c_var[i][m] + s[i][j] + tempos_exec[j] - BigM[i][j]*(1-x_var[i][j][m])) ;
                    model.add(IloRange(env, 0, expr, t_final));
                    expr.end();
                }
            }
        }
        // 8. restrição de janela de tempo
        // ------------------------------------------ TODO: separar restrição em duas partes,
        // ------------------------------------------------ ou consigo usar expressões como limites?
        // ------------------------------------------ TODO: conferir limite superior das restrições
        for (int m=0; m<n_sondas; m++)
        {
            for (int j=0; j<n_projetos; j++)
            {
                IloExpr expr1(env);
                IloExpr expr2(env);
                for (int i=0; i<n_projetos+1; i++)
                {
                    expr1 += c_var[j+1][m] - ((inicio_janela[j]+tempos_exec[j])*x_var[i][j][m]);
                    expr2 += final_janela[j]*x_var[i][j][m] - c_var[j+1][m];
                }
                model.add(IloRange(env, 0, expr1, t_final));
                model.add(IloRange(env, 0, expr2, t_final));
                expr1.end();
                expr2.end();
            }
        }

        // criando a função objetivo
        IloExpr expr(env);
        for (int i=0; i<n_projetos+1; i++)
        {
            for (int j=0; j<n_projetos; j++)
            {
                for (int m=0; m<n_sondas; m++)
                {
                    expr += x[i][j][m] * medias_vpl_incondicional[j];
                }
            }
        }
        model.add(IloObjective(env, expr, IloObjective::Maximize));
        expr.end();

        // declarando o otimizador
        IloCplex cplex(model);
        // resolvendo o modelo
        cplex.solve();
        
        // printando status da otimização
        env.out() << "Solution status = " << cplex.getStatus() << endl;

        // printando valor obtido para a função objetivo
        env.out() << "Solution value  = " << cplex.getObjValue() << endl;

        // delcarando objeto que vai conter valor das variáveis de decisão
        NumMatrix3D x_vals(env);
        NumMatrix2D c_vals(env);
        
        // pegando valores atribuídos às variáveis de decisão
        cplex.getValues(x_vals, x_var);
        env.out() << "x[i][j][m]        = " << x_vals << endl;
        cplex.getValues(c_vals, c_var);
        env.out() << "c[j][m]        = " << c_vals << endl;
        
        // exportando modelo
        cplex.exportModel("nome.lp");

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