# A Batalha do Lago Paranoá

&nbsp;&nbsp;Reacriação brasiliense do Batalha Naval!

<p align="center"> 
<img src="https://i.imgur.com/D7Uyyij.png">
</p>

## Jogo

Jogo possui sistema de mapas onde você pode criar mapas à mão e gera-los aleatoriamente.

Dois players jogam um contra o outro às margens do lago paranoá em busca de sangue, cada um com seu mapa contendo suas embarcações.

A condição de vitória é destruir todos os navios do adversário.

Existe uma atributo de Dano Maximo que define o teto de dano dos ataques, quanto mais alto, mas fácil e destruir os navios e quanto mais baixo, mais estratégico fica o jogo.

Existem 8 tipos de embarcações, cada uma com suas peculiaridades, vantagens e fraquezas.

Existem, também, 5 tipos de ataques que os players podem utilizar, alguns deles com cooldown.

Diferente do batalha naval comum, o critério para se destruir um navio e tirar toda a vida dele (cada tipo de navio possui uma vida inicial diferente). Os navios podem contra-atacar, defender, refletir o ataque, se curar e outros. 

Todos os navios possuem um atributo de visibilidade. Alguns navios já começam o jogo visiveis, outros podem ficar visíveis se atacados e outros ainda nao ficam visíveis durante o jogo nunca. 

## Modo Historia

No modo historia, voce luta contra figuras politicas brasileiras e globais.

<p align="center"> 
<img src="https://i.imgur.com/L7iohHn.png">
</p>

O modo segue uma progressão de dificuldade à la Mortal Kombat em que fica cada vez mais difícil ganhar a partida atual.

O fim de jogo possui um plot twist.

Existem cheats escondidos pelo jogo, basta achar.

## Instruções de como jogar

Para compilar:
```
$ make
```

Para rodar:
```
$ make run
```

## Compatibilidade

Esse programa compila e roda pelo terminal do Ubuntu 16.04 LTS.

Como funções específicas do linux são usadas (como a usleep()), esse programa não é compatível com o Windows.

## Sobre o sistema de mapas

Cada player possui seu mapa de jogo (possivelmente com número de navios e dimensões diferentes). Os mapas são guardados de forma padronizada num arquivo .mapa. Veja o arquivo em ./doc/mapa_de_contexto para entender como é guardado.

## Sobre o sistema de pontuacao e ranking

A pontução de um player pode ser calculada a qualquer momento da partida e pode ser salva num arquivo .ranking para ser visto depois. Varia de [-100, 100].

