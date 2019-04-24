#ifndef GUI_MAPA
#define GUI_MAPA

#include "mapa.hpp"
#include "GUI_basica.hpp"

class GUI_mapa: public GUI_basica{
private:

    // Mapa atual onde as operacoes sao feitas
    Mapa mapa;

    bool mapaNovo();

public:

    GUI_mapa();
    ~GUI_mapa();

    // Ususario cria mapa novo e tem a opcao de salvar
    void criarMapa();

    // Usuario gera um mapa aleatorio, ve o resultado e tem a opcao de salvar
    void gerarMapa();

    // Usuario tenta excluir mapa existente
    void excluirMapa();

    // Mostra mapa escolhido
    void verMapa();

};

#endif