#include <iostream> //cin, cout
#include <string> // string
#include <vector> // vector
#include <unistd.h> // usleep
#include <map> // map

#include "../inc/GUI_mapa.hpp"
#include "../inc/mapa.hpp"
#include "../inc/helpers.hpp"

GUI_mapa::GUI_mapa(){

    opcoes = {

        "Criar mapa", 
        "Gerar mapa aleatorio", 
        "Excluir mapa",
        "Ver mapa",
        "Voltar para o menu principal"

    };

    titulo = "Mapas";
}

GUI_mapa::~GUI_mapa(){}

bool GUI_mapa::mapaNovo(){

    limpaTela();
    quebraLinha(7);
    formatarDist(6);
    std::cout<<"Nome do mapa a ser criado: ";
    std::string nome;
    std::cin.ignore();
    std::getline(std::cin, nome);

    if(arquivoExiste("./doc/" + nome + ".mapa")){

        quebraLinha(2);
        formatarDist(6);
        std::cout<<"Mapa com nome '"<<nome<<"' ja existe\n";
        usleep(2000000);
        return false;

    }

    if(!mapa.setNome(nome))
        mapa = Mapa(),
        mapa.setNome(nome);

    int largura = 0, altura = 0;

    while(largura < 1 or largura > 30){

        formatarDist(6);
        std::cout<<"Largura do mapa (1 ate 30): ";
        std::cin>>largura;

    }

    while(altura < 1 or altura > 30){

        formatarDist(6);
        std::cout<<"Altura do mapa (1 ate 30): ";
        std::cin>>altura;

    }

    mapa.setLarguraEAltura(largura, altura);

    return true;

}

void GUI_mapa::gerarMapa(){

    if(!mapaNovo())
        return;

    limpaTela();

    int numero_de_navios = 0;

    int maximo_de_navios = mapa.getAltura() * mapa.getLargura();

    quebraLinha();

    while(numero_de_navios > maximo_de_navios or numero_de_navios < 1){

        formatarDist();
        std::cout<<"Numero de navios desejado entre [1 - "<<maximo_de_navios<<"]: ";
        std::cin>>numero_de_navios;

    }

    quebraLinha();
    formatarDist();

    std::cout<<"Gerando mapa novo...\n";

    limpaTela();

    mapa.gerarMapa(numero_de_navios);

    quebraLinha();
    formatarDist();

    std::cout<<"Mapa gerado com sucesso!";

    quebraLinha(3);

    printArray(mapa.mostrarMapa(), true);

    quebraLinha(5);
    
    char leitura = '0';

    quebraLinha(3);

    while((leitura == 's') == (leitura == 'n')){ // Eu realmente queria um jeito pra deixar essa parte do codigo mais elegante

        std::cout<<"Salvar mapa? (S ou N): ";
        std::cin>>leitura;
        leitura = ::tolower(leitura);

    }

    if(leitura == 's')
        mapa.salvaMapa();

    mapa = Mapa();
}

