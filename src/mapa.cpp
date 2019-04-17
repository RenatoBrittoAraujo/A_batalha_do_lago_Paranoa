#include <fstream> // ifstream, ofstream
#include <vector> // vector
#include <string> // string
#include <algorithm> // tranform, swap
#include <sstream> // stringstream
#include <map> // map
#include <cstdio> // remove
#include <utility> // pair

#include "../inc/mapa.hpp"
#include "../inc/navio.hpp"
#include "../inc/navios.hpp"
#include "../inc/helpers.hpp"

// Ataque falhou! ...
std::vector<std::string> Mapa::ataquesFalhos({

    "O ataque atigiu a ponte JK e uma parte dela caiu.",
    "O ataque atingiu o congresso e matou o presidente da republica.",
    "O ataque atingiu uma senhora de idade no parque da cidade.",
    "O ataque dizimou uma população de capivaras.",
    "O botao emperrou e nenhum ataque aconteceu",
    "A ONU interviu no ataque e ele foi cancelado por decisao unanime do comite.",
    "O ataque atingiu a UnB e uma parte do minhocao foi destruida.",
    "Por falta de licensa para disparar, o ataque foi proibido pela policia federal.",
    "O vaticano convenceu o ataque a nao acontecer.",
    "Donald Trump contruiu um muro ao redor do ataque, negando ele.",
    "O ataque desistiu e foi embora."

});

// Ataque caiu na agua e ...
std::vector<std::string> Mapa::ataquesNaAgua({

    "matou alguns peixes.",
    "acertou um Jet Ski.",
    "matou um banhista. Seu velorio e amanha.",
    "e sera desenterrado num futuro distante por povos mais avancados.",
    "causou um tsunami que alagou o Pontao.",
    "poluiu patrimonio publico.",
    "se afogou.",
    "foi rapidamente removido pelo esquadrao anti-bombas.",
    "se molhou.",
    "ficou la mesmo.",
    "boiou ate o lago corumba",
    "foi encontrado por um assasino em massa. Parabens, agora pessoas vao morrer e a culpa e sua.",
    "descobriu que na verdade era um peixe e foi nadar."

});

// Os maps abaixo evitam if's

std::map<std::string, int> Mapa::stringOrientacao({

    {"sul", SUL},
    {"norte", NORTE},
    {"leste", LESTE},
    {"oeste", OESTE}

});

std::map<std::string, int> Mapa::stringTipo({

    {"porta_teco_teco", T_Porta_teco_teco},
    {"iate", T_Iate},
    {"prancha_de_sup", T_Prancha_de_sup}

});

std::map<int, std::string> Mapa::intOrientacao({

    {SUL, "sul"},
    {NORTE, "norte"},
    {LESTE, "leste"},
    {OESTE, "oeste"}

});

std::map<int, std::string> Mapa::intTipo({

    {T_Porta_teco_teco, "porta_teco_teco"},
    {T_Iate, "iate"},
    {T_Prancha_de_sup, "prancha_de_sup"}

});

Mapa::Mapa(){

    nome = "";

}

// Por precaucao, deleta todos os enderecos de navios
Mapa::~Mapa(){

    for(auto navio: navios){

        delete navio;

    }

}

// Retorna true se navio esta dentro dos bounds do mapa
bool Mapa::posicaoValida(const int x, const int y, const int tamanho, const int direcao){

    auto calculo = posicaoFinal(x, y, direcao, tamanho);

    if(limiteCheck(x, y) or limiteCheck(calculo.first, calculo.second))
        return false;
    
    return true;

}

// Aloca memoria de navio
Navio * Mapa::alocarNavio(const int tipo){

    Navio * ponteiro;

    if(tipo == T_Porta_teco_teco)
        ponteiro = new Porta_teco_teco;

    if(tipo == T_Iate)
        ponteiro = new Iate;

    if(tipo == T_Prancha_de_sup)
        ponteiro = new Pracha_de_SUP;

    return ponteiro;

}

// Tenta botar um navio novo com dadas especificacoes,
// se da errado, retorna false, caso contrario cria a bota no vetor navios
bool Mapa::inserirNavio(const int x, const int y, const int tipo, const int direcao){

    Navio * novo = alocarNavio(tipo);

    novo->x = x;
    novo->y = y;
    novo->orientacao = direcao;

    if(botarNavio(novo)){

        navios.push_back(novo);
        return true;

    }else{

        delete novo;
        return false;

    }
}

