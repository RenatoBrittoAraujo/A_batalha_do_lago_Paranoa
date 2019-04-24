#ifndef HELPERS
#define HELPERS


// Gera seed para numero aleatorio da rand()
void randomSeed();

// Gera inteiro aleatorio entre [l - r] intervalo inclusivo
int randInt(int l = 0, int r = 1);

// Retorna true se arquivo existe e falso caso contrario
bool arquivoExiste(const std::string& nome);

// Enumeracoes para facilitar entendimento do codigo
// Sim, eu sei, variaveis globais sao feias

// Orientacoes cardinais
enum orientacoes {SUL, LESTE, NORTE, OESTE};

// Tipos de navios
enum tipos {T_Iate, T_Porta_teco_teco, T_Prancha_de_sup, T_Dois_caras_numa_moto, T_Jet_Ski, T_Caravela, T_Espaco_nave, T_FBI};

// Enumeracoes do menu de jogo
enum acoes{SAIR_DO_JOGO, ATAQUE_COMUM, ATAQUE_EM_AREA, CURAR_NAVIO, MISSEL_TELEGUIADO, RELEVAR_POSICAO};

#endif