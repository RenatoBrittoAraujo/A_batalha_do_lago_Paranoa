#include <string> // string
#include <utility> // pair
#include <vector> // vector
#include <algorithm> // min

#include "../inc/navio.hpp"
#include "../inc/navios.hpp"
#include "../inc/helpers.hpp"

// Nomes nada-ve para as embarcacoes
std::vector<std::string> Porta_teco_teco::nomes_de_embarcacoes({
    "Jaraguiricaratauba",
    "Tabajaraguaramalapaula",
    "Piracicubajiraguirupa",
    "Guaripajagurajiguar",
    "Caranautacaraguara",
    "Agarataurabuba",
    "Tiricaticurica",
    "Cacibalubiba",
    "Jiripocavaipiar",
    "Jaguariuna",
    "Jeguejonga",
});

// Os velejadores que lembrei na hora
std::vector<std::string> Caravela::nomes_de_velejadores({
    "Francis Chichester",
    "Ellen MacArthur",
    "Robin Knox-Johnston",
    "Ernest Henry Shackleton",
    "James Cook",
    "Cristovao Colombo",
    "Pedro Alvares Carabral"
});

// Todos os bairros de brasilia
std::vector<std::string> Dois_caras_numa_moto::quebradas({
    "Aguas Claras",
    "Asa Norte",
    "Asa Sul",  
    "Guara 1",
    "Guara 2", // <==== Esse bairro aqui claramente e o melhor
    "Brazlandia",
    "Ceilandia",
    "Cruzeiro",
    "Gama",
    "Lago Norte",
    "Lago Sul",
    "Nucleo Bandeirante",
    "Sudoeste",
    "Paranoa",
    "Planaltina",
    "Park Way",
    "Ponte Alta",
    "Recanto",
    "Riacho Fundo",
    "Samabaia",
    "Santa Maria",
    "Sao Sebas"    
});

/*
    Como a estrutura de todas as classes filhas tem a mesma cara, vou explicar so uma

    No caso o porta teco teco tem 3 atributos unicos, tecotecos, competencia e nome da embarcacao

*/

Porta_teco_teco::Porta_teco_teco(){

    tipo = "porta_teco_teco"; // Para guaradar na hora de salvar
    tamanho = 4; // Tamanho da embarcacao
    caractere = '#'; // Sua representacao no mapa
    maxVida = 150; // Sua vida maxima
    competencia = randInt(1, 10); // Seu atributo unico
    tecotecos = randInt(8, 12); // Seu outro atributo unico
    nome = nomes_de_embarcacoes.at(randInt(0, nomes_de_embarcacoes.size() - 1)); // Nome da embarcao (escrachado porque eu acho mto feio os nomes que o exercito
    amocado = false; // Sempre visivel no mapa                                                        braileiro bota nos navios, avioes, tanques e etc...)

}

std::pair<std::string, std::pair<int ,int>> Porta_teco_teco::processa(const int dano){

    std::string status;
    int delta;
    int contrataque = 0;

    status = "Os bravos guerreiros da embarcacao " + nome + ", as margens do Paranoa, ";

    delta = dano;

    // Chance de seu atributo unico entrar em acao
    if(randInt(0, 30) < tecotecos){
        delta = 0;
        status += "defenderam o ataque.";
    }else
        status += "foram atacados covardemente e perderam " + std::to_string(delta) + " de vida. Agora tem " + std::to_string(std::max(0, vida - delta)) + ".";

    // Chance do seu outro atributo unico entrar em acao
    if(competencia > randInt(0, 30)){
        contrataque = competencia;
        status += " E os bravos e competentes guerreiros da FAB causaram " + std::to_string(contrataque) + " de dano em algum navio seu.";
    }

    competencia++;

    return {status, {delta, contrataque}};

}

