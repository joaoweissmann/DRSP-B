// TODO: debug mode
// TODO: asserts


#include <bits/stdc++.h>
#include "DadosDeEntrada.h"

DadosDeEntrada::DadosDeEntrada()
{
    _nProjetos = 0;
    _nSondas = 0;
    _nPeriodos = 0;
    _propriedadesProj = 0;
    _propriedadesSondas = 0;
    _tInit = 0;
    _tFinal = 0;
    _delta = 0;
    _capitalTotal = 0;
    _projetos.resize(0); // TODO: isso funciona?
    _sondas.resize(0); // TODO: isso funciona?
    _desloc.resize(0); // TODO: isso funciona?
}

int DadosDeEntrada::getNProjetos()
{
    return _nProjetos;
}

int DadosDeEntrada::getNSondas()
{
    return _nSondas;
}

int DadosDeEntrada::getNPeriodos()
{
    return _nPeriodos;
}

int DadosDeEntrada::getPropriedadesProj()
{
    return _propriedadesProj;
}

int DadosDeEntrada::getPropriedadesSondas()
{
    return _propriedadesSondas;
}

int DadosDeEntrada::getTInit()
{
    return _tInit;
}

int DadosDeEntrada::getTFinal()
{
    return _tFinal;
}

int DadosDeEntrada::getDelta()
{
    return _delta;
}

double DadosDeEntrada::getCapitalTotal()
{
    return _capitalTotal;
}

std::vector<Projeto> DadosDeEntrada::getProjetos()
{
    return _projetos;
}

Projeto DadosDeEntrada::getProjeto(int i)
{
    return _projetos[i];
}

std::vector<Sonda> DadosDeEntrada::getSondas()
{
    return _sondas;
}

Sonda DadosDeEntrada::getSonda(int i)
{
    return _sondas[i];
}

std::vector<std::vector<double>> DadosDeEntrada::getDesloc()
{
    return _desloc;
}

double DadosDeEntrada::getDesloc(int i, int j)
{
    return _desloc[i][j];
}

double DadosDeEntrada::getDesloc(Sonda s, Projeto p)
{
    Vertice v{_nSondas, _nProjetos};
    int sondaIndex, projIndex;
    sondaIndex = v.getVerticeIndex(s);
    projIndex = v.getVerticeIndex(p);
    return _desloc[sondaIndex][projIndex];
}

double DadosDeEntrada::getDesloc(Projeto p1, Projeto p2)
{
    Vertice v{_nSondas, _nProjetos};
    int proj1Index, proj2Index;
    proj1Index = v.getVerticeIndex(p1);
    proj2Index = v.getVerticeIndex(p2);
    return _desloc[proj1Index][proj2Index];
}

void DadosDeEntrada::setNProjetos(int value)
{
    _nProjetos = value;
    _projetos.resize(_nProjetos);
    _desloc.resize((_nSondas+_nProjetos));
    for (int i=0; i<(_nSondas+_nProjetos); i++)
    {
        _desloc[i].resize((_nSondas+_nProjetos));
    }
}

void DadosDeEntrada::setNSondas(int value)
{
    _nSondas = value;
    _sondas.resize(_nSondas);
    _desloc.resize((_nSondas+_nProjetos));
    for (int i=0; i<(_nSondas+_nProjetos); i++)
    {
        _desloc[i].resize((_nSondas+_nProjetos));
    }
}

void DadosDeEntrada::setNPeriodos(int value)
{
    _nPeriodos = value;
}

void DadosDeEntrada::setPropriedadesProj(int value)
{
    _propriedadesProj = value;
}

void DadosDeEntrada::setPropriedadesSondas(int value)
{
    _propriedadesSondas = value;
}

void DadosDeEntrada::setTInit(int value)
{
    _tInit = value;
}

void DadosDeEntrada::setTFinal(int value)
{
    _tFinal = value;
}

void DadosDeEntrada::setDelta(int value)
{
    _delta = value;
}

void DadosDeEntrada::setCapitalTotal(double value)
{
    _capitalTotal = value;
}

