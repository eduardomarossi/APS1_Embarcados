// Includes:

#include <asf.h>
#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"
#include "musics.h"

// Defines:

// LED
#define LED_PIO      PIOC
#define LED_PIO_ID   ID_PIOC
#define LED_IDX      8
#define LED_IDX_MASK (1 << LED_IDX)

// Button selection
#define SELECT_PIO      PIOD
#define SELECT_PIO_ID   ID_PIOD
#define SELECT_IDX  28
#define SELECT_IDX_MASK (1 << SELECT_IDX)

// Button play
#define PLAY_PIO      PIOC
#define PLAY_PIO_ID   ID_PIOC
#define PLAY_IDX  31
#define PLAY_IDX_MASK (1 << PLAY_IDX)

// Button buzzer
#define BUZZER_PIO      PIOD
#define BUZZER_PIO_ID   ID_PIOD
#define BUZZER_IDX  30
#define BUZZER_IDX_MASK (1 << BUZZER_IDX)

// Global variables

volatile short int press = 0;
volatile short int selectSong = 0;

// Functions:

void init(void);
void sound(int freq, int dur);
void playCallback(void);
void selectCallback(void);

void sound(int freq, int dur){
	if(freq != 0){
		long dt = (1000*1000)/(2*freq);
		long ncycles = freq*dur/1000;
		for(long i = 0; i < ncycles; i ++){
			pio_clear(BUZZER_PIO, BUZZER_IDX_MASK);
			pio_clear(LED_PIO, LED_IDX_MASK);
			delay_us(dt);
			pio_set(BUZZER_PIO, BUZZER_IDX_MASK);
			pio_set(LED_PIO, LED_IDX_MASK);
			delay_us(dt);
		}
	} else{
		delay_ms(dur);
	}
}

void playCallback(void){
	press = 1;
}

void selectCallback(void) {
	selectSong = 1;
}

void io_init(void)
{
	// Set led
	pmc_enable_periph_clk(LED_PIO_ID);
	pio_configure(LED_PIO, PIO_OUTPUT_0, LED_IDX_MASK, PIO_DEFAULT);

	// Set buzzer
	pmc_enable_periph_clk(BUZZER_PIO_ID);
	pio_configure(BUZZER_PIO, PIO_OUTPUT_0, BUZZER_IDX_MASK, PIO_DEFAULT);
	
	// Initialize PIOs clocks
	pmc_enable_periph_clk(SELECT_PIO_ID);
	pmc_enable_periph_clk(PLAY_PIO_ID);

	// Config PIOs (with pull-up)
	pio_configure(SELECT_PIO, PIO_INPUT, SELECT_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_configure(PLAY_PIO, PIO_INPUT, PLAY_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	
	// Set bounce
	pio_set_debounce_filter(SELECT_PIO, SELECT_IDX_MASK, 100);
	pio_set_debounce_filter(PLAY_PIO, PLAY_IDX_MASK, 100);

	// Config PIOs interruptions (with callbacks)
	pio_handler_set(SELECT_PIO, SELECT_PIO_ID, SELECT_IDX_MASK, PIO_IT_RISE_EDGE, selectCallback);
	pio_handler_set(PLAY_PIO, PLAY_PIO_ID, PLAY_IDX_MASK, PIO_IT_RISE_EDGE, playCallback);
	
	// Active interruptions
	pio_enable_interrupt(SELECT_PIO, SELECT_IDX_MASK);
	pio_enable_interrupt(PLAY_PIO, PLAY_IDX_MASK);
	
	// Config NVIC (with priority 4)
	NVIC_EnableIRQ(SELECT_PIO_ID);
	NVIC_SetPriority(SELECT_PIO_ID, 4);
	NVIC_EnableIRQ(PLAY_PIO_ID);
	NVIC_SetPriority(PLAY_PIO_ID, 4);
}

// Main:

int main (void)
{
	// System clock init code
	board_init();
	sysclk_init();
	gfx_mono_ssd1306_init();
	
	// Disable watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	delay_init();

	// Config PIOs init
	io_init();
	
	// Songs list
	int numSong = 3;
	song musics[3];
	songList(musics);

	// Playing song variables
	int currentSong = 0;
	int play = 1;
	int currentNote = 0;
	
	// Display
	gfx_mono_draw_string(musics[currentSong].name, 10, 10, &sysfont);
	
	// Loop
	while(1) {
		if (press && play) {
			press = 0;
			play = 0;
		} else if (press && (!play)) {
			press = 0;
			play = 1;
		}
		
		if (selectSong) {
			if (currentSong < numSong - 1) {
				currentSong++;
			} else {
				currentSong = 0;
			}
	
			gfx_mono_draw_string(musics[currentSong].name, 10, 10, &sysfont);
			selectSong = 0;
			currentNote = 0;
		}
		
		if (play) {
			if ((currentNote < musics[currentSong].size)) {
				sound(musics[currentSong].notes[currentNote], musics[currentSong].duration[currentNote]);
				currentNote++;
			} else {
				currentNote = 0;
			}
		}
	}
}