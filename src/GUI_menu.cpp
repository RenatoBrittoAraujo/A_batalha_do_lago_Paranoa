#include <iostream> // cout, cin
#include <vector> // vector
#include <string> // string
#include <unistd.h> // usleep

#include "../inc/GUI_menu.hpp"
#include "../inc/navios.hpp"

GUI_menu::GUI_menu(){

    opcoes = {

        "Jogar", 
        "Mapas",
        "Sobre",
        "Score",
        "Sair do jogo"

    };

    titulo = "Menu principal";
}

GUI_menu::~GUI_menu(){}

void GUI_menu::sair(){

    limpaTela();
    quebraLinha(11);
    std::cout<<"          Ate mais, e obrigado pelos peixes\n";
    quebraLinha(10);
    usleep(2000000);

    exit(0);

}

void GUI_menu::sobre(){

    limpaTela();
    quebraLinha(10);
    printaTitulo(25);
    quebraLinha(4);
    std::cout<<"    ___________________________________________________________________________________\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | Versao brasiliense do batalha naval!                                            |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | Jogado por 2 players cada um com seu mapa e navios.                             |\n";
    std::cout<<"    | Ganha o player que eliminar todos os navios inimigos primeiro.                  |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | => Simbolos do mapa:                                                            |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | '~' => Mar                                                                      |\n";
    std::cout<<"    | 'X' => Tiro anterior                                                            |\n";
    std::cout<<"    | 'H' => Iate                                                                     |\n";
    std::cout<<"    | '#' => Porta teco teco                                                          |\n";
    std::cout<<"    | '0' => Prancha de SUP                                                           |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | Todos os navios nascem com atributos escondidos e, a cada ataque,               |\n";
    std::cout<<"    | seus atributos podem mudar e alterar o seu potencial de batalha no jogo.        |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    |---------------------------------------------------------------------------------|\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | => Descricoes dos navios:                                                       |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | -----------------------------                                                   |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | Prancha de SUP:                                                                 |\n";
    std::cout<<"    | Atributos:   remo                                                               |\n";
    std::cout<<"    | Vida inicial:  50                                                               |\n";
    std::cout<<"    | Descricao:                                                                      |\n";
    std::cout<<"    | A Prancha de SUP possui apenas 1 bloco de tamanho, o que                        |\n";
    std::cout<<"    | torna ela dificil de se encontrar no mapa. Ela possui um remo, que              |\n";
    std::cout<<"    | deflete ataques podem a cada ataque defletido, fica mais improvavel             |\n";
    std::cout<<"    | que os ataques subsequentes serao defletidos                                    |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | -----------------------------                                                   |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | Iate:                                                                           |\n";
    std::cout<<"    | Atributos:  fama, dinheiro, e de politico                                       |\n";
    std::cout<<"    | Vida inicial:  100                                                              |\n";
    std::cout<<"    | Descricao:                                                                      |\n";
    std::cout<<"    | O Iate e um barco de gente rica, por isso seu principal atributo e dinheiro.    |\n";
    std::cout<<"    | Quanto mais dinheiro ele possui, menor dano toma pois pode subornar o missel.   |\n";
    std::cout<<"    | Alem disso, seu nivel de fama define o quao facil e detecta-lo num ataque.      |\n";
    std::cout<<"    | O Iate pode ser de um politico, o que faz ele ganhar                            |\n";
    std::cout<<"    | um buff de dinheiro porem sempre e detectado quando e atacado.                  |\n";
    std::cout<<"    | Por ser politico, o dono do Iate pode te processar porque perder                |\n";
    std::cout<<"    | dinheiro e perder vida, e faz mal para a saude.                                 |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | -----------------------------                                                   |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | Porta Teco Teco:                                                                |\n";
    std::cout<<"    | Atributos:   competencia dos pilotos, teco tecos                                |\n";
    std::cout<<"    | Vida inicial:  50                                                               |\n";
    std::cout<<"    | Descricao:                                                                      |\n";
    std::cout<<"    | O Porta Teco-Teco e um navio de grade porte que transporta avioes do            |\n";
    std::cout<<"    | tipo teco-teco, pilotado por pilotos da FAB.                                    |\n";
    std::cout<<"    | Quanto mais avioes um Porta Teco-Teco possui, maior sao as chances de           |\n";
    std::cout<<"    | ele destruir o ataque antes de ele atingir.                                     |\n";
    std::cout<<"    | A competencia dos pilotos do teco teco definem o seu contrataque e a            |\n";
    std::cout<<"    | cada ataque recebido a habilidade dos pilotos aumenta.                          |\n";
    std::cout<<"    | Assim que atingido, o Porta Teco-Teco mostra sua posicao e vida, pois           |\n";
    std::cout<<"    | o barulho dos Teco-Tecos voando e reconhecivel de longe.                        |\n";
    std::cout<<"    | A cada ataque bem sucedido, o numero de Teco-Tecos decrementa em um.            |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    |---------------------------------------------------------------------------------|\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | => Descricao das acoes                                                          |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | O player possui um arsenal de acoes para fazer, cada uma com                    |\n";
    std::cout<<"    | sua caracteristicas e tempo de recarga diferentes                               |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | Alem disso, existe a chance que ataques falhem.                                 |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | Existe o atributo de Dano Maximo, um numero que basicamente diz o quanto        |\n";
    std::cout<<"    | de dano um ataque causa. Quanto mais Dano Maximo, mais dinamico fica o jogo     |\n";
    std::cout<<"    | e mais potente sao todos os ataques                                             |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | -----------------------------                                                   |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | Ataque comum:                                                                   |\n";
    std::cout<<"    | Causa algo entre 1 - Dano Maximo no navio se acertar                            |\n";
    std::cout<<"    | -----------------------------                                                   |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | Ataque em area:                                                                 |\n";
    std::cout<<"    | Causa entre 1 - metade do Dano Maximo na coordenada e nos pontos ao redor       |\n";
    std::cout<<"    | -----------------------------                                                   |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | Curar:                                                                          |\n";
    std::cout<<"    | Cura entre 1 - Dano Maximo de algum dos seus navios                             |\n";
    std::cout<<"    | -----------------------------                                                   |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | Missel teleguiado:                                                              |\n";
    std::cout<<"    | Ataca um inimigo aleatorio e causa entre 1 - Dano Maximo de dano                |\n";
    std::cout<<"    | -----------------------------                                                   |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | Revelar posicao:                                                                |\n";
    std::cout<<"    | Simplesmente mostra no mapa a posicao de um inimigo qualquer                    |\n";
    std::cout<<"    | As vezes mostra posicao de inimigos ja revelados                                |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    |---------------------------------------------------------------------------------|\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    | Muito obrigado por jogar                                                        |\n";
    std::cout<<"    |                                                                                 |\n";
    std::cout<<"    |                                                                                 |\n";  
    std::cout<<"    | Feito por Renato Britto Araujo.                                                 |\n";
    std::cout<<"    | UnB-FGA Orientacao a Objetos 2019/1 EP1                                         |\n";
    std::cout<<"    |_________________________________________________________________________________|\n";

    quebraLinha(7);

    std::cout<<"Digite qualquer tecla para voltar: ";
    char escolha;
    std::cin>>escolha;

}
 