#include <xc.h>         
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//=============================================================================
// CONFIGURACIÓN DE BITS (FUSES)
//=============================================================================
#pragma config FOSC = HS        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config BOREN = ON       
#pragma config LVP = OFF        
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF         

#define _XTAL_FREQ 8000000      

volatile unsigned int pulso_alto = 2000;  
volatile unsigned int pulso_bajo = 38000; 


void CCP1_Init() {
    TRISCbits.TRISC2 = 0; // Pin RC2 como salida
    PORTCbits.RC2 = 0;    
    
    // Configurar Timer1: Reloj interno (Fosc/4), Preescalador 1:1, Timer ON
    T1CON = 0x01; 
    
    // Estado inicial: Ordenamos al hardware que PONGA EL PIN EN ALTO en el primer match.
    // 0x08 = Compare mode, set output on match
    CCP1CON = 0x08; 
    
    // Primer evento a los 2000 ticks
    CCPR1 = TMR1 + 2000; 

    // Habilitar Interrupciones del CCP1
    PIE1bits.CCP1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

void set_servo_angle(unsigned int ticks) {
    PIE1bits.CCP1IE = 0; 
    pulso_alto = ticks;
    pulso_bajo = 40000 - ticks; 
    PIE1bits.CCP1IE = 1;
}

void __interrupt() ISR(void) {
    if (PIR1bits.CCP1IF) {
        PIR1bits.CCP1IF = 0; 
        
        // Verificamos qué orden acaba de ejecutar el hardware
        if (CCP1CON == 0x08) {
            // El hardware acaba de forzar el pin a 1 (ALTO).
            // Preparamos la orden para que el SIGUIENTE evento lo fuerce a 0 (BAJO).
            CCP1CON = 0x09; // 0x09 = Compare mode, clear output on match
            CCPR1 += pulso_alto; 
        } else {
            // El hardware acaba de forzar el pin a 0 (BAJO).
            // Preparamos la orden para que el SIGUIENTE evento lo fuerce a 1 (ALTO).
            CCP1CON = 0x08; 
            CCPR1 += pulso_bajo;
        }
    }
}

void main (void){
    CCP1_Init();
    
    while (1){
        // 0° exactos (1.0 ms = 2,000 ticks)
        set_servo_angle(1000);
        __delay_ms(1000); 
        
        // 180° exactos (2.0 ms = 4,000 ticks)
        set_servo_angle(4800);
        __delay_ms(1000); 
    }
}