#include <cstdlib> // rand
#include <time.h> // time
#include <fstream> //ifstream
#include <map> // map

#include "../inc/helpers.hpp"

// Para deixar mais aleatorios os resultados
void seedAleatoria(){
    static int x = 0;
    x = (x + time(NULL) % 10000) % 100000;
    srand(x);
}

// Essa funcao evita divisao por 0, portanto nao acontece floating point exception quando chamada
int randInt(int l, int r){

    if(r < l or l < 0 or r < 0)
        return 0;

    seedAleatoria();
    return rand() % (r - l + 1) + l;
}

bool arquivoExiste(const std::string& nome) {

    std::ifstream arquivo(nome);
    return arquivo.good();

}