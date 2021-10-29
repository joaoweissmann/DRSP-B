// TODO: debug mode
// TODO: asserts


#include <bits/stdc++.h>
#include "Projeto.h"

Projeto::Projeto()
{
    _coordX = 0;
    _coordY = 0;
    _bacia = 0;
    _nome = 0;
    _maturidade = 0;
    _qualidade = 0;
    _play = 0;
    _soterramento = 0;
    _pcgna = 0;
    _geracao = 0;
    _migracao = 0;
    _reservatorio = 0;
    _geometria = 0;
    _retencao = 0;
    _pshc = 0;
    _mcVol = 0;
    _miVol = 0;
    _mcVpl = 0;
    _miVpl = 0;
    _custo = 0;
    _tempExec = 0;
    _inicioJanela = 0;
    _finalJanela = 0;
    _mapPropIdx.insert(std::pair<std::string, int>("coordX", 0));
    _mapPropIdx.insert(std::pair<std::string, int>("coordY", 1));
    _mapPropIdx.insert(std::pair<std::string, int>("bacia", 2));
    _mapPropIdx.insert(std::pair<std::string, int>("nome", 3));
    _mapPropIdx.insert(std::pair<std::string, int>("maturidade", 4));
    _mapPropIdx.insert(std::pair<std::string, int>("qualidade", 5));
    _mapPropIdx.insert(std::pair<std::string, int>("play", 6));
    _mapPropIdx.insert(std::pair<std::string, int>("soterramento", 7));
    _mapPropIdx.insert(std::pair<std::string, int>("pcgna", 8));
    _mapPropIdx.insert(std::pair<std::string, int>("geracao", 9));
    _mapPropIdx.insert(std::pair<std::string, int>("migracao", 10));
    _mapPropIdx.insert(std::pair<std::string, int>("reservatorio", 11));
    _mapPropIdx.insert(std::pair<std::string, int>("geometria", 12));
    _mapPropIdx.insert(std::pair<std::string, int>("retencao", 13));
    _mapPropIdx.insert(std::pair<std::string, int>("pshc", 14));
    _mapPropIdx.insert(std::pair<std::string, int>("mcVol", 15));
    _mapPropIdx.insert(std::pair<std::string, int>("miVol", 16));
    _mapPropIdx.insert(std::pair<std::string, int>("mcVpl", 17));
    _mapPropIdx.insert(std::pair<std::string, int>("miVpl", 18));
    _mapPropIdx.insert(std::pair<std::string, int>("custos", 19));
    _mapPropIdx.insert(std::pair<std::string, int>("tempExec", 20));
    _mapPropIdx.insert(std::pair<std::string, int>("inicioJanela", 21));
    _mapPropIdx.insert(std::pair<std::string, int>("finalJanela", 22));
}

Projeto::Projeto(double coordX, double coordY, int bacia, int nome, int maturidade, int qualidade, int play, double soterramento,
        double pcgna, double geracao, double migracao, double reservatorio, double geometria, double retencao,
        double pshc, double mcVol, double miVol, double mcVpl, double miVpl, double custo,
        int tempExec, int inicioJanela, int finalJanela)
{
    _coordX = coordX;
    _coordY = coordY;
    _bacia = bacia;
    _nome = nome;
    _maturidade = maturidade;
    _qualidade = qualidade;
    _play = play;
    _soterramento = soterramento;
    _pcgna = pcgna;
    _geracao = geracao;
    _migracao = migracao;
    _reservatorio = reservatorio;
    _geometria = geometria;
    _retencao = retencao;
    _pshc = pshc;
    _mcVol = mcVol;
    _miVol = miVol;
    _mcVpl = mcVpl;
    _miVpl = miVpl;
    _custo = custo;
    _tempExec = tempExec;
    _inicioJanela = inicioJanela;
    _finalJanela = finalJanela;
    _mapPropIdx.insert(std::pair<std::string, int>("coordX", 0));
    _mapPropIdx.insert(std::pair<std::string, int>("coordY", 1));
    _mapPropIdx.insert(std::pair<std::string, int>("bacia", 2));
    _mapPropIdx.insert(std::pair<std::string, int>("nome", 3));
    _mapPropIdx.insert(std::pair<std::string, int>("maturidade", 4));
    _mapPropIdx.insert(std::pair<std::string, int>("qualidade", 5));
    _mapPropIdx.insert(std::pair<std::string, int>("play", 6));
    _mapPropIdx.insert(std::pair<std::string, int>("soterramento", 7));
    _mapPropIdx.insert(std::pair<std::string, int>("pcgna", 8));
    _mapPropIdx.insert(std::pair<std::string, int>("geracao", 9));
    _mapPropIdx.insert(std::pair<std::string, int>("migracao", 10));
    _mapPropIdx.insert(std::pair<std::string, int>("reservatorio", 11));
    _mapPropIdx.insert(std::pair<std::string, int>("geometria", 12));
    _mapPropIdx.insert(std::pair<std::string, int>("retencao", 13));
    _mapPropIdx.insert(std::pair<std::string, int>("pshc", 14));
    _mapPropIdx.insert(std::pair<std::string, int>("mcVol", 15));
    _mapPropIdx.insert(std::pair<std::string, int>("miVol", 16));
    _mapPropIdx.insert(std::pair<std::string, int>("mcVpl", 17));
    _mapPropIdx.insert(std::pair<std::string, int>("miVpl", 18));
    _mapPropIdx.insert(std::pair<std::string, int>("custos", 19));
    _mapPropIdx.insert(std::pair<std::string, int>("tempExec", 20));
    _mapPropIdx.insert(std::pair<std::string, int>("inicioJanela", 21));
    _mapPropIdx.insert(std::pair<std::string, int>("finalJanela", 22));
}

