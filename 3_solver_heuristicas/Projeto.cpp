

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
}

Projeto::Projeto(double coordX, double coordY, int bacia, int nome, int maturidade, int qualidade, int play, double soterramento,
        double pcgna, double geracao, double migracao, double reservatorio, double geometria, double retencao,
        double pshc, double mcVol, double miVol, double mcVpl, double miVpl, double custo,
        int tempExec, int inicioJanela, int finalJanela)
{
    if (coordX < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "coordX fornecida é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << coordX << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(coordX >= 0);
    _coordX = coordX;
    if (coordY < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "coordY fornecida é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << coordY << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(coordY >= 0);
    _coordY = coordY;
    if (bacia < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "bacia fornecida é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << bacia << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(bacia >= 0);
    _bacia = bacia;
    if (nome < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "nome fornecido é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << nome << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(nome >= 0);
    _nome = nome;
    if (maturidade < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "maturidade fornecida é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << maturidade << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(maturidade >= 0);
    _maturidade = maturidade;
    if (qualidade < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "qualidade fornecida é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << qualidade << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(qualidade >= 0);
    _qualidade = qualidade;
    if (play < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "play fornecido é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << play << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(play >= 0);
    _play = play;
    if (soterramento < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "soterramento fornecido é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << soterramento << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(soterramento >= 0);
    _soterramento = soterramento;
    if ((pcgna < 0) || (pcgna > 1))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "pcgna fornecida é menor do que zero ou maior que um." << std::endl;
        std::cout << "Valor fornecido: " << pcgna << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert((pcgna >= 0) && (pcgna <= 1));
    _pcgna = pcgna;
    if ((geracao < 0) || (geracao > 1))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "geracao fornecida é menor do que zero ou maior que um." << std::endl;
        std::cout << "Valor fornecido: " << geracao << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert((geracao >= 0) && (geracao <= 1));
    _geracao = geracao;
    if ((migracao < 0) || (migracao > 1))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "migracao fornecida é menor do que zero ou maior que um." << std::endl;
        std::cout << "Valor fornecido: " << migracao << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert((migracao >= 0) && (migracao <= 1));
    _migracao = migracao;
    if ((reservatorio < 0) || (reservatorio > 1))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "reservatorio fornecida é menor do que zero ou maior que um." << std::endl;
        std::cout << "Valor fornecido: " << reservatorio << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert((reservatorio >= 0) && (reservatorio <= 1));
    _reservatorio = reservatorio;
    if ((geometria < 0) || (geometria > 1))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "geometria fornecida é menor do que zero ou maior que um." << std::endl;
        std::cout << "Valor fornecido: " << geometria << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert((geometria >= 0) && (geometria <= 1));
    _geometria = geometria;
    if ((retencao < 0) || (retencao > 1))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "retencao fornecida é menor do que zero ou maior que um." << std::endl;
        std::cout << "Valor fornecido: " << retencao << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert((retencao >= 0) && (retencao <= 1));
    _retencao = retencao;
    if ((pshc < 0) || (pshc > 1))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "pshc fornecido é menor do que zero ou maior que um." << std::endl;
        std::cout << "Valor fornecido: " << pshc << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert((pshc >= 0) && (pshc <= 1));
    _pshc = pshc;
    if (mcVol < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "mcVol fornecida é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << mcVol << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(mcVol >= 0);
    _mcVol = mcVol;
    if (miVol < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "miVol fornecida é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << miVol << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(miVol >= 0);
    _miVol = miVol;
    _mcVpl = mcVpl;
    _miVpl = miVpl;
    if (custo < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "custo fornecido é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << custo << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(custo >= 0);
    _custo = custo;
    if (tempExec < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "tempExec fornecido é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << tempExec << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(tempExec >= 0);
    _tempExec = tempExec;
    if (inicioJanela < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "inicioJanela fornecido é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << inicioJanela << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(inicioJanela >= 0);
    _inicioJanela = inicioJanela;
    if (finalJanela < inicioJanela)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "finalJanela fornecido é menor do que o inicioJanela." << std::endl;
        std::cout << "Valor fornecido: " << finalJanela << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(finalJanela >= inicioJanela);
    _finalJanela = finalJanela;
}

void Projeto::copyFrom(Projeto p)
{
    _coordX = p.getCoordX();
    _coordY = p.getCoordY();
    _bacia = p.getBacia();
    _nome = p.getNome();
    _maturidade = p.getMaturidade();
    _qualidade = p.getQualidade();
    _play = p.getPlay();
    _soterramento = p.getSoterramento();
    _pcgna = p.getPcgna();
    _geracao = p.getGeracao();
    _migracao = p.getMigracao();
    _reservatorio = p.getReservatorio();
    _geometria = p.getGeometria();
    _retencao = p.getRetencao();
    _pshc = p.getPshc();
    _mcVol = p.getMcVol();
    _miVol = p.getMiVol();
    _mcVpl = p.getMcVpl();
    _miVpl = p.getMiVpl();
    _custo = p.getCusto();
    _tempExec = p.getTempExec();
    _inicioJanela = p.getInicioJanela();
    _finalJanela = p.getFinalJanela();
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

void Projeto::setCoordX(double value)
{
    if (value < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "coordX fornecida é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(value >= 0);
    _coordX = value;
}

void Projeto::setCoordY(double value)
{
    if (value < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "coordY fornecida é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(value >= 0);
    _coordY = value;
}

void Projeto::setBacia(int value)
{
    if (value < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "bacia fornecida é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(value >= 0);
    _bacia = value;
}

void Projeto::setNome(int value)
{
    if (value < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "nome fornecido é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(value >= 0);
    _nome = value;
}

void Projeto::setMaturidade(int value)
{
    if (value < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "maturidade fornecida é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(value >= 0);
    _maturidade = value;
}

void Projeto::setQualidade(int value)
{
    if (value < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "qualidade fornecida é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(value >= 0);
    _qualidade = value;
}

void Projeto::setPlay(int value)
{
    if (value < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "play fornecido é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(value >= 0);
    _play = value;
}

void Projeto::setSoterramento(double value)
{
    if (value < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "soterramento fornecido é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(value >= 0);
    _soterramento = value;
}

void Projeto::setPcgna(double value)
{
    if ((value < 0) || (value > 1))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "pcgna fornecida é menor do que zero ou maior do que um." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert((value >= 0) && (value <= 1));
    _pcgna = value;
}

void Projeto::setGeracao(double value)
{
    if ((value < 0) || (value > 1))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "geracao fornecida é menor do que zero ou maior do que um." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert((value >= 0) && (value <= 1));
    _geracao = value;
}

void Projeto::setMigracao(double value)
{
    if ((value < 0) || (value > 1))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "migracao fornecida é menor do que zero ou maior do que um." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert((value >= 0) && (value <= 1));
    _migracao = value;
}

void Projeto::setReservatorio(double value)
{
    if ((value < 0) || (value > 1))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "reservatorio fornecida é menor do que zero ou maior do que um." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert((value >= 0) && (value <= 1));
    _reservatorio = value;
}

void Projeto::setGeometria(double value)
{
    if ((value < 0) || (value > 1))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "geometria fornecida é menor do que zero ou maior do que um." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert((value >= 0) && (value <= 1));
    _geometria = value;
}

void Projeto::setRetencao(double value)
{
    if ((value < 0) || (value > 1))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "retencao fornecida é menor do que zero ou maior do que um." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert((value >= 0) && (value <= 1));
    _retencao = value;
}

void Projeto::setPshc(double value)
{
    if ((value < 0) || (value > 1))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "pshc fornecida é menor do que zero ou maior do que um." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert((value >= 0) && (value <= 1));
    _pshc = value;
}

void Projeto::setMcVol(double value)
{
    if (value < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "mcVol fornecido é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(value >= 0);
    _mcVol = value;
}

void Projeto::setMiVol(double value)
{
    if (value < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "miVol fornecido é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(value >= 0);
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
    if (value < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "custo fornecido é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(value >= 0);
    _custo = value;
}

void Projeto::setTempExec(int value)
{
    if (value < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "tempExec fornecido é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(value >= 0);
    _tempExec = value;
}

void Projeto::setInicioJanela(int value)
{
    if (value < 0)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "inicioJanela fornecido é menor do que zero." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(value >= 0);
    _inicioJanela = value;
}

void Projeto::setFinalJanela(int value)
{
    if (value < _inicioJanela)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "finalJanela fornecido é menor do que o inicioJanela." << std::endl;
        std::cout << "Valor fornecido: " << value << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(value >= _inicioJanela);
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

