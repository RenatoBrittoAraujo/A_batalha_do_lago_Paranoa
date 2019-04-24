#include <string> // string
#include <iostream> // cin, cout
#include <unistd.h> // usleep
#include <algorithm>

#include "../inc/mapa.hpp"
#include "../inc/jogo.hpp"
#include "../inc/GUI_jogo.hpp"
#include "../inc/helpers.hpp"

std::vector<std::string> GUI_jogo::nomes_estranhos({
    "CARLAO_BORRACHA",
    "Maicon Jekson",
    "XxX-MENOR-PROBLEMA-XxX",
    "Notlim Esoj",
    "Cleber",
    "Maicon",
    "Geraldo",
    "John Lenon",
    "Cristiano Ronaldo",
    "Madonna",
    "Faustao",
    "Erastotenes",
    "Platao",
    "Aristoteles",
    "Pitagoras",
    "Tales de Mileto",
    "Nietzche",
    "Richard Feymann",
    "Carl Sagan",
    "Linus Torvald",
    "Wernher von Braun",
    "Albert Einstein",
    "Isaac Newton",
    "Marie Curie",
    "Stephen Hawkings"
});

void GUI_jogo::escolherMapa(Mapa * player, const int id_player){

    limpaTela();
    quebraLinha(2);
    formatarDist();

    std::cout<<"Selecao do mapa do player "<<id_player<<":\n";
    
    listarMapas(true);

    std::string selecao = "";

    while(true){

        while(!arquivoExiste("./doc/" + selecao + ".mapa")){

            formatarDist();
            std::cout<<"Selecao: ";
            std::getline(std::cin, selecao);

        }
        
        if(player->abrirMapa(selecao))
            break;
        
        else{
            formatarDist();
            std::cout<<"Aconteceu um erro, escolha de novo\n";
        }
    }
    
    formatarDist();
    std::cout<<"Mapa lido com sucesso!\n";

    player->configurarJogo();
    jogo.limparCooldown(id_player);

    usleep(1000000);
}

void GUI_jogo::escolherNome(const int player){

    quebraLinha(2);

    std::string selecao = "";

    formatarDist();

    std::cout<<"Selecao de nome do player "<<player<<": ";
    std::getline(std::cin, selecao);

    jogo.setNome(selecao, player);

}

void GUI_jogo::geracaoDeMapa(){

    limpaTela();
    quebraLinha();
    
    int largura = 0, altura = 0;

    while(largura < 1 or largura > 30){

        formatarDist();
        std::cout<<"Largura do mapa (1 ate 30): ";
        std::cin>>largura;

    }  

    quebraLinha(2);

    while(altura < 1 or altura > 30){

        formatarDist();
        std::cout<<"Altura do mapa (1 ate 30): ";
        std::cin>>altura;

    }

    jogo.getPlayer(1)->setLarguraEAltura(largura, altura);
    jogo.getPlayer(2)->setLarguraEAltura(largura, altura);

    int numero_de_navios = 0;

    int maximo_de_navios = jogo.getAltura(1) * jogo.getLargura(1);

    quebraLinha(2);

    while(numero_de_navios > maximo_de_navios or numero_de_navios < 1){

        formatarDist();
        std::cout<<"Numero de navios desejado entre [1 - "<<maximo_de_navios<<"]: ";
        std::cin>>numero_de_navios;

    }

    jogo.getPlayer(1)->gerarMapa(numero_de_navios);
    jogo.getPlayer(2)->gerarMapa(numero_de_navios);

    jogo.getPlayer(1)->configurarJogo();
    jogo.getPlayer(2)->configurarJogo();

    jogo.limparCooldown(1);
    jogo.limparCooldown(2);

}

