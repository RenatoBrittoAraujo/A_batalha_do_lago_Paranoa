#ifndef JOGO
#define JOGO

#include "mapa.hpp"

class Jogo{

private:

    // Mapa de cada player
    Mapa player1;
    Mapa player2;

    // Numero de navios no comeco do jogo para calcular pontuacao
    int numero_de_navios_player1;
    int numero_de_navios_player2;

    // Nome de cada player
    std::string nome_player1;
    std::string nome_player2;

    // O tempo que o player deve esperar no turno atual para poder usar determinaod ataque
    int cooldown_player1[10];
    int cooldown_player2[10];

    // Retorna o endereco de array pro player desejeado
    int * cooldownAlvo(const int player);

    // E o valor de dano maximo que o ataque comum causa, e outros ataques dependem dele
    // portanto e possivel definir com esse valor o quao dinamico o jogo sera
    int maxDano = 100;

    // Retorna o navio que ataca
    Navio * getAlgumNavio(const int player);

    // Gera ataque coordenada do mapa e retorna seu resultado
    std::string tiroEmCoordenada(const int x, const int y, const int player, const int dano, Navio * atacante = NULL, bool emMassa = false);

    // Processa o tipo de ataque equivalente ao ataque comum
    std::string ataqueComum(const int x, const int y, const int player);

    // Processa um ataque em area
    std::string ataqueEmArea(const int x, const int y, const int player); 

    // Cura algum navio do dono da acao
    std::string curar(const int player);

    // Ataca algum navio do inimigo
    std::string misselTeleguiado(const int player);

    // Revela posicao de algum navio do inimigo
    std::string relevarPosicao(const int player);

    // Enumeracoes do menu de jogo
    enum acoes{SAIR_DO_JOGO, ATAQUE_COMUM, ATAQUE_EM_AREA, CURAR_NAVIO, MISSEL_TELEGUIADO, RELEVAR_POSICAO};

    // Transforma tipo de navio em int para string com seu nome
    static std::map<int, std::string> intParaNome;

    // Retorna o numero de navios no mapa do player
    int getNumeroDeNavios(const int player);

    // Retorna o numero de navios inicial no mapa do player
    int getNumeroDeNaviosInicial(const int player);

public:

    // Retorn ponteiro para mapa de player
    Mapa * getPlayer(const int player);

    // Retorna o valor de pontuacao do jogador
    int calcularPontuacao(const int player);

    // Seta nome do player
    void setNome(std::string nome, const int id);

    // Retorna true se player tem barcos no jogo
    bool estaVivo(const int player);

    // Retorna nome do jogador alvo
    std::string getNome(const int player);

    // Retornar altura do mapa do jogador alvo
    int getAltura(const int player);

    // Retornar altura do mapa do jogador alvo
    int getLargura(const int player);

    // Retorna o id do outro jogador
    int outroJogador(const int player);

    // Processa acao escolhida por player
    std::string processarAcao(int * x, int * y, const int player, const int escolha);

    // Seta o cooldown de todas os ataques como 0
    void limparCooldown(const int player);

    // Diminui em 1 o cooldown dos ataques do player se formem maiores que 0
    void diminuirCooldown(const int player);

    // Muda o Dano Maximo para mudar o estilo do jogo
    void setMaxDano(const int novo);

    // Retona valor de Dano Maximo
    int getMaxDano();

    // Seta o numero de navios no comeco do jogo para cada player
    void setNumeroDeNaviosInicial();

    // Salva pontuacao do player no arquivo .scoreboard
    int salvarPontuacao(const int player);

};

#endif