// Tranforma arquivo .mapa em array de navios
bool Mapa::abrirMapa(std::string nome){

    std::string caminho = "./doc/" + nome + ".mapa";

    if(!arquivoExiste(caminho))
        return false;

    this->nome = nome;

    std::ifstream leitura;
    leitura.open(caminho);

    std::string dados;

    altura = largura = 0;

    while(!leitura.eof()){

        std::getline(leitura, dados);

        // Comentario
        if(dados[0] == '#' or dados.empty()){
            continue;
        }

        // L ...
        if(dados.substr(0, 2) == "L "){
            largura = std::stoi(dados.substr(2));

            if(largura != 0 and altura != 0)
                limparRepresentacao();

            continue;
        }   

        // A ...
        if(dados.substr(0, 2) == "A "){
            altura = std::stoi(dados.substr(2));

            if(largura != 0 and altura != 0)
                limparRepresentacao();

            continue;
        } 

        // Tranforma leitura em minuscula
        std::transform(dados.begin(), dados.end(), dados.begin(), ::tolower);

        // Se 'FIM', para de ler
        if(dados == "fim")
            break;

        int direcao, x, y;
        std::string tipo = dados;

        std::stringstream ss;

        std::getline(leitura, dados);

        ss << dados;

        ss >> x >> y;

        std::getline(leitura, dados);

        std::transform(dados.begin(), dados.end(), dados.begin(), ::tolower);

        direcao = stringOrientacao[dados];

        // Tenta inserir navio
        // teoricamente, se o mapa for feito usando o proprio programa
        // nunca retorna falso essa funcao, mas ela esta ai por questoes de resiliencia
        inserirNavio(x, y, stringTipo[tipo], direcao);

    }

    leitura.close();

    return true;

}

// Salva mapa no doc/
void Mapa::salvaMapa(){

    destroiMapa();

    std::ofstream arquivo;

    arquivo.open("./doc/" + nome + ".mapa");

    arquivo << "# Numero de navios: " << getNumeroDeNavios() << std::endl << std::endl;

    arquivo << "# Largura\n";

    arquivo << "L " << largura << std::endl << std::endl;

    arquivo << "# Altura\n";

    arquivo << "A " << altura << std::endl << std::endl;

    for(auto navio: navios){

        arquivo << navio->tipo << std::endl;

        arquivo << navio->x << ' ' << navio->y << std::endl;

        arquivo << intOrientacao[navio->orientacao] << std::endl << std::endl;

    }

    arquivo << "FIM\n";

    arquivo.close();

}

// Apaga arquivo de mapa
bool Mapa::destroiMapa(){

    return !std::remove(("./doc/" + nome + ".mapa").c_str());

}

// Calcula posicao final dado o tamanho do navio e a direcao para onde ele esta virado
std::pair<int, int> Mapa::posicaoFinal(const int x, const int y, const int orientacao, int tamanho){
        
        int x_final = x, y_final = y;

        tamanho--;

        switch(orientacao){
            
            case SUL:
                y_final = y - tamanho;
                break;

            case NORTE:
                y_final = y + tamanho;
                break;

            case LESTE:
                x_final = x + tamanho;
                break;

            case OESTE:
                x_final = x - tamanho;
                break;

        }

        return {x_final, y_final};
}

// Testa se coordenada esta no mapa
bool Mapa::limiteCheck(const int x, const int y){

    return (x < 1 or x > largura or y < 1 or y > altura);

}

// Gera representacao vazia de mapa
void Mapa::limparRepresentacao(){

    representacao.clear();

    for(int i = 0; i < altura + 1; i++){
        
        std::string linha(largura + 1, '~');
        representacao.push_back(linha);

    }

}

// Retorna true se sobre dado conjunto de coordenadas nao existe nada alem de agua
bool Mapa::coordenadasValidas(int x_1, int y_1, int x_2, int y_2){

    for(int i = std::min(x_1, x_2); i <= std::max(x_1, x_2); i++)
        for(int j = std::min(y_1, y_2); j <= std::max(y_1, y_2); j++)
            if(representacao[j][i] != '~')
                return false;

    return true;

}

// Tenta botar navio e retona o successo
bool Mapa::botarNavio(Navio * navio){

    int x = navio->x;
    int y = navio->y;

    auto posicao_final = posicaoFinal(x, y, navio->orientacao, navio->tamanho);

    int lx = posicao_final.first;
    int ly = posicao_final.second;

    if(limiteCheck(x, y) or limiteCheck(lx, ly))
        return false;

    if(!coordenadasValidas(x, y, lx, ly))
        return false;

    for(int i = std::min(x, lx); i <= std::max(x, lx); i++)
        for(int j = std::min(ly, y); j <= std::max(ly, y); j++)
            representacao[j][i] = navio->representacao();

    return true;
}

// Cria nova representacao de mapa e retorna seu endereco para ser printada
std::vector<std::string> * Mapa::mostrarMapa(){

    limparRepresentacao();

    for(auto navio: navios){

        botarNavio(navio);

    }
            
    return &representacao;

}

void Mapa::setLarguraEAltura(const int largura, const int altura){

    this->largura = largura;
    this->altura = altura;

}

// Tenta botar navios aleatorios no mapa ate conseguir todos ou pular pro proximo se nao conseguiu
void Mapa::gerarMapa(const int numero_de_navios){

    limparRepresentacao();

    for(int i = 0; i < numero_de_navios; i++){ 

        int repeticoes = 0;
        bool valido = false;

        while(repeticoes < 100){

            int x = randInt(1, largura);
            int y = randInt(1, altura);
            int orientacao = randInt(SUL, OESTE);
            int tipo = randInt(1, 3);

            valido = inserirNavio(x, y, tipo - 1, orientacao);

            if(valido)
                break;

            repeticoes++;

        }
    }

}