void GUI_jogo::configurarPartida(){

    limpaTela();
    quebraLinha();
    printaTitulo();

    int danoMaximo = 0;

    formatarDist();
    std::cout<<"Dano Maximo define o quanto de\n";
    formatarDist();
    std::cout<<"dano/cura que as acoes causam. Quanto\n";
    formatarDist();
    std::cout<<"mais Dano Maximo, mais dinamico jogo,\n";
    formatarDist();
    std::cout<<"porem depende de sorte.\n";
    formatarDist();
    std::cout<<"Quanto menos Dano Maximo,\n";
    formatarDist();
    std::cout<<"mais estrategico fica o jogo.\n";

    quebraLinha(1);
    formatarDist();
    std::cout<<"100 e o modo padrao de jogo\n";

    quebraLinha(2);

    while(danoMaximo < 10 or danoMaximo > 1000){
        formatarDist();
        std::cout<<"Dano Maximo (10 - 1000): ";
        std::cin>>danoMaximo;
    }

    jogo.setMaxDano(danoMaximo);

    if(singlePlayer){

        quebraLinha(3);
        formatarDist();
        std::cout<<"Niveis da inteligencia vao de 1 a 3,\n";
        formatarDist();
        std::cout<<"quanto mais alto, mais dificil\n";
        

        int escolha = 0;

        quebraLinha(1);

        while(escolha < 1 or escolha > 3){
            
            formatarDist();
            std::cout<<"Dificuldade da Inteligencia: ";
            std::cin>>escolha;

        }

        jogo.setDificuldade(escolha);

    }

    limpaTela();
    quebraLinha();
    printaTitulo();
    quebraLinha();

    char escolherMapas = '0';

    while(escolherMapas != 'g' and escolherMapas != 'e'){

        formatarDist();
        std::cout<<"Deseja escolher mapas ou gerar\n";
        formatarDist();
        std::cout<<"mapas aleatorios? (E ou G) ";
        std::cin>>escolherMapas;
        escolherMapas = ::tolower(escolherMapas);

    }

    if(escolherMapas == 'g'){

        geracaoDeMapa();

        std::cin.ignore();

        escolherNome(1);

        if(singlePlayer)
            jogo.setNome("(AI) " + nomes_estranhos[randInt(0, (int)nomes_estranhos.size() - 1)], 2);
        else 
            escolherNome(2);

    }else{

        std::cin.ignore();

        escolherMapa(jogo.getPlayer(1), 1);

        escolherNome(1);

        escolherMapa(jogo.getPlayer(2), 2);
        
        if(singlePlayer)
            jogo.setNome("(AI) " + nomes_estranhos[randInt(0, (int)nomes_estranhos.size() - 1)], 2);

    }

    jogo.setNumeroDeNaviosInicial();

}

void GUI_jogo::escolherCoordenadas(int * x, int * y, const int player){

    while(*x < 1 or *x > jogo.getLargura(jogo.outroJogador(player))){
        

        std::cout<<"Coordenada X do ataque: ";
        std::cin>>*x;

    }

    while(*y < 1 or *y > jogo.getAltura(jogo.outroJogador(player))){

        std::cout<<"Coordenada Y do ataque: ";
        std::cin>>*y;

    }

}

