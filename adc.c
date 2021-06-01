#include <adc.h>
#include <MLCD.C>



void main()
{  int16 ldr;
   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_INTERNAL);
 

   setup_ccp1(CCP_PWM|CCP_SHUTDOWN_AC_L|CCP_SHUTDOWN_BD_L);
   setup_ccp2(CCP_PWM);
   set_pwm1_duty((int16)0);
   set_pwm2_duty((int16)0);
   lcd_init();
   while(TRUE)
   {
      set_adc_channel(0);
      delay_us(50);
      LDR=read_adc();      
     // set_pwm1_duty(LDR);
      lcd_gotoxy(1,1);
      printf (lcd_putc, "LDR= %4Ld", ldr);
      delay_ms(250);
   }

}