bool Mapa::setNome(std::string nome){

    if(!this->nome.empty())
        return false;
    
    this->nome = nome;
    return true;

}

std::string Mapa::getNome(){

    return nome;

}

int Mapa::getLargura(){

    return largura;

}

int Mapa::getAltura(){

    return altura;

}

int Mapa::getNumeroDeNavios(){

    return (int) navios.size();

}

void Mapa::removerUltimo(){

    if(!navios.empty()){

        delete navios.back();
        navios.pop_back();

    }
}

// Acha o ponteiro do navio que esta nas coordenadas x e y (se tiver)
Navio * Mapa::encontrarCoordenada(const int x, const int y){

    Navio * alvo = mapeamento[{x, y}];

    if(alvo == NULL or !alvo->estaVivo())
        return NULL;

    return alvo;

}

// Processa o ataque
std::string Mapa::ataque(const int x, const int y, Navio * inimigo, const int dano, bool emMassa){

    Navio * atingido = encontrarCoordenada(x, y);

    // Se o ataque for em massa, so sting relevante se houver algum dano nos adversarios
    if(atingido == NULL and emMassa)
        return "";

    std::string resultado;

    bool deuCerto = true;

    // 1/10 chance de ataque falhar
    if(!randInt(0, 10) and !emMassa)
        resultado = "Ataque falhou! " + ataquesFalhos[randInt(0 , (int)ataquesFalhos.size() - 1)];

    // Se atingir agua
    else if(atingido == NULL and !emMassa)
        resultado = "Ataque atingiu a agua e " + ataquesNaAgua[randInt(0 , (int)ataquesNaAgua.size() - 1)];

    else{

        resultado += atingido->ataque(dano, inimigo);

        // Se morreu o navio alvo
        if(!atingido->estaVivo()){

            resultado += " A embarcao explodiu em chamas e todos tiveram uma morte lenta e dolorosa!";
            navioMorreu(atingido);

        }

        // Se morreu o atacante no contra-ataque
        if(!inimigo->estaVivo())
            resultado += " O contra-ataque do inimigo matou todos na embarcação do atacante!";

    }

    // Guarda as coordenadas do ultimo ataque para ser representada no mapa
    if(deuCerto and !emMassa)
        ultimos_ataques.push_back({x, y});
    
    // Se houver mais de tres coordenadas guardadas, apaga mais velha
    if(ultimos_ataques.size() > 3 and !emMassa)
        ultimos_ataques.erase(ultimos_ataques.begin());

    return resultado;

}

// Navio aleatorio de mapa
Navio * Mapa::algumNavio(){

    return navios[randInt(0, (int)navios.size() - 1)];

}

// Cria nova representacao de jogo do mapa
std::vector<std::string> * Mapa::mostrarMapaDeJogo(){

    mapa_de_jogo.clear();

    for(int i = 0; i <= altura; i++)
        mapa_de_jogo.push_back(std::string(largura + 1, '~'));

    // Mostra ultimos ataques
    for(auto ataque: ultimos_ataques){

        mapa_de_jogo[ataque.second][ataque.first] = 'X';

    }

    // Mostra navios nao escondidos
    for(auto navio: navios){

        if(!navio->getAmocado()){

            navioNoJogo(navio);

        }

    }

    return &mapa_de_jogo;

}

// Printa representacao do navio se ele estiver visivel para o inimigo no mapa de jogo
void Mapa::navioNoJogo(Navio * navio){

    int x = navio->x;
    int y = navio->y;

    auto posicao_final = posicaoFinal(x, y, navio->orientacao, navio->tamanho);

    int lx = posicao_final.first;
    int ly = posicao_final.second;

    for(int i = std::min(x, lx); i <= std::max(x, lx); i++)
        for(int j = std::min(ly, y); j <= std::max(ly, y); j++)
            mapa_de_jogo[j][i] = navio->representacao();

}

// Preenche estrututa map de ponteiros para navios dado coordenadas
void Mapa::mapear(){

    for(auto navio: navios){

        int x = navio->x;
        int y = navio->y;

        auto posicao_final = posicaoFinal(x, y, navio->orientacao, navio->tamanho);

        int lx = posicao_final.first;
        int ly = posicao_final.second;

        for(int i = std::min(x, lx); i <= std::max(x, lx); i++)
            for(int j = std::min(ly, y); j <= std::max(ly, y); j++){
                mapeamento[{i, j}] = navio;
            }
    }
}

// Apaga navio da estrutura map e da array navios
void Mapa::navioMorreu(Navio * navio){

    mapeamento.erase(mapeamento.find({navio->x, navio->y}));

    navios.erase(std::find(navios.begin(), navios.end(), navio));

}

void Mapa::configurarVida(){

    for(auto navio: navios){

        navio->setVida(navio->getMaxVida());

    }

}

void Mapa::configurarJogo(){

    configurarVida();
    mapear();

}