#ifndef INTELIGENCIA
#define INTELIGENCIA

#include <vector> // vector
#include <string> // string
#include <utility> // pair

/*
    No modo single-player, essa e a classe que simula um player tentando tomar as melhores decisoes
    possiveis baseadas num nivel de dificuldade que vai de facil, medio ate dificil
    
    O unico metodo publico dessa classe e 'proximaAcao' que recebe o mesmo estado de jogo que um player humano
    teria e baseado nessa informacao e na sua memoria, cria uma nova acao de jogo
    
    Resolvi fazer ela completamente separada das outras classes para nao existir chance dela 'roubar' no jogo
    acessando informacoes que o player humano nao tem acesso. O unico input que ela recebe é o mesmo
    que o player humano tem.
*/

class Inteligencia{

private:

    // Quanto menor a dificuldade, menos decisoes ponderadas a inteligencia toma
    // 1 -> facil, 2 -> medio, 3 -> dificil
    int dificuldade;

    // O mapa literal do jogo
    const std::vector<std::string> * mapa;

    // Cria uma lista de navios no mapa
    void procurarNavios();

    // Guarda todas as coordenadas onde encontra navios
    std::vector<std::pair<int, int>> navios;

    // Retorna o ponto do mapa com o maior numero de pontos ocupados ao redor por navios para ataque em area
    // Primeira int e o numero de navios ao redor desse ponto e o par a coordenada do ponto
    std::pair<int ,std::pair<int, int>> procurarPontoDeMaisBlocos();

    // Dimensoes do mapa
    int largura;
    int altura;

    // Define o valor de largura e altura
    void getDimensoes();

public:

    // Entrada: mapa, numero de navios vivos do jogador, ponteiro para vetor de cooldown
    // Saida: int: tipo de acao, par int: (x, y) do ataque (vai estar zerada se nao for ataque com coordenadas)
    std::pair<int, std::pair<int, int>> proximaAcao(const std::vector<std::string> * mapa, int navios_vivos, const int * cooldown);

    // Define o nivel de dificuldade de inteligencia
    void setDificuldade(const int dificuldade);

};

#endif