bool GUI_jogo::turno(const int player){

    int x = 0, y = 0, escolha;

    std::string resultado = "FALHA";
    
    if(!singlePlayer or (singlePlayer and player == 1)){

        std::string noticia = "";

        while(resultado.substr(0, 5) == "FALHA"){

            limpaTela();
            quebraLinha(4);
            formatarDist();

            std::cout<<jogo.getNome(1)<<": "<<jogo.getNumeroDeNavios(1)<<" navio(s) | ";
            std::cout<<jogo.getNome(2)<<": "<<jogo.getNumeroDeNavios(2)<<" navio(s)"<<std::endl;
            quebraLinha(1);
            formatarDist();
            std::cout<<"Turno de "<<jogo.getNome(player)<<" | Pontuacao atual: "<<jogo.calcularPontuacao(player)<<std::endl;
            quebraLinha(2);

            printArray(jogo.getPlayer(jogo.outroJogador(player))->mostrarMapaDeJogo(), true);

            quebraLinha(2);

            if(!noticia.empty()){
                
                formatarDist();
                
                std::cout<<std::endl<<noticia<<std::endl;
            }

            quebraLinha(4);

            escolha = menuEscolha(&opcoes);

            if(escolha == 0)
                return true;

            if(escolha <= 2)
                escolherCoordenadas(&x, &y, player);

            resultado = jogo.processarAcao(x , y, player, escolha);

            if(resultado.substr(0, 5) == "FALHA"){
            
                quebraLinha(2);
                formatarDist();
                if(resultado.size() == 5)
                    noticia = "Aconteceu um erro inesperado, tente de novo";
                else
                    noticia = "Espere mais " + resultado.substr(5) + " turno(s) para poder usar esse ataque de novo";

                quebraLinha(1);

                x = y = 0;
            
            }

        }

    }else{

        limpaTela();
        quebraLinha(4);
        formatarDist();

        std::cout<<jogo.getNome(1)<<": "<<jogo.getNumeroDeNavios(1)<<" navio(s) | ";
        std::cout<<jogo.getNome(2)<<": "<<jogo.getNumeroDeNavios(2)<<" navio(s)"<<std::endl;
        quebraLinha(1);
        formatarDist();
        std::cout<<"Turno de "<<jogo.getNome(player)<<" | Pontuacao atual: "<<jogo.calcularPontuacao(player)<<std::endl;
        quebraLinha(2);

        printArray(jogo.getPlayer(jogo.outroJogador(player))->mostrarMapaDeJogo(), true);

        quebraLinha(2);

        formatarDist();
        std::cout<<"Processando turno de " + jogo.getNome(2) + "...\n";

        quebraLinha(5);

        usleep(1500000);

        resultado = jogo.turnoDeInteligencia();

    }

    jogo.diminuirCooldown(player);

    limpaTela();

    if(singlePlayer and player == 2){
        
        quebraLinha(4);
        formatarDist();
        std::cout<<"Acao da inteligencia: "<<jogo.getUltimaAcao()<<std::endl;
        quebraLinha(2);

    }else{

        quebraLinha(4);
        formatarDist();
        std::cout<<"Sua acao: "<<jogo.getUltimaAcao()<<std::endl;
        quebraLinha(2);


    }

    printArray(jogo.getPlayer(jogo.outroJogador(player))->mostrarMapaDeJogo(), true);
    
    quebraLinha(4);
    
    formatarDist();
    std::cout<<"------------ Resultado --------------\n\n";

    formatarDist();
    std::cout<<resultado<<std::endl;

    quebraLinha(2);

    travaDeLeitura();

    return false;

}

bool GUI_jogo::jogar(bool * vitoria){

    int player_atual = 1;

    bool sair = false;

    while(jogo.estaVivo(1) and jogo.estaVivo(2) and !sair){

        sair = turno(player_atual);

        player_atual = jogo.outroJogador(player_atual);

    }

    if(sair)
        return true;

    if(vitoria != NULL){

        *vitoria = jogo.estaVivo(1);

        return false;

    }

    limpaTela();
    quebraLinha();
    formatarDist();

    player_atual = std::max(player_atual, jogo.outroJogador(player_atual));

    if(!singlePlayer or (singlePlayer and player_atual == 2))
        std::cout<<jogo.getNome(player_atual)<<" perdeu todas suas embarcações!\n";
    else
        std::cout<<"Voce perdeu todas as suas embarcacoes\n";

    quebraLinha();

    usleep(2500000);

    limpaTela();
    quebraLinha();
    formatarDist();

    player_atual = jogo.outroJogador(player_atual);

    std::cout<<jogo.getNome(player_atual)<<" atingiu uma vitoria triufante na batalha sangrenta sobre os mares de Brasília!\n";

    quebraLinha(2);
    formatarDist();
    std::cout<<"Pontuacao: "<<jogo.calcularPontuacao(player_atual)<<std::endl;

    quebraLinha(4);
    

    if(!singlePlayer){
    
        usleep(2000000);

        char leitura = '0';
        while(leitura != 's' and leitura != 'n'){
        
            formatarDist();
            std::cout<<"Deseja salvar no scoreboard (S ou N)?: ";
            std::cin>>leitura;

        }

        if(leitura == 's'){
        
            jogo.salvarPontuacao(player_atual);
            quebraLinha(2);
            formatarDist();
            std::cout<<"Salvo!\n";
            usleep(1000000);
        
        }
        
    }else{
        
        travaDeLeitura();

    }

    return false;

}

