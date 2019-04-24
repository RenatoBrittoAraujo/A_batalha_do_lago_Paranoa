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
    virtual std::pair<std::string, std::pair<int, int>> processa(const int dano);

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
    virtual std::pair<std::string, std::pair<int, int>> processa(const int dano);

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
    virtual std::pair<std::string, std::pair<int ,int>> processa(const int dano);

};

class JetSki: public Navio{

private:

    // Quando turbo esta ligado, JetSki nao e atacado no proximo turno
    bool turbo;

public:

    // Retorna enumeracao do tipo da embarcao
    virtual int getTipo();

    JetSki();

    // Funcao da classe abstrata Navio
    virtual std::pair<std::string, std::pair<int ,int>> processa(const int dano);

};

class Espaco_nave: public Navio{

private:

    // Define a recuperacao de vida da espaco nave
    int tecnologia;

    // Se os tripulantes forem vogons, eles podem tentar destruir a terra para fazer um auto estrada,
    // e no processo matam um navio aleatorio seu
    bool vogons;

public:

    // Retorna enumeracao do tipo da embarcao
    virtual int getTipo();

    Espaco_nave();

    // Funcao da classe abstrata Navio
    virtual std::pair<std::string, std::pair<int ,int>> processa(const int dano);

};

class Caravela: public Navio{

private:

    // Quanto mais especiarias, maior sao as chaces do ataque ser evitado, porem causa mais dano
    int especiarias;

    // Nome do comandante da caravela
    std::string velejador;

    // Nomes de velejadores famosos
    static std::vector<std::string> nomes_de_velejadores;


public:

    // Retorna enumeracao do tipo da embarcao
    virtual int getTipo();

    Caravela();

    // Funcao da classe abstrata Navio
    virtual std::pair<std::string, std::pair<int ,int>> processa(const int dano);

};

class Dois_caras_numa_moto: public Navio{

private:

    // O valor de responsa na quebrada, ta ligado? Quanto maior o valor de responsa
    // mais os dois caras podem chamar os menor da quebrada pra resolver a treta
    // e contra-atacar
    int quebrada;

    // Quebrada de origem dos dois caras numa moto
    std::string nome_da_quebrada;

    // Nomes de bairros de brasilia
    static std::vector<std::string> quebradas;

public:

    // Retorna enumeracao do tipo da embarcao
    virtual int getTipo();

    Dois_caras_numa_moto();

    // Funcao da classe abstrata Navio
    virtual std::pair<std::string, std::pair<int ,int>> processa(const int dano);

};

class FBI: public Navio{

private:

    // Probabilidade mindfuck de na verdade o suposto agentes do FBI serem na verdade espioes russos
    // que ao serem atacados matam o adversario e morrem no processo
    bool EspioesRussos;

public:

    // Retorna enumeracao do tipo da embarcao
    virtual int getTipo();

    FBI();

    // Funcao da classe abstrata Navio
    virtual std::pair<std::string, std::pair<int ,int>> processa(const int dano);

};

#endif