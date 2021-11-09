

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
    _projetos.resize(0);
    _sondas.resize(0); 
    _desloc.resize(0);
}

DadosDeEntrada::DadosDeEntrada(int nProjetos, int nSondas, int nPeriodos, int propriedadesProj, int propriedadesSondas,
                               int tInit, int tFinal, int delta, double capitalTotal, std::vector<Projeto> projetos, 
                               std::vector<Sonda> sondas, std::vector<std::vector<double>> desloc)
{
    _nPeriodos = nPeriodos;
    _propriedadesProj = propriedadesProj;
    _propriedadesSondas = propriedadesSondas;
    _tInit = tInit;
    _tFinal = tFinal;
    _delta = delta;
    _capitalTotal = capitalTotal;

    if (nProjetos != projetos.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "nProjetos não compatível com tamanho do vetor projetos." << std::endl;
        std::cout << "nProjetos: " << nProjetos << std::endl;
        std::cout << "projetos.size(): " << projetos.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(nProjetos == projetos.size());
    _nProjetos = nProjetos;
    _projetos.resize(nProjetos);
    for (int i=0; i<nProjetos; i++)
    {
        _projetos[i] = Projeto();
    }
    for (int i=0; i<nProjetos; i++)
    {
        _projetos[i].copyFrom(projetos[i]);
    }

    if (nSondas != sondas.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "nSondas não compatível com tamanho do vetor sondas." << std::endl;
        std::cout << "nSondas: " << nSondas << std::endl;
        std::cout << "sondas.size(): " << sondas.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(nSondas == sondas.size());
    _nSondas = nSondas;
    _sondas.resize(nSondas);
    for (int i=0; i<nSondas; i++)
    {
        _sondas[i] = Sonda();
    }
    for (int i=0; i<nSondas; i++)
    {
        _sondas[i].copyFrom(sondas[i]);
    }

    if ((nProjetos+nSondas) != desloc.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "(nProjetos+nSondas) não compatível com tamanho do vetor desloc." << std::endl;
        std::cout << "(nProjetos+nSondas): " << (nProjetos+nSondas) << std::endl;
        std::cout << "desloc.size(): " << desloc.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert((nProjetos+nSondas) == desloc.size());
    for (int i=0; i<(nProjetos+nSondas); i++)
    {
        if ((nProjetos+nSondas) != desloc[i].size())
        {
            std::cout << std::endl;
            std::cout << "################## ATENÇÃO #################" << std::endl;
            std::cout << "(nProjetos+nSondas) não compatível com tamanho do vetor desloc[" << i << "]." << std::endl;
            std::cout << "(nProjetos+nSondas): " << (nProjetos+nSondas) << std::endl;
            std::cout << "desloc[" << i << "].size(): " << desloc[i].size() << std::endl;
            std::cout << "############################################" << std::endl;
        }
        assert((nProjetos+nSondas) == desloc[i].size());
    }
    _desloc.resize((nSondas+nProjetos));
    for (int i=0; i<(nSondas+nProjetos); i++)
    {
        _desloc[i].resize((nSondas+nProjetos));
    }
    for (int i=0; i<(nSondas+nProjetos); i++)
    {
        for (int j=0; j<(nSondas+nProjetos); j++)
        {
            _desloc[i][j] = desloc[i][j];
        }
    }
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
    if (i >= _projetos.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de projeto fornecido inválido." << std::endl;
        std::cout << "Índice: " << i << std::endl;
        std::cout << "projetos.size(): " << _projetos.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(i < _projetos.size());
    return _projetos[i];
}

std::vector<Sonda> DadosDeEntrada::getSondas()
{
    return _sondas;
}

Sonda DadosDeEntrada::getSonda(int i)
{
    if (i >= _sondas.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de sonda fornecido inválido." << std::endl;
        std::cout << "Índice: " << i << std::endl;
        std::cout << "sondas.size(): " << _sondas.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(i < _sondas.size());
    return _sondas[i];
}

std::vector<std::vector<double>> DadosDeEntrada::getDesloc()
{
    return _desloc;
}

double DadosDeEntrada::getDesloc(Sonda s, Projeto p)
{
    int sondaIndex, projIndex;
    sondaIndex = s.getNome();
    projIndex = p.getNome() + _nSondas;

    if (sondaIndex >= _nSondas)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de sonda fornecido inválido." << std::endl;
        std::cout << "Índice: " << sondaIndex << std::endl;
        std::cout << "nSondas: " << _nSondas << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(sondaIndex < _nSondas);

    if (projIndex >= (_nProjetos + _nSondas))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de projeto fornecido inválido." << std::endl;
        std::cout << "Índice: " << projIndex << std::endl;
        std::cout << "nProjetos + _nSondas: " << _nProjetos + _nSondas << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(projIndex < (_nProjetos + _nSondas));

    if (sondaIndex >= _desloc.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de sonda fornecido inválido." << std::endl;
        std::cout << "Índice: " << sondaIndex << std::endl;
        std::cout << "desloc.size: " << _desloc.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(sondaIndex < _desloc.size());

    if (projIndex >= _desloc[0].size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de projeto fornecido inválido." << std::endl;
        std::cout << "Índice: " << projIndex << std::endl;
        std::cout << "desloc.size: " << _desloc[0].size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(projIndex < _desloc[0].size());

    return _desloc[sondaIndex][projIndex];
}

double DadosDeEntrada::getDesloc(Projeto p1, Projeto p2)
{
    int proj1Index, proj2Index;
    proj1Index = p1.getNome() + _nSondas;
    proj2Index = p2.getNome() + _nSondas;

    if (proj1Index >= (_nProjetos + _nSondas))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice do projeto1 fornecido inválido." << std::endl;
        std::cout << "Índice: " << proj1Index << std::endl;
        std::cout << "nSondas + nProjetos: " << _nSondas + _nProjetos << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(proj1Index < (_nSondas + _nProjetos));

    if (proj2Index >= (_nProjetos + _nSondas))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice do projeto 2 fornecido inválido." << std::endl;
        std::cout << "Índice: " << proj2Index << std::endl;
        std::cout << "nProjetos + _nSondas: " << _nProjetos + _nSondas << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(proj2Index < (_nProjetos + _nSondas));

    if (proj1Index >= _desloc.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice do projeto1 fornecido inválido." << std::endl;
        std::cout << "Índice: " << proj1Index << std::endl;
        std::cout << "desloc.size: " << _desloc.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(proj1Index < _desloc.size());

    if (proj2Index >= _desloc[0].size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice do projeto2 fornecido inválido." << std::endl;
        std::cout << "Índice: " << proj2Index << std::endl;
        std::cout << "desloc.size: " << _desloc[0].size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(proj2Index < _desloc[0].size());

    return _desloc[proj1Index][proj2Index];
}

double DadosDeEntrada::getDeslocIdx2Idx(int idx1, int idx2)
{
    if (idx1 >= _desloc.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice1 fornecido inválido." << std::endl;
        std::cout << "Índice1: " << idx1 << std::endl;
        std::cout << "desloc.size: " << _desloc.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(idx1 < _desloc.size());

    if (idx2 >= _desloc[0].size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice2 fornecido inválido." << std::endl;
        std::cout << "Índice2: " << idx2 << std::endl;
        std::cout << "desloc.size: " << _desloc[0].size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(idx2 < _desloc[0].size());

    return _desloc[idx1][idx2];
}

double DadosDeEntrada::getDeslocSonda2Proj(int sNome, int pNome)
{
    int sondaIndex, projIndex;
    sondaIndex = sNome;
    projIndex = pNome + _nSondas;

    if (sondaIndex >= _nSondas)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de sonda fornecido inválido." << std::endl;
        std::cout << "Índice: " << sondaIndex << std::endl;
        std::cout << "nSondas: " << _nSondas << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(sondaIndex < _nSondas);

    if (projIndex >= (_nProjetos + _nSondas))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de projeto fornecido inválido." << std::endl;
        std::cout << "Índice: " << projIndex << std::endl;
        std::cout << "nProjetos + _nSondas: " << _nProjetos + _nSondas << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(projIndex < (_nProjetos + _nSondas));

    if (sondaIndex >= _desloc.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de sonda fornecido inválido." << std::endl;
        std::cout << "Índice: " << sondaIndex << std::endl;
        std::cout << "desloc.size: " << _desloc.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(sondaIndex < _desloc.size());

    if (projIndex >= _desloc[0].size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de projeto fornecido inválido." << std::endl;
        std::cout << "Índice: " << projIndex << std::endl;
        std::cout << "desloc.size: " << _desloc[0].size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(projIndex < _desloc[0].size());

    return _desloc[sondaIndex][projIndex];
}

double DadosDeEntrada::getDeslocProj2Proj(int p1Nome, int p2Nome)
{
    int proj1Index, proj2Index;
    proj1Index = p1Nome + _nSondas;
    proj2Index = p2Nome + _nSondas;

    if (proj1Index >= (_nProjetos + _nSondas))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice do projeto1 fornecido inválido." << std::endl;
        std::cout << "Índice: " << proj1Index << std::endl;
        std::cout << "nSondas + nProjetos: " << _nSondas + _nProjetos << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(proj1Index < (_nSondas + _nProjetos));

    if (proj2Index >= (_nProjetos + _nSondas))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice do projeto 2 fornecido inválido." << std::endl;
        std::cout << "Índice: " << proj2Index << std::endl;
        std::cout << "nProjetos + _nSondas: " << _nProjetos + _nSondas << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(proj2Index < (_nProjetos + _nSondas));

    if (proj1Index >= _desloc.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice do projeto1 fornecido inválido." << std::endl;
        std::cout << "Índice: " << proj1Index << std::endl;
        std::cout << "desloc.size: " << _desloc.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(proj1Index < _desloc.size());

    if (proj2Index >= _desloc[0].size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice do projeto2 fornecido inválido." << std::endl;
        std::cout << "Índice: " << proj2Index << std::endl;
        std::cout << "desloc.size: " << _desloc[0].size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(proj2Index < _desloc[0].size());

    return _desloc[proj1Index][proj2Index];
}

void DadosDeEntrada::setNProjetos(int value)
{
    _nProjetos = value;
    
    _projetos.resize(_nProjetos);
    for (int i=0; i<_nProjetos; i++)
    {
        _projetos[i] = Projeto{};
    }

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
    for (int i=0; i<_nSondas; i++)
    {
        _sondas[i] = Sonda{};
    }
    
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

void DadosDeEntrada::setProjetos(std::vector<Projeto> v)
{
    if (v.size() != _projetos.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Tamanho do vetor de projetos fornecido inválido." << std::endl;
        std::cout << "Tamanho: " << v.size() << std::endl;
        std::cout << "projetos.size(): " << _projetos.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(v.size() == _projetos.size());

    for (int i=0; i<_nProjetos; i++)
    {
        _projetos[i].copyFrom(v[i]);
    }
}

void DadosDeEntrada::setProjeto(Projeto v, int i)
{
    if (i >= _projetos.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de projeto fornecido inválido." << std::endl;
        std::cout << "Índice: " << i << std::endl;
        std::cout << "projetos.size(): " << _projetos.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(i < _projetos.size());

    _projetos[i].copyFrom(v);
}

void DadosDeEntrada::setSondas(std::vector<Sonda> v)
{
    if (v.size() != _sondas.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Tamanho do vetor de sondas fornecido inválido." << std::endl;
        std::cout << "Tamanho: " << v.size() << std::endl;
        std::cout << "sondas.size(): " << _sondas.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(v.size() == _sondas.size());

    for (int i=0; i<_nSondas; i++)
    {
        _sondas[i].copyFrom(v[i]);
    }
}

void DadosDeEntrada::setSonda(Sonda v, int i)
{
    if (i >= _sondas.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de sonda fornecido inválido." << std::endl;
        std::cout << "Índice: " << i << std::endl;
        std::cout << "sondas.size(): " << _sondas.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(i < _sondas.size());

    _sondas[i].copyFrom(v);
}

void DadosDeEntrada::setDesloc(std::vector<std::vector<double>> v)
{
    if (v.size() != _desloc.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Vetor de deslocamentos fornecido inválido." << std::endl;
        std::cout << "Tamanho: " << v.size() << std::endl;
        std::cout << "projetos.size(): " << _desloc.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(v.size() == _desloc.size());
    
    for (int i=0; i<(_nSondas+_nProjetos); i++)
    {
        if (v[i].size() != _desloc[i].size())
        {
            std::cout << std::endl;
            std::cout << "################## ATENÇÃO #################" << std::endl;
            std::cout << "Vetor de deslocamentos fornecido inválido." << std::endl;
            std::cout << "Tamanho: " << v[i].size() << std::endl;
            std::cout << "projetos.size(): " << _desloc[i].size() << std::endl;
            std::cout << "############################################" << std::endl;
        }
        assert(v[i].size() == _desloc[i].size());
    }

    for (int i=0; i<(_nSondas+_nProjetos); i++)
    {
        for (int j=0; j<(_nSondas+_nProjetos); j++)
        {
            _desloc[i][j] = v[i][j];
        }
    }
}

void DadosDeEntrada::setDesloc(Sonda s, Projeto p, double v)
{
    int sondaIndex, projIndex;
    sondaIndex = s.getNome();
    projIndex = p.getNome() + _nSondas;

    if (sondaIndex >= _nSondas)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de sonda fornecido inválido." << std::endl;
        std::cout << "Índice: " << sondaIndex << std::endl;
        std::cout << "nSondas: " << _nSondas << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(sondaIndex < _nSondas);

    if (projIndex >= (_nProjetos + _nSondas))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de projeto fornecido inválido." << std::endl;
        std::cout << "Índice: " << projIndex << std::endl;
        std::cout << "nProjetos + _nSondas: " << _nProjetos + _nSondas << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(projIndex < (_nProjetos + _nSondas));

    if (sondaIndex >= _desloc.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de sonda fornecido inválido." << std::endl;
        std::cout << "Índice: " << sondaIndex << std::endl;
        std::cout << "desloc.size: " << _desloc.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(sondaIndex < _desloc.size());

    if (projIndex >= _desloc[0].size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de projeto fornecido inválido." << std::endl;
        std::cout << "Índice: " << projIndex << std::endl;
        std::cout << "desloc.size: " << _desloc[0].size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(projIndex < _desloc[0].size());

    _desloc[sondaIndex][projIndex] = v;
}

void DadosDeEntrada::setDesloc(Projeto p1, Projeto p2, double v)
{
    int proj1Index, proj2Index;
    proj1Index = p1.getNome() + _nSondas;
    proj2Index = p2.getNome() + _nSondas;

    if (proj1Index >= (_nProjetos + _nSondas))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice do projeto1 fornecido inválido." << std::endl;
        std::cout << "Índice: " << proj1Index << std::endl;
        std::cout << "nSondas + nProjetos: " << _nSondas + _nProjetos << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(proj1Index < (_nSondas + _nProjetos));

    if (proj2Index >= (_nProjetos + _nSondas))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice do projeto 2 fornecido inválido." << std::endl;
        std::cout << "Índice: " << proj2Index << std::endl;
        std::cout << "nProjetos + _nSondas: " << _nProjetos + _nSondas << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(proj2Index < (_nProjetos + _nSondas));

    if (proj1Index >= _desloc.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice do projeto1 fornecido inválido." << std::endl;
        std::cout << "Índice: " << proj1Index << std::endl;
        std::cout << "desloc.size: " << _desloc.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(proj1Index < _desloc.size());

    if (proj2Index >= _desloc[0].size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice do projeto2 fornecido inválido." << std::endl;
        std::cout << "Índice: " << proj2Index << std::endl;
        std::cout << "desloc.size: " << _desloc[0].size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(proj2Index < _desloc[0].size());

    _desloc[proj1Index][proj2Index] = v;
}

void DadosDeEntrada::setDeslocIdx2Idx(int idx1, int idx2, double v)
{
    if (idx1 >= _desloc.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice1 fornecido inválido." << std::endl;
        std::cout << "Índice1: " << idx1 << std::endl;
        std::cout << "desloc.size: " << _desloc.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(idx1 < _desloc.size());

    if (idx2 >= _desloc[0].size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice2 fornecido inválido." << std::endl;
        std::cout << "Índice2: " << idx2 << std::endl;
        std::cout << "desloc.size: " << _desloc[0].size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(idx2 < _desloc[0].size());

    _desloc[idx1][idx2] = v;
}

void DadosDeEntrada::setDeslocSonda2Proj(int sNome, int pNome, double v)
{
    int sondaIndex, projIndex;
    sondaIndex = sNome;
    projIndex = pNome + _nSondas;

    if (sondaIndex >= _nSondas)
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de sonda fornecido inválido." << std::endl;
        std::cout << "Índice: " << sondaIndex << std::endl;
        std::cout << "nSondas: " << _nSondas << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(sondaIndex < _nSondas);

    if (projIndex >= (_nProjetos + _nSondas))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de projeto fornecido inválido." << std::endl;
        std::cout << "Índice: " << projIndex << std::endl;
        std::cout << "nProjetos + _nSondas: " << _nProjetos + _nSondas << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(projIndex < (_nProjetos + _nSondas));

    if (sondaIndex >= _desloc.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de sonda fornecido inválido." << std::endl;
        std::cout << "Índice: " << sondaIndex << std::endl;
        std::cout << "desloc.size: " << _desloc.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(sondaIndex < _desloc.size());

    if (projIndex >= _desloc[0].size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice de projeto fornecido inválido." << std::endl;
        std::cout << "Índice: " << projIndex << std::endl;
        std::cout << "desloc.size: " << _desloc[0].size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(projIndex < _desloc[0].size());

    _desloc[sondaIndex][projIndex] = v;
}

void DadosDeEntrada::setDeslocProj2Proj(int p1Nome, int p2Nome, double v)
{
    int proj1Index, proj2Index;
    proj1Index = p1Nome + _nSondas;
    proj2Index = p2Nome + _nSondas;

    if (proj1Index >= (_nProjetos + _nSondas))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice do projeto1 fornecido inválido." << std::endl;
        std::cout << "Índice: " << proj1Index << std::endl;
        std::cout << "nSondas + nProjetos: " << _nSondas + _nProjetos << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(proj1Index < (_nSondas + _nProjetos));

    if (proj2Index >= (_nProjetos + _nSondas))
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice do projeto 2 fornecido inválido." << std::endl;
        std::cout << "Índice: " << proj2Index << std::endl;
        std::cout << "nProjetos + _nSondas: " << _nProjetos + _nSondas << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(proj2Index < (_nProjetos + _nSondas));

    if (proj1Index >= _desloc.size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice do projeto1 fornecido inválido." << std::endl;
        std::cout << "Índice: " << proj1Index << std::endl;
        std::cout << "desloc.size: " << _desloc.size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(proj1Index < _desloc.size());

    if (proj2Index >= _desloc[0].size())
    {
        std::cout << std::endl;
        std::cout << "################## ATENÇÃO #################" << std::endl;
        std::cout << "Índice do projeto2 fornecido inválido." << std::endl;
        std::cout << "Índice: " << proj2Index << std::endl;
        std::cout << "desloc.size: " << _desloc[0].size() << std::endl;
        std::cout << "############################################" << std::endl;
    }
    assert(proj2Index < _desloc[0].size());

    _desloc[proj1Index][proj2Index] = v;
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
        std::cout << std::endl;
    } std::cout << std::endl;

    std::cout << "dados lidos de sondas: " << std::endl;
    for (int i=0; i<_nSondas; i++)
    {
        std::cout << _sondas[i].getCoordX() << " ";
        std::cout << _sondas[i].getCoordY() << " ";
        std::cout << std::endl;
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

