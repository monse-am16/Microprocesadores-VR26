#include <xc.h>

//=============================================================================
// CONFIGURACIÓN DE FUSES
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

#define _XTAL_FREQ 8000000       

// DEFINICIÓN DE PINES PARA BOTONES Y LEDS
#define BTN_GRABAR        PORTBbits.RB1
#define BTN_GUARDAR       PORTBbits.RB2
#define BTN_REPRODUCIR    PORTBbits.RB3
#define BTN_PARAR_BORRAR  PORTBbits.RB4

#define LED_GRABANDO      PORTCbits.RC1
#define LED_REPRODUCIENDO PORTCbits.RC2

#define MAX_PASOS 20 // Máximo de posiciones a guardar

volatile unsigned int ciclos_pulso = 3000; 

unsigned int secuencia[MAX_PASOS];
unsigned char total_pasos = 0;
unsigned char modo = 0; // 0 = Normal, 1 = Modo Grabar, 2 = Modo Reproducir

void init_Oscilador(void) {
    OSCCON = 0b01110001; // 8 MHz
}

void init_Entradas(void) {
    // Configurar RB0 al RB4 como entradas
    TRISB = 0b00011111;
    
    // Configurar RB0 (AN12) como analógico
    ANSELHbits.ANS12 = 1; 
    
    // Asegurar que los pines de los botones sean digitales
    ANSELHbits.ANS10 = 0; // RB1
    ANSELHbits.ANS8 = 0;  // RB2
    ANSELHbits.ANS9 = 0;  // RB3
    ANSELHbits.ANS11 = 0; // RB4
    
    // Configuración ADC
    ADCON0 = 0b10110001;
    ADCON1 = 0b10000000;
}

void init_Salidas_PWM(void) {
    // RC0 (Servo), RC1 (LED Grabar), RC2 (LED Reproducir) como salidas
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    
    // Apagar todo al iniciar
    PORTC = 0x00;
    
    T1CON = 0b00000000; 
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    T1CONbits.TMR1ON = 1;
}

unsigned int leer_ADC(void) {
    __delay_us(20);             
    ADCON0bits.GO_nDONE = 1;    
    while(ADCON0bits.GO_nDONE); 
    return ((ADRESH << 8) + ADRESL);
}

// INTERRUPCIÓN DEL TIMER1 (PWM)
void __interrupt() ISR(void) {
    static unsigned char estado_alto = 0;
    unsigned int timer_recarga;

    if (PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0; 
        T1CONbits.TMR1ON = 0; 

        if (estado_alto == 0) {
            PORTCbits.RC0 = 1;      
            timer_recarga = 65536 - ciclos_pulso;
            estado_alto = 1;
        } else {
            PORTCbits.RC0 = 0;      
            timer_recarga = 65536 - (40000 - ciclos_pulso); 
            estado_alto = 0;
        }

        TMR1H = (unsigned char)(timer_recarga >> 8);
        TMR1L = (unsigned char)(timer_recarga & 0xFF);
        T1CONbits.TMR1ON = 1; 
    }
}


void main(void) {
    unsigned int valor_potenciometro;
    
    init_Oscilador();
    init_Entradas(); 
    init_Salidas_PWM();

    while(1) {
        
        // Control de LEDS Indicadores
        
        if (modo == 0) {
            LED_GRABANDO = 0;
            LED_REPRODUCIENDO = 0;
        } else if (modo == 1) {
            LED_GRABANDO = 1;
            LED_REPRODUCIENDO = 0;
        } else if (modo == 2) {
            LED_GRABANDO = 0;
            LED_REPRODUCIENDO = 1;
        }

        
        // Lectura de botones generales     
        // Botón de detener Y borrar 
        if (BTN_PARAR_BORRAR == 1) {
            __delay_ms(50);
            if (BTN_PARAR_BORRAR == 1) {
                modo = 0;         // Fuerza el regreso al modo normal
                total_pasos = 0;  // Borra la memoria
                while(BTN_PARAR_BORRAR == 1); 
            }
        }

        // Botón entrar/salir del modo grabar. 
        if (BTN_GRABAR == 1) {
            __delay_ms(50); 
            if (BTN_GRABAR == 1) {
                if (modo == 1) {
                    modo = 0; 
                } else {
                    modo = 1; 
                    total_pasos = 0; 
                }
                while(BTN_GRABAR == 1); 
            }
        }

        // Boton reproducir secuencia. 
        if (BTN_REPRODUCIR == 1 && modo != 2) {
            __delay_ms(50); 
            if (BTN_REPRODUCIR == 1) {
                if (total_pasos > 0) {
                    modo = 2; 
                }
                while(BTN_REPRODUCIR == 1);
            }
        }
        
        // En modo 0 o modo 1 el usuario controla el servo
        if (modo == 0 || modo == 1) {
            valor_potenciometro = leer_ADC();
            
            // Simulación: 
            ciclos_pulso = 1953 + (unsigned int)(((unsigned long)valor_potenciometro * 1683) / 1023);           
            
            // Físico:
            // ciclos_pulso = 1953 + (unsigned int)(((unsigned long)valor_potenciometro * 3889) / 1023);    
            
            // Si está grabando y presiona Guardar
            if (modo == 1 && BTN_GUARDAR == 1) {
                __delay_ms(50); 
                if (BTN_GUARDAR == 1) {
                    if (total_pasos < MAX_PASOS) {
                        secuencia[total_pasos] = ciclos_pulso;
                        total_pasos++;
                    }
                    while(BTN_GUARDAR == 1); 
                }
            }
            __delay_ms(15);
        }
        
        // Modo 2: Reproducción automática
        else if (modo == 2) {
            for(int i = 0; i < total_pasos; i++) {
                ciclos_pulso = secuencia[i]; 
                
                // Bucle de pausa dividido para escuchar los botones de aborto
                for(int pausa = 0; pausa < 15; pausa++) {
                    __delay_ms(10);
                    
                    // Si se presiona el botón de Detener/Borrar durante la reproducción
                    if (BTN_PARAR_BORRAR == 1) {
                        modo = 0;
                        total_pasos = 0; // Borra la memoria inmediatamente
                        while(BTN_PARAR_BORRAR == 1);
                        break; // Sale del for de pausa
                    }
                    
                    // Si se presiona el botón de Reproducir de nuevo para pausar/salir
                    if (BTN_REPRODUCIR == 1) {
                        modo = 0;
                        while(BTN_REPRODUCIR == 1);
                        break; // Sale del for de pausa
                    }
                }
                
                if (modo == 0) break; // Sale del for principal de la secuencia si se abortó
            }
        }
    }
}
