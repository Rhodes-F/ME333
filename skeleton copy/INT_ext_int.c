#include "NU32.h" // constants, funcs for startup and UART
#include <stdio.h>


static volatile unsigned int time = 0;
char msg[500];

void __ISR(_EXTERNAL_0_VECTOR, IPL6SRS) Ext0ISR(void) { // step 1: the ISR
	int count = 0;
	
	while (count <= 400000 && INTCONbits.INT0EP == 0) {
		count++;
	}
	
	if (count >= 400000) {
		if (time == 0) {
			_CP0_SET_COUNT(0);
      sprintf(msg, "Press the USER button again to stop the timer.\r\n");
			NU32_WriteUART3(msg);
			time = 1;
		}
		
		else {
			time = _CP0_GET_COUNT();
			sprintf(msg, "%0.3f seconds elapsed\r\n", (float)time / 40000000);
			NU32_WriteUART3(msg);
      NU32_WriteUART3(msg);
	    sprintf(msg, "Press the USER button to start the timer.\r\n");
			time = 0;
		}
	}
	
	IFS0bits.INT0IF = 0; // clear interrupt flag IFS0<3>
}

int main(void) {
  NU32_Startup(); // cache on, min flash wait, interrupts on, LED/button init, UART init
  __builtin_disable_interrupts(); // step 2: disable interrupts
  INTCONbits.INT0EP = 0;          // step 3: INT0 triggers on falling edge
  IPC0bits.INT0IP = 6;            // step 4: interrupt priority 2
  IPC0bits.INT0IS = 1;            // step 4: interrupt priority 1
  IFS0bits.INT0IF = 0;            // step 5: clear the int flag
  IEC0bits.INT0IE = 1;            // step 6: enable INT0 by setting IEC0<3>
  __builtin_enable_interrupts();  // step 7: enable interrupts
                                  // Connect RD7 (USER button) to INT0 (RD0)
	NU32_LED1 = 0; // LED1
	
	sprintf(msg, "Press the USER button to start the timer.\r\n");
	NU32_WriteUART3(msg);

  while(1) {
      ; // do nothing, loop forever
  }

  return 0;
}
