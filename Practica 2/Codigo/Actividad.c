#include <xc.h>         // Biblioteca principal del compilador XC8

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

// Declaración de patrones escritos en binario: 
unsigned char patron_d[8] = {0b00111100, 0b01000011, 0b10000001, 0b10000001, 0b10000001, 0b10000001, 0b10000001, 0b11111111};
unsigned char patron_g[8] = {0b10011111, 0b10010001, 0b10010001, 0b10010001, 0b10011001, 0b10000001, 0b10000001l, 0b11111111};
unsigned char patron_m[8] = {0b11111111, 0b01000000, 0b00100000, 0b00010000, 0b00010000, 0b00100000, 0b01000000, 0b11111111};
unsigned char patron_n[8] = {0b11111111, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b11111111};


void main(void){
    TRISB = 0; // Puerto B como salida (filas). 
    TRISD = 0; // Puerto D como salida (columnas). 
    
    PORTB = 0; // Reset de puerto B.
    PORTD = 0; // Reset de puerto D. 
    
    while(1){
        // LETRA D:
        for(int t = 0; t < 25; t++){     // El ciclo for de t retiene la imagen por aproximadamente un segundo, ya que 25*8*5 = 1000 ms. 
            for(char i = 0; i<8; i++){
                PORTB = 1<<i; // Multiplexación. 
                PORTD = ~patron_d[i]; // Display del patrón en la matriz de 8x8.   
                __delay_ms(5);
            }   
        }  
        // El procedimiento se repite para cada letra. 
        // LETRA G: 
        for(int t = 0; t < 25; t++){
           for(char i = 0; i<8; i++){
               PORTB = 1<<i; // Multiplexación. 
               PORTD = ~patron_g[i]; 
               __delay_ms(5);
           }
        }
        
        // LETRA M:
        for(int t = 0; t < 25; t++){
           for (char i=0; i<8; i++){
                  PORTB = 1<<i; // Multiplexación.
                  PORTD=~patron_m[i];
                  __delay_ms(5);
           }
        }

        // LETRA N:
        for(int t = 0; t < 25; t++){
           for (char i=0;i<8;i++){
                  PORTB = 1<<i; // Multiplexación. 
                  PORTD=~patron_n[i];
                  __delay_ms(5);
           }
        }
    }
}

