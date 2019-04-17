#ifndef NAVIOS
#define NAVIOS

#include <utility> // pair
#include <string> // string

#include "navio.hpp"

class Porta_teco_teco: public Navio{

private:

    // Aumenta chance de defletir ataque e chance de contra ataque
    int tecotecos;

    // Competencia dos pilotos da FAB
    int competencia;

    // Nome do navio
    std::string nome;

    // Nomes novos para embarcacoes
    static std::vector<std::string> nomes_de_embarcacoes;

public:

    // Retorna enumeracao do tipo da embarcao
    virtual int getTipo();

    Porta_teco_teco();

    // Extensao da funcao abstrata processa da classe Navio
    virtual std::pair<std::string, std::pair<int, int>> processa(int * dano);

};

class Pracha_de_SUP: public Navio{

private:

    // Valor de remo indica chance de ataque dar certo
    int remo;

public:

    // Retorna enumeracao do tipo da embarcao
    virtual int getTipo();

    Pracha_de_SUP();

    // Extensao da funcao abstrata processa da classe Navio
    virtual std::pair<std::string, std::pair<int, int>> processa(int * dano);

};

class Iate: public Navio{

private:

    // Atritubtos que definem potencia do ataque
    // Quanto maior o dinheiro, menor o dano
    int dinheiro;
    
    // Quanto maior a fama, maior a chance de revelar tipo de barco
    int fama;
    
    // Se e politico, ganha atributo de dinheiro porem posicao e sempre
    // revelada e abre processo juducial contra inimigo
    bool ePolitico;

public:

    // Retorna enumeracao do tipo da embarcao
    virtual int getTipo();

    Iate();

    // Funcao da classe abstrata Navio
    virtual std::pair<std::string, std::pair<int ,int>> processa(int * dano);

};

#endif