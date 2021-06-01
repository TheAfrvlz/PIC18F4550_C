#include <ACELEROMETRO.h>
#include <MLCD.c>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Kalman.h>
#use I2C(MASTER, SCL=PIN_b1, SDA=PIN_b0,slow)//Configuración del I2C
#use TIMER(TIMER=1, TICK=1ms, BITS=16, NOISR) 
#define RAD_TO_GRAD 180/PI 




/*FUNCIONES ACELEROMETRO*/
unsigned char MPU6050_Read(unsigned char address);
void MPU6050_Write(unsigned char address, unsigned char Data);
int16 MPU6050_Getdata(unsigned char address);
void MPU6050_init();
/*-----------------------*/


               

void main(){
   SIGNED int16 accX,accY, accZ;
   SIGNED int16 gyroX,gyroY,gyroZ;
   DOUBLE accXangle,accYangle; 
   DOUBLE gyroXangle,gyroYangle;
   DOUBLE kalAngleX,kalAngleY;            
   UNSIGNED int16 timer;
   lcd_init ();
   MPU6050_init () ;
   delay_ms (500) ;


 
while(true){
      accX = Mpu6050_GetData (MPU6050_RA_ACCEL_XOUT_H);  
      accY = Mpu6050_GetData (MPU6050_RA_ACCEL_YOUT_H);
      accZ = Mpu6050_GetData (MPU6050_RA_ACCEL_ZOUT_H);  
      gyroX = Mpu6050_GetData(MPU6050_RA_GYRO_XOUT_H); 
      gyroY = Mpu6050_GetData(MPU6050_RA_GYRO_YOUT_H);
      gyroZ = Mpu6050_GetData(MPU6050_RA_GYRO_ZOUT_H);
      
      set_ticks(0);
      accXangle = (atan2 (accY, accZ) + PI) * RAD_TO_GRAD; 
      DOUBLE gyroXrate = (double) gyroX / 131.0; 
      gyroXangle += gyroXrate * ( (DOUBLE) (get_ticks () - timer)  / 1000);  
      kalAngleX = kalmanCalculate (accXangle, gyroXrate, (get_ticks()-timer)); 
      timer = get_ticks ();
      
      
      //timer=0; 
      set_ticks(0);                    
      accYangle = (atan2 (accX, accZ) + PI) * RAD_TO_GRAD;
      DOUBLE gyroYrate = (double) gyroY / 131.0;                                                   
      gyroYangle += gyroYrate * ( (DOUBLE) (get_ticks () - timer)  / 1000);
      kalAngleY = kalmanCalculate (accYangle, gyroYrate, (get_ticks()-timer));
      timer = get_ticks ();
      
      lcd_gotoxy(1, 1) ;                                
      printf (LCD_PUTC, "X=%f", kalAngleX);
   lcd_gotoxy(1, 2) ;                                
      printf (LCD_PUTC, "Y=%f", kalAngleY);
      
}
}

unsigned char MPU6050_Read(unsigned char address){
   int8 Data;     
   MPU6050_I2C_Start();           
   MPU6050_I2C_Wr( MPU6050_ADDRESS );      
   MPU6050_I2C_Wr(address);    
   MPU6050_I2C_Start();          
   MPU6050_I2C_Wr( MPU6050_ADDRESS | 1 );  
   Data=MPU6050_I2C_Rd(0);        
    MPU6050_I2C_Stop();              
   return Data;   
   }  
void MPU6050_Write(unsigned char address,unsigned char Data){
   MPU6050_I2C_Start();               
   MPU6050_I2C_Wr( MPU6050_ADDRESS );    
   MPU6050_I2C_Wr( address);   
   MPU6050_I2C_Wr( Data);       
   MPU6050_I2C_Stop();     
   }
int16 MPU6050_Getdata(unsigned char address){
   int16 H=0,L=0;    
   MPU6050_I2C_Start();       
   MPU6050_I2C_Wr( MPU6050_ADDRESS );      
   MPU6050_I2C_Wr(address);    
   MPU6050_I2C_Start();         
   MPU6050_I2C_Wr( MPU6050_ADDRESS |1);   
   H=i2C_read();           
   L=i2C_read(0);         
   MPU6050_I2C_Stop();          
   return (H<<8)|L;
}                                              
void MPU6050_init(){

   Mpu6050_Write(MPU6050_RA_PWR_MGMT_1,0X80); 
   delay_ms(5);
   Mpu6050_Write(MPU6050_RA_PWR_MGMT_1, 0x00); 
   Mpu6050_Write(MPU6050_RA_SMPLRT_DIV, 0x07);  //Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
   Mpu6050_Write(MPU6050_RA_CONFIG, 0x00);      
                                      
   Mpu6050_Write(MPU6050_RA_GYRO_CONFIG, 0x00); 
                                      
   Mpu6050_Write(MPU6050_RA_ACCEL_CONFIG, 0x00); 
                                     
   Mpu6050_Write(MPU6050_RA_USER_CTRL, 0x00);   
   Mpu6050_Write(MPU6050_RA_PWR_MGMT_1, 0x01);                         
   delay_ms(10);
   }