bool GUI_jogo::tipoDeJogo(){

    limpaTela();
    quebraLinha();
    printaTitulo();
    quebraLinha(2);

    formatarDist();
    std::cout<<"Selecione o modo da partida:\n";

    quebraLinha(2);

    std::vector<std::string> opcoes = {
        "Single-player",
        "Multi-player",
        "Voltar para o menu principal"
    };

    enum {VOLTAR, SINGLE_PLAYER, MULTI_PLAYER};

    int escolha = menuEscolha(&opcoes);

    if(escolha == VOLTAR)
        return false;

    singlePlayer = !(escolha - 1);

    return true;

}

void GUI_jogo::modoHistoria(){

    limpaTela();
    quebraLinha();

    std::cout<<"                JOGUE COM O TERMINAL OCUPANDO TODA A TELA PARA UMA MELHOR EXPERIENCIA!\n\n\n\n";

    std::cout<<"        O ano e 2020, um futuro distopico onde a politica brasileira decaiu a puro pao e circo.\n";
    std::cout<<"    Todos os antigos rivais politicos da republica se uniram contra o bem estar do povo brasileiro.\n";
    std::cout<<"  Os politicos estao roubando cada vez mais de cofres publicos e fazendo cada vez mais mal para o pais.\n";
    std::cout<<"   Voce e um cidadao cansado da marmelada e resolveu se levantar e fazer justica com as proprias maos!\n\n";
    
    std::string preparado;
    formatarDist();
    std::cout<<"Esta preparado? (sim ou nao) ";
    std::cin>>preparado;
    std::transform(preparado.begin(), preparado.end(), preparado.begin(), ::tolower);
    
    if(!(preparado == "sim" or preparado == "s"))
        return;

    // SETUP DAS INFORMACOES DE JOGO

    std::vector<std::string> chefoes = {

        "Malafaia",
        "Arruda",
        "Roriz",
        "Sarney",
        "Lula",
        "Dilma",
        "Temer",
        "Bolsonaro",
        "Trump",
        "Daciolo" 

    };

    std::vector<std::string> descricao = {

        "Voce anda por brasilia atras de algum politico, ao chegar no lago paranoa se depara com Silas Malafaia num Iate!",

        "Silas ligou para seu grande amigo, Arruda, e ele veio trazendo pilotos da FAB!",

        "Roriz esta passando e viu a luta contra Arruda, como arruda lhe devia dinheiro, resolveu cobrar de voce!",

        "Sarney foi chamado ao saber que alguem amecava a politica suja brasileira!",

        "Lula, apos fugir da prisao e assitir um jogo do corinthians, resolveu chamar seus amigos da prisao contra voce!",

        "Chocada com a morte de seu pai Lula, Dilma Rouseff para de dar seu passeio de bicicleta e vem te atacar!",

        "Temer pegou um voo da Transilvania para Brasilia para tentar tomar seu sangue!",

        "O exercito brasileiro convocou todas as tropas e Bolsonaro em pessoa apareceu para lutar contra voce!",

        "Trump ficou chocado com seu poder belico e trouxe todo o exercito dos estados unidos para te parar!",

        "Donald Trump foi derrotado e o mundo finalmente foi liberado da tirania..."
    };

    // Configuracoes de modo historia

    singlePlayer = true;
    jogo.setMaxDano(100);
    jogo.setDificuldade(3);

    // Par = tamanho do mapa
    // Inteiro = numero_de_navios

    std::vector<std::pair<std::pair<int, int>, int>> mapa_player = {

        {{7,7}, 7},
        {{7,7}, 7},
        {{7,7}, 7},
        {{8,8}, 8},
        {{9,9}, 9},
        {{10,10}, 10},
        {{11,11}, 11},
        {{11,11}, 11},
        {{12,12}, 12},
        {{20,20}, 20}

    };
    
    std::vector<std::pair<std::pair<int, int>, int>> mapa_inimigo = {

        {{4,4}, 1},
        {{4,4}, 2},
        {{5,5}, 4},
        {{6,6}, 6},
        {{8,8}, 7},
        {{10,10}, 9},
        {{11,11}, 10},
        {{12,12}, 11},
        {{15,15}, 13},
        {{30,30}, 27}

    };
    
    quebraLinha();

    limpaTela();
    quebraLinha();

    formatarDist();
    std::cin.ignore();
    std::cout<<"Seu nome: ";
    std::string nome;

    std::getline(std::cin, nome);

    jogo.setNome(nome, 1);

    std::vector<std::string> carregando = {

        "Carregando politicos babacas",
        "Tentando nao ser processado",
        "Ficando puto com a situaco do pais",
        "Tentando levar politicos a serio",
        "Lembrando da eleicao",
        "Carregando pao e circo"

    };

    for(int i = 0; i < (int)carregando.size(); i++){

        usleep(randInt(5, 10) * 100000);
        limpaTela();
        quebraLinha();
        formatarDist();
        std::cout<<carregando[i] + "...\n";
        quebraLinha();

    }

    limpaTela();
    usleep(2000000);

    jogo.setNome(nome, 1);

    for(int i = 0; i < (int)chefoes.size(); i++){

        limpaTela();
        quebraLinha();
        formatarDist();
        std::cout<<descricao[i]<<std::endl;
        quebraLinha();
        travaDeLeitura();

        if(i == (int)chefoes.size() - 1)
            break;

        printaInimigo(chefoes[i]);

        if(nome != "cheater"){

            jogo.setNome(chefoes[i], 2);
            jogo.novosMapas();

            jogo.getPlayer(1)->setLarguraEAltura(mapa_player[i].first.first, mapa_player[i].first.second);
            jogo.getPlayer(2)->setLarguraEAltura(mapa_inimigo[i].first.first, mapa_inimigo[i].first.second);  

            jogo.getPlayer(1)->gerarMapa(mapa_player[i].second);
            jogo.getPlayer(2)->gerarMapa(mapa_inimigo[i].second);

            jogo.setNumeroDeNaviosInicial();

            jogo.getPlayer(1)->configurarJogo();
            jogo.getPlayer(2)->configurarJogo();

            jogo.limparCooldown(1);
            jogo.limparCooldown(2);

            bool vitoria = true;

            if(jogar(&vitoria))
                return;

            if(!vitoria){

                limpaTela();
                quebraLinha();
                formatarDist();

                std::cout<<"VOCE FOI DERROTADO!\n";

                quebraLinha(2);
                formatarDist();

                std::cout<<chefoes[i]<<" venceu a batalha!\n";

                quebraLinha();
                travaDeLeitura();

                return;

            }else{

                limpaTela();
                quebraLinha();
                formatarDist();

                std::cout<<"VOCE DERROROU O INIMIGO!\n";
                
                quebraLinha(2);

                formatarDist();
                std::cout<<chefoes[i]<<" perdeu a batalha.\n";

                quebraLinha();
                travaDeLeitura();

            }

        }

    }

    limpaTela();
    quebraLinha();
    formatarDist();
    std::cout<<"O chao comeca a tremer. A clima comeca a ficar escuro. Uma tempestade comeca a cair!";
    quebraLinha();
    travaDeLeitura();
    
    limpaTela();
    quebraLinha();
    formatarDist();
    std::cout<<"Ao longe voce ve uma frota enorme!";
    quebraLinha();
    travaDeLeitura();

    printaInimigo("frota");

    limpaTela();
    quebraLinha();
    formatarDist();
    std::cout<<"Voce procura o capitao das embarcoes mas ve apenas um cabo...";
    quebraLinha();
    usleep(3000000);
    quebraLinha();
    travaDeLeitura();
    
    printaInimigo("daciolo");
    


}

void GUI_jogo::printaInimigo(std::string nome){

    limpaTela();
    quebraLinha();

    if(nome != "frota")
        printaImagem(nome);
    else 
        printaImagem(nome, 0);

    quebraLinha();
    travaDeLeitura();

}