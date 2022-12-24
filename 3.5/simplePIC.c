#include <xc.h>          // Load the proper header for the processor

// #define Maxcycles  1000000;
// #define Deltacycles 100000;

// void delay(cycles);

int main(void) {
  // int cycle_m = Maxcycles;
  // int cycle_d = Deltacycles;
  // TRISF = 0xFFFC;        // Pins 0 and 1 of Port F are LED1 and LED2.  Clear
  //                        // bits 0 and 1 to zero, for output.  Others are inputs.
  // LATFbits.LATF0 = 0;    // Turn LED1 on and LED2 off.  These pins sink current
  // LATFbits.LATF1 = 1;    // on the NU32, so "high" (1) = "off" and "low" (0) = "on"

  // while(1) {
  //   delay(cycle_m);
  //   LATFINV = 0x0003;    // toggle LED1 and LED2; same as LATFINV = 0x3;
  //   cycle_m-=cycle_d;
  //   if (cycle_m <= 0){
  //     cycle_m= Maxcycles;
  //   }
  // }

  int i1=5, i2=6, i3;

  i3= i1+i2;
  return 0;
}

// void delay(cycles) {
//   int j;
//   for (j = 0; j < cycles; j++) { // number is 1 million
//     while(!PORTDbits.RD7) {
//         ;   // Pin D7 is the USER switch, low (FALSE) if pressed.
//     }
//   }
// }
