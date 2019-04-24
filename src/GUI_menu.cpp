#include <iostream> // cout, cin
#include <vector> // vector
#include <string> // string
#include <unistd.h> // usleep
#include <utility> // pair
#include <fstream> // ifstream

#include "../inc/GUI_menu.hpp"
#include "../inc/navios.hpp"
#include "../inc/helpers.hpp"

GUI_menu::GUI_menu(){

    opcoes = {

        "Modo Historia",
        "Jogar Partida", 
        "Mapas",
        "Sobre",
        "Scoreboard",
        "Sair do jogo"

    };

    titulo = "Menu principal";
}

GUI_menu::~GUI_menu(){}

void GUI_menu::sair(){

    limpaTela();
    quebraLinha(11);
    std::cout<<"        Aᴛᴇ ᴍᴀɪꜱ, ᴇ ᴏʙʀɪɢᴀᴅᴏ ᴘᴇʟᴏꜱ ᴘᴇɪxᴇꜱ\n";
    quebraLinha(10);
    usleep(2000000);

    exit(0);

}

void GUI_menu::sobre(){

    limpaTela();
    quebraLinha(10);
    printaTitulo(26);
    quebraLinha(4);
    printaImagem("sobre");
    quebraLinha(4);
    travaDeLeitura();

}
 

void GUI_menu::scoreboard(){

    limpaTela();
    quebraLinha();
    printaTitulo();
    
    quebraLinha(2);

    formatarDist();
    std::cout<<"Scoreboard:\n";

    quebraLinha(2);

    std::string caminho = "./doc/pontucao.ranking";

    std::ifstream arquivo(caminho);

    if(arquivo.good()){

        int posicao = 1;

        while(!arquivo.eof()){

            std::string arquivo_nome;
            int arquivo_pontos;

            arquivo >> arquivo_nome >> arquivo_pontos;

            formatarDist();
            if(!arquivo_nome.empty())
                std::cout<<posicao++<<". "<<arquivo_nome<<" - - - - - "<<arquivo_pontos<<std::endl;

        }

        arquivo.close();

    }else{

        formatarDist();
        std::cout<<"Nao ha nenhum registro no scoreboard, jogue partidas para preencher ele!\n";

    }

    quebraLinha();
    
    travaDeLeitura();

}