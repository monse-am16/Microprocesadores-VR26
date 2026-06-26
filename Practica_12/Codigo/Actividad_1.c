#include <xc.h>         // Biblioteca principal del compilador XC8
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lcd.h"
#include "Keypad.h"

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

void main(void){
    OSCCON = 0x71;
   
    ANSEL = 0x00;
   
    InitKeypad();
    LCD lcd = {&PORTC, 2, 3, 4, 5, 6, 7};
   
    LCD_Init(lcd);
    LCD_Set_Cursor(0,0);
    LCD_putrs("Teclado Listo:"); // Mensaje estático desde memoria de programa
    LCD_Set_Cursor(1, 0);       // Nos posicionamos en la segunda fila (Fila 1)
   
    char teclaPresionada;
    int columnaActual = 0;
   
    while(1){
        // Esta función se queda esperando (bloqueada) hasta que el usuario pulse una tecla
        teclaPresionada = switch_press_scan();
        // Imprime el carácter correspondiente en la LCD
        
        LCD_putc(teclaPresionada);
        columnaActual++;
           
        // Si llegamos al final de la línea de la LCD (típicamente 16 caracteres)
        if (columnaActual >= 16) {
            LCD_Set_Cursor(1, 0); // Regresa al inicio de la segunda fila
            columnaActual = 0;
        }
    }
}
