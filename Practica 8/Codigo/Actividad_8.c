#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lcd.h"

//=============================================================================
// CONFIGURACIÓN DE BITS DE CONFIGURACIÓN (FUSES)
//=============================================================================
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
#define _XTAL_FREQ 8000000      // Frecuencia del oscilador

// Inicialización del ADC para dos canales
void ADC_Init(){
    ANSEL = 0x03;  // Configuramos AN0 (Pin A0) y AN1 (Pin A1) como analógicos
    ANSELH = 0x00;
    ADCON1 = 0x80; // Justificación a la derecha
    ADCON0 = 0x01; // Encendemos el módulo ADC
}

// Función para leer el ADC dependiendo del canal solicitado
unsigned int ADC_Read(unsigned char channel){
    // Limpiar los bits de selección de canal (CHS3:CHS0) con una máscara
    ADCON0 &= 0xC3; 
    // Recorrer los bits para seleccionar el canal (0 o 1)
    ADCON0 |= (channel << 2); 
    
    __delay_ms(2); // Tiempo de adquisición para que el capacitor se cargue
    
    GO_nDONE = 1;  // Inicia la conversión
    while(GO_nDONE); // Espera a que la conversión termine
    
    return((ADRESH << 8) + ADRESL); // Justificación a la derecha
}

void main(void){
    ADC_Init();
    
    TRISA = 0x03; // RA0 y RA1 configurados como entradas analógicas
    TRISB = 0xFF; // Todo el puerto B configurado como entradas
    OPTION_REG &= 0b01111111; 
    WPUB = 0xFF;              
    
    LCD lcd = {&PORTC, 2, 3, 4, 5, 6, 7};
    LCD_Init(lcd);
    
    char buffer[17];
    
    // Variables de estado
    unsigned char modo_display = 0; // 0 = Voltaje, 1 = Porcentaje, 2 = ADC Puro
    unsigned char modo_canal = 0;   // 0 = Canal 1 (AN0), 1 = Canal 2 (AN1)
    
    unsigned char ant_modo_display = 5;
    unsigned char ant_modo_canal = 5;
    
    while(1){
        
        // Boton 1: Voltaje a Porcentaje a ADC
        if (PORTBbits.RB0 == 0){
            __delay_ms(50); 
            if (PORTBbits.RB0 == 0){
                modo_display++;               
                if (modo_display > 2){        
                    modo_display = 0;
                }
                while(PORTBbits.RB0 == 0);    
            }
        }
        
        // Boton 2: Cambia Canal
        if (PORTBbits.RB1 == 0){
            __delay_ms(50); 
            if (PORTBbits.RB1 == 0){
                modo_canal = !modo_canal;     
                while(PORTBbits.RB1 == 0);    
            }
        }
        
        // Limpia de pantalla
        if (modo_display != ant_modo_display || modo_canal != ant_modo_canal) {
            LCD_Clear();
            ant_modo_display = modo_display;
            ant_modo_canal = modo_canal;
        }
        
        // Lectura de canal
        unsigned int adc_result = ADC_Read(modo_canal);
        
        
        // Actualización de pantalla         
        LCD_Set_Cursor(0, 0);
        if (modo_canal == 0){
            LCD_putrs("Canal 1 ");
        } else {
            LCD_putrs("Canal 2 ");
        }
        
        // Mostrar la lectura
        LCD_Set_Cursor(1, 0);
        
        if (modo_display == 0){
            unsigned int volt = (adc_result * 50000UL) / 1023;
            unsigned int part_ent = volt / 10000;
            unsigned int part_dec = volt % 10000;
            sprintf(buffer, "Voltaje: %u.%04u", part_ent, part_dec);
            LCD_putrs(buffer);
        } 
        else if (modo_display == 1){
            unsigned int por = (adc_result * 10) / 102;
            sprintf(buffer, "Porcentaje: %u%% ", por); // Se añade un espacio para limpiar caracteres residuales
            LCD_putrs(buffer);
        }
        else {
            sprintf(buffer, "ADC: %-4u       ", adc_result); // Espacios al final para limpiar
            LCD_putrs(buffer);
        }
        
        __delay_ms(100); // Pequeña pausa para no saturar el display
    }
}