void DadosDeEntrada::setProjetos(std::vector<std::vector<double>> v)
{
    Projeto p;
    for (int i=0; i<_nProjetos; i++)
    {
        _projetos[i].setBacia(v[i][p.getPropIdx("bacia")]);
        _projetos[i].setCoordX(v[i][p.getPropIdx("coordX")]);
        _projetos[i].setCoordY(v[i][p.getPropIdx("coordY")]);
        _projetos[i].setCusto(v[i][p.getPropIdx("custo")]);
        _projetos[i].setFinalJanela(v[i][p.getPropIdx("finalJanela")]);
        _projetos[i].setGeometria(v[i][p.getPropIdx("geometria")]);
        _projetos[i].setGeracao(v[i][p.getPropIdx("geracao")]);
        _projetos[i].setInicioJanela(v[i][p.getPropIdx("inicioJanela")]);
        _projetos[i].setMaturidade(v[i][p.getPropIdx("maturidade")]);
        _projetos[i].setMcVol(v[i][p.getPropIdx("mcVol")]);
        _projetos[i].setMcVpl(v[i][p.getPropIdx("mcVpl")]);
        _projetos[i].setMigracao(v[i][p.getPropIdx("migracao")]);
        _projetos[i].setMiVol(v[i][p.getPropIdx("miVol")]);
        _projetos[i].setMiVpl(v[i][p.getPropIdx("miVpl")]);
        _projetos[i].setNome(v[i][p.getPropIdx("nome")]);
        _projetos[i].setPcgna(v[i][p.getPropIdx("pcgna")]);
        _projetos[i].setPlay(v[i][p.getPropIdx("play")]);
        _projetos[i].setPshc(v[i][p.getPropIdx("pshc")]);
        _projetos[i].setQualidade(v[i][p.getPropIdx("qualidade")]);
        _projetos[i].setReservatorio(v[i][p.getPropIdx("reservatorio")]);
        _projetos[i].setRetencao(v[i][p.getPropIdx("retencao")]);
        _projetos[i].setSoterramento(v[i][p.getPropIdx("soterramento")]);
        _projetos[i].setTempExec(v[i][p.getPropIdx("tempExec")]);
    }
}

void DadosDeEntrada::setProjetos(std::vector<Projeto> v)
{
    for (int i=0; i<_nProjetos; i++)
    {
        _projetos[i].setBacia(v[i].getBacia());
        _projetos[i].setCoordX(v[i].getCoordX());
        _projetos[i].setCoordY(v[i].getCoordY());
        _projetos[i].setCusto(v[i].getCusto());
        _projetos[i].setFinalJanela(v[i].getFinalJanela());
        _projetos[i].setGeometria(v[i].getGeometria());
        _projetos[i].setGeracao(v[i].getGeracao());
        _projetos[i].setInicioJanela(v[i].getInicioJanela());
        _projetos[i].setMaturidade(v[i].getMaturidade());
        _projetos[i].setMcVol(v[i].getMcVol());
        _projetos[i].setMcVpl(v[i].getMcVpl());
        _projetos[i].setMigracao(v[i].getMigracao());
        _projetos[i].setMiVol(v[i].getMiVol());
        _projetos[i].setMiVpl(v[i].getMiVpl());
        _projetos[i].setNome(v[i].getNome());
        _projetos[i].setPcgna(v[i].getPcgna());
        _projetos[i].setPlay(v[i].getPlay());
        _projetos[i].setPshc(v[i].getPshc());
        _projetos[i].setQualidade(v[i].getQualidade());
        _projetos[i].setReservatorio(v[i].getReservatorio());
        _projetos[i].setRetencao(v[i].getRetencao());
        _projetos[i].setSoterramento(v[i].getSoterramento());
        _projetos[i].setTempExec(v[i].getTempExec());
    }
}

void DadosDeEntrada::setProjeto(Projeto v, int i)
{
    _projetos[i].setBacia(v.getBacia());
    _projetos[i].setCoordX(v.getCoordX());
    _projetos[i].setCoordY(v.getCoordY());
    _projetos[i].setCusto(v.getCusto());
    _projetos[i].setFinalJanela(v.getFinalJanela());
    _projetos[i].setGeometria(v.getGeometria());
    _projetos[i].setGeracao(v.getGeracao());
    _projetos[i].setInicioJanela(v.getInicioJanela());
    _projetos[i].setMaturidade(v.getMaturidade());
    _projetos[i].setMcVol(v.getMcVol());
    _projetos[i].setMcVpl(v.getMcVpl());
    _projetos[i].setMigracao(v.getMigracao());
    _projetos[i].setMiVol(v.getMiVol());
    _projetos[i].setMiVpl(v.getMiVpl());
    _projetos[i].setNome(v.getNome());
    _projetos[i].setPcgna(v.getPcgna());
    _projetos[i].setPlay(v.getPlay());
    _projetos[i].setPshc(v.getPshc());
    _projetos[i].setQualidade(v.getQualidade());
    _projetos[i].setReservatorio(v.getReservatorio());
    _projetos[i].setRetencao(v.getRetencao());
    _projetos[i].setSoterramento(v.getSoterramento());
    _projetos[i].setTempExec(v.getTempExec());
}

