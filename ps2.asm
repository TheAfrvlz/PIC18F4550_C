
_main:

;ps2.c,29 :: 		void main() {
;ps2.c,30 :: 		PORTD.RD2 = 0;
	BCF         PORTD+0, 2 
;ps2.c,31 :: 		TRISD.RD2 = 0;      //RW <- 0
	BCF         TRISD+0, 2 
;ps2.c,32 :: 		ADCON1 = 0x0F;
	MOVLW       15
	MOVWF       ADCON1+0 
;ps2.c,33 :: 		Lcd_Init();              //inicializacion de la pantalla LCD
	CALL        _Lcd_Init+0, 0
;ps2.c,35 :: 		UART1_Init(9600);                                  // Initialize UART module at 9600 bps
	BSF         BAUDCON+0, 3, 0
	CLRF        SPBRGH+0 
	MOVLW       207
	MOVWF       SPBRG+0 
	BSF         TXSTA+0, 2, 0
	CALL        _UART1_Init+0, 0
;ps2.c,36 :: 		delay_ms(100);
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       4
	MOVWF       R12, 0
	MOVLW       186
	MOVWF       R13, 0
L_main0:
	DECFSZ      R13, 1, 1
	BRA         L_main0
	DECFSZ      R12, 1, 1
	BRA         L_main0
	DECFSZ      R11, 1, 1
	BRA         L_main0
	NOP
;ps2.c,37 :: 		Ps2_Config();                                       // Init PS/2 Keyboard
	CALL        _Ps2_Config+0, 0
;ps2.c,38 :: 		Delay_ms(100);                                      // Wait for keyboard to finish
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       4
	MOVWF       R12, 0
	MOVLW       186
	MOVWF       R13, 0
L_main1:
	DECFSZ      R13, 1, 1
	BRA         L_main1
	DECFSZ      R12, 1, 1
	BRA         L_main1
	DECFSZ      R11, 1, 1
	BRA         L_main1
	NOP
;ps2.c,40 :: 		while(1)
L_main2:
;ps2.c,42 :: 		if(Ps2_Key_Read(&keydata, &special, &down))
	MOVLW       _keydata+0
	MOVWF       FARG_Ps2_Key_Read_value+0 
	MOVLW       hi_addr(_keydata+0)
	MOVWF       FARG_Ps2_Key_Read_value+1 
	MOVLW       _special+0
	MOVWF       FARG_Ps2_Key_Read_special+0 
	MOVLW       hi_addr(_special+0)
	MOVWF       FARG_Ps2_Key_Read_special+1 
	MOVLW       _down+0
	MOVWF       FARG_Ps2_Key_Read_pressed+0 
	MOVLW       hi_addr(_down+0)
	MOVWF       FARG_Ps2_Key_Read_pressed+1 
	CALL        _Ps2_Key_Read+0, 0
	MOVF        R0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_main4
;ps2.c,44 :: 		if (down && (keydata == 16) || (keydata == 18)) {                  // Backspace
	MOVF        _down+0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L__main35
	MOVF        _keydata+0, 0 
	XORLW       16
	BTFSS       STATUS+0, 2 
	GOTO        L__main35
	GOTO        L__main34
L__main35:
	MOVF        _keydata+0, 0 
	XORLW       18
	BTFSC       STATUS+0, 2 
	GOTO        L__main34
	GOTO        L_main9
L__main34:
;ps2.c,45 :: 		UART1_Write(16);
	MOVLW       16
	MOVWF       FARG_UART1_Write_data_+0 
	CALL        _UART1_Write+0, 0
;ps2.c,46 :: 		pos --;
	DECF        _pos+0, 1 
;ps2.c,47 :: 		Lcd_chr(1, pos, ' ');
	MOVLW       1
	MOVWF       FARG_Lcd_Chr_row+0 
	MOVF        _pos+0, 0 
	MOVWF       FARG_Lcd_Chr_column+0 
	MOVLW       32
	MOVWF       FARG_Lcd_Chr_out_char+0 
	CALL        _Lcd_Chr+0, 0
;ps2.c,48 :: 		Lcd_cmd(_LCD_MOVE_CURSOR_LEFT);
	MOVLW       16
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;ps2.c,49 :: 		delay_ms(200);
	MOVLW       3
	MOVWF       R11, 0
	MOVLW       8
	MOVWF       R12, 0
	MOVLW       119
	MOVWF       R13, 0
L_main10:
	DECFSZ      R13, 1, 1
	BRA         L_main10
	DECFSZ      R12, 1, 1
	BRA         L_main10
	DECFSZ      R11, 1, 1
	BRA         L_main10
;ps2.c,50 :: 		}
	GOTO        L_main11
L_main9:
;ps2.c,51 :: 		else if (down && (keydata == 13)) {             // Enter
	MOVF        _down+0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_main14
	MOVF        _keydata+0, 0 
	XORLW       13
	BTFSS       STATUS+0, 2 
	GOTO        L_main14
L__main33:
;ps2.c,52 :: 		UART1_Write(0x0D);
	MOVLW       13
	MOVWF       FARG_UART1_Write_data_+0 
	CALL        _UART1_Write+0, 0
;ps2.c,53 :: 		Lcd_OUT(1, 1, CadB);
	MOVLW       1
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       1
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       _CadB+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(_CadB+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;ps2.c,55 :: 		pos=1;                            // send carriage return to usart terminal
	MOVLW       1
	MOVWF       _pos+0 
;ps2.c,56 :: 		Lcd_cmd(_LCD_RETURN_HOME);
	MOVLW       2
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;ps2.c,57 :: 		}
	GOTO        L_main15
L_main14:
;ps2.c,58 :: 		else if (down && !special && keydata) {              //tecla detectada
	MOVF        _down+0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_main18
	MOVF        _special+0, 1 
	BTFSS       STATUS+0, 2 
	GOTO        L_main18
	MOVF        _keydata+0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_main18
L__main32:
;ps2.c,59 :: 		Lcd_chr(1, pos, keydata);
	MOVLW       1
	MOVWF       FARG_Lcd_Chr_row+0 
	MOVF        _pos+0, 0 
	MOVWF       FARG_Lcd_Chr_column+0 
	MOVF        _keydata+0, 0 
	MOVWF       FARG_Lcd_Chr_out_char+0 
	CALL        _Lcd_Chr+0, 0
;ps2.c,60 :: 		UART1_Write(keydata);
	MOVF        _keydata+0, 0 
	MOVWF       FARG_UART1_Write_data_+0 
	CALL        _UART1_Write+0, 0
;ps2.c,61 :: 		pos ++;
	INCF        _pos+0, 1 
;ps2.c,62 :: 		pos>16? pos = 0 : 0;
	MOVF        _pos+0, 0 
	SUBLW       16
	BTFSC       STATUS+0, 0 
	GOTO        L_main19
	CLRF        _pos+0 
	GOTO        L_main20
L_main19:
L_main20:
;ps2.c,63 :: 		}
L_main18:
L_main15:
L_main11:
;ps2.c,66 :: 		}
L_main4:
;ps2.c,67 :: 		delay_ms(1);
	MOVLW       3
	MOVWF       R12, 0
	MOVLW       151
	MOVWF       R13, 0
L_main21:
	DECFSZ      R13, 1, 1
	BRA         L_main21
	DECFSZ      R12, 1, 1
	BRA         L_main21
	NOP
	NOP
;ps2.c,68 :: 		if(UART1_Data_Ready()){
	CALL        _UART1_Data_Ready+0, 0
	MOVF        R0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_main22
;ps2.c,70 :: 		uart_rd = UART1_Read();
	CALL        _UART1_Read+0, 0
	MOVF        R0, 0 
	MOVWF       _uart_rd+0 
;ps2.c,72 :: 		if(uart_rd == 0x0D){
	MOVF        R0, 0 
	XORLW       13
	BTFSS       STATUS+0, 2 
	GOTO        L_main23
;ps2.c,73 :: 		Lcd_OUT(2, 1, DataSe);
	MOVLW       2
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       1
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       _DataSe+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(_DataSe+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;ps2.c,74 :: 		for(dse = 0; dse < 16; dse++)
	CLRF        _dse+0 
L_main24:
	MOVLW       16
	SUBWF       _dse+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_main25
;ps2.c,76 :: 		DataSe[dse] = ' ';
	MOVLW       _DataSe+0
	MOVWF       FSR1 
	MOVLW       hi_addr(_DataSe+0)
	MOVWF       FSR1H 
	MOVF        _dse+0, 0 
	ADDWF       FSR1, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR1H, 1 
	MOVLW       32
	MOVWF       POSTINC1+0 
;ps2.c,74 :: 		for(dse = 0; dse < 16; dse++)
	INCF        _dse+0, 1 
;ps2.c,77 :: 		}
	GOTO        L_main24
L_main25:
;ps2.c,79 :: 		dse = 0;                              //empieza a escribir renglon2
	CLRF        _dse+0 
;ps2.c,80 :: 		Lcd_chr(1, pos-1, keydata);           //regreso del renglon 1 despues de un enter
	MOVLW       1
	MOVWF       FARG_Lcd_Chr_row+0 
	DECF        _pos+0, 0 
	MOVWF       FARG_Lcd_Chr_column+0 
	MOVF        _keydata+0, 0 
	MOVWF       FARG_Lcd_Chr_out_char+0 
	CALL        _Lcd_Chr+0, 0
;ps2.c,81 :: 		}
	GOTO        L_main27
L_main23:
;ps2.c,82 :: 		else if(uart_rd == 16)
	MOVF        _uart_rd+0, 0 
	XORLW       16
	BTFSS       STATUS+0, 2 
	GOTO        L_main28
;ps2.c,84 :: 		dse--;
	DECF        _dse+0, 1 
;ps2.c,85 :: 		DataSe[dse] = ' ';
	MOVLW       _DataSe+0
	MOVWF       FSR1 
	MOVLW       hi_addr(_DataSe+0)
	MOVWF       FSR1H 
	MOVF        _dse+0, 0 
	ADDWF       FSR1, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR1H, 1 
	MOVLW       32
	MOVWF       POSTINC1+0 
;ps2.c,86 :: 		}
	GOTO        L_main29
L_main28:
;ps2.c,89 :: 		DataSe[dse]=uart_rd;
	MOVLW       _DataSe+0
	MOVWF       FSR1 
	MOVLW       hi_addr(_DataSe+0)
	MOVWF       FSR1H 
	MOVF        _dse+0, 0 
	ADDWF       FSR1, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR1H, 1 
	MOVF        _uart_rd+0, 0 
	MOVWF       POSTINC1+0 
;ps2.c,90 :: 		dse++;
	INCF        _dse+0, 1 
;ps2.c,91 :: 		dse<16? dse = 0 : 0;
	MOVLW       16
	SUBWF       _dse+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_main30
	CLRF        _dse+0 
	GOTO        L_main31
L_main30:
L_main31:
;ps2.c,92 :: 		}
L_main29:
L_main27:
;ps2.c,94 :: 		}
L_main22:
;ps2.c,95 :: 		}
	GOTO        L_main2
;ps2.c,98 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
