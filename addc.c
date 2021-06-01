#include <addc.h>
#include<MLCD.c>
void main()
{
int ldr;
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_DIV_4|ADC_TAD_MUL_0);
   lcd_init();
   while(TRUE)
   {
       set_adc_channel(0);
      lcd_gotoxy(1,1);
      ldr = read_adc();
      
      printf(lcd_putc," adc= %d ",ldr);
      
   }

}
