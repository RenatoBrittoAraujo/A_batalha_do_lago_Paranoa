#include <string> // string
#include <utility> // pair
#include <vector> // vector

#include "../inc/navio.hpp"
#include "../inc/navios.hpp"
#include "../inc/helpers.hpp"

// Nomes nada-ve para as embarcacoes
std::vector<std::string> Porta_teco_teco::nomes_de_embarcacoes({

        "Jaraguiricaratauba",
        "Tabajaraguaramalapaula",
        "Piracicubajiraguirupa",
        "Guaripajagurajiguar",
        "Caranautacaraguara",
        "Agarataurabuba",
        "Tiricaticurica",
        "Cacibalubiba",
        "Jiripocavaipiar",
        "Jaguariuna",
        "Jeguejonga",

});

Porta_teco_teco::Porta_teco_teco(){

    tipo = "porta_teco_teco";
    tamanho = 4;
    caractere = '#';
    maxVida = 150;
    competencia = randInt(1, 10);
    tecotecos = randInt(8, 12);
    nome = nomes_de_embarcacoes.at(randInt(0, nomes_de_embarcacoes.size() - 1));
    amocado = false;

}

std::pair<std::string, std::pair<int ,int>> Porta_teco_teco::processa(int * dano){

    std::string status;
    int delta;
    int contrataque = 0;

    status = "Os bravos guerreiros da embarcacao " + nome + ", as margens do Paranoa, ";

    delta = *dano;

    if(randInt(0, 30) < tecotecos){
        delta = 0;
        status += "defenderam o ataque.";
    }else
        status += "foram atacados covardemente e perderam " + std::to_string(delta) + " de vida. Agora tem " + std::to_string(std::max(0, vida - delta)) + ".";

    if(competencia > randInt(0, 30)){
        contrataque = competencia;
        status += " E os bravos e competentes guerreiros da FAB causaram " + std::to_string(contrataque) + " de dano ao inimigo que atacou.";
    }

    competencia++;

    return {status, {delta, contrataque}};

}

Pracha_de_SUP::Pracha_de_SUP(){

    maxVida = 50;
    tamanho = 1;
    tipo = "Prancha_de_SUP";
    caractere = '0';
    remo = randInt(1, 3);
    amocado = true;

}

std::pair<std::string, std::pair<int, int>> Pracha_de_SUP::processa(int * dano){

    std::string status;
    int delta;

    if(randInt(0, remo) == remo){

        status = "Prancha de SUP defletiu seu ataque com remo!";
        remo++;
        delta = 0;

    }else{

        if(amocado)
            amocado = !(randInt(1, 5) == 4);

        status = std::string(amocado ? ("Atingiu uma Prancha de SUP") : ("Atigiu um navio desconhecido")) + 
                " e causou " + std::to_string(*dano) + " de dano!";
        delta = *dano;

    }

    return {status, {delta, 0}};

}

Iate::Iate(){

    tipo = "Iate";
    fama = randInt(20, 100);
    ePolitico = (bool)randInt(0, 5);
    dinheiro = randInt(10, 100) + (ePolitico ? 50 : 0);
    maxVida = 100;
    caractere = 'H';
    tamanho = 2;
    amocado = ePolitico;

}

std::pair<std::string, std::pair<int ,int>> Iate::processa(int * dano){

    std::string status;
    int delta = 0;
    int contrataque = 0;

    delta = (*dano * 40) / dinheiro;

    if(ePolitico){

        delta = std::max(delta - 5, 0);

        status = "Iate de politico e atacado e perde " + std::to_string(delta) + " de vida.";

        if(randInt(0, 1)){
            status += " Politico abre inquerito e tira 10 de vida do navio que atacou.";
            contrataque = 10;
        }

    }else{

        if(amocado)
            amocado = !((randInt(0, 100) <= fama));

        status = std::string(amocado ? ("Atingiu um Iate") : "Atigiu um navio desconhecido") + 
                " e causou " + std::to_string(delta) + " de dano!";

    }

    return {status, {delta, contrataque}};

}

int Iate::getTipo(){

    return T_Iate;

}

int Pracha_de_SUP::getTipo(){

    return T_Prancha_de_sup;

}

int Porta_teco_teco::getTipo(){

    return T_Porta_teco_teco;

}