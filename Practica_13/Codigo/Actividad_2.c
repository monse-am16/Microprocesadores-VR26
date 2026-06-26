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
#define _XTAL_FREQ 8000000      


void ADC_Init(){
    ANSEL = 0x01;  
    ANSELH = 0x00; 
    ADCON1 = 0x80; 
    ADCON0 = 0x01; 
}

unsigned int ADC_Read(unsigned char channel){
    __delay_us(20);             
    ADCON0 &= 0x83;             
    ADCON0 |= channel << 2;
    GO_nDONE = 1;               
    while(GO_nDONE);            
    return((ADRESH << 8) + ADRESL); 
}

void PWM_Init() {
    TRISCbits.TRISC2 = 0;   
    PR2 = 255;              
    CCP1CON = 0b00001100;   
    CCPR1L = 0;             
    T2CON = 0b00000100;     
}


void main(void){
    ADC_Init();
    PWM_Init(); 
    
    TRISDbits.TRISD0 = 0; // RD0 como salida (IN1)
    TRISDbits.TRISD1 = 0; // RD1 como salida (IN2)
    
    TRISBbits.TRISB0 = 1; // RB0 como entrada (Interruptor)
    
    unsigned int valor_adc; 
    
    while(1){
        // Control de Velocidad (PWM)
        valor_adc = ADC_Read(0); 
        CCPR1L = (unsigned char)(valor_adc >> 2);
        
        // Control de Dirección (Puente H)
        if (PORTBbits.RB0 == 1) {
            // Si el interruptor está encendido, gira a la derecha
            PORTDbits.RD0 = 1; // IN1 = Alto
            PORTDbits.RD1 = 0; // IN2 = Bajo
        } else {
            // Si el interruptor está apagado, gira a la izquierda
            PORTDbits.RD0 = 0; // IN1 = Bajo
            PORTDbits.RD1 = 1; // IN2 = Alto
        }
    }
}
