#include <xc.h>         // Biblioteca principal del compilador XC8
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lcd.h"

//=============================================================================
// CONFIGURACION DE BITS DE CONFIGURACION (FUSES)
//=============================================================================

// Seleccion de oscilador (usar XT si estas usando un cristal de 4 MHz)
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
#define JOY_RESET_BTN RB0

// Caracter 0: Corazon
const unsigned char corazon[8] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000,
    0b00000
};

// Caracter 1: Carita Feliz
const unsigned char carita[8] = {
    0b00000,
    0b01010,
    0b01010,
    0b00000,
    0b10001,
    0b01110,
    0b00000,
    0b00000
};

void LCD_Custom_Char(unsigned char loc, const unsigned char *charmap) {
    if (loc < 8) {
        LCD_Cmd(0x40 + (loc * 8)); 
        for (int i = 0; i < 8; i++) {
            LCD_putc(charmap[i]);  
        }
    }
}

// Inicialización del ADC para dos canales
void ADC_Init(){
    ANSEL = 0x03;  // Configuramos AN0 (Pin A0) y AN1 (Pin A1) como analógicos
    ANSELH = 0x00;
    ADCON1 = 0x80; // Justificación a la derecha
    ADCON0 = 0x01; // Encendemos el módulo ADC
}

// Función para leer el ADC dependiendo del canal solicitado
unsigned int ADC_Read(unsigned char channel){
    ADCON0 &= 0xC3; 
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
    
    int pos[2] = {0,0}; // pos[0] -> x, pos[1] -> y. 
    
    int obs_x = 10; 
    int obs_y = 1; 
    LCD_Clear();
    bool game_over = false; 
    
    unsigned char boton_presionado = 0; // Bandera anti-rebote para el botón
    unsigned char personaje_actual = 0; // 0 = Corazón, 1 = Monito

    while(1){
        if(game_over){
            LCD_Clear(); 
            LCD_Set_Cursor(1,1); 
            LCD_putrs("  GAME OVER  "); 
            __delay_ms(2000); 
            
            pos[0] = 0; pos[1] = 0; 
            game_over = false; 
            LCD_Clear();
        }
        
        
        LCD_Clear();
        LCD_Custom_Char(0, corazon); // Guarda corazón en posición 0
        LCD_Custom_Char(1, carita);  // Guarda carita en posición 1
        
        // Lectura de canal x,y. 
        unsigned int adc_x = ADC_Read(0); 
        unsigned int adc_y = ADC_Read(1); 
        
        // Máximo 1020 (1023 bits). 
        // Mínimo 1 
        
        if(adc_x < 300) pos[0]++; 
        else if(adc_x > 600) pos[0]--;
        
        if(adc_y < 300) pos[1]++; 
        else if(adc_y > 600) pos[1]--;
        
        
        // Si la posición en x es mayor a 15, se le resta 16
        if(pos[0] > 15){
            pos[0] -= 16; 
            obs_x -= 5; 
            if(obs_x < 0) obs_x += 16; 
            if(obs_x == 0 || obs_x == 1) obs_x = 3; 
        }
        // Si la posición en x es menor a 0, se le agrega 16. 
        if(pos[0] < 0){
            pos[0] += 16; 
            obs_x += 5; 
            if(obs_x > 15) obs_x -= 16; 
            if(obs_x == 15 || obs_x == 14) obs_x = 13;
        }
        
        // Si la posicion en y es mayor a 1, se mantiene en 1. 
        if(pos[1] > 1) pos[1] = 1; 
        // Si la posicion en y es menor a 0, se mantiene en 0. 
        if(pos[1] < 0) pos[1] = 0; 
        
        
        
        // Actualizacion de posicion. 
        LCD_Set_Cursor(pos[1], pos[0]); 
        LCD_putc(personaje_actual); 
        
        // Dibujar obstaculo 
        LCD_Set_Cursor(obs_y, obs_x); 
        LCD_putc(255); 
        
        if(pos[0] == obs_x && pos[1] == obs_y){
            game_over = true; 
            continue; 
        }
        
        // Al usar pull-up, el botón entrega un '0' lógico cuando es presionado
        if (JOY_RESET_BTN == 0) {
            __delay_ms(20); // Filtro anti-rebote (Debounce)
            if (JOY_RESET_BTN == 0 && boton_presionado == 0) {
                personaje_actual = (personaje_actual == 0) ? 1 : 0; // Intercambia 0 y 1
                boton_presionado = 1; // Bloquea hasta que suelte el botón
            }
        } else {
            boton_presionado = 0; // Se liberó el botón
        }
        
        
        __delay_ms(300);
        
        
    }
    
}
