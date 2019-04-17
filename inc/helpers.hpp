#ifndef HELPERS
#define HELPERS

#include <map> // map

// Gera seed para numero aleatorio da rand()
void randomSeed();

// Gera inteiro aleatorio entre [l - r] intervalo inclusivo
int randInt(int l = 0, int r = 1);

// Retorna true se arquivo existe e falso caso contrario
bool arquivoExiste(const std::string& nome);

// Enumeracoes para facilitar entendimento do codigo
// Sim, eu sei, variaveis globais sao feias

enum orientacoes {SUL, LESTE, NORTE, OESTE};

enum tipos {T_Iate, T_Porta_teco_teco, T_Prancha_de_sup};

#endif