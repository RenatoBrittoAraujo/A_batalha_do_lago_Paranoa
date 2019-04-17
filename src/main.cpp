#include "../inc/GUI_menu.hpp"
#include "../inc/GUI_mapa.hpp"
#include "../inc/GUI_jogo.hpp"

int main(){

    enum {
    // Menu principal
            SAIR, JOGAR, FAZER_MAPA, SOBRE, SCOREBOARD,

    // Menu mapa
            MENU_PRINCIPAL, CRIAR_MAPA, RAND_MAPA, DESTROI_MAPA, LISTAR_MAPAS, VER_MAPA 
    };
    
    GUI_menu menu;

    while(true){

        int opcao = menu.menuEscolha();

        if(opcao == JOGAR){

            GUI_jogo jogo;

            jogo.escolhaDeMapas();

            jogo.jogar();

        }
        
        if(opcao == FAZER_MAPA){

            GUI_mapa menu_de_mapa;
                
            while(opcao != MENU_PRINCIPAL){

                opcao = menu_de_mapa.menuEscolha() + SCOREBOARD + 1; // Por causa do enum

                if(opcao == CRIAR_MAPA)
                    menu_de_mapa.criarMapa();

                if(opcao == RAND_MAPA)
                    menu_de_mapa.gerarMapa();

                if(opcao == DESTROI_MAPA)
                    menu_de_mapa.excluirMapa();                

                if(opcao == LISTAR_MAPAS)
                    menu_de_mapa.listarMapas();

                if(opcao == VER_MAPA)
                    menu_de_mapa.verMapa();
                
            }

        }
        
        if(opcao == SOBRE)
            menu.sobre();

        if(opcao == SCOREBOARD)
            menu.scoreboard();
        
        if(opcao == SAIR)
            menu.sair();
    
    }

    return 0;
}

