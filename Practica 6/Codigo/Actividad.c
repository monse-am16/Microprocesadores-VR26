#include <xc.h>         // Biblioteca principal del compilador XC8
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

#define _XTAL_FREQ 8000000      // Frecuencia del oscilador

//=============================================================================
// CARACTERES ESPECIALES
//=============================================================================

// Caracter 0: Corazón
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

// Función para guardar en CGRAM
void LCD_Custom_Char(unsigned char loc, const unsigned char *charmap) {
    if (loc < 8) {
        LCD_Cmd(0x40 + (loc * 8)); 
        for (int i = 0; i < 8; i++) {
            LCD_putc(charmap[i]);  
        }
    }
}

//=============================================================================
// FUNCIÓN PRINCIPAL
//=============================================================================
void main(void){
    ANSEL = 0x00;   
    ANSELH = 0x00;

    TRISBbits.TRISB0 = 1;      // Pin RB0 como entrada
    OPTION_REGbits.nRBPU = 0;  // Habilitar resistencias pull-ups globales en PORTB

    LCD lcd = {&PORTC, 2, 3, 4, 5, 6, 7}; // PORT, RS, EN, D4, D5, D6, D7 
    LCD_Init(lcd); 
    
    // Guardar caracteres en memoria RAM del LCD
    LCD_Custom_Char(0, corazon); // Guarda corazón en posición 0
    LCD_Custom_Char(1, carita);  // Guarda carita en posición 1
    LCD_Set_Cursor(0,0);         // Regresar a la memoria normal (DDRAM)
    
    // Variables para el control del menú
    bool estado = false;             // Falso = Mensaje 1, Verdadero = Mensaje 2
    bool actualizar_pantalla = true; // Bandera para dibujar solo cuando sea necesario
    
    while(1){
        
        // Lectura de botón.
        if (PORTBbits.RB0 == 0) {       // Si el botón está presionado (GND)
            __delay_ms(30);             // Pausa para evitar debounce
            
            if (PORTBbits.RB0 == 0) {   // Confirmar que sigue presionado
                estado = !estado;       // Invertir el estado 
                actualizar_pantalla = true; // Activar la bandera para redibujar
                
                while(PORTBbits.RB0 == 0); // Bucle de espera
            }
        }
        
        // Actualización de pantalla.
        if (actualizar_pantalla) {
            LCD_Clear(); 
            
            if (!estado) {
                // Estado 0: Mensaje original con corazón
                LCD_Set_Cursor(0,0);
                LCD_putrs(" HELLO WORLD! ");
                LCD_Set_Cursor(1,0);
                LCD_putc(0); // Imprimir corazón 
                LCD_putrs(" MODO 1 ");
                LCD_putc(0); 
            } else {
                // Estado 1: Nuevo mensaje con carita feliz
                LCD_Set_Cursor(0,0);
                LCD_putrs(" HOLA MUNDO! ");
                LCD_Set_Cursor(1,0);
                LCD_putc(1); // Imprimir carita
                LCD_putrs(" MODO 2 ");
                LCD_putc(1); 
            }
            
            actualizar_pantalla = false; 
        }
    }
}
