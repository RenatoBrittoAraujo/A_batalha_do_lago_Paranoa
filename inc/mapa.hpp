#ifndef MAPA
#define MAPA

#include <vector> // vector
#include <string> // string
#include <utility> // pair
#include <map> // map

#include "../inc/navio.hpp"
#include "../inc/navios.hpp"

class Mapa{

private:

    // Guarda nome do mapa (e nome do arquivo sem sufixo .mapa)
    std::string nome;

    // Altura do mapa
    int altura;

    // Largura do mapa
    int largura;

    // Vetor de ponteiros para navios do mapa
    std::vector<Navio*> navios;

    // Retorna se posicao do navio atual e valida
    bool posicaoValida(const int x, const int y, const int tamanho, const int direcao);

    // Retorna um par de valores no plano para as posicoes finais de uma navio
    std::pair<int, int> posicaoFinal(const int x, const int y, const int orientacao, int tamanho);

    // Retorna verdadeiro se ponto estiver fora do mapa
    bool limiteCheck(const int x, const int y);

    // Retorna endereco de representacao bidimensional do mapa
    std::vector<std::string> representacao;

    // Mapa que o player ve
    std::vector<std::string> mapa_de_jogo;

    // Recorda as coordenadas dos ultimos ataques
    std::vector<std::pair<int, int>> ultimos_ataques;

    // Bota navio no mapa de jogo
    void navioNoJogo(Navio * navio);

    // Retorna o navio corespondente a coordenada ou null se nao encontrar
    Navio * encontrarCoordenada(const int x, const int y);

    // Mapeia coordenada no mapa para navio
    std::map<std::pair<int, int>, Navio *> mapeamento;

    // Preenche mapeamento de navios
    void mapear();

    // Vetor de representação preenchido de espacos vazios
    void limparRepresentacao();

    // Define a vida de todos os navios como maxima
    void configurarVida();

    // Retorna verdadeiro se entre as dadas posicoes e possivel botar um navio
    bool coordenadasValidas(int x1, int y1, int x2, int y2);

    // Tenta botar navio no mapa, retorna falso caso nao consiga
    bool botarNavio(Navio * navio);

    // Aloca na memoria o tipo de navio e retona o ponteiro para ele (isso para evitar
    // a criação de varios vetore de classes para cada classe filha)
    Navio * alocarNavio(int tipo);

    static std::vector<std::string> ataquesFalhos;

    static std::vector<std::string> ataquesNaAgua;

    // Map que associa direcoes cardinais de string pra int e de int para string
    // E associa tipos de navios de int para string e de string para int 
    static std::map<std::string, int> stringOrientacao;

    static std::map<std::string, int> stringTipo;

    static std::map<int, std::string> intOrientacao;

    static std::map<int, std::string> intTipo;
 
 public:

    Mapa();
    ~Mapa();

    // Tenta colocar navio em mapa
    bool inserirNavio(const int x, const int y, const int tipo, const int direcao);

    // Remove ultimo navio criado
    void removerUltimo();

    // Seta nome do arquivo do mapa
    bool setNome(std::string nome);

    // Retorna nome do arquivo do mapa
    std::string getNome();
    
    // Remove navio mortou do vetor navios, e mapeamento
    void navioMorreu(Navio * navio);

    // Retorna largura do mapa
    int getLargura();

    // Retorna altura do mapa
    int getAltura();

    // Retorna o numero de navios no mapa
    int getNumeroDeNavios();

    // Tranforma arquivo .mapa em vetor de navios
    bool abrirMapa(std::string nome);

    // Cria / Atualiza arquivo de mapa
    void salvaMapa();

    // Deleta arquivo de mapa
    bool destroiMapa();

    // Processa ataque no mapa e retorna string de descicao do ataque
    std::string ataque(const int x, const int y, Navio * inimigo, const int dano, bool emMassa = false);

    // Retorna representacao bidimensional de mapa
    std::vector<std::string> * mostrarMapa();

    // Define altura e largura de mapa
    void setLarguraEAltura(const int largura, const int altura);

    // Cria mapa aleatorio
    void gerarMapa(const int numero_de_navios);

    // Retorna um ponteiro para o navio do ataque
    Navio * algumNavio();

    // Remove navios com vida menor ou igual a 0
    void removerMortos();

    // Retona um mapa dos ataques dados e navios revelados
    std::vector<std::string> * mostrarMapaDeJogo();

    // Configura vida do navios e mapea navios na estrutura map
    void configurarJogo();

};

#endif