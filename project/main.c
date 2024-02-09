#include "MKL05Z4.h"
#include "TPM.h"
#include "bluetooth_variables.h"
#include "i2c.h"
#include "lcd1602.h"
#include "octave_variables.h"
#include "playlist_variables.h"
#include "uart0.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_point = 0;
char display[] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
                  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20};

void UART0_IRQHandler(void) {
  if (UART0->S1 & UART0_S1_RDRF_MASK) {
    temp =
        UART0->D; 
    if (!rx_FULL) {
      if (temp != CR) {
        rx_buf[rx_buf_pos] = temp;
        rx_buf_pos++;
      } else {
        rx_buf[rx_buf_pos] = 0;
        rx_FULL = 1;
      }
    }
    NVIC_EnableIRQ(UART0_IRQn);
  }
}

void SysTick_Handler(void) {
  if (!playlist_condition) {
    TPM0->MOD = mod_curr;
    ampl = (int)mod_curr / 50;
    TPM0->CONTROLS[3].CnV =
        ampl; // Nowa wartosc kreujaca wspólczynnik wypelnienia PWM
    TPM0->SC |= TPM_SC_CMOD(1);
    if (silence == 1) {
      TPM0->SC &= ~(TPM_SC_CMOD(3));
      TPM0->CNT = 0;
    }
  }
  if (playlist_condition) {
    sekunda += 1;

    if (sekunda == czas) {
      switch (gap_ton) {
      case 0:
        if (music_number == 1) {
          czas = Fuga_W[ton];
          mod_curr = Tony[Fuga[ton]] / Oktawa[gama];
        }
        if (music_number == 2) {
          czas = Kotek_W[ton];
          mod_curr = Tony[Kotek[ton]] / Oktawa[gama];
        }
        if (music_number == 3) {
          czas = Maskoff_W[ton];
          mod_curr = Tony[Maskoff[ton]] / Oktawa[gama];
        }
        if (music_number == 4) {
          czas = lotr_W[ton];
          mod_curr = Tony[lotr[ton]] / Oktawa[gama];
        }
        TPM0->MOD = mod_curr;
        ampl = (int)mod_curr / 50;
        TPM0->CONTROLS[3].CnV =
            ampl; // Nowa wartosc kreujaca wspólczynnik wypelnienia PWM
        TPM0->SC |= TPM_SC_CMOD(1);
        sekunda = 0;
        gap_ton = 1;
        break;
      case 1:
        TPM0->SC &= ~(TPM_SC_CMOD(3));
        TPM0->CNT = 0;
        sekunda = 0;
        if (music_number == 1) {
          czas = Fuga_Gap[ton];
          ton_size = 16;
        }
        if (music_number == 2) {
          czas = Kotek_Gap[ton];
          ton_size = 18;
        }
        if (music_number == 3) {
          czas = Maskoff_Gap[ton];
          ton_size = 43;
        }
        if (music_number == 4) {
          czas = lotr_Gap[ton];
          ton_size = 24;
        }
        ton += 1;
        if (ton == ton_size) {
          ton = 0;
          playlist_condition = 0;
          silence = 1;
        }
        gap_ton = 0;
        break;
      }
    }
  }
}

int main(void) {
  UART0_Init();
  PWM_Init();
  LCD1602_Init();
  SysTick_Config(SystemCoreClock / DIV_CORE);

  ampl = (int)mod_curr / 50;

  while (1) {
    if (rx_FULL) {
      sprintf(display, "%s", rx_buf);
      LCD1602_SetCursor(0, 0);
      LCD1602_Print(display);

      /* OCTAVE KEYS SUPPORT */
      if (strcmp(rx_buf, C_ON) == 0) {
        silence = 0;
        mod_curr = 40082 / Oktawa[gama];
      } else if (strcmp(rx_buf, C_OFF) == 0)
        silence = 1;

      if (strcmp(rx_buf, Css_ON) == 0) {
        silence = 0;
        mod_curr = 37826 / Oktawa[gama];
      } else if (strcmp(rx_buf, Css_OFF) == 0)
        silence = 1;

      if (strcmp(rx_buf, D_ON) == 0) {
        silence = 0;
        mod_curr = 35701 / Oktawa[gama];
      } else if (strcmp(rx_buf, D_OFF) == 0)
        silence = 1;

      if (strcmp(rx_buf, Dss_ON) == 0) {
        silence = 0;
        mod_curr = 33702 / Oktawa[gama];
      } else if (strcmp(rx_buf, Dss_OFF) == 0)
        silence = 1;

      if (strcmp(rx_buf, E_ON) == 0) {
        silence = 0;
        mod_curr = 31813 / Oktawa[gama];
      } else if (strcmp(rx_buf, E_OFF) == 0)
        silence = 1;

      if (strcmp(rx_buf, F_ON) == 0) {
        silence = 0;
        mod_curr = 30027 / Oktawa[gama];
      } else if (strcmp(rx_buf, F_OFF) == 0)
        silence = 1;

      if (strcmp(rx_buf, Fss_ON) == 0) {
        silence = 0;
        mod_curr = 28339 / Oktawa[gama];
      } else if (strcmp(rx_buf, Fss_OFF) == 0)
        silence = 1;

      if (strcmp(rx_buf, G_ON) == 0) {
        silence = 0;
        mod_curr = 26748 / Oktawa[gama];
      } else if (strcmp(rx_buf, G_OFF) == 0)
        silence = 1;

      if (strcmp(rx_buf, Gss_ON) == 0) {
        silence = 0;
        mod_curr = 25249 / Oktawa[gama];
      } else if (strcmp(rx_buf, Gss_OFF) == 0)
        silence = 1;

      if (strcmp(rx_buf, A_ON) == 0) {
        silence = 0;
        mod_curr = 23830 / Oktawa[gama];
      } else if (strcmp(rx_buf, A_OFF) == 0)
        silence = 1;

      if (strcmp(rx_buf, Ass_ON) == 0) {
        silence = 0;
        mod_curr = 22493 / Oktawa[gama];
      } else if (strcmp(rx_buf, Ass_OFF) == 0)
        silence = 1;

      if (strcmp(rx_buf, B_ON) == 0) {
        silence = 0;
        mod_curr = 21229 / Oktawa[gama];
      } else if (strcmp(rx_buf, B_OFF) == 0)
        silence = 1;

      /* PERIPHERAL KEYS SUPPORT */
      if (strcmp(rx_buf, PLAYLIST) == 0) {
        playlist_condition = ~playlist_condition;
      }

      if (strcmp(rx_buf, OCTAVE_UP) == 0) {
        if (playlist_condition == 1) {
          ton = 0;
          music_number += 1;
          if (music_number == 5)
            music_number = 4;
        } else {
          gama += 1;
          if (gama == 7)
            gama = 6;
        }
      }

      if (strcmp(rx_buf, OCTAVE_DOWN) == 0) {
        if (playlist_condition == 1) {
          ton = 0;
          music_number -= 1;
          if (music_number == 0)
            music_number = 1;
        } else {
          gama -= 1;
          if (gama == -1)
            gama = 0;
        }
      }

      check_point--;

      rx_buf_pos = 0;
      rx_FULL = 0;
    } else {
    }
  }
}
