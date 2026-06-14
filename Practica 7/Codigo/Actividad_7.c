#include <xc.h>         // Biblioteca principal del compilador XC8
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lcd.h"

//=============================================================================
// CONFIGURACI N DE BITS DE CONFIGURACI N (FUSES)
//=============================================================================

// Selecci# n de oscilador (usar XT si est s usando un cristal de 4 MHz)
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
    ANSELH = 0x00;
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

volatile unsigned char disp_mod = 0;
volatile bool boton = false; 
unsigned char ant_mod = 5;

void main(void){
    ADC_Init();
    
    TRISA = 0x01;
    TRISB = 0xFF;
    OPTION_REG = OPTION_REG & 0b01111111;
    GIE = 1;
    INTE = 1;
    INTEDG = 0; 
    
    LCD lcd = {&PORTC,2,3,4,5,6,7};
    LCD_Init(lcd);
    
    char buffer[10];
    
    while(1){
        if (boton){
            __delay_ms(50);
            if (PORTBbits.RB0 == 0){
                disp_mod++;
                if (disp_mod>2){
                    disp_mod=0;
                }
            }
            boton = false;
        }
        
        if (disp_mod != ant_mod) {
            LCD_Clear();
            ant_mod = disp_mod;
        }
        
        unsigned int adc_result = ADC_Read();
        
        //Voltaje
        if (disp_mod == 0){
            LCD_Set_Cursor(0,0);
            LCD_putrs("Voltaje: ");
            LCD_Set_Cursor(0,9);
            unsigned int volt = (adc_result*50000UL)/1023;
            unsigned int part_ent = volt / 10000;
            unsigned int part_dec = volt % 10000;
            sprintf(buffer, "%u.%04u",part_ent,part_dec); //Nos permite convertir valores en cadenas de caracteres
            LCD_putrs(buffer);
        }        
        //Porcentaje
        else if (disp_mod == 1){
            LCD_Set_Cursor(0,0);
            LCD_putrs("Porcentaje: ");
            LCD_Set_Cursor(0,12);
            unsigned int por = (adc_result*10)/102;
            sprintf(buffer,"%u %%",por);
            LCD_putrs(buffer);
        }
        //ADC Puro
        else{
            LCD_Set_Cursor(0,0);
            LCD_putrs("ADC: ");
            LCD_Set_Cursor(0,5);
            sprintf(buffer,"%u",adc_result);
            LCD_putrs(buffer);
        }
        __delay_ms(200);
    }
}
void __interrupt() ISR(void){
    if(INTF){
        boton = true;
        INTF = 0;
    }
}
