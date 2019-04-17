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
    void configurarPlayer(Mapa * player, const int id_player);

public:


    // Roda turnos ate que um jogador perca o jogo
    void jogar();

    // Players escolhem seus nome e mapas
    void escolhaDeMapas();

    // Processa o turno de um jogador
    bool turno(const int player);

    // Mostra tela de configuracao de opcoes de jogo
    void configurarJogo();

};

#endif