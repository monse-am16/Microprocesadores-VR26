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
    ANSEL = 0x03;  // Configuramos AN0 (Pin A0) y AN1 (Pin A1) como analógicos
    ANSELH = 0x00;
    ADCON1 = 0x80; // Justificación a la derecha
    ADCON0 = 0x01; // Encendemos el modulo ADC
}

unsigned int ADC_Read(unsigned char channel){
    __delay_us(5); 
    ADCON0 &= 0x83;             
    ADCON0 |= channel << 2;
    __delay_us(20);             
    
    GO_nDONE = 1;               
    while(GO_nDONE);            
    return((ADRESH << 8) + ADRESL); 
}

void PWM_Init() {
    // Configuración de RC2 como salida digital
    TRISCbits.TRISC2 = 0; 
    
    PR2 = 255;              // Configurar el periodo del PWM
    CCP1CON = 0b00001100;   // Configurar CCP1 en modo PWM
    CCPR1L = 0;             // Iniciar con ciclo de trabajo en 0 
    
    T2CON = 0b00000100;     // Encender Timer2
}

void main(void){
    ADC_Init();
    PWM_Init(); 
    
    unsigned int valor_adc; 
    
    while(1){
        valor_adc = ADC_Read(0); 
        unsigned char pwm = (unsigned char)(valor_adc >> 2); 
        CCPR1L = pwm; 
    }
}
