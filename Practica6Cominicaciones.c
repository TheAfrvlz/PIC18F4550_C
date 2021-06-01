sbit PS2_Data            at Rb0_bit;
sbit PS2_Clock           at Rb1_bit;
sbit PS2_Data_Direction  at TRISb0_bit;
sbit PS2_Clock_Direction at TRISb1_bit;

////////////////////////////////
sbit LCD_RS at RD1_bit;
sbit LCD_EN at RD0_bit;
sbit LCD_D7 at RD7_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D4 at RD4_bit;

// Pin direction
sbit LCD_RS_Direction at TRISD1_bit;
sbit LCD_EN_Direction at TRISD0_bit;
sbit LCD_D7_Direction at TRISD7_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD4_bit;

unsigned char pos = 1, dse = 0;
unsigned short keydata = 0, special = 0, down = 0;
char uart_rd;
char DataSe[16] = {' '};
char CadB[16] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                ' ', ' ', ' ', ' ', ' ', ' '};
//char CAD[16];
void main() {
  PORTD.RD2 = 0;
  TRISD.RD2 = 0;      //RW <- 0
  ADCON1 = 0x0F;
  Lcd_Init();              //inicializacion de la pantalla LCD

  UART1_Init(9600);                                  // Initialize UART module at 9600 bps
  delay_ms(100);
  Ps2_Config();                                       // Init PS/2 Keyboard
  Delay_ms(100);                                      // Wait for keyboard to finish

  while(1)
  {
          if(Ps2_Key_Read(&keydata, &special, &down))
          {
               if (down && (keydata == 16) || (keydata == 18)) {                  // Backspace
               UART1_Write(16);
               pos --;
               Lcd_chr(1, pos, ' ');
               Lcd_cmd(_LCD_MOVE_CURSOR_LEFT);
               delay_ms(200);
               }
               else if (down && (keydata == 13)) {             // Enter
               UART1_Write(0x0D);
               Lcd_OUT(1, 1, CadB);

               pos=1;                            // send carriage return to usart terminal
               Lcd_cmd(_LCD_RETURN_HOME);
               }
                else if (down && !special && keydata) {              //tecla detectada
                Lcd_chr(1, pos, keydata);
                UART1_Write(keydata);
                pos ++;
                pos>16? pos = 0 : 0;
               }


          }
          delay_ms(1);
          if(UART1_Data_Ready()){

             uart_rd = UART1_Read();

             if(uart_rd == 0x0D){
                Lcd_OUT(2, 1, DataSe);
                for(dse = 0; dse < 16; dse++)
                {
                 DataSe[dse] = ' ';
                }

                dse = 0;                              //empieza a escribir renglon2
                Lcd_chr(1, pos-1, keydata);           //regreso del renglon 1 despues de un enter
             }
             else if(uart_rd == 16)
             {
              dse--;
              DataSe[dse] = ' ';
             }
             else
             {
              DataSe[dse]=uart_rd;
              dse++;
              dse<16? dse = 0 : 0;
             }

          }
  }


}