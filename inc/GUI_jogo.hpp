#ifndef GUI_JOGO
#define GUI_JOGO

#include <map> // map

#include "mapa.hpp"
#include "GUI_basica.hpp"
#include "jogo.hpp"


class GUI_jogo: public GUI_basica{

private:

    // Cria instancia de jogo
    Jogo jogo;

    // Escolhe um ponto x e y para o ataque
    // Alguns ataques nao funcionam assim
    void escolherCoordenadas(int * x, int * y, const int player);

    // Menu de jogo
    std::vector<std::string> opcoes = {
        "Ataque comum",
        "Ataque em area",
        "Curandeiro",
        "Missel teleguiado",
        "Revelar posicao",
        "Sair da partida"
    };

    // Configuracao para jogo (escolher mapas, definir nome dos players)
    void escolherMapa(Mapa * player, const int id_player);

    // Gera mapa com mesmas especificacoes para cada player
    void geracaoDeMapa();

    // Os players escolhem seus nomes no jogo
    void escolherNome(const int player);

    // Verdadeiro se tipo de jogo escolhido e singlePlayer
    bool singlePlayer;

    // Processa o turno de um jogador
    bool turno(const int player);

    // Printa a ascii do adversario atual
    void printaInimigo(std::string);

    // Mostra tela de configuracao de opcoes de jogo
    void configurarJogo();

    // Array com nomes estranhos para a Inteligencia
    static std::vector<std::string> nomes_estranhos;

public:

    // Player(s) escolhe se vao jogar no modo single-player ou multi-player
    bool tipoDeJogo();

    // Roda turnos ate que um jogador perca o jogo, retorna verdadeiro se jogar quer sair do jogo
    bool jogar(bool * vitoria = NULL);

    // Players escolhem seus nome e mapas
    void configurarPartida();

    // Seta o nome do player 
    void configuracaoHistoria();

    // Modo historia do jogo
    void modoHistoria();

};

#endif