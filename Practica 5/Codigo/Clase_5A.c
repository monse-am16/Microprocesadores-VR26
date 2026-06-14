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

unsigned char patron[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void main(void){
    TRISD = 0; 
    TRISC = 0;
    
    int num = 0; 
    
    while(1){
        int mil = num/1000;  // Millares
        int cent = (num/100) % 10; // Centenas
        int dec = (num/10) % 10; // Decenas. 
        int uni = num%10; // Unidades.
        
        
        for (int i=0;i<30;i++){
            PORTC = 0b00001000;
            PORTD = patron[mil];  
            __delay_ms(1);
            
            // Mostrar las centenas 
            PORTC = 0b00000100; 
            PORTD = patron[cent];
            __delay_ms(1);
            
            // Mostrar las decenas. 
            PORTC = 0b00000010; 
            PORTD = patron[dec]; 
            __delay_ms(1);
            
            // Mostrar unidades.
            PORTC = 0b00000001;
            PORTD = patron[uni]; 
            __delay_ms(1);
            
        }
        num = (num+1)%10000;
    }
    
}
