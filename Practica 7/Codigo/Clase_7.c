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

//Lectura anal gica. Esta configuracion siemrpe se usa para lecturas analogicas, solo cambia el ansel en caso de querer agregar mas canales analogicos

void ADC_Init(){
    ANSEL = 0x01; // El pin A0 lo usaremos para la lectura anal gica, los dem s los usaremos para lecturas digitales
    ADCON0 = 0x81;
    ADCON1 = 0x80;
}

//Funcion para leer el voltaje analogico

unsigned int ADC_Read(){
    __delay_us(5); //Peque o tiempo de espera para que decanse el capacitor del lector analogico del PIC
    GO_nDONE = 1; // Que inicie la conversion la conversion analogico digital, y se cambia a 0 cuando  la conversion haya finalizado
    while(GO_nDONE);
    return((ADRESH<<8)+ADRESL); //Para justificacion de la palabra de 8 bits a la derecha 
}

void main(void){
    ADC_Init();
    
    LCD lcd = {&PORTC,2,3,4,5,6,7};
    LCD_Init(lcd);
    
    char buffer[10];
    while(1){
        LCD_Clear();
        LCD_Set_Cursor(0,0);
        LCD_putrs("Voltaje: ");
        LCD_Set_Cursor(0,9);
        
        unsigned int adc_result = ADC_Read();
        
        unsigned int volt = (adc_result*50000)/1023;
        unsigned int part_ent = volt / 10000;
        unsigned int part_dec = volt & 10000;
        sprintf(buffer, "%u.%u",part_ent,part_dec); //Nos permite convertir valores en cadenas de caracteres
        LCD_putrs(buffer);
        __delay_ms(200);
    }
}
