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
    ANSEL = 0;
    ANSELH = 0;
    
    OPTION_REG = OPTION_REG & 0b01111111; // Habilita las Pull-ups globales
    WPUB = 0xFF;                          // (Opcional/Recomendado) Activa Pull-ups en todo RB
    
    TRISD = 0; 
    TRISC = 0;
    TRISB = 0xFF; 
    
    PORTD = 0; 
    PORTB = 0; 
    
    int num = 0; 
    
    int direccion = 1;             // 1 = Sube (Incrementa), 0 = Baja (Decrementa)
    
    int estado_anterior_rb0 = 1;   
    
    while(1){
      
        int mil = num/1000;  // Millares
        int cent = (num/100) % 10; // Centenas
        int dec = (num/10) % 10; // Decenas. 
        int uni = num%10; // Unidades.
        
        for (int i=0;i<30;i++){
            PORTC = 0b00001000;
            PORTD = patron[mil];  
            __delay_ms(1);
            
            PORTC = 0b00000100; 
            PORTD = patron[cent];
            __delay_ms(1);
            
            PORTC = 0b00000010; 
            PORTD = patron[dec]; 
            __delay_ms(1);
            
            PORTC = 0b00000001;
            PORTD = patron[uni]; 
            __delay_ms(1);
        }
        
        int estado_actual_rb0 = PORTBbits.RB0;
        
        // Entonces detectamos cuando AHORA es 0 y ANTES era 1.
        if (estado_actual_rb0 == 0 && estado_anterior_rb0 == 1) {
            direccion = !direccion; // Invierte la dirección 
        }
        
        estado_anterior_rb0 = estado_actual_rb0; // Guardamos el estado para el siguiente ciclo
        
        if (direccion == 1) {
            num++;
            if (num > 9999) {
                num = 0;
            }
        } else {
            num--;
            if (num < 0) {
                num = 9999;
            }
        }
        
    }
}
