 float adc1 =0;
 float adc2 =0;
float vx,vy;
void desplazamiento(float, float);
void main(){
 PORTD = 1;//0x10
 PORTB = 0; //0xef
 TRISB=0;
 TRISD=0;
 ADCON1=0X0d;
             while(1){
             adc1 = ADC_Read(0);
             adc2 =ADC_Read(1);
             vx=(adc1*5.0)/1024;
             vy = (adc2*5.0)/1024;
             desplazamiento(vx,vy);
             }
 }
void desplazamiento(float vx, float vy){
   if (vy>0.0 && vy< 0.4 ){
    PORTD=0X80;
    }
     else if (vy>0.4 && vy<1.8){
     PORTD=0X40;
     }
     else if (vy>1.8 && vy<2.3){
     PORTD=0X20;
     }
      else if (vy>2.43 && vy<2.7){
     PORTD=0X10;
     }
      else if (vy>2.72 && vy<3.5){
     PORTD=0X08;
     }
      else if (vy>3.52 && vy<4.0){
     PORTD=0X04;
     }
      else if (vy>4 && vy<4.5){
     PORTD=0X02;
     }
      else if  (vy>4.51 && vy<5.0){
     PORTD=0X01;
      }
     /*********/
     if (vx >0.0 && vx< 0.4 ){
    PORTB=0X7F;
    }
     else if (vx>0.4 && vx<1.8){
     PORTB=0XBF;
     }
     else if (vx>1.8 && vx<2.3){
     PORTB=0XDF;
     }
      else if (vx>2.43 && vx<2.7){
     PORTB=0XEF;
     }
      else if (vx>2.72 && vx<3.5){
     PORTB=0XF7;
     }
      else if (vx>3.52 && vx<4.0){
     PORTB=0XFB;
     }
      else if (vx>4 && vx<4.5){
     PORTB=0XFD;
     }
      else if  (vx>4.51 && vx<5.0){
     PORTB=0XFE;
     }
}