Pracha_de_SUP::Pracha_de_SUP(){

    maxVida = 50;
    tamanho = 1;
    tipo = "prancha_de_sup";
    caractere = '0';
    remo = randInt(1, 3);
    amocado = true;

}

std::pair<std::string, std::pair<int, int>> Pracha_de_SUP::processa(const int dano){

    std::string status;
    int delta;

    if(randInt(0, remo) == remo){

        status = "Prancha de SUP defletiu seu ataque com remo!";
        remo++;
        delta = 0;

    }else{

        // Vale lembrar que nenhum navio vai sumir de mapa depois de mostrado
        // nem ser mostrado aleatoriamente
        // ele so vai ser mostrado se ele estiver escondido e e alvo de alguma acao

        if(amocado)
            amocado = !(randInt(1, 5) == 4);

        status = std::string(!amocado ? ("Atingiu uma Prancha de SUP") : ("Atigiu um navio desconhecido")) + 
                " e causou " + std::to_string(dano) + " de dano!";
        delta = dano;

    }

    return {status, {delta, 0}};

}

Iate::Iate(){

    tipo = "iate";
    fama = randInt(0, 100);
    ePolitico = (bool)randInt(0, 5);
    dinheiro = randInt(10, 100) + (ePolitico ? 50 : 0);
    maxVida = 100;
    caractere = 'H';
    tamanho = 2;
    amocado = !ePolitico;

}

std::pair<std::string, std::pair<int ,int>> Iate::processa(const int dano){

    std::string status;
    int delta = 0;
    int contrataque = 0;

    delta = (dano * 50) / dinheiro;

    if(ePolitico){

        delta = std::max(delta - 5, 0);

        status = "Iate de politico e atacado e perde " + std::to_string(delta) + " de vida.";

        if(randInt(0, 1)){
            status += " Politico abre inquerito e tira 10 de vida de algum navio seu.";
            contrataque = 10;
        }

    }else{

        if(amocado)
            amocado = !((randInt(0, 100) <= fama));

        status = std::string(!amocado ? ("Atingiu um Iate") : "Atigiu um navio desconhecido") + 
                " e causou " + std::to_string(delta) + " de dano!";

    }

    return {status, {delta, contrataque}};

}

JetSki::JetSki(){

    maxVida = 30;
    tamanho = 1;
    tipo = "jet_ski";
    caractere = '@';
    amocado = true;
    turbo = randInt(0, 1);

}

std::pair<std::string, std::pair<int, int>> JetSki::processa(const int dano){

    std::string status;
    int delta;

    if(turbo){

        status = "Jet Ski saiu correndo e fugiu do seu ataque.";
        turbo = false;
        delta = 0;

    }else{

        if(amocado)
            amocado = !(randInt(1, 6) == 4);

        status = std::string(!amocado ? ("Atingiu um Jet Ski") : ("Atigiu um navio desconhecido")) + 
                " e causou " + std::to_string(dano) + " de dano!";
        delta = dano;

        turbo = !randInt(0, 4);

    }

    return {status, {delta, 0}};

}

Caravela::Caravela(){

    maxVida = 100;
    tamanho = 3;
    tipo = "caravela";
    caractere = '8';
    amocado = true;
    especiarias = randInt(0, 10);
    velejador = nomes_de_velejadores[randInt(0, (int)nomes_de_velejadores.size() - 1)];

}

std::pair<std::string, std::pair<int, int>> Caravela::processa(const int dano){

    std::string status;
    int delta;

    if(amocado)
        amocado = !(randInt(1, 3) == 4);

    delta = dano;

    if(especiarias > randInt(4, 11)){

        status = "A incrivel habilidade maritima de " + velejador + " evitou o ataque e foi direto pra novo mundo vender especiarias\n";
        especiarias--;
        delta = 0;

    }else{

        status = std::string(!amocado ? ("Atingiu uma Caravela, fazendo " + velejador + " ficar muito triste com voce") : ("Atigiu um navio desconhecido")) + 
                " e causou " + std::to_string(dano) + " de dano!";
        delta = dano;

    }

    return {status, {delta, 0}};

}

