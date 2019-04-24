#ifndef GUI_BASICA
#define GUI_BASICA

#include <vector> // vector
#include <string> // string

/*
    Essa classe guarda funcoes para facilitar fazer a parte grafica
    do jogo ficar mais bonita disponibilizando para suas classes
    filhas ferramentas que fazer o print pro terminal mais simples
*/

class GUI_basica{

protected:    

    // Titulo que aparece no menu
    std::string titulo;

    // Opcoes variaveis de menu
    std::vector<std::string> opcoes;

    GUI_basica();
    ~GUI_basica();

    // Limpa a tela do terminal
    void limpaTela();

    // Imprime o titulo do jogo
    void printaTitulo(const int espaco = 6);

    // Printa espacos no terminal
    void formatarDist(const int espaco = 6);

    // Printa array de caracteres, sep = numero de carateres entre elemento da array
    void printArray(const std::vector<std::string> * vetor, const bool numeracao = false, const int espaco = 6, const int sep = 2);

    // Quebra linha um numero determinado de vezes
    void quebraLinha(const int espaco = 5);
    
    // Exibe opcoes baseadas no vetor statico opcoes
    void exibirOpcao(const int escolha = -1, const int espaco = 18, std::vector<std::string> * opcoes = NULL);

    // Espera input do usuario para ir para o proximo estado de jogo
    void travaDeLeitura();

    // Printa arte ascii na tela
    void printaImagem(std::string nome, const int espaco = 10);

public:

    // Cria menu para opcoes diferentes, se opcoes for nula, cria menu com vetor de opcoes estatico
    // criado junto com a classe
    int menuEscolha(std::vector<std::string> * opcoes = NULL);

    // Mostra uma lista dos mapas disponiveis
    void listarMapas(bool mesmaTela = false);

};

#endif