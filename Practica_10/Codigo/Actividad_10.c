#include <xc.h>         // Biblioteca principal del compilador XC8
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lcd.h"

//=============================================================================
// CONFIGURACIÓN DE BITS DE CONFIGURACIÓN (FUSES)
//=============================================================================

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator para 8MHz)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (disabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection (disabled)
#pragma config WRT = OFF        // Flash Program Memory Write Enable (disabled)
#pragma config CP = OFF         // Flash Program Memory Code Protection (disabled)


//=============================================================================
// DEFINICIONES
//=============================================================================

#define _XTAL_FREQ 8000000      // Frecuencia del oscilador 8 MHz

volatile unsigned int tiempo = 0; 
volatile unsigned int contador = 0; 
char exec[10]; 


// Inicialización de Timer
void Timer1_Init(){
    // Configuraci�n del T1CON
    // Bits 5-4 (T1CKPS): 01 -> Preescalador de 1:8
    // Bit 1 (TMR1CS): 0 -> Reloj interno (Fosc/4)
    // Bit 0 (TMR1ON): 1 -> Enciende el Timer1
    T1CON = 0b00110001; 
    
    // Carga del valor inicial para 10 ms
    // 65536 - 2500 = 63036 = 0xF63C en Hexadecimal
    TMR1H = 0xF6; 
    TMR1L = 0x3C; 
    
    // Configuración de Interrupciones
    PIR1bits.TMR1IF = 0;  // Limpiamos la bandera del Timer1 
    PIE1bits.TMR1IE = 1;  // Interrupción específica del Timer1
    INTCONbits.PEIE = 1;  // Interrupciones de periféricos
    INTCONbits.GIE = 1;   // Interrupciones globales
}


void __interrupt() ISR(void){
    if(PIR1bits.TMR1IF){
        
        contador++; 
        
        if(contador >= 100){
            tiempo++;
            contador = 0; 
        }
        
        TMR1H = 0xF6; 
        TMR1L = 0x3C; 
        
        PIR1bits.TMR1IF = 0;
    }
}

void ADC_Init(){
    ANSEL = 0x03;  
    ANSELH = 0x00;
    ADCON1 = 0x80; 
    ADCON0 = 0x01; 
}

unsigned int ADC_Read(unsigned char channel){
    __delay_us(5); 
    ADCON0 &= 0x83; 
    ADCON0 |= channel<<2; // Recorriemiento de dos bits. 
    __delay_ms(2); 
    
    GO_nDONE = 1; 
    while(GO_nDONE);
    return((ADRESH<<8)+ADRESL);
}


void main(void){
    ADC_Init(); 
    Timer1_Init();
    
    LCD lcd = {&PORTC, 2, 3, 4, 5, 6, 7}; 
    LCD_Init(lcd); 
    
    LCD_Clear(); 
    
    char buffer[16]; 
    LCD_Set_Cursor(1,12);
    LCD_putrs("00:00"); 
    
    while(1){
        unsigned int adc_result = ADC_Read(0); 
        unsigned int volt = (adc_result * 50000UL) / 1023;
        unsigned int part_ent = volt / 10000;
        unsigned int part_dec = volt % 10000;
        LCD_Set_Cursor(0,0); 
        sprintf(buffer, "Voltaje: %u.%04u", part_ent, part_dec);
        LCD_putrs(buffer);
        LCD_Set_Cursor(1,11); 
        sprintf(exec, "%02u:%02u", tiempo/60, tiempo%60);
        LCD_putrs(exec);
    }
}
