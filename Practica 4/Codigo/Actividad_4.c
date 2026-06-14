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

unsigned char display[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void main(void){
    // Configuración de pines como digitales. 
    ANSEL = 0; 
    ANSELH = 0; 
    
    // Habilitar resistencias internas de pull-up. 
    OPTION_REG = OPTION_REG & 0b01111111; 
    
    // Configuración de entradas y salidas. 
    TRISB = 0xFF;
    TRISC = 0x0; 
    TRISD = 0x0; 
    
    PORTC = 0xFF;
    PORTD = 0xFF; 
    
    // Variables del programa.
    int contador = 0; 
    char paso = 1; 
    
    // Variables para guardar el estado anterior de los botones (para evitar conteo continuo)
    char estado_inc_anterior = 1; 
    char estado_dec_anterior = 1; 
    char estado_modo_anterior = 1; 
    
    char decenas = 0; 
    char unidades = 0; 
    
    while(1){
        // Modo de conteo (RB2)
        if(PORTBbits.RB2 == 0 && estado_modo_anterior == 1){
            __delay_ms(20);
            if(PORTBbits.RB2 == 0){ 
                if(paso == 1){
                    paso = 2;
                } else {
                    paso = 1;
                }
            }
        }
        estado_modo_anterior = PORTBbits.RB2;
        
        // Botón de incremento (Exclusivo para RB0)
        if(PORTBbits.RB0 == 0 && estado_inc_anterior == 1){
            __delay_ms(20);
            if(PORTBbits.RB0 == 0){ // Confirmamos el mismo pin RB0
                contador += paso; 
                if (contador > 99) contador = contador - 100; // Ajuste matemático de desbordamiento superior
            }
        }
        estado_inc_anterior = PORTBbits.RB0; // Actualizamos el estado de RB0
        
        // Botón de decremento (Exclusivo para RB1)
        if(PORTBbits.RB1 == 0 && estado_dec_anterior == 1){
            __delay_ms(20);
            if(PORTBbits.RB1 == 0){ // Confirmamos el mismo pin RB1
                contador -= paso; 
                if(contador < 0) contador = contador + 100; // Ajuste matemático de desbordamiento inferior
            }
        }
        estado_dec_anterior = PORTBbits.RB1; // Actualizamos el estado de RB1
        
        // Matemáticas para los displays
        decenas = contador / 10;
        unidades = contador % 10; 
        
        // Mostrar en los puertos
        PORTC = display[decenas]; 
        PORTD = display[unidades];
    } 
}

