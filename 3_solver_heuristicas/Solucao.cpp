// Copyright 2021 João Ricardo Weissmann Santos
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// File comments:
// 
// TODO: descrever conteúdo do arquivo, em alto nível

#include <bits/stdc++.h>
#include "Solucao.h"

// Implementation comments:
//
// TODO

Solucao::Solucao(DadosDeEntrada dataset)
{
    // TODO
} 

Solucao::Solucao(DadosDeEntrada dataset, std::map<int, std::list<int>> alocacoes, 
                 std::map<int, int> mapProj2Inicio, std::map<int, int> mapProj2Final)
{
    // TODO
}

std::map<int, std::list<int>> Solucao::getAlocacoes()
{
    // TODO
}

std::list<int> Solucao::getAlocacoes(int sondaNome)
{
    // TODO
}

std::list<int> Solucao::getAlocacoes(Sonda s)
{
    // TODO
}

int Solucao::getAlocacao(int sondaNome, int indice)
{
    // TODO
}

int Solucao::getAlocacao(Sonda s, int indice)
{
    // TODO
}

std::map<int, int> Solucao::getMapProj2Inicio()
{
    // TODO
}

int Solucao::getInicioDeProjeto(int projNome)
{
    // TODO
}

int Solucao::getInicioDeProjeto(Projeto proj)
{
    // TODO
}

std::map<int, int> Solucao::getMapProj2Final()
{
    // TODO
}

int Solucao::getFinalDeProjeto(int projNome)
{
    // TODO
}

int Solucao::getFinalDeProjeto(Projeto proj)
{
    // TODO
}

std::set<int, std::greater<int>> Solucao::getProjetosUsados()
{
    // TODO
}

bool Solucao::getSeProjetoAlocado(int projNome)
{
    // TODO
}

bool Solucao::getSeProjetoAlocado(Projeto proj)
{
    // TODO
}

std::map<int, int> Solucao::getMapProj2Sonda()
{
    // TODO
}

int Solucao::getSondaDeProjeto(int projNome)
{
    // TODO
}

int Solucao::getSondaDeProjeto(Projeto proj)
{
    // TODO
}

std::map<int, int> Solucao::getMapSonda2TotalFree()
{
    // TODO
}

int Solucao::getTotalFree(int sondaNome)
{
    // TODO
}

int Solucao::getTotalFree(Sonda s)
{
    // TODO
}

std::map<int, int> Solucao::getMapSonda2MaxFree()
{
    // TODO
}

int Solucao::getMaxFree(int sondaNome)
{
    // TODO
}

int Solucao::getMaxFree(Sonda s)
{
    // TODO
}

double Solucao::getFitness()
{
    // TODO
}

double Solucao::getCusto()
{
    // TODO
}

int Solucao::getTotalFree()
{
    // TODO
}

int Solucao::getTotalSetup()
{
    // TODO
}

int Solucao::getMaxFree()
{
    // TODO
}

std::map<int, std::vector<int>> Solucao::getCandidatos()
{
    // TODO
}

std::vector<int> Solucao::getCandidatos(int sondaNome)
{
    // TODO
}

std::vector<int> Solucao::getCandidatos(Sonda s)
{
    // TODO
}

std::set<int, std::greater<int>> Solucao::getSondasDisponiveis()
{
    // TODO
}

bool Solucao::getSeSondaDisponivel(int sondaNome)
{
    // TODO
}

bool Solucao::getSeSondaDisponivel(Sonda s)
{
    // TODO
}

void Solucao::setAlocacoes(std::map<int, std::list<int>> alocacoes)
{
    // TODO
}

void Solucao::setMapProj2Inicio(std::map<int, int> mapProj2Inicio)
{
    // TODO
}

void Solucao::setInicioDeProjeto(Projeto proj)
{
    // TODO
}

void Solucao::setInicioDeProjeto(int projNome)
{
    // TODO
}

void Solucao::setMapProj2Final(std::map<int, int> mapProj2Final)
{
    // TODO
}

void Solucao::setFinalDeProjeto(Projeto proj)
{
    // TODO
}

void Solucao::setFinalDeProjeto(int projNome)
{
    // TODO
}

void Solucao::inserirNoInicio(Sonda s, Projeto proj, int inicio, int final)
{
    // TODO
}

void Solucao::inserirNoInicio(int sondaNome, int projNome, int inicio, int final)
{
    // TODO
}

void Solucao::inserirNoFinal(Sonda s, Projeto proj, int inicio, int final)
{
    // TODO
}

void Solucao::inserirNoFinal(int sondaNome, int projNome, int inicio, int final)
{
    // TODO
}

void Solucao::inserirAposProjeto(Sonda s, Projeto projReferencia, Projeto proj, int inicio, int final)
{
    // TODO
}

void Solucao::inserirAposProjeto(int sondaNome, int projReferenciaNome, int projNome, int inicio, int final)
{
    // TODO
}

void Solucao::inserirAntesDeProjeto(Sonda s, Projeto projReferencia, Projeto proj, int inicio, int final)
{
    // TODO
}

void Solucao::inserirAntesDeProjeto(int sondaNome, int projReferenciaNome, int projNome, int inicio, int final)
{
    // TODO
}

void Solucao::inserirNoIndice(Sonda s, int indice, Projeto proj, int inicio, int final)
{
    // TODO
}

void Solucao::inserirNoIndice(int sondaNome, int indice, int projNome, int inicio, int final)
{
    // TODO
}

void Solucao::removerProjeto(Sonda s, Projeto proj)
{
    // TODO
}

void Solucao::removerProjeto(int sondaNome, int projNome)
{
    // TODO
}

void Solucao::removerPorIndice(Sonda s, int indice)
{
    // TODO
}

void Solucao::removerPorIndice(int sondaNome, int indice)
{
    // TODO
}

void Solucao::trocarProjetos(Sonda s, Projeto projSai, Projeto projEntra, int inicio, int final)
{
    // TODO
}

void Solucao::trocarProjetos(int sondaNome, int projSaiNome, int projEntraNome, int inicio, int final)
{
    // TODO
}

void Solucao::print()
{
    // TODO
}
