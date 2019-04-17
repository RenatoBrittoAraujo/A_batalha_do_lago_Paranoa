#include <iostream> // cout
#include <string> // string
#include <unistd.h> // usleep
#include <sys/types.h> // DIR, opendir, readdir, closedir
#include <dirent.h> // dirent

#include "../inc/GUI_basica.hpp"

GUI_basica::GUI_basica(){}
GUI_basica::~GUI_basica(){}

void GUI_basica::limpaTela(){

    std::cout << "\033[2J\033[1;1H";

}

void GUI_basica::formatarDist(const int espaco){

    for(int i = 0; i < espaco; i++)
        std::cout<<' ';

}

void GUI_basica::printaTitulo(const int espaco){

    formatarDist(espaco); std::cout<<"         A  BATALHA  DO  LAGO         "<<std::endl;
    formatarDist(espaco); std::cout<<" ____ ____ ____ ____       _____ ____ "<<std::endl;
    formatarDist(espaco); std::cout<<" |  | |  | |  | |  | |\\  | |   | |  | "<<std::endl;
    formatarDist(espaco); std::cout<<" |__| |__| |__| |__| | \\ | |   | |__| "<<std::endl;
    formatarDist(espaco); std::cout<<" |    |  | | \\_ |  | |  \\| |___| |  | "<<std::endl;
    
}

std::vector<std::string> opcoes = {};

void GUI_basica::exibirOpcao(const int escolha, const int espaco, std::vector<std::string> * opcoes){

    if(opcoes == NULL)
        opcoes = &(this->opcoes);

    for(int i = 0; i < (int)opcoes->size(); i++){
        formatarDist(espaco);

        if(escolha < 0 or escolha > (int)opcoes->size() - 1)
            std::cout << (i + 1 == (int)opcoes->size() ? 0 : i + 1) << ". " << opcoes->at(i) << std::endl;

        else if(i + 1 == escolha or (escolha == 0 and i + 1 == (int)opcoes->size()))
            std::cout << "=>" << ' ' << opcoes->at(i) << std::endl;

        else
            std::cout << "  " << ' ' << opcoes->at(i) << std::endl;
         
    }
}

void GUI_basica::printArray(const std::vector<std::string> * vetor, const bool numeracao, const int espaco, const int sep){

    if(numeracao){
        formatarDist(sep + 9);
        for(size_t i = 1; i < (size_t)vetor->at(0).size(); i++){

            std::cout<<i;
            formatarDist(sep - (i > 8));

        }
        std::cout<<std::endl;
        formatarDist(sep + 8);
        for(size_t i = 1; i < (size_t)vetor->at(0).size(); i++){

            std::cout<<"__";
            formatarDist(1);

        }
        std::cout<<std::endl;
    }
            

    for(size_t i = 1; i < (size_t)vetor->size(); i++){

        formatarDist(espaco);

        if(numeracao){
            std::cout<<i<<(i > 9 ? "":" ")<<"|";
            formatarDist(sep);
        }

        for(size_t j = 1; j < (size_t)vetor->at(i).size(); j++){

            std::cout<<vetor->at(i).at(j);
            formatarDist(sep);

        }

        std::cout<<std::endl;

    }

}

void GUI_basica::quebraLinha(const int espaco){

    for(int i = 0; i < espaco; i++)
        std::cout << std::endl;

}

int GUI_basica::menuEscolha(std::vector<std::string> * opcoes){

    bool temTitulo = false;

    if(opcoes == NULL)
        opcoes = &(this->opcoes),
        temTitulo = true;

    char leitura = 'a';

    while(leitura < '0' or leitura > '0' + (int)opcoes->size() - 1){

        if(temTitulo)
            limpaTela(),
            quebraLinha();

        if(temTitulo){
            printaTitulo();
            quebraLinha(2);
            formatarDist(10);
            std::cout<<titulo<<':'<<std::endl;
            quebraLinha(2);
        }

        exibirOpcao(-1, 12, opcoes);
        quebraLinha();

        std::cout<<"Sua escolha: ";
        std::cin>>leitura;

        usleep(1000);
    }

    usleep(1000);

    if(temTitulo){
        limpaTela();
        quebraLinha();
        printaTitulo();
        quebraLinha(2);
        formatarDist(10);
        std::cout<<titulo<<':'<<std::endl;
        formatarDist(10);
        std::cout<<"Carregando...\n";
        quebraLinha(1);
        exibirOpcao(leitura - '0', 12, opcoes);
        quebraLinha();
    }

    usleep(300000);

    return leitura - '0';
}

void GUI_basica::listarMapas(bool mesmaTela){

    if(!mesmaTela)
        limpaTela();
        
    quebraLinha();
    formatarDist();

    std::cout<<"Lista de mapas:\n\n";

    DIR *diretorio;

    struct dirent *arquivo;

    diretorio = opendir((const char *)("./doc/."));

    while ((arquivo = readdir(diretorio)) != NULL) {
        
        std::string nome = std::string(arquivo->d_name);

        if(nome.size() < 6)
            continue;

        if(nome.substr(nome.size() - 5)  == ".mapa"){
            
            formatarDist();
            std::cout << "- " << nome.substr(0, nome.size() - 5) << std::endl;
        
        }
    }
    
    closedir(diretorio);
    
    quebraLinha();

    if(!mesmaTela){
        std::cout<<"Digite qualquer tecla para voltar: ";
        char leitura;
        std::cin>>leitura;
    }
}