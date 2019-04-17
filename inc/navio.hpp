#ifndef NAVIO
#define NAVIO

#include <string> // string
#include <utility> // pair

class Navio{

protected:

    // Vida atual do navio, 0 = morto
    int vida;

    // Valor maximo de vida de um navio
    int maxVida;

    // Caractere que representa navio no mapa
    char caractere;

    // Aponta posicao do player foi compromissada
    bool amocado;

public:

    // Numero de quadrados do navio
    int tamanho;
    
    // Direcao cardinal 0 = sul, 1 = leste, 2 = norte, 3 = oeste
    int orientacao;

    // String de tipo do navio
    std::string tipo;

    // X no eixo de coordenadas
    int x;

    // Y no eixo de coordenadas
    int y;

    Navio();
    virtual ~Navio() = default;
    
    // Uma funcao especifica para cada tipo de navio
    // em que ele tem uma chance baseada em fatores
    // que variam de caso a caso de evitar um ataque
    // Classes filho tem suas proprias implementacoes
    // dessa funcao para dado ataque
    // string = descricao do ataque
    // int 1 = dano ao proprio navio
    // int 2 = contrataque
    // Dessa forma, o ataque de todos os navios e
    // processado pela mesma funcao mas sao diferentes
    virtual std::pair<std::string, std::pair<int, int>> processa(int * dano) = 0;

    // Retorna o numero identificador do navio
    virtual int getTipo()=0;

    // Processa o ataque e retorna status
    std::string ataque(int * dano, Navio * inimigo);

    // Retorno verdadeiro se navio esta vivo e falso caso contrario
    bool estaVivo();

    // Altera vida do navio
    void setVida(const int delta);

    // Define direcao do navio
    void setOrientacao(const int orientacao);

    // Retorna caractere que representa navio no mapa
    char representacao();

    // Navio se esconde
    void amocar();

    // Navio aparece
    void desamocar();

    // Retorna se navio esta visivel para o adversario
    bool getAmocado();

    // Retorna vida maxima do navio
    int getMaxVida();

};

#endif