## Resumo :

Esse projeto consiste em um sistema embarcado que reproduz três musicas monofônicas através do controle do `OLED 1 XPLAINED PRO` via interface SPI (Serial Peripheral Interface Bus).

## Materiais:

    - 1x Microcontrolador SAME70 Xplained
    - 1x OLED1 Xplained
    - 1x Buzzer
    - 1x Protoboard
    - 2x Jumpers
    
## Periféricos uC:

    - Power Managment Controller (PMC)
    - Serial Protocol Interface (SPI)
    - Parallel Input Output (PIO)
    
## Ligações elétricas:

    - OLED1 Xplained -> EXT1
    - Buzzer (Positivo) -> GND
    - Buzzer (Negativo) -> PD30
    
## Como utilizar
Conectar o OLED1 Xplained e o buzzer às entradas do microcontrolador conforme descritas acima e rodar o arquivo principal do programa ([`main.c`])(/src/main.c). Com isso, o projeto está pronto para reproduzir as músicas escolhidas. Para escolher a música que será tocada, pressionar o botão 1 do OLED1 Xplained e para pausar ou reproduzir a música, pressionar o botão 2 do OLED1 Xplained. Quando a música estiver tocando, o LED irá piscar de acordo com a música.
        
## Estrutura do software:  
 
1. ***[`main.c`]***(/src/main.c): Arquivo responsável pela lógica principal do programa. Nele se define o buzzer, os Leds, os botões utilizados e as funções necessárias para rodar o programa.
2. ***[`mario.h`]***(/src/mario.h), ***[`pirates.h`]***(/src/pirates.h), ***[`underworld.h`]***(/src/underworld.h) : Arquivos que contém as músicas utilizadas, nele se define as notas, a duração e o nome da música.
3.***[`musics.h`]***(/src/musics.h): Arquivo que organiza em structs as músicas definidas e as reúne na função songList().
    
## Conexão do Periférico:

 1. OLED botão 1: conecta-se ao pino 9 (PD28) do Microcontrolador.
 2. OLED botão 2: conecta-se ao pino 3 (PC31) do Microcontrolador.
 3. LED1 : conecta-se ao PC8 do Microcontrolador.

## Resultado
 
link do vídeo: https://youtu.be/kfLgnO72To8

