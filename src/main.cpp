#include "../inc/GUI_menu.hpp"
#include "../inc/GUI_mapa.hpp"
#include "../inc/GUI_jogo.hpp"
#include "../inc/helpers.hpp"

int main(){

    // Meu objetivo era fazer a main mais limpa possivel, esse foi o melhor jeito que encontrei sem
    // fazer a main perder o sentido e atribuir toda a funcionalidade de jogo a outras classes

    // Ou seja, a main esta limpa e concisa mas ainda tem uma parte vital no funcionamento do jogo

    enum {
    // Menu principal
            SAIR, JOGAR_HISTORIA, JOGAR_PARTIDA, MAPAS, SOBRE, SCOREBOARD,

    // Menu mapa
            MENU_PRINCIPAL, CRIAR_MAPA, RAND_MAPA, DESTROI_MAPA, VER_MAPA 
    };
    
    GUI_menu menu;

    while(true){

        int opcao = menu.menuEscolha();

        if(opcao == JOGAR_HISTORIA){

            GUI_jogo jogo;

            jogo.modoHistoria();

        }

        if(opcao == JOGAR_PARTIDA){

            GUI_jogo jogo;

            if(jogo.tipoDeJogo()){ // Usuario pode escolher sair

                jogo.configurarPartida();

                jogo.jogar();
            
            }

        }
        
        if(opcao == MAPAS){

            GUI_mapa menu_de_mapa;
                
            while(opcao != MENU_PRINCIPAL){

                opcao = menu_de_mapa.menuEscolha() + SCOREBOARD + 1; // Por causa do enum

                if(opcao == CRIAR_MAPA)
                    menu_de_mapa.criarMapa();

                if(opcao == RAND_MAPA)
                    menu_de_mapa.gerarMapa();

                if(opcao == DESTROI_MAPA)
                    menu_de_mapa.excluirMapa();   

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