Espaco_nave::Espaco_nave(){

    maxVida = 120;
    tamanho = 1;
    tipo = "espaco_nave";
    caractere = '+';
    amocado = false;
    tecnologia = randInt(1, 10);
    tamanho = 5;
    vogons = !randInt(0, 10);

}

std::pair<std::string, std::pair<int, int>> Espaco_nave::processa(const int dano){

    std::string status;
    int delta = dano;
    int contrataque = 0;

    if(vogons){

        amocado = false;
        delta = dano * 1.5;

        status = "Voce acertou uma nave de VOGONS e causou " + std::to_string(delta) + " de dano! Eles ficaram levemente irritados com esse fato que resolveram destruir a terra para passar uma estrada intergalatica no caminho. Mas desistiram e matar um navio seu.";

        contrataque = 10000;

    }else{

        if(amocado)
            amocado = !(randInt(1, 6) == 4);

        delta = std::min(tecnologia * randInt(1, 10), dano - 5);

        status = std::string(!amocado ? ("Atingiu uma Espaco Nave") : ("Atigiu um navio desconhecido")) + 
                 std::string(" e causou " + std::to_string(dano) + " de dano! Porem a tecnologia altissima da espaco nave recuperou " + std::to_string(delta) + " de vida.");
        
        delta = dano - delta;

    }

    return {status, {delta, contrataque}};

}

Dois_caras_numa_moto::Dois_caras_numa_moto(){

    maxVida = 10;
    tamanho = 1;
    tipo = "dois_caras_numa_moto";
    caractere = '$';
    amocado = true;
    quebrada = randInt(0, 100);
    nome_da_quebrada = quebradas[randInt(0, (int)quebradas.size() - 1)];

}

std::pair<std::string, std::pair<int, int>> Dois_caras_numa_moto::processa(const int dano){

    std::string status;
    int delta = dano;

    if(amocado)
        amocado = !(randInt(1, 3) == 1);

    status = std::string(!amocado ? ("Tu meteu o loco pra cima dos irmaozinho de " + nome_da_quebrada) : ("Atigiu um navio desconhecido")) + 
            " e causou " + std::to_string(dano) + " de dano!";

    int mermaoCeTaLoco = 0;

    if(quebrada){

        mermaoCeTaLoco = quebrada;

    }

    return {status, {delta, mermaoCeTaLoco}};

}

FBI::FBI(){

    maxVida = 60;
    tamanho = 2;
    tipo = "fbi";
    caractere = '?';
    amocado = true;
    EspioesRussos = !randInt(0, 10);

}

std::pair<std::string, std::pair<int, int>> FBI::processa(const int dano){

    std::string status;
    int delta;
    int contrataque = 0;

    if(EspioesRussos){

        status = "Ola, aqui e o governo russo para te informar que voce acertou um espiao nosso. Nos nao toleramos isso, um navio seu sera destruido. Gloria a Putin.";
        delta = 10000;
        contrataque = 10000;

    }else{

        status = std::string("Atigiu um navio desconhecido") + 
                " e causou " + std::to_string(dano) + " de dano!";

        delta = dano;

    }

    return {status, {delta, contrataque}};

}

int Iate::getTipo(){

    return T_Iate;

}

int Pracha_de_SUP::getTipo(){

    return T_Prancha_de_sup;

}

int Porta_teco_teco::getTipo(){

    return T_Porta_teco_teco;

}

int FBI::getTipo(){

    return T_FBI;

}

int Caravela::getTipo(){

    return T_Caravela;

}

int Dois_caras_numa_moto::getTipo(){

    return T_Dois_caras_numa_moto;

}

int JetSki::getTipo(){

    return T_Jet_Ski;

}

int Espaco_nave::getTipo(){

    return T_Espaco_nave;

}