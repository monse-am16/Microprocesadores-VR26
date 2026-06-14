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
#define LED PORTCbits.RC0

unsigned char patron[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void blink_led(){
    for(int i=1;i<4;i++){
        LED =1;
        __delay_ms(500);
        LED = 0; 
        __delay_ms(500);
    }
}


void main(void){
    ANSEL = 0;
    ANSELH = 0; 
    OPTION_REG = OPTION_REG & 0b01111111; 
    
    TRISC = 0; 
    TRISD = 0; 
    TRISB = 0xFF; 
    
    // Eliminar voltajes residuales. 
    PORTC = 0;
    PORTD = 0; 
    
    GIE = 1; // Habilitar interrupciones globales.
    INTE = 1; // Habilitar interrupción externa. 
    INTEDG = 0; // Habilitar interrupción (Flanco de subida o de bajada). 0 -> Flanco de bajada. 
    
    unsigned char count = 0; 
    
    while(1){
        PORTD = patron[count];
        __delay_ms(500); 
        count = (count+1)%10; 
    }
}

void __interrupt() ISR(void){
    if(INTF){ // bit que se activa con la interrupción externa. 
        GIE = 0; // Deshabilita todas las interrupciones. Dentro de las interrupciones no existen interrupciones. 
        blink_led(); // Parpadeo de LED.
        GIE = 1;  // Habilitación de interrupciones. 
        INTF = 0; // Deshabilitación de la bandera, para que no se cicle en loop. 
    }
}
