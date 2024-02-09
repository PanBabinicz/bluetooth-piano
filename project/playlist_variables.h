#include "MKL05Z4.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MOD_MAX		40082
#define ZEGAR 		1310720
#define DIV_CORE	16


extern float		ampl_v;
extern float 		freq;
extern uint16_t	mod_curr;
extern uint16_t	ampl;
extern uint16_t Tony[];
extern uint16_t Oktawa[];


extern uint8_t	Kotek[];
extern uint8_t	Kotek_W[];
extern uint8_t 	Kotek_Gap[];


extern uint8_t	Fuga[];
extern uint8_t	Fuga_W[];
extern uint8_t 	Fuga_Gap[];


extern uint8_t	Maskoff[];
extern uint8_t	Maskoff_W[];
extern uint8_t 	Maskoff_Gap[];
	
	
extern uint8_t 	lotr[];
extern uint8_t	lotr_W[];
extern uint8_t 	lotr_Gap[];
	

extern uint8_t 	playlist_condition;
extern uint8_t 	music_number;
extern uint8_t 	ton_size;
extern uint8_t	ton;
extern int8_t		gama;
extern uint8_t 	sekunda;			
extern uint8_t 	sekunda_OK;	 
extern uint8_t	gap_ton;
extern uint8_t 	on_off;
extern uint8_t 	czas;
extern uint8_t 	silence;


