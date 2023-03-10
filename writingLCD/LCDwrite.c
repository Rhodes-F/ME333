#include "NU32.h"          // constants, funcs for startup and UART
#include "LCD.h"

#define MSG_LEN 20

void LCD_ClearLine(int ln) {
	LCD_Move(ln, 0);
	const char msg[16] = "                ";
	LCD_WriteString(msg);
}

int main() {
  char msg[MSG_LEN];
  int nreceived = 1;

  NU32_Startup();         // cache on, interrupts on, LED/button init, UART init
  
  LCD_Setup();
  
  while (1) {
    NU32_WriteUART3("What do you want to write? ");
    NU32_ReadUART3(msg, MSG_LEN);             // get the response
    LCD_Clear();                              // clear LCD screen
    LCD_Move(0,0);
    LCD_WriteString(msg);                     // write msg at row 0 col 0
    sprintf(msg, "Received %d", nreceived);   // display how many messages received
    ++nreceived;
    LCD_Move(1,3);
    LCD_WriteString(msg);                     // write new msg at row 1 col 3
    NU32_WriteUART3("\r\n");          
    
    // while(!PORTDbits.RD7) {
    //     ;   // Pin D7 is the USER switch, low (FALSE) if pressed.
    // }
    // LCD_ClearLine(1);
  }
  return 0;
}