double Projeto::getCoordX()
{
    return _coordX;
}

double Projeto::getCoordY()
{
    return _coordY;
}

int Projeto::getBacia()
{
    return _bacia;
}

int Projeto::getNome()
{
    return _nome;
}

int Projeto::getMaturidade()
{
    return _maturidade;
}

int Projeto::getQualidade()
{
    return _qualidade;
}

int Projeto::getPlay()
{
    return _play;
}

double Projeto::getSoterramento()
{
    return _soterramento;
}

double Projeto::getPcgna()
{
    return _pcgna;
}

double Projeto::getGeracao()
{
    return _geracao;
}

double Projeto::getMigracao()
{
    return _migracao;
}

double Projeto::getReservatorio()
{
    return _reservatorio;
}

double Projeto::getGeometria()
{
    return _geometria;
}

double Projeto::getRetencao()
{
    return _retencao;
}

double Projeto::getPshc()
{
    return _pshc;
}

double Projeto::getMcVol()
{
    return _mcVol;
}

double Projeto::getMiVol()
{
    return _miVol;
}

double Projeto::getMcVpl()
{
    return _mcVpl;
}

double Projeto::getMiVpl()
{
    return _miVpl;
}

double Projeto::getCusto()
{
    return _custo;
}

int Projeto::getTempExec()
{
    return _tempExec;
}

int Projeto::getInicioJanela()
{
    return _inicioJanela;
}

int Projeto::getFinalJanela()
{
    return _finalJanela;
}

std::map<std::string, int> Projeto::getMapPropIdx()
{
    return _mapPropIdx;
}

int Projeto::getPropIdx(std::string s)
{
    auto it = _mapPropIdx.find(s);
    return it->second;
}

void Projeto::setCoordX(double value)
{
    _coordX = value;
}

void Projeto::setCoordY(double value)
{
    _coordY = value;
}

void Projeto::setBacia(int value)
{
    _bacia = value;
}

void Projeto::setNome(int value)
{
    _nome = value;
}

void Projeto::setMaturidade(int value)
{
    _maturidade = value;
}

void Projeto::setQualidade(int value)
{
    _qualidade = value;
}

void Projeto::setPlay(int value)
{
    _play = value;
}

void Projeto::setSoterramento(double value)
{
    _soterramento = value;
}

void Projeto::setPcgna(double value)
{
    _pcgna = value;
}

void Projeto::setGeracao(double value)
{
    _geracao = value;
}

void Projeto::setMigracao(double value)
{
    _migracao = value;
}

void Projeto::setReservatorio(double value)
{
    _reservatorio = value;
}

void Projeto::setGeometria(double value)
{
    _geometria = value;
}

void Projeto::setRetencao(double value)
{
    _retencao = value;
}

void Projeto::setPshc(double value)
{
    _pshc = value;
}

void Projeto::setMcVol(double value)
{
    _mcVol = value;
}

void Projeto::setMiVol(double value)
{
    _miVol = value;
}

void Projeto::setMcVpl(double value)
{
    _mcVpl = value;
}

void Projeto::setMiVpl(double value)
{
    _miVpl = value;
}

void Projeto::setCusto(double value)
{
    _custo = value;
}

void Projeto::setTempExec(int value)
{
    _tempExec = value;
}

void Projeto::setInicioJanela(int value)
{
    _inicioJanela = value;
}

void Projeto::setFinalJanela(int value)
{
    _finalJanela = value;
}

void Projeto::print()
{
    std::cout << std::endl;
    std::cout << "O projeto " << _nome << " tem:" << std::endl;
    std::cout << "Coordenada x: " << _coordX << std::endl;
    std::cout << "Coordenada y: " << _coordY << std::endl;
    std::cout << "Bacia: " << _bacia << std::endl;
    std::cout << "Maturidade: " << _maturidade << std::endl;
    std::cout << "Qualidade: " << _qualidade << std::endl;
    std::cout << "Play: " << _play << std::endl;
    std::cout << "Soterramento: " << _soterramento << std::endl;
    std::cout << "PCGNA: " << _pcgna << std::endl;
    std::cout << "Geração: " << _geracao << std::endl;
    std::cout << "Migração: " << _migracao << std::endl;
    std::cout << "Reservatório: " << _reservatorio << std::endl;
    std::cout << "Geometria: " << _geometria << std::endl;
    std::cout << "Retenção: " << _retencao << std::endl;
    std::cout << "PSHC: " << _pshc << std::endl;
    std::cout << "MC Volume: " << _mcVol << std::endl;
    std::cout << "MI Volume: " << _miVol << std::endl;
    std::cout << "MC VPL: " << _mcVpl << std::endl;
    std::cout << "MI VPL: " << _miVpl << std::endl;
    std::cout << "Custo: " << _custo << std::endl;
    std::cout << "Tempo de execução: " << _tempExec << std::endl;
    std::cout << "Início da janela: " << _inicioJanela << std::endl;
    std::cout << "Final da janela: " << _finalJanela << std::endl;
    std::cout << std::endl;
}

