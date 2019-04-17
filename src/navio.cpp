#include <string> // string
#include <algorithm> // min, max

#include "../inc/navio.hpp"

// Navio generico para testar (supostamente nao acontece durante o jogo)
Navio::Navio(){

    caractere = 'x';
    maxVida = 100;
    vida = maxVida;
    tamanho = 1;
    orientacao = 0;
    tipo = "Navio comum";
    amocado = 0;

}

// Ataque generico, nao deveria acontecer durante o jogo
std::pair<std::string, std::pair<int, int>> processa(const int dano){

    return {"Navio tomou " + std::to_string(dano) + " de dano.", {dano, 0}};

}

bool Navio::estaVivo(){

    return vida > 0;

}

// Essa e a central que processa os ataques em todos os navios
// recebe o dano e o inimigo que atacou e processa o dano recebido, o
// contra ataque e retorna a string que descreve o ataque
std::string Navio::ataque(int * dano, Navio * inimigo){

    std::pair<std::string, std::pair<int, int>> resultado = processa(dano);

    setVida(-resultado.second.first);

    if(resultado.second.second > 0)
        inimigo->setVida(-resultado.second.second);

    return resultado.first;

}

// Vida sempre fica entre [0 - maxVida]
void Navio::setVida(const int delta){

    vida = std::min(maxVida, std::max(0, vida + delta));

}

void Navio::setOrientacao(const int orientacao){

    this->orientacao = orientacao;

}

char Navio::representacao(){

    return caractere;

}

bool Navio::getAmocado(){

    return amocado;

}

int Navio::getMaxVida(){

    return maxVida;

}

void Navio::amocar(){

    amocado = true;

}

void Navio::desamocar(){

    amocado = false;

}