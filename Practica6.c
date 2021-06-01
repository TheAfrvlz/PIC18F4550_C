// Lcd pinout settings
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

unsigned short keydata = 0, special = 0, down = 0;

sbit PS2_Data            at RC0_bit;                            //PIN C0 - Data
sbit PS2_Clock           at RC1_bit;                            //PIN C1 - Clock
sbit PS2_Data_Direction  at TRISC0_bit;
sbit PS2_Clock_Direction at TRISC1_bit;

//Variables auxiliares

unsigned char pos = 1,dse = 0;
char uart_rd;
char DataSe[16] = {' '};
char CadB[16] = {' ',' ',' ',' ',' ',' ',' ',' ',
                 ' ',' ',' ',' ',' ',' ',' ',' '
};                //Fin Cadena



void main()
{
   ADCON1 = 0x0F;
   PORTD.RD2 = 0;     //RW = 0;
   TRISD.RD2 = 0;     //PD2 = SALIDA
   Lcd_Init();        //Inicializacion del LCD

  UART1_Init(9600);                                   // Inicializa UART module a 9600 baudios
  delay_ms(100);                                      //Delay del LCD cuando se inicializa
  Ps2_Config();                                       // Inicializa el teclado PS/2
  Delay_ms(100);                                      //Delay del teclado cuando se inicializa


  while(1)
  {
   if (Ps2_Key_Read(&keydata, &special, &down)) {     //Lectura del teclado

      if (down && (keydata == 16) || (keydata == 18)) {                  // Tecla Backspace
          // UART1_Write(16);
           pos--;
           Lcd_Chr(1,pos,' ');
           Lcd_Cmd(_LCD_MOVE_CURSOR_LEFT);
           delay_ms(200);
         }
      else if (down && (keydata == 13)) {             // Enter
        UART1_Write(0x0D);                            // Envia el dato y retorna el LCD a 1,1
        Lcd_Out(1,1,CadB);
        pos = 1;
        Lcd_Cmd(_LCD_RETURN_HOME);
      }
      else if (down && !special && keydata) {         //Tecla detectada
         //else{
         Lcd_chr(1,pos,keydata);
        // UART1_Write(keydata);
         pos++;
         pos>16? pos = 1 : 0;
         //}
      }
    }
    Delay_ms(1);                                      // Antirrebote

    if (UART1_Data_Ready()) {     // Si data es recibido,
      uart_rd = UART1_Read();     // Lee el dato recibido,

      if (uart_rd == 0x0D)
      {
         Lcd_Out(2,1,DataSe);

         for(dse = 0; dse<16; dse++)
         {
             DataSe[dse] = ' ';
         }
         dse = 0;
         Lcd_chr(1,pos-1,keydata);  //Regresa al anterior
      }
      else if (uart_rd == 16)
      {
         dse--;
         DataSe[dse] = ' ';
      }
      else
      {
      DataSe[dse] = uart_rd;
         dse++;
         dse>15? dse = 0: 0;    
      }


    }

  } //end while
}
