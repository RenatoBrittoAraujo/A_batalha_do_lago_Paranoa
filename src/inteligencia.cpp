#include <vector> // vector
#include <string> // string
#include <utility> // pair

#include "../inc/inteligencia.hpp"
#include "../inc/helpers.hpp"
#include "../inc/navios.hpp"

#include <iostream>
#include <unistd.h>

std::pair<int, std::pair<int, int>> Inteligencia::proximaAcao(const std::vector<std::string> * mapa, int navios_vivos, const int * cooldown){

    this->mapa = mapa;

    getDimensoes();

    // Primeira prioridade: ataque em area
    // Depende de haver navios visiveis no mapa, quanto maior a dificuldade, mas 

    auto maxBlocos = procurarPontoDeMaisBlocos();

    if(!navios.empty() and randInt(0, dificuldade * maxBlocos.first) > maxBlocos.first + 2 and randInt(0, 5) and !cooldown[ATAQUE_EM_AREA]){

        return {ATAQUE_EM_AREA, {maxBlocos.second.first, maxBlocos.second.second}};

    }
    
    // Segunda prioridade: ataque comum
    // Atira em um navio aleatorio, caso exista

    procurarNavios();

    if(!navios.empty() and randInt(0, 5 + 2 * dificuldade)){

        auto coordenada = navios[randInt(0, (int)navios.size() - 1)];

        return {ATAQUE_COMUM, {coordenada.first, coordenada.second}};

    }

    // Terceira prioridade: encontrar navio
    // Caso nao encontre poucos ou nenhum navio no mapa, vai procurar algum

    if(((int)navios.size() < 2) and randInt(0, 2 + dificuldade + (dificuldade > 1 ? 2 : 0)) and !cooldown[RELEVAR_POSICAO]){

        return {RELEVAR_POSICAO, {0, 0}};

    }

    // Quarta prioridade: curar navio
    // Caso tenha poucos navios e falou os casos anteriores

    if(navios_vivos < 3 and randInt(0, 3) > navios_vivos and !cooldown[CURAR_NAVIO]){

        return {CURAR_NAVIO, {0, 0}};

    }

    // Quinta prioridade: missel teleguiado
    // Se nao achar achar navios ou falhar os casos anteriores, tenta missel teleguiado

    if(navios.size() < 5 and randInt(0, dificuldade) and !cooldown[MISSEL_TELEGUIADO]){

        return {MISSEL_TELEGUIADO, {0, 0}};

    }

    // Se nenhuma dos casos anteriores passou, atira em um lugar aleatorio

    return {1, {randInt(1, largura - 1), randInt(1, altura - 1)}};

}

// Essa funcao e praticamente uma duplicacao da funcao 'ataque em area', o motivo pelo qual
// fiz isso e para garantir que a inteligencia nao possui nenhuma informacao privilegiada
// por estar 100% desconectada com o resto de jogo exceto por proximaAcao()
std::pair<int ,std::pair<int, int>> Inteligencia::procurarPontoDeMaisBlocos(){

    int maxBlocos = 0;
    
    int coor_x = 0, coor_y = 0;

    // Para da coordenada (x, y) no mapa

    for(int y = 1; y < altura; y++){

        for(int x = 1; x < largura ; x++){

            int atual = 0;

            // Conta o numero de blocos no retangulo formado pela coordenada e os blocos adjcentes

            for(int lx = x - 1; lx <= x + 1; lx++){

                for(int ly = y - 1; ly <= y + 1; ly++){
             
                    if(lx < 1 or lx >= largura or ly < 1 or ly >= altura)
                        continue;

                    char ponto = mapa->at(ly)[lx];

                    if(ponto != 'X' and ponto != '~')
                        atual++;

                }

            }

            // Se achou mais navios nesse ponto, salva ele como o melhor

            if(atual > maxBlocos){

                maxBlocos = atual;

                coor_x = x;

                coor_y = y;

            }

        }

    }

    // E retorna a primeira das melhores opcoes de ataque em area encontrada

    return {maxBlocos, {coor_x, coor_y}};

}

void Inteligencia::procurarNavios(){

    navios.clear();
    
    // Preenche o vetor navios com todos os pontos do mapa que contem algum navio visivel

    for(int y = 1; y < altura; y++){

        for(int x = 1; x < largura ; x++){

            char ponto = mapa->at(y)[x];

            if(ponto != 'X' and ponto != '~'){
                navios.push_back({x ,y});
            }

        }

    }

}

void Inteligencia::setDificuldade(const int dificuldade){

    this->dificuldade = dificuldade;

}

void Inteligencia::getDimensoes(){

    largura = mapa->at(0).size();

    altura = mapa->size();

}