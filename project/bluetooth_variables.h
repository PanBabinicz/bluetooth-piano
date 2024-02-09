#include "MKL05Z4.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LF	0xa		
#define CR	0xd		


extern char rx_buf[16];

extern uint8_t rx_buf_pos;
extern uint8_t rx_FULL;
extern uint8_t too_long;

extern char buf;
extern char temp;

