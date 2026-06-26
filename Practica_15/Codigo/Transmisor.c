#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//=============================================================================
// CONFIGURACIÓN DE FUSES
//=============================================================================
#pragma config FOSC = HS        // Oscilador de alta velocidad (Cristal de 8 MHz)
#pragma config WDTE = OFF       // Watchdog Timer desactivado
#pragma config PWRTE = OFF      // Power-up Timer desactivado
#pragma config BOREN = ON       // Brown-out Reset activado
#pragma config LVP = OFF        // Programación de bajo voltaje desactivada
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF         

#define _XTAL_FREQ 8000000      

void UART_Init(void) {
    TRISCbits.TRISC6 = 0;       // Pin TX
    TRISCbits.TRISC7 = 1;       // Pin RX
    
    SPBRG = 51;                 // 9600 baudios
    TXSTA = 0x24;               
    RCSTA = 0x90;               
}

void UART_Write(char data) {
    while(!TXSTAbits.TRMT);     // Espera a que el buffer esté vacío
    TXREG = data;               // Envía el dato
}


void main(void) {
    ANSELH = 0x00;              // Puerto B es digital
    TRISBbits.TRISB0 = 1;       // RB0 como entrada
    
    UART_Init();                // Arranca puerto serial
    
    bool estado_anterior = false; // Almacena el estado previo del botón
    
    while(1) {
        bool estado_actual = (PORTBbits.RB0 == 1);
        
        if (estado_actual != estado_anterior) {
            __delay_ms(20); // Retardo antirrebote (debounce)
            
            // Volver a leer para confirmar que no fue ruido
            if ((PORTBbits.RB0 == 1) == estado_actual) { 
                if (estado_actual == true) {
                    UART_Write('A'); // Se presionó
                } else {
                    UART_Write('B'); // Se soltó
                }
                estado_anterior = estado_actual; // Actualizar el estado
            }
        }
    }
}
