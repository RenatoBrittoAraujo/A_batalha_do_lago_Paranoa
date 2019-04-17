#include <string> // string
#include <iostream> // cin, cout
#include <unistd.h> // usleep

#include "../inc/mapa.hpp"
#include "../inc/jogo.hpp"
#include "../inc/GUI_jogo.hpp"
#include "../inc/helpers.hpp"

void GUI_jogo::escolherMapa(Mapa * player, const int id_player){

    limpaTela();
    quebraLinha(2);
    formatarDist();

std::cout<<"Selecao do mapa do player "<<id_player<<":\n";
    
    listarMapas(true);

    std::string selecao = "";

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

void GUI_jogo::escolherNome(const int player){

    quebraLinha(2);

    std::string selecao = "";

    formatarDist();

    std::cout<<"Selecao de nome do player "<<player<<": ";
    std::getline(std::cin, selecao);

    jogo.setNome(selecao, player);

}

void GUI_jogo::geracaoDeMapa(){

    limpaTela();
    quebraLinha(2);
    
    int largura = 0, altura = 0;

    while(largura < 1 or largura > 30){

        formatarDist();
        std::cout<<"Largura do mapa (1 ate 30): ";
        std::cin>>largura;

    }  

    quebraLinha(2);

    while(altura < 1 or altura > 30){

        formatarDist();
        std::cout<<"Altura do mapa (1 ate 30): ";
        std::cin>>altura;

    }

    jogo.getPlayer(1)->setLarguraEAltura(largura, altura);
    jogo.getPlayer(2)->setLarguraEAltura(largura, altura);

    int numero_de_navios = 0;

    int maximo_de_navios = jogo.getAltura(1) * jogo.getLargura(1);

    quebraLinha(2);

    while(numero_de_navios > maximo_de_navios or numero_de_navios < 1){

        formatarDist();
        std::cout<<"Numero de navios desejado entre [1 - "<<maximo_de_navios<<"]: ";
        std::cin>>numero_de_navios;

    }

    jogo.getPlayer(1)->gerarMapa(numero_de_navios);
    jogo.getPlayer(2)->gerarMapa(numero_de_navios);

    jogo.getPlayer(1)->configurarJogo();
    jogo.getPlayer(2)->configurarJogo();

    jogo.limparCooldown(1);
    jogo.limparCooldown(2);

}

void GUI_jogo::escolhaDeMapas(){

    limpaTela();
    quebraLinha(2);

    int danoMaximo = 0;

    formatarDist();
    std::cout<<"Dano Maximo define o quanto de dano/cura que as acoes causam.\n";
    formatarDist();
    std::cout<<"Quanto mais Dano Maximo, mais dinamico jogo, porem depende de sorte.\n";
    formatarDist();
    std::cout<<"Quanto menos Dano Maximo, mais estrategico fica o jogo.\n";

    quebraLinha(1);
    formatarDist();
    std::cout<<"Por volta de 100 e o modo padrao de jogo\n";

    quebraLinha(2);

    while(danoMaximo < 10 or danoMaximo > 1000){
        formatarDist();
        std::cout<<"Digite um valor para Dano Maximo (10 - 1000): ";
        std::cin>>danoMaximo;
    }

    jogo.setMaxDano(danoMaximo);

    limpaTela();
    quebraLinha();

    char escolherMapas = '0';

    while(escolherMapas != 'g' and escolherMapas != 'e'){

        formatarDist();
        std::cout<<"Deseja escolher mapas ou gerar mapas aleatorios? (E ou G) ";
        std::cin>>escolherMapas;
        escolherMapas = ::tolower(escolherMapas);

    }

    if(escolherMapas == 'g'){

        geracaoDeMapa();

        std::cin.ignore();

        escolherNome(1);
        escolherNome(2);

    }else{

        std::cin.ignore();

        escolherMapa(jogo.getPlayer(1), 1);

        escolherNome(1);

        escolherMapa(jogo.getPlayer(2), 2);
    
        escolherNome(2);
    }

    jogo.setNumeroDeNaviosInicial();

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

        std::cout<<"Turno de "<<jogo.getNome(player)<<". Pontuacao atual: "<<jogo.calcularPontuacao(player)<<std::endl;    
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

            x = y = 0;
        
        }

    }

    jogo.diminuirCooldown(player);

    limpaTela();
    quebraLinha(7);

    printArray(jogo.getPlayer(jogo.outroJogador(player))->mostrarMapaDeJogo(), true);
    
    quebraLinha(4);
    
    std::cout<<"------------ Resultado --------------\n\n";

    std::cout<<resultado<<std::endl;

    quebraLinha(2);

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

    quebraLinha(2);
    formatarDist();
    std::cout<<"Pontuacao: "<<jogo.calcularPontuacao(player_atual)<<std::endl;

    quebraLinha(4);
    
    usleep(2000000);

    char leitura = '0';
    while(leitura != 's' and leitura != 'n'){
    
        formatarDist();
        std::cout<<"Deseja salvar no scoreboard (S ou N)?: ";
        std::cin>>leitura;

    }

    if(leitura == 's'){
    
        jogo.salvarPontuacao(player_atual);
        quebraLinha(2);
        formatarDist();
        std::cout<<"Salvo!\n";
        usleep(1000000);
    
    }

}