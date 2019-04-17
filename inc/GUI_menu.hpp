#ifndef GUI_MENU
#define GUI_MENU

#include "GUI_basica.hpp"

class GUI_menu: public GUI_basica{

public:

    GUI_menu();
    ~GUI_menu();

    // Mostra informacoes sobre o jogo
    void sobre();

    // Mostra tela de saida
    void sair();

};

#endif