## Projeto de Monitoramento de Nível de Caixa D'Água

This is a Brazilian project to monitor water tank level.

Este é um projeto que desenvolvi para monitorar o nível da caixa d'água do meu
prédio. Trata-se de um projeto particular, que está sendo divulgado para ajudar a
quem precisa de algo similar. Não pretendo prover suporte técnico, mas poderei
esclarecer algumas dúvidas. Aceitarei eventuais PRs, desde que sirvam para mim, a
fim de não modificar o projeto desenvolvido para o condomínio.

Eu vou manter esse projeto em português para o caso de outra pessoa necessitar
fazer manutenção no sistema do meu prédio (assim eu poderei viajar e até mesmo
me mudar).

### Projeto

O projeto faz a medição da caixa d'água inferior (subsolo) e da caixa superior
(cobertura). Há 03 LEDs para cada caixa que indicam os volumes de água: 80%, 50%
e 30%. O circuito principal fica localizado na casa das bombas, montado em uma
caixa de projeto eletrônico, e possui 06 LEDs (03 para a caixa inferior e 03 para
a caixa superior). Uma outra caixa, localizada na portaria do prédio, possui 06
LEDs que indicam as mesmas condições e também um buzzer, que emite sons
diferentes para situações diferentes. Essa caixa da portaria também possui um
push button, utilizado para reiniciar remotamente o Arduino, caso seja
necessário. Em cada caixa d'água, há um sensor que mede a profundidade da água.

### Programas utilizados

### Material utilizado

* 01 Arduino Uno
* 12 LEDs comuns de 5mm, sendo 04 vermelhos, 04 amarelos e 04 verdes
* 12 resistores de 330 ohms
* 02 sensores utlrasônicos de distância à prova d'água
* 01 buzzer passivo
* 01 push button normalmente aberto

Eu comprei todo esse material na China e creio que a licença do GitHub não me
permita listar os links. Para saber onde comprei e o que comprei,
[clique aqui](http://eriberto.pro.br/files/arduino-caixa-agua/).

### Material secundário

Há uma lista de material que você deverá querer para montar o projeto, como canos
e alicate. Eu optei por não usar solda, então, comprei fios individuais com
conectores Dupont, removi os conectores metálicos das capas com uma agulha (é só
levantar uma travinha plástica) e os reintroduzi em novas capas que unificam
vários conectores (machos ou fêmeas). Então, tive que comprar todo esse material.
Essa manobra evitou a compra de um alicate de crimpar caro.

Você pode improvisar algumas coisas. Muito do que está aqui vem do meu
perfeccionismo.

* Canos e curvas de PVC para instalar o sensor dentro da caixa d'água
* Alicate de decapar para fios 26, 28 e 30 AWG
* Kit de conectores Dupont
* Fios com conectores metálicos Dupont macho e fêmea
* Cabo de alarme de 10 vias (para interligar a caixa da portaria)
* Caixas para projetos de eletrônica
* Caixas herméticas de passagem para abrigar os circuitos dos sensores
* Acabamento para os LEDs
* Isolamento termo retrátil

### Considerações importantes e dicas

* O sensor de distância não permite o aumento do tamanho do fio. Se você tentar
fazer isso, a leitura apresentará falhas e dará resultados totalmente fora da
realidade. Assim sendo, coloque a placa de circuito do sensor dentro de uma caixa
hemética e utilize um fio para levar os quatro terminais dessa placa até o
Arduino.

* O código fonte utilizado gera saída serial para a tela do notebook (monitor
serial), relatando as profundidades obtidas pela leitura. Utilize esses dados
para inserir as profundidades corretas no início do código, após realizar
medições.

### Desenhos, esquemas e fotos

### Dúvidas e perguntas

### Licença de uso e modificação

Copyright 2021 João Eriberto Mota Filho

Este projeto é regido pela licença MIT e mantido em
https://github.com/eribertomota/arduino-caixa-dagua.git
