#include <xc.h>

//=============================================================================
// CONFIGURACIÓN DE BITS DE CONFIGURACIÓN (FUSES) - ACTUALIZADOS PARA HARDWARE
//=============================================================================
#pragma config FOSC = INTRC_NOCLKOUT 
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config MCLRE = OFF      
#pragma config BOREN = ON       
#pragma config LVP = OFF        
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF         

// Frecuencia del oscilador
#define _XTAL_FREQ 8000000      

// Variable global para controlar el ancho del pulso
volatile unsigned int ciclos_pulso = 3000; // Inicia en 1.5 ms (Centro)


// Configuración del reloj interno
void init_Oscilador(void) {
    OSCCON = 0b01110001;
}


void init_ADC(void) {
    TRISBbits.TRISB0 = 1;
    ANSELHbits.ANS12 = 1; 
    ADCON0 = 0b10110001;
    ADCON1 = 0b10000000;
}

unsigned int leer_ADC(void) {
    __delay_us(20);             
    ADCON0bits.GO_nDONE = 1;    
    while(ADCON0bits.GO_nDONE); 
    
    return ((ADRESH << 8) + ADRESL);
}


void init_PWM_Software(void) {
    // Configurar pin RC0 como salida para el servo
    TRISCbits.TRISC0 = 0;
    PORTCbits.RC0 = 0;

    // Configurar Timer1 (Reloj interno, Prescaler 1:1)
    T1CON = 0b00000000; 

    // Limpiar bandera y habilitar interrupción del Timer1
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    
    // Habilitar interrupciones globales y periféricas
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    // Encender Timer1
    T1CONbits.TMR1ON = 1;
}

void __interrupt() ISR(void) {
    static unsigned char estado_alto = 0;
    unsigned int timer_recarga;

    if (PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0; // Limpiar bandera
        
        T1CONbits.TMR1ON = 0; // Apagar timer un instante para recargar seguro

        if (estado_alto == 0) {
            // Empieza la parte en alto del pulso
            PORTCbits.RC0 = 1;      
            timer_recarga = 65536 - ciclos_pulso;
            estado_alto = 1;
        } else {
            // Empieza la parte en bajo del pulso
            PORTCbits.RC0 = 0;      
            timer_recarga = 65536 - (40000 - ciclos_pulso); 
            estado_alto = 0;
        }

        // Cargar los valores al Timer1
        TMR1H = (unsigned char)(timer_recarga >> 8);
        TMR1L = (unsigned char)(timer_recarga & 0xFF);
        
        T1CONbits.TMR1ON = 1; // Volver a encender
    }
}

void main(void) {
    unsigned int valor_potenciometro;
    
    init_Oscilador(); 
    init_ADC();
    init_PWM_Software();

    while(1) {
        //  Leer el valor del potenciómetro (devuelve de 0 a 1023)
        valor_potenciometro = leer_ADC();
        
        // Mapear el valor del ADC al rango del Servo
        ciclos_pulso = 953 + (unsigned int)(((unsigned long)valor_potenciometro * 4000) / 1023);    
        
        __delay_ms(15);
    }
}
