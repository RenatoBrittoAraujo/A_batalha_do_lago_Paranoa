#include <string> // string
#include <utility> // pair
#include <fstream> // ifstream, ofstream
#include <queue> // priority_queue

#include "../inc/jogo.hpp"
#include "../inc/mapa.hpp"
#include "../inc/helpers.hpp"

int Jogo::salvarPontuacao(const int player){

    int pontuacao = calcularPontuacao(player);
    std::string nome = getNome(player);

    std::pair<int, std::string> pontuacaoNova = {pontuacao, nome};

    std::string caminho = "./doc/pontucao.ranking";

    std::ifstream arquivo(caminho);

    std::priority_queue<std::pair<int, std::string>> ranking;
    
    ranking.push(pontuacaoNova);

    if(arquivo.good()){

        while(!arquivo.eof()){

            std::string arquivo_nome;
            int arquivo_pontos;

            arquivo >> arquivo_nome >> arquivo_pontos;

            ranking.push({arquivo_pontos, arquivo_nome});

        }

        arquivo.close();

    }

    std::remove(caminho.c_str());

    std::ofstream novoArquivo(caminho);

    int posicao = 1;
    int posicao_player = posicao;
    int score_anterior = ranking.top().first;

    while(!ranking.empty()){

        if(ranking.top().first == pontuacao)
            posicao_player = posicao;

        if(ranking.top().first < score_anterior)
            posicao++;
            
        if(!ranking.top().second.empty())
            novoArquivo << ranking.top().second << ' ' << ranking.top().first << std::endl;

        ranking.pop();

    }

    novoArquivo.close();

    return posicao_player;

}

int Jogo::getNumeroDeNavios(const int player){

    return getPlayer(player)->getNumeroDeNavios();

}

int Jogo::getNumeroDeNaviosInicial(const int player){

    if(player == 1)
        return numero_de_navios_player1;
    else
        return numero_de_navios_player2;

}

int Jogo::calcularPontuacao(const int player){

    return ((double)getNumeroDeNavios(player) / (double)getNumeroDeNaviosInicial(player) -
            (double)getNumeroDeNavios(outroJogador(player)) / getNumeroDeNaviosInicial(outroJogador(player))) * 100;

}

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

void Jogo::setNumeroDeNaviosInicial(){

    numero_de_navios_player1 = getNumeroDeNavios(1);
    numero_de_navios_player2 = getNumeroDeNavios(2);

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

std::string Jogo::tiroEmCoordenada(const int x, const int y, const int player, const int dano, Navio * atacante, bool emMassa){

    if(atacante == NULL)
        atacante = getAlgumNavio(player);

    return getPlayer(outroJogador(player))->ataque(x, y, atacante, dano, emMassa);

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

    int dano = randInt(1, getMaxDano());

    return tiroEmCoordenada(x, y, player, dano);  

}

std::string Jogo::ataqueEmArea(const int x, const int y, const int player){

    cooldownAlvo(player)[ATAQUE_EM_AREA] = 4;

    std::string resultado;

    Navio * atacante = getAlgumNavio(player);

    int dano = randInt(1, getMaxDano()/4);

    for(int i = x - 1; i <= x + 1; i++)
        for(int j = y - 1; j <= y + 1; j++){

            if(i < 1 or i > getLargura(outroJogador(player)))
                continue;

            if(j < 1 or j > getAltura(outroJogador(player)))
                continue;

            if(!atacante->estaVivo())
                continue;

            std::string recebeu = tiroEmCoordenada(i, j, player, dano, atacante, true);

            if(!recebeu.empty())
                resultado += (!resultado.empty() ? "\n" : "") + recebeu;

        }

    return resultado;

}

std::string Jogo::curar(const int player){

    cooldownAlvo(player)[CURAR_NAVIO] = 2;

    int cura = randInt(1, getMaxDano() / 2);

    Navio * aliado = getAlgumNavio(player);

    aliado->setVida(cura);

    return std::string("Um navio do tipo " + intParaNome[aliado->getTipo()]) + " foi curado.";

}

std::string Jogo::misselTeleguiado(const int player){

    cooldownAlvo(player)[MISSEL_TELEGUIADO] = 3;

    int dano = randInt(1, getMaxDano() / 2);

    Navio * atacado = getAlgumNavio(outroJogador(player));

    Navio * atacante = getAlgumNavio(player);

    return atacado->ataque(dano, atacante);

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

#include <iostream>

void Jogo::setMaxDano(const int novo){

    std::cout<<"MAX DANO ALTERADO-------------------\n";

    maxDano = novo;

}

int Jogo::getMaxDano(){

    return maxDano;

}