void DadosDeEntrada::setSondas(std::vector<std::vector<double>> v)
{
    Sonda s;
    for (int i=0; i<_nSondas; i++)
    {
        _sondas[i].setCoordX(v[i][s.getPropIdx("coordX")]);
        _sondas[i].setCoordY(v[i][s.getPropIdx("coordY")]);
        _sondas[i].setNome(i);
    }
}

void DadosDeEntrada::setSondas(std::vector<Sonda> v)
{
    for (int i=0; i<_nSondas; i++)
    {
        _sondas[i].setCoordX(v[i].getCoordX());
        _sondas[i].setCoordY(v[i].getCoordY());
        _sondas[i].setNome(v[i].getNome());
    }
}

void DadosDeEntrada::setSonda(Sonda v, int i)
{
    _sondas[i].setCoordX(v.getCoordX());
    _sondas[i].setCoordY(v.getCoordY());
    _sondas[i].setNome(v.getNome());
}

void DadosDeEntrada::setDesloc(std::vector<std::vector<double>> v)
{
    for (int i=0; i<(_nSondas+_nProjetos); i++)
    {
        for (int j=0; j<(_nSondas+_nProjetos); j++)
        {
            _desloc[i][j] = v[i][j];
        }
    }
}

void DadosDeEntrada::setDesloc(int i, int j, double value)
{
    _desloc[i][j] = value;
}

void DadosDeEntrada::print()
{
    
    std::cout << std::endl;
    std::cout << "A instância tem: " << std::endl;
    std::cout << _nProjetos << " projetos" << std::endl;
    std::cout << _capitalTotal << " como orçamento total" << std::endl;
    std::cout << _tInit << " como o tempo inicial" << std::endl;
    std::cout << _tFinal << " como o tempo final" << std::endl;
    std::cout << _delta << " como delta tempo" << std::endl;
    std::cout << _nPeriodos << " períodos de tempo" << std::endl;
    std::cout << _nSondas << " sondas disponíveis" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Dados lidos de projetos:" << std::endl;
    for (int i=0; i<_nProjetos; i++)
    {
        std::cout << _projetos[i].getCoordX() << " ";
        std::cout << _projetos[i].getCoordY() << " ";
        std::cout << _projetos[i].getBacia() << " ";
        std::cout << _projetos[i].getNome() << " ";
        std::cout << _projetos[i].getMaturidade() << " ";
        std::cout << _projetos[i].getQualidade() << " ";
        std::cout << _projetos[i].getPlay() << " ";
        std::cout << _projetos[i].getSoterramento() << " ";
        std::cout << _projetos[i].getPcgna() << " ";
        std::cout << _projetos[i].getGeracao() << " ";
        std::cout << _projetos[i].getMigracao() << " ";
        std::cout << _projetos[i].getReservatorio() << " ";
        std::cout << _projetos[i].getGeometria() << " ";
        std::cout << _projetos[i].getRetencao() << " ";
        std::cout << _projetos[i].getPshc() << " ";
        std::cout << _projetos[i].getMcVol() << " ";
        std::cout << _projetos[i].getMiVol() << " ";
        std::cout << _projetos[i].getMcVpl() << " ";
        std::cout << _projetos[i].getMiVpl() << " ";
        std::cout << _projetos[i].getCusto() << " ";
        std::cout << _projetos[i].getTempExec() << " ";
        std::cout << _projetos[i].getInicioJanela() << " ";
        std::cout << _projetos[i].getFinalJanela() << " ";
    } std::cout << std::endl;

    std::cout << "dados lidos de sondas: " << std::endl;
    for (int i=0; i<_nSondas; i++)
    {
        std::cout << _sondas[i].getCoordX() << " ";
        std::cout << _sondas[i].getCoordY() << " ";
    } std::cout << std::endl;
    
    std::cout << "deslocamentos lidos: " << std::endl;
    for (int i=0; i<(_nSondas+_nProjetos); i++)
    {
        for (int j=0; j<(_nSondas+_nProjetos); j++)
        {
            std::cout << _desloc[i][j] << " ";
        } std::cout << std::endl;
    } std::cout << std::endl;
    
}

