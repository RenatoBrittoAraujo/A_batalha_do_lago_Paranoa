#include <string> // string
#include <iostream> // cin, cout
#include <unistd.h> // usleep

#include "../inc/mapa.hpp"
#include "../inc/jogo.hpp"
#include "../inc/GUI_jogo.hpp"
#include "../inc/helpers.hpp"

void GUI_jogo::configurarPlayer(Mapa * player, const int id_player){

    limpaTela();
    quebraLinha();
    formatarDist();

    std::string selecao = "";

    std::cout<<"Selecao de nome do player "<<id_player<<": ";
    std::getline(std::cin, selecao);

    jogo.setNome(selecao, id_player);
    
    listarMapas(true);

    selecao = "";

    while(true){

        while(!arquivoExiste("./doc/" + selecao + ".mapa")){

            formatarDist();
            std::cout<<"Selecao: ";
            std::getline(std::cin, selecao);

        }
        
        if(player->abrirMapa(selecao))
            break;
        
        else{
            formatarDist();
            std::cout<<"Aconteceu um erro, escolha de novo\n";
        }
    }
    
    formatarDist();
    std::cout<<"Mapa lido com sucesso!\n";

    player->configurarJogo();
    jogo.limparCooldown(id_player);

    usleep(1000000);
}

void GUI_jogo::escolhaDeMapas(){

    std::cin.ignore();

    configurarPlayer(jogo.getPlayer(1), 1);

    configurarPlayer(jogo.getPlayer(2), 2);

}

void GUI_jogo::escolherCoordenadas(int * x, int * y, const int player){

    while(*x < 1 or *x > jogo.getLargura(jogo.outroJogador(player))){
        

        std::cout<<"Coordenada X do ataque: ";
        std::cin>>*x;

    }

    while(*y < 1 or *y > jogo.getAltura(jogo.outroJogador(player))){

        std::cout<<"Coordenada Y do ataque: ";
        std::cin>>*y;

    }

}

bool GUI_jogo::turno(const int player){
    
    int x = 0, y = 0;

    std::string resultado = "FALHA";

    std::string noticia = "";

    while(resultado.substr(0, 5) == "FALHA"){

        limpaTela();
        quebraLinha(4);
        formatarDist();

        std::cout<<"Turno de "<<jogo.getNome(player)<<std::endl;
        quebraLinha(2);

        printArray(jogo.getPlayer(jogo.outroJogador(player))->mostrarMapaDeJogo(), true);

        quebraLinha(2);

        if(!noticia.empty()){
            
            formatarDist();
            
            std::cout<<std::endl<<noticia<<std::endl;
        }

        quebraLinha(4);

        int escolha = menuEscolha(&opcoes);

        if(escolha == 0)
            return true;

        if(escolha <= 2)
            escolherCoordenadas(&x, &y, player);

        resultado = jogo.processarAcao(&x , &y, player, escolha);

        if(resultado.substr(0, 5) == "FALHA"){
        
            quebraLinha(2);
            formatarDist();
            if(resultado.size() == 5)
                noticia = "Aconteceu um erro inesperado, tente de novo";
            else
                noticia = "Espere mais " + resultado.substr(5) + " turno(s) para poder usar esse ataque de novo";

            quebraLinha(1);
        
        }

    }

    jogo.diminuirCooldown(player);

    quebraLinha(2);
    
    std::cout<<"---------LOG DE ATAQUE---------\n\n";

    std::cout<<resultado<<std::endl;

    std::cout<<"\n-------------------------------\n";

    char leitura;
    quebraLinha(2);
    std::cout<<"Proximo turno ";
    std::cin>>leitura;

    return false;

}

void GUI_jogo::jogar(){

    int player_atual = 1;

    bool sair = false;

    while(jogo.estaVivo(player_atual) and !sair){

        sair = turno(player_atual);

        player_atual = jogo.outroJogador(player_atual);

    }

    if(sair)
        return;

    limpaTela();
    quebraLinha();
    formatarDist();
    std::cout<<jogo.getNome(player_atual)<<" perdeu todas suas embarcações!\n";
    quebraLinha();

    usleep(2500000);

    limpaTela();
    quebraLinha();
    formatarDist();

    player_atual = jogo.outroJogador(player_atual);

    std::cout<<jogo.getNome(player_atual)<<" atingiu uma vitoria triufante na batalha sangrenta sobre os mares de Brasília!\n";
    quebraLinha(4);
    
    usleep(2000000);

    char leitura = '0';
    while(leitura != 's' and leitura != 'n'){
    
        formatarDist();
        std::cout<<"Deseja salvar no scoreboard (S ou N)?: ";
        std::cin>>leitura;

    }

}