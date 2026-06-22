#include <xc.h>         // Biblioteca principal del compilador XC8
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lcd.h"

//=============================================================================
// CONFIGURACI N DE BITS DE CONFIGURACI N (FUSES)
//=============================================================================

// Selecci n de oscilador (usar XT si est s usando un cristal de 4 MHz)
#pragma config FOSC = HS        // Oscillator Selection bits (XT oscillator)
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

#define _XTAL_FREQ 8000000      // Frecuencia del oscilador (para __delay_ms y __delay_us)

volatile unsigned int tiempo = 0; 
volatile unsigned int contador = 0; 
char exec[10]; 

void Timer0_init(){
    OPTION_REG = 0x7; 
    TMR0 = 178; 
    T0IE = 1; 
    GIE = 1; 
}

void __interrupt() ISR(void){
    if(T0IF){
        contador++; 
        if(contador > 100){
            tiempo++;
            contador = 0; 
        }
        TMR0 = 178; 
        T0IF = 0;
    }
}

void ADC_Init(){
    ANSEL = 0x03;  // Configuramos AN0 (Pin A0) y AN1 (Pin A1) como analógicos
    ANSELH = 0x00;
    ADCON1 = 0x80; // Justificación a la derecha
    ADCON0 = 0x01; // Encendemos el módulo ADC
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
    
    Timer0_init();
    
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
