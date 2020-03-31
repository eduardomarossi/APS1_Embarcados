 Resumo :

Esse projeto consiste em um sistema embarcado que reproduz uma musica monofonia atravez do controle do `OLED 1 XPLAINED PRO` via interface SPI (Serial Peripheral Interface Bus).

link vídeo: https://youtu.be/kfLgnO72To8

 Materiais:

    - 1x Microcontrolador SAME70 Xplained
    - 1x OLED1 Xplained
    - 1x Buzzer
    - 1x Protoboard
    - 2x Jumpers

 Periféricos uC:

    - Power Managment Controller (PMC)
    - Serial Protocol Interface (SPI)
    - Parallel Input Output (PIO)
    
 Ligaçoes eletricas:

    - OLED1 Xplained -> EXT1
    - Buzzer (Positivo) -> GND
    - Buzzer (Negativo) -> PD30
        
 Extrutura do software:  

    - main.c: Arquivo responsavel pela logica principal do programa. Nele se define o buzzer, os Leds, os botoes utilizados e as funçoes necessarias para rodar o programa.
    - mario.h, pirates.h, underworld.h : Arquivos que contém as msuicas utilizadas, nele se define as notas, a duração e o nome da música.
    - musics.h: Arquivo que organiza em structs as musicas definidas e as reune na funçao songList().
    
 Conexão e Funcionalidades:

    - OLED botao 1: conecta-se ao pino 9 (PD28) da placa e é utilizado para escolher a musica que será tocada
    - OLED botao 2: conecta-se ao pino 3 (PC31) da placa e é utilizada para começar e pausar a musica
    - LED1 : conecta-se ao PC8 da placa, este pisca de acordo com a musica.
 


 Resultado