void GUI_mapa::criarMapa(){

    if(!mapaNovo())
        return;

    limpaTela();

    std::vector<std::string> opcoes = {
        "Adicionar navio",
        "Remover ultimo navio",
        "Salvar e sair",
        "Sair"
    };

    enum {SAIR, ADD_NAVIO, REM_NAVIO, SALVAR_SAIR};

    while(1){

        limpaTela();
        quebraLinha(2);
        formatarDist();
        std::cout<<"Mapa '"<<mapa.getNome()<<"':\n";
        quebraLinha(2);
        printArray(mapa.mostrarMapa(), true);
        quebraLinha();

        int escolha = menuEscolha(&opcoes);
        
        if(escolha == SAIR)
            return;

        std::map<std::string, int> orientacao;

        enum orientacoes{SUL, LESTE, NORTE, OESTE};

        orientacao["sul"] = SUL;
        orientacao["leste"] = LESTE;
        orientacao["norte"] = NORTE;
        orientacao["oeste"] = OESTE;

        if(escolha == ADD_NAVIO){
            std::string direcao = "";
            int tipo = 0, x = 0, y = 0;

            std::vector<std::string> opcoes = {
                "Iate",
                "Porta Teco Teco",
                "Prancha de SUP",
                "Dois caras numa moto",
                "Jet Ski",
                "Caravela",
                "Espaco Nave",
                "[CONFIDENCIAL]",
                "Voltar"
            };

            limpaTela();
            quebraLinha(2);
            formatarDist();
            std::cout<<"Mapa '"<<mapa.getNome()<<"':\n";
            quebraLinha(2);
            printArray(mapa.mostrarMapa(), true);
            quebraLinha();

            tipo = menuEscolha(&opcoes);

            if(tipo != 0){

                while(x < 1 or x > mapa.getLargura()){
                    std::cout<<"Eixo X: ";
                    std::cin>>x;
                } 

                while(y < 1 or y > mapa.getAltura()){
                    std::cout<<"Eixo Y: ";
                    std::cin>>y;
                }

                while(orientacao.find(direcao) == orientacao.end()){
                    std::cout<<"Orientacao (norte, sul, leste, oeste): ";
                    std::cin>>direcao;
                }

                quebraLinha(1);

                tipo--;

                if(mapa.inserirNavio(x, y, tipo, orientacao[direcao]))
                    formatarDist(),
                    std::cout<<"Navio colocado\n";
                else
                    formatarDist(),
                    std::cout<<"Orientacao invalida\n";

                usleep(1000000);

            }

        }

        if(escolha == REM_NAVIO){

            mapa.removerUltimo();

        }

        if(escolha == SALVAR_SAIR){

            mapa.salvaMapa();

            std::cout<<"Mapa '"<<mapa.getNome()<<"' foi salvo, retornando...\n";
            usleep(1300000);

            return;

        }
    }

}


void GUI_mapa::excluirMapa(){

    limpaTela();
    listarMapas(1);
    formatarDist();
    std::cout<<"Nome do mapa a ser excluido: ";
    std::cin.ignore();
    std::string nome;
    std::getline(std::cin, nome);

    if(mapa.abrirMapa(nome)){

        limpaTela();
        quebraLinha();
        formatarDist();
        std::cout<<"Mapa carregado com sucesso\n";
        char leitura;

        while((leitura == 's') == (leitura == 'n')){

            formatarDist(6);
            std::cout<<"Tem certeza que quer excluir? (S ou N) ";
            std::cin>>leitura;
            leitura = ::tolower(leitura);
            usleep(100000);

        }

        quebraLinha(2);
        formatarDist();

        if(leitura == 's'){

            if(mapa.destroiMapa())
                std::cout<<"Mapa '"<<nome<<"' excluido\n";
            else
                std::cout<<"Ocorreu um erro na exclusao do mapa '"<<nome<<"'\n";

        }else{

            std::cout<<"Mapa nao excluido, retornando...\n";

        }

        mapa = Mapa();

    }else{

        quebraLinha(2);
        formatarDist();
        std::cout<<"Mapa com nome '"<<nome<<"' nao encontrado\n";
        
    }

    travaDeLeitura();

}

void GUI_mapa::verMapa(){

    limpaTela();
    listarMapas(1);
    formatarDist();
    std::cout<<"Nome do mapa: ";
    std::string nome;
    
    std::cin.ignore();
    std::getline(std::cin, nome);

    if(!arquivoExiste("./doc/" + nome + ".mapa")){

        quebraLinha(2);
        formatarDist();
        std::cout<<"Mapa com nome '"<<nome<<"' nao encontrado\n";
        travaDeLeitura();
        return;

    }

    limpaTela();
    quebraLinha();
    formatarDist();
    std::cout<<"Mapa '"<<nome<<"':\n\n";

    mapa.abrirMapa(nome);
    printArray(mapa.mostrarMapa(), true);

    quebraLinha();
    
    travaDeLeitura();

}