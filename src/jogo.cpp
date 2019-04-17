#include <string> // string

#include "../inc/jogo.hpp"
#include "../inc/mapa.hpp"
#include "../inc/helpers.hpp"

std::map<int, std::string> Jogo::intParaNome({

        {T_Porta_teco_teco, "Porta Teco Teco"},
        {T_Iate, "Iate"},
        {T_Prancha_de_sup, "Prancha de SUP"}

    });

Mapa * Jogo::getPlayer(const int player){

    if(player == 1)
        return &player1;
    else
        return &player2;

}

void Jogo::setNome(std::string nome, const int player){

    if(player == 1)
        nome_player1 = nome;

    else
        nome_player2 = nome;
}

bool Jogo::estaVivo(const int player){

    return !!(getPlayer(player)->getNumeroDeNavios());

}

std::string Jogo::getNome(const int player){

    if(player == 1)
        return nome_player1;
    else
        return nome_player2;
}

Navio * Jogo::getAlgumNavio(const int player){

    return getPlayer(player)->algumNavio();

}

int Jogo::getAltura(const int player){

    return getPlayer(player)->getAltura();
}

int Jogo::getLargura(const int player){

    return getPlayer(player)->getLargura();

}

int Jogo::outroJogador(const int player){

    return !(player - 1) + 1;

}

std::string Jogo::tiroEmCoordenada(const int x, const int y, const int player, Navio * atacante, bool emMassa){

    if(atacante == NULL)
        atacante = getAlgumNavio(player);

    return getPlayer(outroJogador(player))->ataque(x, y, atacante, emMassa);

    if(!atacante->estaVivo())
        getPlayer(player)->navioMorreu(atacante);

}

std::string Jogo::processarAcao(int * x, int * y, const int player, const int escolha){

    if(escolha > 0 and escolha < 5 and cooldownAlvo(player)[escolha])
        return "FALHA" + std::to_string(cooldownAlvo(player)[escolha]);

    if(escolha == ATAQUE_COMUM)
        return ataqueComum(*x, *y, player);

    if(escolha == ATAQUE_EM_AREA)
        return ataqueEmArea(*x, *y, player);        

    if(escolha == CURAR_NAVIO)
        return curar(player);

    if(escolha == MISSEL_TELEGUIADO)
        return misselTeleguiado(player);

    if(escolha == RELEVAR_POSICAO)
        return relevarPosicao(player);

    return "FALHA";

}

std::string Jogo::ataqueComum(const int x, const int y, const int player){

    return tiroEmCoordenada(x, y, player);  

}

std::string Jogo::ataqueEmArea(const int x, const int y, const int player){

    cooldownAlvo(player)[ATAQUE_EM_AREA] = 4;

    std::string resultado;

    Navio * atacante = getAlgumNavio(player);

    for(int i = x - 1; i <= x + 1; i++)
        for(int j = y - 1; j <= y + 1; j++){

            if(i < 1 or i > getLargura(outroJogador(player)))
                continue;

            if(j < 1 or j > getAltura(outroJogador(player)))
                continue;

            if(!atacante->estaVivo())
                continue;

            std::string recebeu = tiroEmCoordenada(i, j, player, atacante, true);

            if(!recebeu.empty())
                resultado += (!resultado.empty() ? "\n" : "") + recebeu;

        }

    return resultado;

}

std::string Jogo::curar(const int player){

    cooldownAlvo(player)[CURAR_NAVIO] = 2;

    int cura = randInt(1, maxDano / 2);

    Navio * aliado = getAlgumNavio(player);

    aliado->setVida(cura);

    return std::string("Um navio do tipo " + intParaNome[aliado->getTipo()]) + " foi curado.";

}

std::string Jogo::misselTeleguiado(const int player){

    cooldownAlvo(player)[MISSEL_TELEGUIADO] = 3;

    int dano = randInt(1, maxDano / 2);

    Navio * atacado = getAlgumNavio(outroJogador(player));

    Navio * atacante = getAlgumNavio(player);

    return atacado->ataque(&dano, atacante);

}

std::string Jogo::relevarPosicao(const int player){

    cooldownAlvo(player)[RELEVAR_POSICAO] = 4;

    Navio * inimigo = getAlgumNavio(outroJogador(player));

    inimigo->desamocar();

    return std::string("Um navio do tipo " + intParaNome[inimigo->getTipo()]) + " foi mostrado no mapa.";

}

void Jogo::limparCooldown(const int player){

    for(int i = 0; i < 5; i++)
        cooldownAlvo(player)[i] = 0;

}

void Jogo::diminuirCooldown(const int player){

    for(int i = 0; i < 5; i++)
        cooldownAlvo(player)[i] -= !!cooldownAlvo(player)[i];

}

int * Jogo::cooldownAlvo(const int player){

    if(player == 1)
        return cooldown_player1;
    else
        return cooldown_player2;

}

void Jogo::setMaxDano(const int novo){

    maxDano = novo;

}