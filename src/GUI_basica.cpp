#include <iostream> // cout, cin
#include <string> // string
#include <unistd.h> // usleep
#include <sys/types.h> // DIR, opendir, readdir, closedir
#include <dirent.h> // dirent
#include <algorithm> // transform
#include <fstream> // ifstream

#include "../inc/GUI_basica.hpp"

GUI_basica::GUI_basica(){}
GUI_basica::~GUI_basica(){}

// Isso printa algo no terminal que limpa tudo que ta escrito nele exceto o cursor
// So deus sabe porque, ou quem sabe regex.
void GUI_basica::limpaTela(){

    std::cout << "\033[2J\033[1;1H";

}

void GUI_basica::formatarDist(const int espaco){

    for(int i = 0; i < espaco; i++)
        std::cout<<' ';

}

void GUI_basica::printaTitulo(const int espaco){

    formatarDist(espaco); std::cout<<"●▬▬▬▬▬▬▬▬▬▬▬▬▬▬๑۩۩๑▬▬▬▬▬▬▬▬▬▬▬▬▬▬●"<<std::endl<<std::endl;
    formatarDist(espaco); std::cout<<"         A ʙᴀᴛᴀʟʜᴀ ᴅᴏ ʟᴀɢᴏ       "<<std::endl<<std::endl;
    formatarDist(espaco); std::cout<<"█▀▀█ █▀▀█ █▀▀█ █▀▀█ █▀▀▄ █▀▀█ █▀▀█"<<std::endl;
    formatarDist(espaco); std::cout<<"█  █ █▄▄█ █▄▄▀ █▄▄█ █  █ █  █ █▄▄█"<<std::endl;
    formatarDist(espaco); std::cout<<"█▀▀▀ ▀  ▀ ▀ ▀▀ ▀  ▀ ▀  ▀ ▀▀▀▀ ▀  ▀"<<std::endl<<std::endl;
    formatarDist(espaco); std::cout<<"●▬▬▬▬▬▬▬▬▬▬▬▬▬▬๑۩۩๑▬▬▬▬▬▬▬▬▬▬▬▬▬▬●"<<std::endl<<std::endl;
        
}

// Vetor padrao cujo qual se voce nao passar nada para a funcao menu escolha, ela imprime as opcoes desse
std::vector<std::string> opcoes = {};

// Printa, para um elemento especifico do vetor opcoes sua representacao no menu
void GUI_basica::exibirOpcao(const int escolha, const int espaco, std::vector<std::string> * opcoes){

    // Caso nao tenha sido passado um vetor especifico, ele pega o estatico da classe
    if(opcoes == NULL)
        opcoes = &(this->opcoes);

    // Para cada uma dos elementos de opcao sua representacao
    for(int i = 0; i < (int)opcoes->size(); i++){
        formatarDist(espaco);

        // Caso escolha nao tenha sido feita, printa com o numero na frente
        if(escolha < 0 or escolha > (int)opcoes->size() - 1)
            std::cout << (i + 1 == (int)opcoes->size() ? 0 : i + 1) << ". " << opcoes->at(i) << std::endl;

        // Depois de ser feita, printa item alvo da escolha com seta na frente
        else if(i + 1 == escolha or (escolha == 0 and i + 1 == (int)opcoes->size()))
            std::cout << "▶ " << ' ' << opcoes->at(i) << std::endl;

        // E os outros sem nada na frente
        else
            std::cout << "  " << ' ' << opcoes->at(i) << std::endl;
         
    }
}

void GUI_basica::printArray(const std::vector<std::string> * vetor, const bool numeracao, const int espaco, const int sep){

    // Se numeracao esta ligada, printa alem do vetor, o numero das posicoes
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
            
    // Printa o vetor com numeracao
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

// Menu usado por todas as GUI's para mostrar opcoes necessarias
// Retorna um inteiro da opcao que o usuario fez
// Vale lembrar que sempre tem a opcao '0' que retorna 0 e teoricamente
// volta de qualquer menu para qualquer anterior
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
        
    }

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

// Vai no diretorio ./doc e printa todos os arquivos .mapa la
void GUI_basica::listarMapas(bool mesmaTela){

    if(!mesmaTela)
        limpaTela();
        
    quebraLinha();
    formatarDist();

    std::cout<<"Lista de mapas:\n\n";

    // As unicas partes desse programa inteiro que eu nao sei como funcionam sao as duas linhas de codigo abaixo

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

    if(!mesmaTela)
        travaDeLeitura();
}

// Espera ususario apertar enter para continuar
void GUI_basica::travaDeLeitura(){

    formatarDist();
    std::cout<<"Aperte ENTER para continuar ";
    std::string leitura;
    std::cin.clear();
    std::cin.ignore();
    std::getline(std::cin, leitura);

}

void GUI_basica::printaImagem(std::string nome, const int espaco){

    std::transform(nome.begin(), nome.end(), nome.begin(), ::tolower);

    std::ifstream arquivo("./doc/asciiart/" + nome + ".asciiart");

    if(!arquivo.good())
        return;

    while(!arquivo.eof()){

        std::string linha;

        std::getline(arquivo, linha);

        if(!linha.empty())
            formatarDist(espaco);

        std::cout<<linha<<std::endl;
        
    }

    arquivo.close();

}