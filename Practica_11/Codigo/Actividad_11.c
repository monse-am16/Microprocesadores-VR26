#include <xc.h>         // Biblioteca principal del compilador XC8
#include <stdio.h>
#include <stdlib.h>

//=============================================================================
// CONFIGURACIÓN DE BITS DE CONFIGURACIÓN (FUSES)
//=============================================================================
#pragma config FOSC = HS        // Oscillator Selection bits (HS para 8 MHz)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (disabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection (disabled)
#pragma config WRT = OFF        // Flash Program Memory Write Enable (disabled)
#pragma config CP = OFF         // Flash Program Memory Code Protection (disabled)

#define _XTAL_FREQ 8000000      

volatile unsigned char duty_cycle_2 = 0; 
unsigned char soft_pwm_counter = 0;

void __interrupt() ISR(void) {
    // Verificamos si la interrupción fue causada por el desbordamiento del Timer0
    if (INTCONbits.T0IE && INTCONbits.T0IF) {
        INTCONbits.T0IF = 0;       // Limpiamos la bandera de interrupción
        TMR0 = 128;                // Precargamos el Timer0 para aumentar la frecuencia 
        
        soft_pwm_counter++;        // Incrementamos el contador de 0 a 255
        
        // Lógica del comparador por software
        if (soft_pwm_counter < duty_cycle_2) {
            PORTDbits.RD0 = 1;     // Encender el LED
        } else {
            PORTDbits.RD0 = 0;     // Apagar el LED
        }
    }
}


void ADC_Init(){
    ANSEL = 0x03;       
    ANSELH = 0;         
    ADCON1 = 0x80;      
    ADCON0 = 0x01;      
}

unsigned int ADC_Read(unsigned char channel){
    __delay_us(5); 
    ADCON0 &= 0x83;             
    ADCON0 |= channel << 2;
    __delay_ms(2);             
    
    GO_nDONE = 1;               
    while(GO_nDONE);            
    return((ADRESH << 8) + ADRESL); 
}

void HardwarePWM_Init() {
    // Configuración de RC2 como salida digital
    TRISCbits.TRISC2 = 0; 
    
    PR2 = 255;              // Configurar el periodo del PWM
    CCP1CON = 0b00001100;   // Configurar CCP1 en modo PWM
    CCPR1L = 0;             // Iniciar con ciclo de trabajo en 0 
    
    T2CON = 0b00000100;     // Encender Timer2
}

void SoftwarePWM_Init() {
    // Configurar RD0 como salida digital para el LED 2
    TRISDbits.TRISD0 = 0;   
    PORTDbits.RD0 = 0;
    
    // Configurar Timer0 para las interrupciones
    OPTION_REGbits.T0CS = 0; // Usar reloj interno (Fosc/4)
    OPTION_REGbits.PSA = 1;  // Asignar pre-escalador al WDT (Timer0 queda 1:1)
    TMR0 = 128;              // Valor inicial
    
    // Habilitar interrupciones
    INTCONbits.T0IE = 1;     
    INTCONbits.PEIE = 1;     
    INTCONbits.GIE = 1;      
}

void main(void){
    
    ADC_Init();  
    HardwarePWM_Init();  
    SoftwarePWM_Init();
    
    unsigned int valor_adc_1 = 0;
    unsigned int valor_adc_2 = 0; 
    
    while(1){
        valor_adc_1 = ADC_Read(0); 
        valor_adc_2 = ADC_Read(1); 
        
        // Ajuste de escala de 10 bits a 8 bits. 
        unsigned char duty_cycle_1 = (unsigned char)(valor_adc_1 >> 2);
        
        // Asignamos el valor del ADC2 a la variable global. 
        duty_cycle_2 = (unsigned char)(valor_adc_2 >> 2); 
        
        CCPR1L = duty_cycle_1;
        
        __delay_ms(10);
    }
}
